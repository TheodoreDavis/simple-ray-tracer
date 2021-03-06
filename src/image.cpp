#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdint>

#include <inc/V3.h>
#include <inc/image.h>

int image_write_rgb(std::string filename, V3 **img, uint32_t img_height, uint32_t img_width, uint8_t img_maxval) {

	uint32_t i, j;

	/*
		check dimensions of img that they match the given function parameters
	*/


	/*
		open file-out stream
	*/
	filename += ".ppm";
	std::ofstream fout(filename.c_str(), std::ios::out | std::ios::trunc);
	fout.close();
	fout = std::ofstream(filename.c_str(), std::ios::out | std::ios::binary);
	if (!fout) {

		std::cout << "IMAGE ERR: Could not open file[" << filename << "]" << std::endl;
		return -1;
	}

	/*
		write correct header to file
	*/
	fout << "P6\n" << std::to_string(img_width) << "\n" << std::to_string(img_height) << "\n" << std::to_string(img_maxval) << std::endl;

	/*
		write image to file
	*/
	for (i = 0; i < img_height; i++) {
		for (j = 0; j < img_width; j++) {
			uint8_t r = (uint8_t)(std::clamp(img[i][j].r(), 0.0f, 1.0f) * img_maxval);
			uint8_t g = (uint8_t)(std::clamp(img[i][j].g(), 0.0f, 1.0f) * img_maxval);
			uint8_t b = (uint8_t)(std::clamp(img[i][j].b(), 0.0f, 1.0f) * img_maxval);
			//fout.write((char *)&r, sizeof(char));
			//fout.write((char *)&g, sizeof(char));
			//fout.write((char *)&b, sizeof(char));
			fout << r << g << b;
		}
		//fout << std::endl;
	}

	fout.close();
	if (!fout.good()) {

		std::cout << "IMAGE ERR: Could not write to file [" << filename << "]" << std::endl;
		return 1;
	}

	return 0;
}
