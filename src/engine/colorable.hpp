#ifndef ENGINE_COLORABLE_HPP
#define ENGINE_COLORABLE_HPP

namespace Engine {
// copied, edited with vim and by hand to compy with our naming convetion, from
// https://jonasjacek.github.io/colors/
enum class Color : int {
  transparent = -1,
  black,
  maroon,
  green,
  olive,
  navy,
  purple,
  teal,
  silver,
  grey,
  red,
  lime,
  yellow,
  blue,
  fuchsia,
  aqua,
  white,
  grey0,
  navyBlue,
  darkBlue,
  blue3,
  blue3_1,
  blue1,
  dark_green,
  deep_sky_blue4,
  deep_sky_blue4_1,
  deep_sky_blue4_2,
  dodger_blue3,
  dodger_blue2,
  green4,
  spring_green4,
  turquoise4,
  deep_sky_blue3,
  deep_sky_blue3_2,
  dodger_blue1,
  green3,
  spring_green3,
  dark_cyan,
  light_sea_green,
  deep_sky_blue2,
  deep_sky_blue1,
  green3_1,
  spring_green3_1,
  spring_green2,
  cyan3,
  dark_turquoise,
  turquoise2,
  green1,
  spring_green2_1,
  spring_green1,
  medium_spring_green,
  cyan2,
  cyan1,
  dark_red,
  deep_pink4,
  purple4,
  purple4_1,
  purple3,
  blue_violet,
  orange4,
  grey37,
  medium_purple4,
  slate_blue3,
  slate_blue3_1,
  royal_blue1,
  chartreuse4,
  dark_sea_green4,
  pale_turquoise4,
  steel_blue,
  steel_blue3,
  cornflower_blue,
  chartreuse3,
  dark_sea_green4_1,
  cadet_blue,
  cadet_blue_1,
  sky_blue3,
  steel_blue1,
  chartreuse3_1,
  pale_green3,
  sea_green3,
  aquamarine3,
  medium_turquoise,
  steel_blue1_1,
  chartreuse2,
  sea_green2,
  sea_green1,
  sea_green1_1,
  aquamarine1,
  dark_slate_gray2,
  dark_red_1,
  deep_pink4_1,
  dark_magenta,
  dark_magenta_1,
  dark_violet,
  purple_1,
  orange4_1,
  light_pink4,
  plum4,
  medium_purple3,
  medium_purple3_1,
  slate_blue1,
  yellow4,
  wheat4,
  grey53,
  light_slate_grey,
  medium_purple,
  light_slate_blue,
  yellow4_1,
  dark_olive_green3,
  dark_sea_green,
  light_sky_blue3,
  light_sky_blue3_1,
  sky_blue2,
  chartreuse2_1,
  dark_olive_green3_1,
  pale_green3_1,
  dark_sea_green3,
  dark_slate_gray3,
  sky_blue1,
  chartreuse1,
  light_green,
  light_green_1,
  pale_green1,
  aquamarine1_1,
  dark_slate_gray1,
  red3,
  deep_pink4_2,
  medium_violet_red,
  magenta3,
  dark_violet_1,
  purple_2,
  dark_orange3,
  indian_red,
  hot_pink3,
  medium_orchid3,
  medium_orchid,
  medium_purple2,
  dark_golden_rod,
  light_salmon3,
  rosy_brown,
  grey63,
  medium_purple2_1,
  medium_purple1_1,
  gold3,
  darkKhaki,
  navajo_white3,
  grey69,
  light_steel_blue3,
  light_steel_blue,
  yellow3,
  dark_olive_green3_2,
  dark_sea_green3_1,
  dark_sea_green2,
  light_cyan3,
  light_sky_blue1,
  green_yellow,
  dark_olive_green2,
  pale_green1_1,
  dark_sea_green2_1,
  dark_sea_green1,
  pale_turquoise1,
  red3_1,
  deep_pink3,
  deep_pink3_1,
  magenta3_1,
  magenta3_2,
  magenta2,
  dark_orange3_1,
  indian_ed_1,
  hot_pink3_1,
  hot_pink2,
  orchid,
  medium_orchid1,
  orange3,
  light_salmon3_1,
  light_pink3,
  pink3,
  plum3,
  violet,
  gold3_1,
  light_goldenrod3,
  tan,
  misty_rose3,
  thistle3,
  plum2,
  yellow3_1,
  khaki3,
  light_goldenrod2,
  light_yellow3,
  grey84,
  light_steel_blue1,
  yellow2,
  dark_olive_green1,
  dark_olive_green1_1,
  dark_sea_green1_1,
  honeydew2,
  light_cyan1,
  red1,
  deep_pink2,
  deep_pink1,
  deep_pink1_1,
  magenta2_1,
  magenta1,
  orange_red1,
  indian_red1,
  indian_red1_1,
  hot_pink,
  hot_pink_1,
  medium_orchid1_1,
  dark_orange,
  salmon1,
  light_coral,
  pale_violet_red1,
  orchid2,
  orchid1,
  orange1,
  sandy_brown,
  light_salmon1,
  light_pink1,
  pink1,
  plum1,
  gold1,
  light_golden_rod2_1,
  light_golden_rod2_2,
  navajo_white1,
  misty_rose1,
  thistle1,
  yellow1,
  light_golden_rod1,
  khaki1,
  wheat1,
  cornsilk1,
  grey100,
  grey3,
  grey7,
  grey11,
  grey15,
  grey19,
  grey23,
  grey27,
  grey30,
  grey35,
  grey39,
  grey42,
  grey46,
  grey50,
  grey54,
  grey58,
  grey62,
  grey66,
  grey70,
  grey74,
  grey78,
  grey82,
  grey85,
  grey89,
  grey93,
};

int color_to_int(Color c) noexcept;

/*
 Interface representing anything that can be printed on screen using both a
 foreground and a background color.
*/
class Colorable {
protected:
  Colorable() = default;

public:
  virtual Color foreground() const;
  virtual Color background() const;
  virtual ~Colorable() = default;
};

} // namespace Engine

#endif // ENGINE_COLORABLE_HPP