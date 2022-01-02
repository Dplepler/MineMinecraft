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
#include <vector>
#include <string>
#include <cmath>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "texture.h"
#include "shaderClass.h"
  
#define BLOCKS_SIZE 1

class Chunk
{
public:

	std::vector<Texture*> textureList;

	// C'Tor
	Chunk(Shader* shaderProgram);

	// Draw block
	void print_block(glm::vec3 position, GLfloat size, block_T type);
	void print_chunk();
	void draw();
	void VAO_push(VAO* VAO1);
	void texture_push(Texture* texture);
	void generateTexture(Shader* shaderProg);
	bool collision(glm::vec3 position);

	// D'Tor
	~Chunk();

private:

	std::vector<VAO*> VAOlist;

	

};


#endif