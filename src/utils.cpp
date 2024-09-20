#include "utils.hpp"

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

uint8_t
read_uint8_from_file (std::ifstream &fptr)
{
  char byte = fptr.get ();

  if (fptr.eof ())
    throw std::runtime_error (
        "Reading from file failed: end of file reached.");

  return static_cast<uint8_t> (byte);
}

uint16_t
read_le_uint16_from_file (std::ifstream &fptr)
{
  uint8_t lo = read_uint8_from_file (fptr);
  uint8_t hi = read_uint8_from_file (fptr);
  return ((static_cast<uint16_t> (hi) << 8) | lo);
}

uint32_t
read_le_uint32_from_file (std::ifstream &fptr)
{
  uint16_t lo = read_le_uint16_from_file (fptr);
  uint16_t hi = read_le_uint16_from_file (fptr);

  return ((static_cast<uint32_t> (hi) << 16) | lo);
}

uint32_t
read_le_int32_from_file (std::ifstream &fptr)
{
  uint16_t lo = read_le_uint16_from_file (fptr);
  uint16_t hi = read_le_uint16_from_file (fptr);

  return static_cast<int32_t> (((static_cast<uint32_t> (hi) << 16) | lo));
}

std::string
read_le_string_from_file (std::ifstream &fptr, size_t len)
{
  std::vector<char> str;
  str.reserve (len);

  for (size_t i = 0; i < len; i++)
    str.push_back (static_cast<char> (read_uint8_from_file (fptr)));

  std::reverse (str.begin (), str.end ());

  std::string output (str.begin (), str.end ());
  return output;
}

std::vector<uint8_t>
read_uint8_array_from_file (std::ifstream &fptr, size_t len)
{
  std::vector<uint8_t> output (len);
  for (size_t i = 0; i < len; i++)
    output.at (i) = read_uint8_from_file (fptr);

  return output;
}
