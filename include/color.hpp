#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include <cstdint>
#include <string>

class Color {
	uint8_t red;	// from 0..255
	uint8_t blue;	// from 0..255
	uint8_t green;	// from 0..255
	
	double luminance; // from 0.0..255.0
	double red_scaled;
	double blue_scaled;
public:
	Color (uint8_t r, uint8_t g, uint8_t b);

	std::string to_string (void);
};

#endif /* _COLOR_HPP_ */
