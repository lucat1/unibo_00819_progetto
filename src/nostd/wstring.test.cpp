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
}
