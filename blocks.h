#ifndef BLOCK_CLASS_H
#define BLOCK_CLASS_H

#define VERTICES_SIZE 264	 // 24 vertices * every instance has 11 bytes of information
#define INDICES_SIZE 36				
#define COORDS_AMOUNT 3

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "texture.h"
#include "shaderClass.h"

class Block
{
public:
	// C'Tor
	Block(size_t size, GLfloat x, GLfloat y, GLfloat z);

	// Draw block
	void draw();

	// D'Tor
	~Block();

	// Vertices: The points of the cube / block
	GLfloat* vertices;
	// Indices for vertices order
	GLuint* indices;

	VAO* VAO1;
	VBO* VBO1;
	EBO* EBO1;

	glm::mat4 blockModel;
	glm::vec3 blockPos;
	
	GLfloat position[COORDS_AMOUNT];

};







#endif