#ifndef _BITMAP_V5_HEADER_HPP_
#define _BITMAP_V5_HEADER_HPP_

#include <array>
#include <cstdint>
#include <string>

class BitmapV5Header
{
  uint32_t header_size;
  uint32_t img_width;
  uint32_t img_height;
  uint16_t num_color_planes;
  uint16_t bits_per_pixel;
  uint32_t compression_method;
  uint32_t img_size;
  uint32_t x_ppm; // x pixels per meter
  uint32_t y_ppm; // y pixels per meter
  uint32_t len_color_table;
  uint32_t num_important_colors;
  uint32_t red_bitmask;
  uint32_t green_bitmask;
  uint32_t blue_bitmask;
  uint32_t alpha_bitmask;
  std::string color_space_type; // len of 4
  std::array<uint8_t, 36> color_space_endpoints;
  uint32_t red_gamma;
  uint32_t green_gamma;
  uint32_t blue_gamma;
  /// @see https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapv5header#members
  uint32_t intent;
  uint32_t icc_profile_data;
  uint32_t icc_profile_size;
};

#endif /* _BITMAP_V5_HEADER_HPP_ */
