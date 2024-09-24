#include "bitmap/bmp_image.hpp"
#include "utils.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

static constexpr uint16_t BITMAP_FILE_SIGNATURE = 0x4D42;

BitmapImage::BitmapImage (const std::string &_filename) : filename (_filename)
{
  std::ifstream fptr (this->filename, std::ios::binary);
  if (!fptr)
    {
      std::cerr << std::format ("Error opening fptr, {}\n", this->filename);
    }

  try
    {
      fptr.seekg (0x0, fptr.beg);
    }
  catch (const std::runtime_error &)
    {
      throw std::runtime_error (
          std::format ("BitmapImage constructor failed: Could not seek to "
                       "beginning of fptr, '{}'.",
                       this->filename));
    }

  if (read_le_uint16_from_file (fptr) != BITMAP_FILE_SIGNATURE)
    throw std::runtime_error (std::format (
        "BitmapImage constructor failed: File, `{}`, is not a bitmap image.",
        this->filename));

  try
    {
      this->size = read_le_uint32_from_file (fptr);
      fptr.seekg (0x4, std::ios::cur); // skip 4 reserved bytes
      this->data_offset = read_le_uint32_from_file (fptr);
    }
  catch (const std::runtime_error &)
    {
      throw std::runtime_error (
          std::format ("BitmapImage constructor failed: Failed to read data "
                       "from fptr, '{}'.",
                       this->filename));
    }

  try
    {
      this->DIB_header.emplace (fptr);
    }
  catch (const std::runtime_error &e)
    {
      throw e;
    }

  fptr.seekg (this->data_offset, std::ios::beg);
  this->raw_data = std::make_unique<std::vector<uint8_t> > (
      read_uint8_array_from_file (fptr, this->DIB_header->img_size));

  std::vector<uint32_t> tmp;
  for (size_t i = 0; i < this->DIB_header->img_size; i += 3)
    {
      tmp.push_back ((this->raw_data->at (i))
                     | (this->raw_data->at (i + 1) << 8)
                     | (this->raw_data->at (i + 2) << 16));

      if (tmp.size () == static_cast<size_t> (this->DIB_header->img_width))
        {
          this->pixel_data.push_back (tmp);
          tmp.clear ();
        }
    }

  if (!tmp.empty ())
    this->pixel_data.push_back (tmp);

  for (auto row : this->pixel_data)
    {
      for (uint32_t pixel : row)
        {
          uint8_t r = (pixel & this->DIB_header->red_bitmask) >> 16;
          uint8_t g = (pixel & this->DIB_header->green_bitmask) >> 8;
          uint8_t b = (pixel & this->DIB_header->blue_bitmask);
          std::cout << std::format ("({:02X}, {:02X}, {:02X}) ", r, g, b);
        }
      std::cout << std::endl;
    }
}

std::ostream &
operator<< (std::ostream &os, const BitmapImage &img)
{
  os << std::format ("{{ {} }}", img.to_string ());

  return os;
}

std::string
BitmapImage::to_string (void) const
{
  return std::format ("filename: {}, size: {:08X}, data_offset: {:08X}, DIB "
                      "header: {{ {} }}",
                      filename, size, data_offset, DIB_header->to_string ());
}
