#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

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

/**
 *  Reads a single little-endian `int32_t` from the given file, throwing a
 *  runtime exception if eof is reached.
 */
uint32_t read_le_int32_from_file (std::ifstream &fptr);

/**
 *  Reads a single little-endian `std::string` from the given file, throwing a
 *  runtime exception if eof is reached.
 */
std::string read_le_string_from_file (std::ifstream &fptr, size_t len);

std::vector<uint8_t> read_uint8_array_from_file (std::ifstream &fptr,
                                                 size_t len);

#endif /* _UTILS_HPP_ */
