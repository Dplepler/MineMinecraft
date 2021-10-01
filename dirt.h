#ifndef DIRT_CLASS_H
#define DIRT_CLASS_H

#include "blocks.h"

class Dirt : public Block
{

public:
	// C'Tor
	Dirt(size_t size, GLfloat x, GLfloat y, GLfloat z, Shader* shaderProg);
	~Dirt();
	Texture* texture;

	
};

#endif