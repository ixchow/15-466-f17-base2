#pragma once

#include <string>
#include <vector>
#include <stdint.h>

/*
 * Load and save PNG files.
 */

enum OriginLocation {
	LowerLeftOrigin,
	UpperLeftOrigin,
};

bool load_png(std::string filename, unsigned int *width, unsigned int *height, std::vector< uint32_t > *data, OriginLocation origin);
void save_png(std::string filename, unsigned int width, unsigned int height, uint32_t const *data, OriginLocation origin);

bool load_png(std::istream &from, unsigned int *width, unsigned int *height, std::vector< uint32_t > *data, OriginLocation origin = UpperLeftOrigin);
void save_png(std::ostream &to, unsigned int width, unsigned int height, uint32_t const *data, OriginLocation origin = UpperLeftOrigin);
