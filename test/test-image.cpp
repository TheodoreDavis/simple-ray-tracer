#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

#include "../inc/v3.h"
#include "../inc/image.h"

int main(int argc, char *argv[]) {
	
	uint32_t i, j;
	
	uint32_t img_height = 200;
	uint32_t img_width = 200;
	
	v3 **img = (v3**)malloc(img_height * sizeof(v3*));
	for (i = 0; i < img_height; i++) {
		img[i] = (v3*)malloc(img_width * sizeof(v3));
	}
	
	for (i = 0; i < img_height; i++) {
		for (j = 0; j < img_width; j++) { img[i][j] = v3(0.5, 0.25, 0.75); }
	}
	
	mkdir("out", 0777);
	
	image_write_rgb("./out/test-img", img, img_height, img_width);
	
	free(img);
	
	return 0;
}