#include "color.hpp"

#include <format>
#include <iostream>

Color::Color (double r, double g, double b) : red (r), blue (b), green (g)
{
  //TODO: gamma correct rgb first!
  this->luminance
      = 0.299 * this->red + 0.587 * this->green + 0.114 * this->blue;

  this->red_color_difference = -1.902 * (this->red - this->luminance);
  this->blue_color_difference = 1.505 * (this->blue - this->luminance);

  std::cout << std::format ("{}\t", to_string ());
  std::cout << std::format ("{:5.02f}\t{:5.02f}\t{:5.02f}\n", this->luminance,
                            this->red_color_difference,
                            this->blue_color_difference);
}

std::string
Color::to_string (void)
{
  return std::format ("({:1.02f}, {:1.02f}, {:1.02f}) ", red, blue, green);
}
