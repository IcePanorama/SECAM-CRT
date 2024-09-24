#include "color.hpp"

#include <format>
#include <iostream>

Color::Color (uint8_t r, uint8_t g, uint8_t b) : red (r), blue (b), green (g)
{
  constexpr double LUMA_R_COEFFICIENT = 0.299;
  constexpr double LUMA_G_COEFFICIENT = 0.587;
  constexpr double LUMA_B_COEFFICIENT = 0.114;

  this->luminance = LUMA_R_COEFFICIENT * r + LUMA_G_COEFFICIENT * g
                    + LUMA_B_COEFFICIENT * b;

  constexpr double COLOR_R_COEFFICIENT = -1.902;
  constexpr double COLOR_B_COEFFICIENT = -1.505;

  this->red_scaled = COLOR_R_COEFFICIENT * (red - this->luminance);
  this->blue_scaled = COLOR_B_COEFFICIENT * (blue - this->luminance);
}

std::string
Color::to_string (void)
{
  return std::format ("({:02X}, {:02X}, {:02X}) ", red, blue, green);
}
