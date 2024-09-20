#include "bitmap/bmp_image.hpp"
#include "utils.hpp"

#include <cassert>
#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>

#define BITMAP_FILE_SIGNATURE (0x4D42)

BitmapImage::BitmapImage (const std::string &_filename) : filename (_filename)
{
  std::ifstream file (this->filename, std::ios::binary);
  if (!file)
    {
      std::cerr << std::format ("Error opening file, {}\n", this->filename);
    }

  try
    {
      file.seekg (0x0, file.beg);
    }
  catch (std::runtime_error &)
    {
      throw std::runtime_error (
          std::format ("BitmapImage constructor failed: Could not seek to "
                       "beginning of file, '{}'.",
                       this->filename));
    }

  if (read_le_uint16_from_file (file) != BITMAP_FILE_SIGNATURE)
    throw std::runtime_error (std::format (
        "BitmapImage constructor failed: File, `{}`, is not a bitmap image.",
        this->filename));

  try
    {
      this->size = read_le_uint32_from_file (file);
      file.seekg (0x4, std::ios::cur); // skip 4 reserved bytes
      this->data_offset = read_le_uint32_from_file (file);
    }
  catch (std::runtime_error &)
    {
      throw std::runtime_error (
          std::format ("BitmapImage constructor failed: Failed to read data "
                       "from file, '{}'.",
                       this->filename));
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
  return std::format ("filename: {}, size: {:04X}, data_offset: {:04X}",
                      filename, size, data_offset);
}
