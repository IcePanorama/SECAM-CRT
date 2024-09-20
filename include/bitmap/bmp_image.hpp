#ifndef _BITMAP_IMAGE_HPP_
#define _BITMAP_IMAGE_HPP_

#include "bitmap/bmp_header.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class BitmapImage
{
  std::string filename;
  uint32_t size;             // in bytes
  uint32_t data_offset;      // offset from beg. of file to bmp data
  BitmapV5Header DIB_header; // DIB = device-independent bitmap
  std::unique_ptr<std::vector<uint8_t> > raw_data;
public:
  BitmapImage (std::string filename);
};

#endif /* _BITMAP_IMAGE_HPP_ */
