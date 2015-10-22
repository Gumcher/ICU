#include "ArrayUtils.h"
#include "SDLPixel.h"

void freeUint8Array(uint32_t **arr, int rows) {
	for(int i = 0; i < rows; i++)
		free(arr[i]);

	free(arr);
}


uint32_t** imgToArray(SDL_Surface* img) {
	uint32_t **arr;
	arr = malloc(img->w * sizeof(uint32_t*));
	for(int i = 0; i < img->w; i++)
		arr[i] = malloc(img->h * sizeof(uint32_t));

	for(int i = 0; i < img->h; i++) {
		for(int j = 0; j < img->w; j++) {
			arr[j][i] =  getpixel(img, j, i);		
		}
	}

	return arr;
}


void print_array2D(uint32_t **arr, size_t xmin, size_t xmax, size_t ymin, size_t ymax, int log) {	
	if(!log) {
		for(size_t x = xmin; x < xmax; ++x)
		{
			for(size_t y = ymin; y < ymax; ++y)
			{
				printf("\t (%zu,%zu)Val = %02u\n ",x,y,arr[x][y]);
			}
			printf("\n\n");
		}
	}
	else {
		FILE *log = NULL;
		log = fopen("./log.txt", "w+");
		fprintf(log, "----------------------------------\n");
		fprintf(log, "Array %zux%zu to %zux%zu\n\n", xmin, ymin, xmax,ymax);
		fprintf(log, "----------------------------------\n");
		for(size_t x = xmin; x < xmax; ++x)
		{
			for(size_t y = ymin; y < ymax; ++y)
			{
				fprintf(log, "(%zu,%zu)Val = %02u\n ",x,y,arr[x][y]);
			}
			fprintf(log, "\n\n");
		}
	
		fclose(log);
	}
}
