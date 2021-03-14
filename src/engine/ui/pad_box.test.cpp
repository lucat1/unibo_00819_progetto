#include "../../util/test.hpp"
#include "pad_box.hpp"
#include <assert.h>
#include <wchar.h>
using namespace Engine::UI;

int main() {
  it("properly adds left padding", {
    PadBox *b = new PadBox(10, 10, {{PADDING_LEFT, 2}});
    bsize_t size = b->size();
    assert(size.s[0] == 2);
    assert(size.s[1] == 0);
  });

  it("properly adds right padding", {
    PadBox *b = new PadBox(10, 10, {{PADDING_RIGHT, 2}});
    bsize_t size = b->size();
    assert(size.s[0] == 2);
    assert(size.s[1] == 0);
  });

  it("properly adds top padding", {
    PadBox *b = new PadBox(10, 10, {{PADDING_TOP, 2}});
    bsize_t size = b->size();
    assert(size.s[0] == 0);
    assert(size.s[1] == 2);
  });

  it("properly adds bottom padding", {
    PadBox *b = new PadBox(10, 10, {{PADDING_BOTTOM, 2}});
    bsize_t size = b->size();
    assert(size.s[0] == 0);
    assert(size.s[1] == 2);
  });
}
