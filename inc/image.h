#ifndef _IMAGE_
#define _IMAGE_

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

#include <inc/V3.h>

int image_write_rgb(std::string filename, V3 **img, uint32_t img_height, uint32_t img_width, uint8_t img_maxval = 255);

#endif
