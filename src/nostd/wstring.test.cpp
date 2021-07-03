#include "string.hpp"
#include "test.hpp"
#include <cassert>
#include <cstring>
#include <sstream>

using Nostd::it;
using Nostd::String;

int main() {
  it("creates an empty String", [] {
    String s;
    assert(s.c_str()[0] == u'\0');
    assert(s.capacity() == 2);
    assert(s.size() == 1);
    assert(s.length() == 0);
  });

  it("initializes a String from a String", [] {
    String s1 = "test string";
    String s2 = s1;
    for (size_t i = 0; i < s2.size(); i++)
      assert(s2[i] == s1[i]);
    assert(s2.size() == s1.size());
    assert(s2.length() == s1.length());
  });

  it("initializes a String from a String substring", [] {
    String s = "test test";
    String ts(s, 2, 5);
    assert(ts[0] == u's');
    assert(ts[1] == u't');
    assert(ts[2] == u' ');
    assert(ts[3] == u't');
    assert(ts[4] == u'e');
    assert(ts[5] == u'\0');
    assert(ts.size() == 6);
    assert(ts.length() == 5);
  });

  it("initializes a String from a char*", [] {
    String s = "test";
    assert(s[0] == u't');
    assert(s[1] == u'e');
    assert(s[2] == u's');
    assert(s[3] == u't');
    assert(s[4] == u'\0');
    assert(s.size() == 5);
    assert(s.length() == 4);
  });

  it("initializes a String from a char* with len", [] {
    String s("test", 2);
    assert(s[0] == u't');
    assert(s[1] == u'e');
    assert(s[2] == u'\0');
    assert(s.size() == 3);
    assert(s.length() == 2);
  });

  it("length matches wcslen", [] {
    String s = "dadsadsadsadsaadasdad";
    assert(s.length() == strlen(s.c_str()));
  });

  it("resizes the string according to spec", [] {
    String s = "test";
    s.resize(2);
    assert(s.length() == 2);
    assert(s.size() == 3);
    assert(s[2] == u'\0');
  });

  it("clears the string according to spec", [] {
    String s = "test string";
    s.clear();
    assert(s.length() == 0);
    assert(s.size() == 1);
    assert(s[0] == u'\0');
  });

  it("correctly reports when the string is empty", [] {
    String s;
    assert(s.empty());
  });

  it("allows access & mods to the front char", [] {
    String s = "test string";
    assert(s.front() == u't');
    s.front() = u'T';
    assert(s.front() == u'T');
  });

  it("allows access & mods to the back char", [] {
    String s = "test string";
    assert(s.back() == u'g');
    s.back() = u'G';
    assert(s.back() == u'G');
  });

  it("correctly appends another String", [] {
    String s = "test string";
    String another_s(" test");
    s.append(another_s);
    assert(s.length() == another_s.length() + 11);
    assert(strcmp(s.c_str(), "test string test") == 0);
    assert(s[s.size() - 1] == u'\0');
  });

  it("correctly appends a char*", [] {
    String s = "test string";
    s.append(" test");
    assert(s.length() == 16);
    assert(strcmp(s.c_str(), "test string test") == 0);
    assert(s[s.size() - 1] == u'\0');
  });

  it("correctly pushes_back a char char", [] {
    String s = "test string";
    s.push_back(u's');
    assert(s.length() == 12);
    assert(strcmp(s.c_str(), "test strings") == 0);
    assert(s[s.size() - 1] == u'\0');
  });

  it("correctly inserts a String at position", [] {
    String s = "te string";
    String s1 = "test";
    s.insert(2, s1, 2, 2);
    s.insert(s.length(), s1);
    assert(s.length() == 15);
    assert(strcmp(s.c_str(), "test stringtest") == 0);
    assert(s[s.size() - 1] == u'\0');
  });

  it("correctly inserts a char* at position", [] {
    String s = "te string";
    s.insert(2, "st");
    assert(s.length() == 11);
    assert(strcmp(s.c_str(), "test string") == 0);
    assert(s[s.size() - 1] == u'\0');
  });

  it("correctly inserts a char char at position", [] {
    String s = "te string";
    s.insert(2, u's');
    s.insert(3, u't');
    assert(s.length() == 11);
    assert(strcmp(s.c_str(), "test string") == 0);
    assert(s[s.size() - 1] == u'\0');
  });

  it("reports the correct compairson results on Strings", [] {
    String str = "test";
    String str1 = "test";
    assert(str.compare(str1) == 0);
    String str2 = "tes";
    assert(str.compare(str2) != 0);
  });

  it("reports the correct compairson results on char*s", [] {
    String str = "test";
    assert(str.compare("test") == 0);
    assert(str.compare(1, 4, " test", 2) == 0);
  });

  it("finds the given String sbustring", [] {
    String str = "another test string";
    String to_be_found = "ther";
    size_t i = str.find(to_be_found);
    assert(i != String::npos);
    assert(i == 3);
  });

  it("finds the given char* sbustring", [] {
    String str = "another test string";
    size_t i = str.find("test");
    assert(i != String::npos);
    assert(i == 8);
  });

  it("finds the given char char", [] {
    String str = "another test string";
    size_t i = str.find(u't');
    assert(i != String::npos);
    assert(i == 3);
  });

  it("returns the proper substring", [] {
    String str = "test test";
    str = str.substr(2, 5);
    assert(str.compare("st te") == 0);
  });
  it("trims whitespace from the right side", [] {
    String str = "test   \t \v  ";
    str = str.rtrim();
    assert(str.compare("test") == 0);
  });

  it("trims whitespace from the left side", [] {
    String str = "  \t\v   test";
    str = str.ltrim();
    assert(str.compare("test") == 0);
  });

  it("properly assigns to a c string", [] {
    String s;
    const char *str = "test string";
    s = str;
    assert(strcmp(s.c_str(), str) == 0);
    assert(s.length() == strlen(str));
  });

  it("properly assigns to a char", [] {
    String s;
    s = u'*';
    assert(s[0] == u'*');
    assert(s.length() == 1);
    assert(s.size() == 2);
  });

  it("properly appens with the operator", [] {
    String s;
    String c_str("a");
    s += c_str;
    s += "b";
    s += u'c';
    assert(strcmp(s.c_str(), "abc") == 0);
  });

  it("prints a string to output stream", [] {
    String str = "test string";
    std::stringstream out;
    out << str;
    assert(strcmp(out.str().c_str(), str.c_str()) == 0);
  });

  it("reads a word from input stream", [] {
    std::stringstream in(std::string("first_word second_word"));
    String str;
    in >> str;
    assert(str.compare("first_word") == 0);
  });

  it("reads a line from input stream until \\n", [] {
    std::stringstream in(std::string("first_word second_word\n"));
    String str;
    getline(in, str);
    assert(str.compare("first_word second_word") == 0);
  });

  it("reads a line from input stream until EOF", [] {
    std::stringstream in(std::string("a long sentence"));
    String str;
    Nostd::getline(in, str);
    assert(str.compare("a long sentence") == 0);
  });
}
