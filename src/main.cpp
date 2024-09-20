#include "bitmap/bmp_image.hpp"

#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

int
main (void)
{
  const std::string FILENAME = "image.bmp";
  std::optional<BitmapImage> img;

  try
    {
      img.emplace (FILENAME);
    }
  catch (const std::runtime_error &e)
    {
      std::cerr << e.what () << std::endl;
      return -1;
    }

  std::cout << *img << std::endl;

  return 0;
}
