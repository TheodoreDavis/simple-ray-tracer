#include <inc/image.h>
#include <inc/v3.h>

int image_write_rgb(std::string filename, v3 **img, uint32_t img_height, uint32_t img_width, uint8_t img_maxval) {
	
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
	fout << "P3" << std::endl;
	fout << img_width << " " << img_height << std::endl;
	fout << img_maxval << std::endl;
	
	/*
		write image to file
	*/
	for (i = 0; i < img_height; i++) {
		for (j = 0; j < img_width; j++) {
			uint8_t r = (uint8_t)(img[i][j].r() * img_maxval);
			uint8_t g = (uint8_t)(img[i][j].g() * img_maxval);
			uint8_t b = (uint8_t)(img[i][j].b() * img_maxval);
			//fout.write((char *)&r, sizeof(char));
			//fout.write((char *)&g, sizeof(char));
			//fout.write((char *)&b, sizeof(char));
			fout << r << " ";
			fout << g << " ";
			fout << b << " ";
		}
		fout << std::endl;
	}
	
	fout.close();
	if (!fout.good()) {
		
		std::cout << "IMAGE ERR: Could not write to file [" << filename << "]" << std::endl; 
		return 1;
	}
	
	return 0;
}