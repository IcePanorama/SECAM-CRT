#include <cstdint>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

int
main (void)
{
  const std::string FILENAME = "image.bmp";
  std::ifstream file (FILENAME, std::ios::binary);
  if (!file)
    {
      std::cerr << std::format ("Error opening file, %s\n", FILENAME);
      return -1;
    }

  for (int i = 0; i < 10; i++)
    {
      uint8_t byte = static_cast<uint8_t> (file.get ());
      if (file.eof ())
        std::cout << "End of file.\n";
      std::cout << std::format ("{:02X}\n", byte);
    }

  return 0;
}
