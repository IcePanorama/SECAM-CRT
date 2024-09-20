#ifndef _BITMAP_IMAGE_HPP_
#define _BITMAP_IMAGE_HPP_

#include "bitmap/bmp_header.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class BitmapImage
{
  uint32_t size;             // in bytes
  uint32_t data_offset;      // offset from beg. of file to bmp data
  BitmapV5Header DIB_header; // DIB = device-independent bitmap
  std::unique_ptr<std::vector<uint8_t> > raw_data;

public:
  const std::string filename;

  BitmapImage (const std::string &_filename);

  std::string to_string (void) const;
  friend std::ostream &operator<< (std::ostream &os, const BitmapImage &img);
};

#endif /* _BITMAP_IMAGE_HPP_ */
