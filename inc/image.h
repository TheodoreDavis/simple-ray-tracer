#ifndef _image_
#define _image_

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>

#include "./v3.h"

int image_write_rgb(std::string filename, v3 **img, uint32_t img_height, uint32_t img_width, uint8_t img_maxval = 255);

#endif