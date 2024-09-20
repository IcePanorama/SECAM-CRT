#include "bitmap/bmp_header.hpp"
#include "utils.hpp"

#include <format>
#include <ios>
#include <iostream>
#include <stdexcept>

static constexpr size_t COLOR_SPACE_TYPE_LEN = 4;
static constexpr uint8_t GRAPHICS_INTENT = 0x2;
static constexpr uint8_t UNCOMPRESSED_COMPRESSION_METHOD = 0x0;

BitmapV5Header::BitmapV5Header (std::ifstream &fptr)
{
  try
    {
      this->header_size = read_le_uint32_from_file (fptr);

      this->img_width = read_le_int32_from_file (fptr);
      this->img_height = read_le_int32_from_file (fptr);

      this->num_color_planes = read_le_uint16_from_file (fptr);
      this->bits_per_pixel = read_le_uint16_from_file (fptr);

      this->compression_method = read_le_uint32_from_file (fptr);
      if (this->compression_method != UNCOMPRESSED_COMPRESSION_METHOD)
        throw std::runtime_error (
            std::format ("BitmapV5Header constructor failed: Unable to handle "
                         "{:08X} compression method.",
                         this->compression_method));

      this->img_size = read_le_uint32_from_file (fptr);
      if (this->img_size == 0)
        throw std::runtime_error ("BitmapV5Header constructor failed: Unable "
                                  "to handle implicit image size.");

      this->x_ppm = read_le_int32_from_file (fptr);
      this->y_ppm = read_le_int32_from_file (fptr);

      this->len_color_table = read_le_uint32_from_file (fptr);
      this->num_important_colors = read_le_uint32_from_file (fptr);

      this->red_bitmask = read_le_uint32_from_file (fptr);
      this->green_bitmask = read_le_uint32_from_file (fptr);
      this->blue_bitmask = read_le_uint32_from_file (fptr);
      this->alpha_bitmask = read_le_uint32_from_file (fptr);

      this->color_space_type
          = read_le_string_from_file (fptr, COLOR_SPACE_TYPE_LEN);

      this->color_space_endpoints
          = read_uint8_array_from_file (fptr, COLOR_SPACE_ENDPOINTS_LEN);

      this->red_gamma = read_le_uint32_from_file (fptr);
      this->blue_gamma = read_le_uint32_from_file (fptr);
      this->green_gamma = read_le_uint32_from_file (fptr);

      this->intent = read_le_uint32_from_file (fptr);
      if (this->intent != GRAPHICS_INTENT)
        throw std::runtime_error (
            std::format ("BitmapV5Header constructor failed: Unable to handle "
                         "{:08X} intent.",
                         this->intent));

      this->color_profile_data = read_le_uint32_from_file (fptr);
      this->color_profile_size = read_le_uint32_from_file (fptr);

      fptr.seekg (0x4, std::ios::cur); // skip 4 reserved bytes
    }
  catch (const std::runtime_error &e)
    {
      throw e;
    }
}

std::string
BitmapV5Header::to_string (void) const
{
  return std::format (
      "header size: {:08X}, img width: {:08X}, img height: {:08X}, # of color "
      "planes: {:04X}, bpp: {:04X}, compression method: {:08X}, img size: "
      "{:08X}, x ppm: {:08X}, y ppm: {:08X}, color table length: {:08X}, # of"
      " important colors: {:08X}, r bitmask: {:08X}, g bitmask: {:08X}, b "
      "bitmask: {:08X}, a bitmask: {:08X}, color space type: {}, r gamma: "
      "{:08X}, g gamma: {:08X}, b gamma: {:08X}, intent: {:08X}, color profile"
      " data: {:08X}, color profile size: {:08X}",
      header_size, img_width, img_height, num_color_planes, bits_per_pixel,
      compression_method, img_size, x_ppm, y_ppm, len_color_table,
      num_important_colors, red_bitmask, green_bitmask, blue_bitmask,
      alpha_bitmask, color_space_type, red_gamma, green_gamma, blue_gamma,
      intent, color_profile_data, color_profile_size);
}

std::ostream &
operator<< (std::ostream &os, const BitmapV5Header &h)
{
  os << std::format ("{{ {} }}", h.to_string ());
  return os;
}
