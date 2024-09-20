#ifndef _BITMAP_IMAGE_HPP_
#define _BITMAP_IMAGE_HPP_

#include "bitmap/bmp_header.hpp"

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

/** @see: https://en.wikipedia.org/wiki/BMP_file_format#File_structure */
class BitmapImage
{
  const std::string filename;
  uint32_t size;        // in bytes
  uint32_t data_offset; // offset from beg. of file to bmp data
  std::optional<BitmapV5Header> DIB_header; // DIB = device-independent bitmap
  std::unique_ptr<std::vector<uint8_t> > raw_data;

public:
  BitmapImage (const std::string &_filename);

  std::string to_string (void) const;
  friend std::ostream &operator<< (std::ostream &os, const BitmapImage &img);
};

#endif /* _BITMAP_IMAGE_HPP_ */
