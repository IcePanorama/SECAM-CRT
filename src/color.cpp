#include "color.hpp"

#include <format>

Color::Color (uint8_t r, uint8_t g, uint8_t b) : red (r), blue (b), green (g)
{
}

std::string
Color::to_string (void)
{
  return std::format ("({:02X}, {:02X}, {:02X}) ", red, blue, green);
}
