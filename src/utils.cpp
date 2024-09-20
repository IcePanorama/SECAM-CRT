#include "utils.hpp"
#include <array>
#include <cstdint>
#include <stdexcept>

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
  uint8_t hi = read_uint8_from_file (fptr);
  uint8_t lo = read_uint8_from_file (fptr);
  return ((static_cast<uint16_t> (hi) << 8) | lo);
}

uint32_t
read_le_uint32_from_file (std::ifstream &fptr)
{
  uint16_t hi = read_le_uint16_from_file (fptr);
  uint16_t lo = read_le_uint16_from_file (fptr);

  return ((static_cast<uint32_t> (hi) << 16) | lo);
}
