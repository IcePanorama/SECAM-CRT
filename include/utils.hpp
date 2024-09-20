#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <cstdint>
#include <fstream>

/**
 *  Reads a single `uint8_t` from the given file, throwing a runtime exception
 *  if eof is reached.
 */
uint8_t read_uint8_from_file (std::ifstream &fptr);

/**
 *  Reads a single little-endian `uint16_t` from the given file, throwing a
 *  runtime exception if eof is reached.
 */
uint16_t read_le_uint16_from_file (std::ifstream &fptr);

/**
 *  Reads a single little-endian `uint32_t` from the given file, throwing a
 *  runtime exception if eof is reached.
 */
uint32_t read_le_uint32_from_file (std::ifstream &fptr);

#endif /* _UTILS_HPP_ */
