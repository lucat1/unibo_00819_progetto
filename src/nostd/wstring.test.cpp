#include "test.hpp"
#include "wstring.hpp"
#include <cassert>
#include <sstream>
using namespace Nostd;

int main() {
  it("creates an empty WString", [] {
    WString ws;
    assert(ws.c_str()[0] == L'\0');
    assert(ws.capacity() == 2);
    assert(ws.size() == 1);
    assert(ws.length() == 0);
  });

  it("initializes a WString from a WString", [] {
    WString ws1 = L"test wstring";
    WString ws2 = ws1;
    for (size_t i = 0; i < ws2.size(); i++)
      assert(ws2[i] == ws1[i]);
    assert(ws2.size() == ws1.size());
    assert(ws2.length() == ws1.length());
  });

  it("initializes a WString from a WString substring", [] {
    WString ws = L"test test";
    WString tws(ws, 2, 5);
    assert(tws[0] == L's');
    assert(tws[1] == L't');
    assert(tws[2] == L' ');
    assert(tws[3] == L't');
    assert(tws[4] == L'e');
    assert(tws[5] == L'\0');
    assert(tws.size() == 6);
    assert(tws.length() == 5);
  });

  it("initializes a WString from a wchar_t*", [] {
    WString ws = L"test";
    assert(ws[0] == L't');
    assert(ws[1] == L'e');
    assert(ws[2] == L's');
    assert(ws[3] == L't');
    assert(ws[4] == L'\0');
    assert(ws.size() == 5);
    assert(ws.length() == 4);
  });

  it("initializes a WString from a wchar_t* with len", [] {
    WString ws(L"test", 2);
    assert(ws[0] == L't');
    assert(ws[1] == L'e');
    assert(ws[2] == L'\0');
    assert(ws.size() == 3);
    assert(ws.length() == 2);
  });

  it("length matches wcslen", [] {
    WString ws = L"dadsadsadsadsaadasdad";
    assert(ws.length() == wcslen(ws.c_str()));
  });

  it("resizes the string according to spec", [] {
    WString ws = L"test";
    ws.resize(2);
    assert(ws.length() == 2);
    assert(ws.size() == 3);
    assert(ws[2] == L'\0');
  });

  it("clears the string according to spec", [] {
    WString ws = L"test string";
    ws.clear();
    assert(ws.length() == 0);
    assert(ws.size() == 1);
    assert(ws[0] == L'\0');
  });

  it("correctly reports when the string is empty", [] {
    WString ws;
    assert(ws.empty());
  });

  it("allows access & mods to the front char", [] {
    WString ws = L"test string";
    assert(ws.front() == L't');
    ws.front() = L'T';
    assert(ws.front() == L'T');
  });

  it("allows access & mods to the back char", [] {
    WString ws = L"test string";
    assert(ws.back() == L'g');
    ws.back() = L'G';
    assert(ws.back() == L'G');
  });

  it("correctly appends another WString", [] {
    WString ws = L"test string";
    WString another_ws(L" test");
    ws.append(another_ws);
    assert(ws.length() == another_ws.length() + 11);
    assert(wcscmp(ws.c_str(), L"test string test") == 0);
    assert(ws[ws.size() - 1] == L'\0');
  });

  it("correctly appends a wchar_t*", [] {
    WString ws = L"test string";
    ws.append(L" test");
    assert(ws.length() == 16);
    assert(wcscmp(ws.c_str(), L"test string test") == 0);
    assert(ws[ws.size() - 1] == L'\0');
  });

  it("correctly pushes_back a wchar_t char", [] {
    WString ws = L"test string";
    ws.push_back(L's');
    assert(ws.length() == 12);
    assert(wcscmp(ws.c_str(), L"test strings") == 0);
    assert(ws[ws.size() - 1] == L'\0');
  });

  it("correctly inserts a WString at position", [] {
    WString ws = L"te string";
    WString ws1 = L"test";
    ws.insert(2, ws1, 2, 2);
    ws.insert(ws.length(), ws1);
    assert(ws.length() == 15);
    assert(wcscmp(ws.c_str(), L"test stringtest") == 0);
    assert(ws[ws.size() - 1] == L'\0');
  });

  it("correctly inserts a wchar_t* at position", [] {
    WString ws = L"te string";
    ws.insert(2, L"st");
    assert(ws.length() == 11);
    assert(wcscmp(ws.c_str(), L"test string") == 0);
    assert(ws[ws.size() - 1] == L'\0');
  });

  it("correctly inserts a wchar_t char at position", [] {
    WString ws = L"te string";
    ws.insert(2, L's');
    ws.insert(3, L't');
    assert(ws.length() == 11);
    assert(wcscmp(ws.c_str(), L"test string") == 0);
    assert(ws[ws.size() - 1] == L'\0');
  });

  it("reports the correct compairson results on WStrings", [] {
    WString str = L"test";
    WString str1 = L"test";
    assert(str.compare(str1) == 0);
    WString str2 = L"tes";
    assert(str.compare(str2) != 0);
  });

  it("reports the correct compairson results on wchar_t*s", [] {
    WString str = L"test";
    assert(str.compare(L"test") == 0);
    assert(str.compare(1, 4, L" test", 2) == 0);
  });

  it("finds the given WString sbustring", [] {
    WString str = L"another test string";
    WString to_be_found = L"ther";
    size_t i = str.find(to_be_found);
    assert(i != WString::npos);
    assert(i == 3);
  });

  it("finds the given wchar_t* sbustring", [] {
    WString str = L"another test string";
    size_t i = str.find(L"test");
    assert(i != WString::npos);
    assert(i == 8);
  });

  it("finds the given wchar_t char", [] {
    WString str = L"another test string";
    size_t i = str.find(L't');
    assert(i != WString::npos);
    assert(i == 3);
  });

  it("returns the proper substring", [] {
    WString str = L"test test";
    str = str.substr(2, 5);
    assert(str.compare(L"st te") == 0);
  });

  it("trims whitespace from the right side", [] {
    WString str = L"test   \t \v  ";
    str = str.rtrim();
    assert(str.compare(L"test") == 0);
  });

  it("trims whitespace from the left side", [] {
    WString str = L"  \t\v   test";
    str = str.ltrim();
    assert(str.compare(L"test") == 0);
  });

  it("properly assigns to a c string", [] {
    WString ws;
    const wchar_t *str = L"test string";
    ws = str;
    assert(wcscmp(ws.c_str(), str) == 0);
    assert(ws.length() == wcslen(str));
  });

  it("properly assigns to a char", [] {
    WString ws;
    ws = L'*';
    assert(ws[0] == L'*');
    assert(ws.length() == 1);
    assert(ws.size() == 2);
  });

  it("properly appens with the operator", [] {
    WString ws;
    WString c_str(L"a");
    ws += c_str;
    ws += L"b";
    ws += L'c';
    assert(wcscmp(ws.c_str(), L"abc") == 0);
  });

  it("prints a string to output stream", [] {
    WString str = L"test string";
    std::wstringstream out;
    out << str;
    assert(wcscmp(out.str().c_str(), str.c_str()) == 0);
  });

  it("reads a word from input stream", [] {
    std::wstringstream in(std::wstring(L"first_word second_word"));
    WString str;
    in >> str;
    assert(str.compare(L"first_word") == 0);
  });

  it("reads a line from input stream until \\n", [] {
    std::wstringstream in(std::wstring(L"first_word second_word\n"));
    WString str;
    getline(in, str);
    assert(str.compare(L"first_word second_word") == 0);
  });

  it("reads a line from input stream until EOF", [] {
    std::wstringstream in(std::wstring(L"a long sentence"));
    WString str;
    Nostd::getline(in, str);
    assert(str.compare(L"a long sentence") == 0);
  });
}
