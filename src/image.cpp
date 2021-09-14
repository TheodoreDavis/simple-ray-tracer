#include <inc/image.h>

int image_write_rgb(std::string filename, uint32_t(**img)[3], uint32_t img_width, uint32_t img_height, uint32_t img_maxval) {
	
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
			uint32_t r = img[i][j][0];
			uint32_t g = img[i][j][1];
			uint32_t b = img[i][j][2];
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