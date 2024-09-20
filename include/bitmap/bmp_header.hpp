#ifndef _BITMAP_V5_HEADER_HPP_
#define _BITMAP_V5_HEADER_HPP_

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

static constexpr size_t COLOR_SPACE_ENDPOINTS_LEN = 36; // in bytes

class BitmapV5Header
{
  uint32_t header_size;
  int32_t img_width;
  int32_t img_height;
  uint16_t num_color_planes;
  uint16_t bits_per_pixel;
  uint32_t compression_method;
  uint32_t img_size;
  int32_t x_ppm; // x pixels per meter
  int32_t y_ppm; // y pixels per meter
  uint32_t len_color_table;
  uint32_t num_important_colors;
  uint32_t red_bitmask;
  uint32_t green_bitmask;
  uint32_t blue_bitmask;
  uint32_t alpha_bitmask;
  std::string color_space_type;
  std::vector<uint8_t> color_space_endpoints;
  uint32_t red_gamma;
  uint32_t green_gamma;
  uint32_t blue_gamma;
  /**
   *  @see \
   *    https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapv5header#members
   */
  uint32_t intent;
  uint32_t color_profile_data;
  uint32_t color_profile_size;

public:
  BitmapV5Header (std::ifstream &fptr);
};

#endif /* _BITMAP_V5_HEADER_HPP_ */
