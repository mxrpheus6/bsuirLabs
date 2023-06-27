#pragma pack(push, 1)

typedef struct BITMAPFILEHEADER {
	unsigned char ID[2];
	unsigned int sizeOfFile;
	unsigned char unused[4];
	unsigned int pixelOffset;
} BITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER {
	unsigned int sizeOfHeader;
	unsigned int width;
	unsigned int height;
	unsigned short colorPlanes;
	unsigned short bitsPerPixel;
	unsigned int compressionMethod;
	unsigned int sizeData;
	unsigned int pWidth;
	unsigned int pHeight;
	unsigned int colorsCount;
	unsigned int colorsImp;
} BITMAPINFOHEADER;

typedef struct Pixel {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
} Pixel;

#pragma pack (pop)

typedef struct BMPFile {
	BITMAPFILEHEADER bhdr;
	BITMAPINFOHEADER dhdr;
	unsigned char* data;
	Pixel* array;
} BMPFile;


void readBMPRowByRow(FILE* filePointer, BMPFile* bmpFile);
BMPFile* loadBMPFile(char* fileName);
void freeBMPFile(BMPFile* bmpFile);
void printBMP(BMPFile* bmpFile);
void createCopy(BMPFile* bmpFile, FILE** newFile, char* fileName);
void createNegativeImage(BMPFile* bmpFile, FILE** newFile, char* fileName);
void createBWImage(BMPFile* bmpFile, FILE** newFile, char* fileName);
void GammaCorrection(BMPFile* bmpFile, FILE** newFile, float gamma, char* fileName);
void medianFilter(BMPFile* bmpFile, FILE** newFile, char* fileName, int filterSize);
