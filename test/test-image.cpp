#include <inc/image.h>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <string>

int main() {
	
	uint32_t i, j;
	
	uint32_t img_height = 200;
	uint32_t img_width = 200;
	
	uint32_t (**img)[3] = (uint32_t(**)[3])malloc(img_height * sizeof(uint32_t**));
	for (i = 0; i < img_height; i++) {
		img[i] = (uint32_t(*)[3])malloc(img_width * sizeof(uint32_t[3]));
	}
	
	for (i = 0; i < img_height; i++) {
		for (j = 0; j < img_width; j++) {
			img[i][j][0] = 0;
			img[i][j][1] = 0;
			img[i][j][2] = 255;
		}
	}
	
	image_write_rgb("./out/test-img", img, img_width, img_height);
	
	free(img);
	
	return 0;
}