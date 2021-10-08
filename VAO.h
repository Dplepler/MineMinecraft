#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <glad/glad.h>
#include "VBO.h"

#define GLM_SWIZZLE

enum block_T
{
	BLOCK_DIRT,

};


class VAO
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;

	block_T blockType;
	glm::vec3 position;

	// Constructor that generates a VAO ID
	VAO();

	// Links a VBO Attribute such as a position or color to the VAO
	void LinkAttrib(VBO &VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();
};

#endif
