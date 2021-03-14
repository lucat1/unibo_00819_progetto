#include "../../util/test.hpp"
#include "append.hpp"
#include "pad_box.hpp"
#include "text_box.hpp"
#include "vert_box.hpp"
#include <assert.h>
#include <iostream> // TODO: remove
#include <wchar.h>
using namespace std;
using namespace Engine::UI;

int main() {
  VertBox *box = new VertBox(50, 4);
  TextBox *tb =
      append<TextBox, const wchar_t *>(box, 1, 1, L"this is a test string");
  append<PadBox, map<enum PAD, uint16_t>>(
      box, 1, 1, {{PADDING_LEFT, 2}, {PADDING_RIGHT, 2}});
  it("places elements vertically with appropriate dimentions", {
    bsize_t box_size = box->size();
    bsize_t tb_size = tb->size();
    assert(box_size.s[0] == tb_size.s[0] + 4); // + 4 for the PadBox
    assert(box_size.s[1] == tb_size.s[1]);
  });
}
