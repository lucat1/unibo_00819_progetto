#include "../../util/test.hpp"
#include "text_box.hpp"
#include <assert.h>
#include <wchar.h>
using namespace Engine::UI;

int main() {
  it("splits lines into NULL-terminated strings", {
    TextBox *text_box =
        new TextBox(15, 10, {},
                    L"this is a super super super super super long test string "
                    L"which is also a test string");
    vector<wchar_t *> lines = text_box->split_content();
    for (vector<wchar_t *>::size_type i = 0; i < lines.size(); i++) {
      wchar_t *line = lines.at(i);
      assert(line[wcslen(line)] == '\0');
      delete line;
    }
    lines.clear();
  });

  it("splits a line into a width of 5 properly", {
    TextBox *text_box = new TextBox(5, 10, {}, L"this is a test string");
    vector<wchar_t *> lines = text_box->split_content();
    assert(wcscmp(lines.at(0), L"this ") == 0);
    assert(wcscmp(lines.at(1), L"is a ") == 0);
    assert(wcscmp(lines.at(2), L"test ") == 0);
    assert(wcscmp(lines.at(3), L"stri-") == 0);
    assert(wcscmp(lines.at(4), L"ng") == 0);

    // free memory
    for (vector<wchar_t *>::size_type i = 0; i < lines.size(); i++) {
      wchar_t *line = lines.at(i);
      delete line;
    }
    lines.clear();
  });
}
