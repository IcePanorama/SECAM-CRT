#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include <cstdint>

class Color {
	uint8_t red;	// from 0..255
	uint8_t blue;	// from 0..255
	uint8_t green;	// from 0..255
public:
	Color (uint8_t r, uint8_t g, uint8_t b);
};

#endif /* _COLOR_HPP_ */
