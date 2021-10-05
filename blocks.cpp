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

void Block::worldGen()
{



}

void Block::print_block(GLfloat x, GLfloat y, GLfloat z, GLfloat size)
{
	GLfloat* vertices = new GLfloat[VERTICES_SIZE]
	{ //     COORDINATES     /     COLORS					 / TexCoord    //

		// Left square
		x, y, z,						1.0f, 0.0f, 0.0f,		1.f, 0.f,		-1.f, 0.f, 0.f,		// Lower left front corner  (0) 
		x, y,  z - size,				1.0f, 0.0f, 0.0f,		0.f, 0.f,		-1.f, 0.f, 0.f,		// Lower left back corner   (1)
		x,  y + size, z - size,			0.0f, 1.0f, 0.0f,		0.f, 1.f,		-1.f, 0.f, 0.f,		// Upper left back corner   (2)
		x,  y + size,  z,				0.0f, 1.0f, 0.0f,		1.f, 1.f,		-1.f, 0.f, 0.f,		// Upper left front corner  (3)

		// Front square
		x,  y + size,  z,				0.0f, 1.0f, 0.0f,		0.f, 1.f,		0.f, 0.f, 1.f,		// Upper left front corner  (4)
		x + size, y + size,  z,			0.0f, 0.0f, 1.0f,		1.f, 1.f,		0.f, 0.f, 1.f,		// Upper right front corner (5)
		x + size, y, z,					1.0f, 1.0f, 1.0f,		1.f, 0.f,		0.f, 0.f, 1.f,		// Lower right front corner (6)
		x, y, z,						1.0f, 0.0f, 0.0f,		0.f, 0.f,		0.f, 0.f, 1.f,		// Lower left front corner  (7)

		// Right square
		x + size, y + size, z,			0.0f, 0.0f, 1.0f,	    0.f, 1.0f,		1.f, 0.f, 0.f,		// Upper right front corner (8)
		x + size, y, z,					1.0f, 1.0f, 1.0f,	 	0.f, 0.f,		1.f, 0.f, 0.f,		// Lower right front corner (9)
		x + size, y, z - size,			1.0f, 1.0f, 1.0f,		1.f, 0.f,		1.f, 0.f, 0.f,		// Lower right back corner  (10)
		x + size, y + size, z - size,	0.0f, 0.0f, 1.0f,		1.f, 1.f,		1.f, 0.f, 0.f,		// Upper right back corner  (11)

		// Bottom square
		x, y, z,						1.0f, 0.0f, 0.0f,		1.f, 0.f,		0.f, -1.f, .0f,		// Lower left front corner  (12) 
		x, y, z - size,					1.0f, 0.0f, 0.0f,		1.f, 1.f,		0.f, -1.f, .0f,		// Lower left back corner   (13)
		x + size, y,  z - size,			1.0f, 1.0f, 1.0f,		0.f, 1.f,		0.f, -1.f, .0f,		// Lower right back corner  (14)
		x + size, y, z,					1.0f, 1.0f, 1.0f,		0.f, 0.f,		0.f, -1.f, .0f,		// Lower right front corner (15)

		// Upper square
		x,  y + size,  z - size,		0.0f, 1.0f, 0.0f,		0.f, 1.f,		0.f, 1.f, .0f,		// Upper left back corner   (16)
		x,  y + size, z,				0.0f, 1.0f, 0.0f,		0.f, 0.f,		0.f, 1.f, .0f,		// Upper left front corner  (17)
		x + size,  y + size, z,			0.0f, 0.0f, 1.0f,		1.f, 0.f,		0.f, 1.f, .0f,		// Upper right front corner (18)
		x + size,  y + size,  z - size, 0.0f, 0.0f, 1.0f,		1.f, 1.f,		0.f, 1.f, .0f,		// Upper right back corner  (19)

		// Back square
		x, y, z - size,					1.0f, 0.0f, 0.0f,			1.f, 0.f,		0.f, 0.f, -1.f,		// Lower left back corner   (20)
		x, y + size, z - size,			0.0f, 1.0f, 0.0f,			1.f, 1.f,		0.f, 0.f, -1.f,		// Upper left back corner   (21)
		x + size, y + size, z - size,	0.0f, 0.0f, 1.0f,			0.f, 1.f,		0.f, 0.f, -1.f,		// Upper right back corner  (22)
		x + size, y,  z - size,			1.0f, 1.0f, 1.0f,			0.f, 0.f,		0.f, 0.f, -1.f		// Lower right back corner  (23)

	};


	GLuint* indices = new GLuint[INDICES_SIZE]
	{
		0, 1, 2,
		0, 3, 2,
		4, 5, 6,
		4, 7, 6,
		8, 9, 10,
		8, 11, 10,
		12, 13, 14,
		12, 15, 14,
		16, 17, 18,
		16, 19, 18,
		20, 21, 22,
		20, 23, 22

	};


	VAO* VAO1 = new VAO();
	VAO1->Bind();

	VBO* VBO1 = new VBO(vertices, VERTICES_SIZE * sizeof(float));
	EBO* EBO1 = new EBO(indices, INDICES_SIZE * sizeof(unsigned int));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1->LinkAttrib(*(VBO1), 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1->LinkAttrib(*(VBO1), 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1->LinkAttrib(*(VBO1), 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1->LinkAttrib(*(VBO1), 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	// Prevent from accidentally modifying these values
	VAO1->Unbind();
	VBO1->Unbind();
	EBO1->Unbind();

	this->textureList[this->blockType]->Bind();


	this->VAO_push(VAO1);
	this->draw();

}





Block::~Block() { }

