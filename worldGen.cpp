
#include "worldGen.h"

static const int width = 80;
static const int height = 80;

void generate_world(Chunk* blocks)
{

	
	int size = width * width * height;
	float cubeSize = .05f;

	float* fNoiseSeed2D = new float[size];
	float* fNoiseOutput2D = new float[size];
	uint16_t z = 0;

	// Generate terrain using Perlin Noise
	for (unsigned int i = 0; i < size; i++) fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;
	PerlinNoise2D(width, height, fNoiseSeed2D, 5, 2.0f, fNoiseOutput2D);

	for (uint16_t x = 0; x < width; x++)
	{
		for (uint16_t y = 0; y < height; y++)
		{
			z++;
			blocks->print_block(glm::vec3(cubeSize * float(x), fNoiseOutput2D[y * width + x], cubeSize * float(z)), cubeSize, BLOCK_DIRT);
		}
	
		z = 0;
	}
			
}

void PerlinNoise2D(int nWidth, int nHeight, float* fSeed, int nOctaves, float fBias, float* fOutput)
{

	float fNoise = 0.0f;
	float fScaleAcc = 0.0f;
	float fScale = 1.0f;

	int nPitch = 0;
	int nSampleX1 = 0;
	int nSampleY1 = 0;

	int nSampleX2 = 0;
	int nSampleY2 = 0;

	float fBlendX = 0;
	float fBlendY = 0;

	float fSampleT = 0;
	float fSampleB = 0;

	float value = 0;
	float mod = 0;

	for (uint16_t x = 0; x < nWidth; x++)
	{
		for (uint16_t y = 0; y < nHeight; y++)
		{
			fNoise = 0.0f;
			fScaleAcc = 0.0f;
			fScale = 0.05f;

			for (uint16_t o = 0; o < nOctaves; o++)
			{
				nPitch = nWidth >> o;
				nSampleX1 = (x / nPitch) * nPitch;
				nSampleY1 = (y / nPitch) * nPitch;

				nSampleX2 = (nSampleX1 + nPitch) % nWidth;
				nSampleY2 = (nSampleY1 + nPitch) % nWidth;

				fBlendX = (float)(x - nSampleX1) / (float)nPitch;
				fBlendY = (float)(y - nSampleY1) / (float)nPitch;

				fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY1 * nWidth + nSampleX2];
				fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY2 * nWidth + nSampleX2];

				fScaleAcc += fScale;
				fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
				fScale = fScale / fBias;
			}

			value = fNoise / fScaleAcc;

			mod = fmod(value, .05f);

			// Scale to seed range
			if (mod >= .05f)
				fOutput[y * nWidth + x] = value + mod;
			else
				fOutput[y * nWidth + x] = value - mod;
		}
	}
		


}
