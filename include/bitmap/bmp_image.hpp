#ifndef _BITMAP_IMAGE_HPP_
#define _BITMAP_IMAGE_HPP_

#include <cstdint>

class BitmapImage
{
  uint32_t size;        // in bytes
  uint32_t data_offset; // offset from beg. of file to bmp data
};

#endif /* _BITMAP_IMAGE_HPP_ */
