#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>

int image_write_rgb(std::string filename, uint32_t(**img)[3], uint32_t img_width, uint32_t img_height, uint32_t img_maxval = 255);