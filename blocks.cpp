#include "blocks.h"

Block::Block(size_t size, GLfloat x, GLfloat y, GLfloat z)
{
	unsigned int i = 0;


	position[0] = x;
	position[1] = y;
	position[2] = z;

	// Vertices coordinates
	this->vertices = new GLfloat[VERTICES_SIZE]
	{ //     COORDINATES     /     COLORS					 / TexCoord    //

		// Left square
		x, y, z,						1.0f, 0.0f, 0.0f,		1.f, 0.f,		-1.f, 0.f, 0.f,		// Lower left front corner  (0) 
		x, y,  z + size,				1.0f, 0.0f, 0.0f,		0.f, 0.f,		-1.f, 0.f, 0.f,		// Lower left back corner   (1)
		x,  y + size,   z + size,		0.0f, 1.0f, 0.0f,		0.f, 1.f,		-1.f, 0.f, 0.f,		// Upper left back corner   (2)
		x,  y + size,  z,				0.0f, 1.0f, 0.0f,		1.f, 1.f,		-1.f, 0.f, 0.f,		// Upper left front corner  (3)

		// Front square
		x,  y +size,  z,				0.0f, 1.0f, 0.0f,		0.f, 1.f,		0.f, 0.f, 1.f,		// Upper left front corner  (4)
		x + size,  y + size,  z,		0.0f, 0.0f, 1.0f,		1.f, 1.f,		0.f, 0.f, 1.f,		// Upper right front corner (5)
		x + size, y, z,					1.0f, 1.0f, 1.0f,		1.f, 0.f,		0.f, 0.f, 1.f,		// Lower right front corner (6)
		x, y, z,						1.0f, 0.0f, 0.0f,		0.f, 0.f,		0.f, 0.f, 1.f,		// Lower left front corner  (7)

		// Right square
		x + size,   y +size, z,			0.0f, 0.0f, 1.0f,	    0.f, 1.0f,		1.f, 0.f, 0.f,		// Upper right front corner (8)
		x + size, y, z,					1.0f, 1.0f, 1.0f,	 	0.f, 0.f,		1.f, 0.f, 0.f,		// Lower right front corner (9)
		x + size, y, z + size,			1.0f, 1.0f, 1.0f,		1.f, 0.f,		1.f, 0.f, 0.f,		// Lower right back corner  (10)
		x + size, y + size, z + size,	0.0f, 0.0f, 1.0f,		1.f, 1.f,		1.f, 0.f, 0.f,		// Upper right back corner  (11)

		// Bottom square
		x, y, z,						1.0f, 0.0f, 0.0f,		1.f, 0.f,		0.f, -1.f, .0f,		// Lower left front corner  (12) 
		x, y,  z + size,				1.0f, 0.0f, 0.0f,		1.f, 1.f,		0.f, -1.f, .0f,		// Lower left back corner   (13)
		x + size, y,  z + size,			1.0f, 1.0f, 1.0f,		0.f, 1.f,		0.f, -1.f, .0f,		// Lower right back corner  (14)
		x + size, y, z,					1.0f, 1.0f, 1.0f,		0.f, 0.f,		0.f, -1.f, .0f,		// Lower right front corner (15)

		// Upper square
		x,  y +size,  z + size,			0.0f, 1.0f, 0.0f,		0.f, 1.f,		0.f, 1.f, .0f,		// Upper left back corner   (16)
		x,  y +size, z,					0.0f, 1.0f, 0.0f,		0.f, 0.f,		0.f, 1.f, .0f,		// Upper left front corner  (17)
		x + size,  y + size, z,			0.0f, 0.0f, 1.0f,		1.f, 0.f,		0.f, 1.f, .0f,		// Upper right front corner (18)
		x + size,  y + size,  z + size, 0.0f, 0.0f, 1.0f,		1.f, 1.f,		0.f, 1.f, .0f,		// Upper right back corner  (19)

		// Back square
		x, y, z + size,					1.0f, 0.0f, 0.0f,			1.f, 0.f,		0.f, 0.f, -1.f,		// Lower left back corner   (20)
		x, y +size, z + size,			0.0f, 1.0f, 0.0f,			1.f, 1.f,		0.f, 0.f, -1.f,		// Upper left back corner   (21)
		x + size, y + size, z + size,	0.0f, 0.0f, 1.0f,			0.f, 1.f,		0.f, 0.f, -1.f,		// Upper right back corner  (22)
		x + size, y,  z + size,			1.0f, 1.0f, 1.0f,			0.f, 0.f,		0.f, 0.f, -1.f		// Lower right back corner  (23)

	};

	this->indices = new GLuint[INDICES_SIZE]
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7

	};
	

	this->VAO1 = new VAO();
	this->VAO1->Bind();

	this->VBO1 = new VBO(vertices, VERTICES_SIZE * sizeof(float));
	this->EBO1 = new EBO(indices, INDICES_SIZE * sizeof(unsigned int));
	

	this->blockPos = new glm::vec3(0.f, 0.f, 0.f);
	this->blockModel = new glm::mat4(1.0f);
	*this->blockModel = glm::translate(*this->blockModel, *this->blockPos);

	// Links VBO attributes such as coordinates and colors to VAO
	this->VAO1->LinkAttrib(*(this->VBO1), 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	this->VAO1->LinkAttrib(*(this->VBO1), 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	this->VAO1->LinkAttrib(*(this->VBO1), 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	this->VAO1->LinkAttrib(*(this->VBO1), 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	// Prevent from accidentally modifying these values
	this->VAO1->Unbind();
	this->VBO1->Unbind();
	this->EBO1->Unbind();

}

void Block::draw()
{
	this->VAO1->Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, INDICES_SIZE, GL_UNSIGNED_INT, 0);

}

Block::~Block()
{

	// Delete all the objects we've created
	VAO1->Delete();
	VBO1->Delete();
	EBO1->Delete();
	free(VAO1);
	free(VBO1);
	free(EBO1);
}

