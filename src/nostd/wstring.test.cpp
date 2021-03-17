#include "../util/test.hpp"
#include "wstring.hpp"
#include <assert.h>
using namespace Nostd;

int main() {
  it("creates an empty WString", {
    WString ws;
    assert(ws.c_str()[0] == '\0');
    assert(ws.capacity() == 2);
    assert(ws.size() == 1);
    assert(ws.length() == 0);
  });

  it("initializes a WString from a WString", {
    WString ws1(L"test wstring"); // TODO: proper constructor with assignment
    WString ws2 = ws1;
    for (size_t i = 0; i < ws2.size(); i++)
      assert(ws2[i] == ws1[i]);
    assert(ws2.size() == ws1.size());
    assert(ws2.length() == ws1.length());
  });
  it("initializes a WString from a WString substring", {
    WString ws(L"test test"); // TODO: proper constructor with assignment
    WString tws(ws, 2, 7);
    assert(tws[0] == L's');
    assert(tws[1] == L't');
    assert(tws[2] == L' ');
    assert(tws[3] == L't');
    assert(tws[4] == L'e');
    assert(tws[5] == '\0');
    assert(tws.size() == 6);
    assert(tws.length() == 5);
  });

  it("initializes a WString from a wchar_t*", {
    WString ws(L"test"); // TODO: proper constructor with assignment
    assert(ws[0] == L't');
    assert(ws[1] == L'e');
    assert(ws[2] == L's');
    assert(ws[3] == L't');
    assert(ws[4] == '\0');
    assert(ws.size() == 5);
    assert(ws.length() == 4);
  });

  it("initializes a WString from a wchar_t* with len", {
    WString ws(L"test", 2);
    assert(ws[0] == L't');
    assert(ws[1] == L'e');
    assert(ws[2] == '\0');
    assert(ws.size() == 3);
    assert(ws.length() == 2);
  });

  it("length matches wcslen", {
    WString ws(
        L"dadsadsadsadsaadasdad"); // TODO: proper constructor with assignment
    assert(ws.length() == wcslen(ws.c_str()));
  });

  it("properly assigns to a char", {
    WString ws;
    ws = L'*';
    assert(ws[0] == L'*');
    assert(ws.length() == 1);
    assert(ws.size() == 2);
  });

  it("properly assigns to a c string", {
    WString ws;
    const wchar_t *str = L"test string";
    ws = str;
    assert(wcscmp(ws.c_str(), str) == 0);
    assert(ws.length() == wcslen(str));
  });

  it("resizes the string according to spec", {
    WString ws(L"test"); // TODO: proper constructor with assignment
    ws.resize(2);
    assert(ws.length() == 2);
    assert(ws.size() == 3);
    assert(ws[2] == '\0');
  });

  it("clears the string according to spec", {
    WString ws(L"test string"); // TODO: proper constructor with assignment
    ws.clear();
    assert(ws.length() == 0);
    assert(ws.size() == 1);
    assert(ws[0] == '\0');
  });

  it("correctly reports when the string is empty", {
    WString ws;
    assert(ws.empty());
  });

  it("allows access & mods to the back char", {
    WString ws(L"test string"); // TODO: proper constructor with assignment
    assert(ws.back() == L't');
    ws.back() = L'T';
    assert(ws.back() == L'T');
  });

  it("allows access & mods to the front char", {
    WString ws(L"test string"); // TODO: proper constructor with assignment
    assert(ws.front() == L'g');
    ws.front() = L'G';
    assert(ws.front() == L'G');
  });
}
