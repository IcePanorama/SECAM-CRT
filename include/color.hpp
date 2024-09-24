#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include <string>

class Color {
	/* From 0.0 to 1.0. See: https://en.wikipedia.org/wiki/YDbDr */
	double red;
	double blue;
	double green;

	/* From -1.333 to 1.333. See: https://en.wikipedia.org/wiki/YDbDr */
	double luminance;
	double red_color_difference;
	double blue_color_difference;
public:
	Color (double r, double g, double b);

	std::string to_string (void);
};

#endif /* _COLOR_HPP_ */
