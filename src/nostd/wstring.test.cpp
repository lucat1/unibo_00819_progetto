#include "wstring.hpp"
#include "test.hpp"
#include <cassert>
#include <sstream>

using Nostd::it;
using Nostd::WString;

int main() {
  it("creates an empty WString", [] {
    WString ws;
    assert(ws.c_str()[0] == u'\0');
    assert(ws.capacity() == 2);
    assert(ws.size() == 1);
    assert(ws.length() == 0);
  });

  it("initializes a WString from a WString", [] {
    WString ws1 = "test wstring";
    WString ws2 = ws1;
    for (size_t i = 0; i < ws2.size(); i++)
      assert(ws2[i] == ws1[i]);
    assert(ws2.size() == ws1.size());
    assert(ws2.length() == ws1.length());
  });

  it("initializes a WString from a WString substring", [] {
    WString ws = "test test";
    WString tws(ws, 2, 5);
    assert(tws[0] == u's');
    assert(tws[1] == u't');
    assert(tws[2] == u' ');
    assert(tws[3] == u't');
    assert(tws[4] == u'e');
    assert(tws[5] == u'\0');
    assert(tws.size() == 6);
    assert(tws.length() == 5);
  });

  it("initializes a WString from a char*", [] {
    WString ws = "test";
    assert(ws[0] == u't');
    assert(ws[1] == u'e');
    assert(ws[2] == u's');
    assert(ws[3] == u't');
    assert(ws[4] == u'\0');
    assert(ws.size() == 5);
    assert(ws.length() == 4);
  });

  it("initializes a WString from a char* with len", [] {
    WString ws("test", 2);
    assert(ws[0] == u't');
    assert(ws[1] == u'e');
    assert(ws[2] == u'\0');
    assert(ws.size() == 3);
    assert(ws.length() == 2);
  });

  it("length matches wcslen", [] {
    WString ws = "dadsadsadsadsaadasdad";
    assert(ws.length() == wcslen(ws.c_str()));
  });

  it("resizes the string according to spec", [] {
    WString ws = "test";
    ws.resize(2);
    assert(ws.length() == 2);
    assert(ws.size() == 3);
    assert(ws[2] == u'\0');
  });

  it("clears the string according to spec", [] {
    WString ws = "test string";
    ws.clear();
    assert(ws.length() == 0);
    assert(ws.size() == 1);
    assert(ws[0] == u'\0');
  });

  it("correctly reports when the string is empty", [] {
    WString ws;
    assert(ws.empty());
  });

  it("allows access & mods to the front char", [] {
    WString ws = "test string";
    assert(ws.front() == u't');
    ws.front() = u'T';
    assert(ws.front() == u'T');
  });

  it("allows access & mods to the back char", [] {
    WString ws = "test string";
    assert(ws.back() == u'g');
    ws.back() = u'G';
    assert(ws.back() == u'G');
  });

  it("correctly appends another WString", [] {
    WString ws = "test string";
    WString another_ws(" test");
    ws.append(another_ws);
    assert(ws.length() == another_ws.length() + 11);
    assert(wcscmp(ws.c_str(), "test string test") == 0);
    assert(ws[ws.size() - 1] == u'\0');
  });

  it("correctly appends a char*", [] {
    WString ws = "test string";
    ws.append(" test");
    assert(ws.length() == 16);
    assert(wcscmp(ws.c_str(), "test string test") == 0);
    assert(ws[ws.size() - 1] == u'\0');
  });

  it("correctly pushes_back a char char", [] {
    WString ws = "test string";
    ws.push_back(u's');
    assert(ws.length() == 12);
    assert(wcscmp(ws.c_str(), "test strings") == 0);
    assert(ws[ws.size() - 1] == u'\0');
  });

  it("correctly inserts a WString at position", [] {
    WString ws = "te string";
    WString ws1 = "test";
    ws.insert(2, ws1, 2, 2);
    ws.insert(ws.length(), ws1);
    assert(ws.length() == 15);
    assert(wcscmp(ws.c_str(), "test stringtest") == 0);
    assert(ws[ws.size() - 1] == u'\0');
  });

  it("correctly inserts a char* at position", [] {
    WString ws = "te string";
    ws.insert(2, "st");
    assert(ws.length() == 11);
    assert(wcscmp(ws.c_str(), "test string") == 0);
    assert(ws[ws.size() - 1] == u'\0');
  });

  it("correctly inserts a char char at position", [] {
    WString ws = "te string";
    ws.insert(2, u's');
    ws.insert(3, u't');
    assert(ws.length() == 11);
    assert(wcscmp(ws.c_str(), "test string") == 0);
    assert(ws[ws.size() - 1] == u'\0');
  });

  it("reports the correct compairson results on WStrings", [] {
    WString str = "test";
    WString str1 = "test";
    assert(str.compare(str1) == 0);
    WString str2 = "tes";
    assert(str.compare(str2) != 0);
  });

  it("reports the correct compairson results on char*s", [] {
    WString str = "test";
    assert(str.compare("test") == 0);
    assert(str.compare(1, 4, " test", 2) == 0);
  });

  it("finds the given WString sbustring", [] {
    WString str = "another test string";
    WString to_be_found = "ther";
    size_t i = str.find(to_be_found);
    assert(i != WString::npos);
    assert(i == 3);
  });

  it("finds the given char* sbustring", [] {
    WString str = "another test string";
    size_t i = str.find("test");
    assert(i != WString::npos);
    assert(i == 8);
  });

  it("finds the given char char", [] {
    WString str = "another test string";
    size_t i = str.find(u't');
    assert(i != WString::npos);
    assert(i == 3);
  });

  it("returns the proper substring", [] {
    WString str = "test test";
    str = str.substr(2, 5);
    assert(str.compare("st te") == 0);
  });

  it("trims whitespace from the right side", [] {
    WString str = "test   \t \v  ";
    str = str.rtrim();
    assert(str.compare("test") == 0);
  });

  it("trims whitespace from the left side", [] {
    WString str = "  \t\v   test";
    str = str.ltrim();
    assert(str.compare("test") == 0);
  });

  it("properly assigns to a c string", [] {
    WString ws;
    const char *str = "test string";
    ws = str;
    assert(wcscmp(ws.c_str(), str) == 0);
    assert(ws.length() == wcslen(str));
  });

  it("properly assigns to a char", [] {
    WString ws;
    ws = u'*';
    assert(ws[0] == u'*');
    assert(ws.length() == 1);
    assert(ws.size() == 2);
  });

  it("properly appens with the operator", [] {
    WString ws;
    WString c_str("a");
    ws += c_str;
    ws += "b";
    ws += u'c';
    assert(wcscmp(ws.c_str(), "abc") == 0);
  });

  it("prints a string to output stream", [] {
    WString str = "test string";
    std::wstringstream out;
    out << str;
    assert(wcscmp(out.str().c_str(), str.c_str()) == 0);
  });

  it("reads a word from input stream", [] {
    std::wstringstream in(std::wstring("first_word second_word"));
    WString str;
    in >> str;
    assert(str.compare("first_word") == 0);
  });

  it("reads a line from input stream until \\n", [] {
    std::wstringstream in(std::wstring("first_word second_word\n"));
    WString str;
    getline(in, str);
    assert(str.compare("first_word second_word") == 0);
  });

  it("reads a line from input stream until EOF", [] {
    std::wstringstream in(std::wstring("a long sentence"));
    WString str;
    Nostd::getline(in, str);
    assert(str.compare("a long sentence") == 0);
  });
}
