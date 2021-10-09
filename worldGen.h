#ifndef WORLDGEN_H
#define WORLDGEN_H

#include "blocks.h"
#include <ctime>

void generate_world(Chunk* blocks);
void PerlinNoise2D(int nWidth, int nHeight, float* fSeed, int nOctaves, float fBias, float* fOutput);


#endif