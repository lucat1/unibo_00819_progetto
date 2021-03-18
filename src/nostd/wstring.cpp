#include "wstring.hpp"

Nostd::WString::WString() : Vector(1, '\0') {}

Nostd::WString::WString(WString &str) : Vector(str.size()) {
  for (size_t i = 0; i < str.size(); i++)
    v[i] = str[i];
}

Nostd::WString::WString(WString &str, size_t start, size_t len)
    : Vector(len == npos ? str.size() - start : len + 1) {
  // we also check that we don't go out of the *str array as we
  // could loop infinitely when len = npos (read entire string)
  if (len == npos)
    len = str.length();

  for (size_t i = start; i < start + len; i++)
    v[i - start] = str[i];
  v[len] = '\0';
}

Nostd::WString::WString(const wchar_t *str) : WString(str, wcslen(str)) {}

Nostd::WString::WString(const wchar_t *str, size_t len) : Vector(len + 1) {
  for (size_t i = 0; i < len; i++)
    v[i] = str[i];
  v[len] = '\0';
}

Nostd::WString::WString(WString &&str) {
  delete[] v;
  v = str.v;
  sz = str.sz;
  cap = str.cap;
  str.v = nullptr;
}

bool Nostd::WString::empty() const {
  return sz <= 1 || (sz == 1 && v[0] == '\0');
}
wchar_t *Nostd::WString::c_str() const { return v; }
wchar_t *Nostd::WString::data() const { return v; }
size_t Nostd::WString::length() const { return sz - 1; }
size_t Nostd::WString::max_size() const { return SIZE_MAX; }

// we override the Vector::resize to resize to a n+1 size and keep space for
// the '\0' char
void Nostd::WString::resize(size_t n) {
  Vector::resize(n + 1);
  v[n] = '\0';
}
// we override the Vector::celar to resize to size 1 and keep space for the
// '\0' char
void Nostd::WString::clear() {
  Vector::resize(1);
  v[0] = '\0';
}
wchar_t &Nostd::WString::back() {
  if (empty())
    throw std::out_of_range("called WString::back on an empty string");
  return v[0];
}
wchar_t &Nostd::WString::front() {
  if (empty())
    throw std::out_of_range("called WString::front on an empty string");
  return v[sz - 2];
}

Nostd::WString &Nostd::WString::append(Nostd::WString &str) {
  return insert(sz - 1, str);
}
Nostd::WString &Nostd::WString::append(const wchar_t *str) {
  return insert(sz - 1, str);
}
void Nostd::WString::push_back(const wchar_t c) {
  resize(sz); // increases the size by 1
  v[sz - 2] = c;
  v[sz - 1] = '\0';
}
Nostd::WString &Nostd::WString::insert(size_t start, Nostd::WString &str,
                                       size_t substart, size_t subend) {
  WString substr = str.substr(substart, subend);
  return insert(start, substr.c_str());
}
Nostd::WString &Nostd::WString::insert(size_t start, const wchar_t *str,
                                       size_t len) {
  // deliberately not using Vector::resize as we'd do the copying twice, which
  // is not smart at all. this method is therefore a modified copy of
  // Vector::resize
  if (len == npos)
    len = wcslen(str);
  sz += len;
  calc_cap();
  wchar_t *newv = new wchar_t[cap];

  for (size_t i = 0; i < start; i++)
    newv[i] = v[i];

  for (size_t i = 0; i < len; i++)
    newv[start + i] = str[i];

  for (size_t i = start; i < sz - len; i++)
    newv[i + len] = v[i];

  delete[] v;
  v = newv;
  return *this;
}
Nostd::WString &Nostd::WString::insert(size_t start, const wchar_t c) {
  wchar_t str[2] = {c, '\0'};
  return insert(start, str);
}

int Nostd::WString::compare(Nostd::WString &str) const {
  return compare(0, str.length(), str.c_str());
}
int Nostd::WString::compare(size_t start, size_t len,
                            Nostd::WString &str) const {
  return compare(start, len, str.c_str());
}
int Nostd::WString::compare(const wchar_t *str) const {
  return compare(0, wcslen(str), str);
}
int Nostd::WString::compare(size_t start, size_t len, const wchar_t *str,
                            size_t n) const {
  if (start > len)
    throw std::out_of_range("invalid start position in compare call");

  // n = npos means compare to the end of this->v
  if (n == npos)
    n = length() - start;
  return wcsncmp(v, str + start, n);
}
size_t Nostd::WString::find(Nostd::WString &seq, size_t start) const {
  return find(seq.c_str(), start, seq.length());
}
size_t Nostd::WString::find(const wchar_t *seq, size_t start) const {
  return find(seq, start, wcslen(seq));
}
size_t Nostd::WString::find(const wchar_t *seq, size_t start, size_t n) const {
  if (n == 0)
    return npos; // undefined behaviour, searching for an empty string

  for (size_t i = start; i < length(); i++)
    if (v[i] == seq[0] && wcsncmp(v + i, seq, n) == 0)
      return i;

  return npos;
}
size_t Nostd::WString::find(const wchar_t c, size_t start) const {
  wchar_t str[2] = {c, '\0'};
  return find(str, start);
}
Nostd::WString Nostd::WString::substr(size_t start, size_t len) {
  WString res(*this, start, len);
  return res;
}

Nostd::WString &Nostd::WString::operator=(Nostd::WString &str) {
  Vector::resize(str.size());

  for (size_t i = 0; i <= str.size(); i++)
    v[i] = str[i];
  return *this;
}
Nostd::WString &Nostd::WString::operator=(const wchar_t *str) {
  // we call it always as we could have some cases where shrinking
  // may be applied and therefore memory will be freed
  resize(wcslen(str));

  for (size_t i = 0; i <= wcslen(str); i++) // = to copy the '\0' char
    v[i] = str[i];
  return *this;
}
Nostd::WString &Nostd::WString::operator=(const wchar_t c) {
  resize(1);
  v[0] = c;
  v[1] = '\0';
  return *this;
}

Nostd::WString &Nostd::WString::operator+=(Nostd::WString &str) {
  append(str);
  return *this;
}
Nostd::WString &Nostd::WString::operator+=(const wchar_t *str) {
  append(str);
  return *this;
}
Nostd::WString &Nostd::WString::operator+=(const wchar_t c) {
  push_back(c);
  return *this;
}

std::basic_ostream<wchar_t> &Nostd::operator<<(std::basic_ostream<wchar_t> &os,
                                               const Nostd::WString &str) {
  return os << str.c_str();
}
