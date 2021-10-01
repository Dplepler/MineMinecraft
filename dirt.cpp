#include "dirt.h"

Dirt::Dirt(size_t size, GLfloat x, GLfloat y, GLfloat z, Shader* shaderProg) : Block(size, x, y, z)
{
	// Initialize texture
	texture = new Texture("testPic.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	texture->texUnit(*shaderProg, "tex0", 0);
}

Dirt:: ~Dirt()
{
	texture->Delete();
	free(texture);

}