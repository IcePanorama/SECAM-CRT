#include "bitmap/bmp_header.hpp"
#include "utils.hpp"

#include <format>
#include <stdexcept>

static constexpr size_t COLOR_SPACE_TYPE_LEN = 4;
static constexpr uint8_t GRAPHICS_INTENT = 0x2;

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
      if (this->compression_method != 0)
        throw std::runtime_error (
            std::format ("BitmapV5Header constructor failed: Unable to handle "
                         "{:04X} compression method.",
                         this->compression_method));

      this->img_size = read_le_uint32_from_file (fptr);

      this->x_ppm = read_le_int32_from_file (fptr);
      this->y_ppm = read_le_int32_from_file (fptr);

      this->len_color_table = read_le_uint32_from_file (fptr);
      this->num_important_colors = read_le_uint32_from_file (fptr);

      this->red_bitmask = read_le_uint32_from_file (fptr);
      this->blue_bitmask = read_le_uint32_from_file (fptr);
      this->green_bitmask = read_le_uint32_from_file (fptr);
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
                         "{:04X} intent.",
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
