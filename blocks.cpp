#include "blocks.h"

Block::Block(block_T type) 
{
	this->blockType = type;
}


void Block::draw()
{
	size_t size = VAOlist.size();


	VAOlist[size - 1]->Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, INDICES_SIZE, GL_UNSIGNED_INT, 0);

	
}

void Block::VAO_push(VAO* VAO1)
{
	this->VAOlist.push_back(VAO1);
}

void Block::texture_push(Texture* texture)
{
	this->textureList.push_back(texture);
}

void Block::generateTexture(Shader* shaderProg)
{
	unsigned int i = 0;
	std::string name = "tex";


	for (i = 0; i < BLOCKS_SIZE; i++)
	{
		// Initialize texture
		Texture* texture = new Texture(("textures/" + std::to_string(i) + ".jpg").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
		texture->texUnit(*shaderProg, ("tex" + std::to_string(i)).c_str(), 0);

		texture_push(texture);
	}
}


Block::~Block() { }

