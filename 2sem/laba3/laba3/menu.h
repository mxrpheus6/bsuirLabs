void menuInformation(void);
void mainMenu(char* path, FILE** newFile, float* gamma);
//void medianFilter(BMPFile* bmpFile, FILE** newFile, char* fileName, int filterSize) {
//	createCopy(bmpFile, newFile, fileName);
//	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
//	int bytesPerPixel = bmpFile->dhdr.bitsPerPixel / 8;
//	int width = bmpFile->dhdr.width;
//	int height = bmpFile->dhdr.height;
//
//	//Pixel* pixels = (Pixel*)malloc(height * width * sizeof(Pixel));
//	//fread(pixels, sizeof(Pixel), height * width, *newFile);
//
//	Pixel* newPixels = (Pixel*)malloc(height * width * sizeof(Pixel));
//	//memcpy(newPixels, bmpFile->array, height * width * sizeof(Pixel));
//	fread(newPixels, sizeof(Pixel), height * width, *newFile);
//
//	int halfFilterSize = filterSize / 2;
//
//	for (int i = halfFilterSize; i < height - halfFilterSize; i++) {
//		for (int j = halfFilterSize; j < width - halfFilterSize; j++) {
//			unsigned char* redValues = malloc(filterSize * filterSize * sizeof(unsigned char));
//			unsigned char* greenValues = malloc(filterSize * filterSize * sizeof(unsigned char));
//			unsigned char* blueValues = malloc(filterSize * filterSize * sizeof(unsigned char));
//			int index = 0;
//			for (int k = -halfFilterSize; k <= halfFilterSize; k++) {
//				for (int l = -halfFilterSize; l <= halfFilterSize; l++) {
//					int x = j + k;
//					int y = i + l;
//					if (y >= 0 && y < height && x >= 0 && x < width && index >= 0 && index < filterSize * filterSize) {
//						int pixelIndex = y * width + x;
//						redValues[index] = newPixels[pixelIndex].red;
//						greenValues[index] = newPixels[pixelIndex].green;
//						blueValues[index] = newPixels[pixelIndex].blue;
//					}
//					index++;
//				}
//			}
//			qsort(redValues, index, sizeof(unsigned char), compare);
//			qsort(greenValues, index, sizeof(unsigned char), compare);
//			qsort(blueValues, index, sizeof(unsigned char), compare);
//			int medianIndex = index / 2;
//			int newPixelIndex = i * width + j;
//			newPixels[newPixelIndex].red = redValues[medianIndex];
//			newPixels[newPixelIndex].green = greenValues[medianIndex];
//			newPixels[newPixelIndex].blue = blueValues[medianIndex];
//			free(redValues);
//			free(greenValues);
//			free(blueValues);
//		}
//	}
//
//	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
//	fwrite(newPixels, sizeof(Pixel), height * width, *newFile);
//
//	//free(pixels);
//	free(newPixels);
//}