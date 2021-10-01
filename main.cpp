#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "camera.h"
#include "dirt.h"

#define WIDTH 1920
#define HEIGHT 1080

GLfloat size = .5f;
GLfloat x = -.5f;
GLfloat y = .5f;
GLfloat z = -.5f;

GLfloat* vertices = new GLfloat[VERTICES_SIZE]
{ //     COORDINATES     /     COLORS					 / TexCoord    //

	// Left square
	x, y, z,						1.0f, 0.0f, 0.0f,		1.f, 0.f,		-1.f, 0.f, 0.f,		// Lower left front corner  (0) 
	x, y,  z + size,				1.0f, 0.0f, 0.0f,		0.f, 0.f,		-1.f, 0.f, 0.f,		// Lower left back corner   (1)
	x,  y + size, z + size,			0.0f, 1.0f, 0.0f,		0.f, 1.f,		-1.f, 0.f, 0.f,		// Upper left back corner   (2)
	x,  y + size,  z,				0.0f, 1.0f, 0.0f,		1.f, 1.f,		-1.f, 0.f, 0.f,		// Upper left front corner  (3)

	// Front square
	x,  y + size,  z,				0.0f, 1.0f, 0.0f,		0.f, 1.f,		0.f, 0.f, 1.f,		// Upper left front corner  (4)
	x + size, y + size,  z,			0.0f, 0.0f, 1.0f,		1.f, 1.f,		0.f, 0.f, 1.f,		// Upper right front corner (5)
	x + size, y, z,					1.0f, 1.0f, 1.0f,		1.f, 0.f,		0.f, 0.f, 1.f,		// Lower right front corner (6)
	x, y, z,						1.0f, 0.0f, 0.0f,		0.f, 0.f,		0.f, 0.f, 1.f,		// Lower left front corner  (7)

	// Right square
	x + size,   y + size, z,			0.0f, 0.0f, 1.0f,	    0.f, 1.0f,		1.f, 0.f, 0.f,		// Upper right front corner (8)
	x + size, y, z,					1.0f, 1.0f, 1.0f,	 	0.f, 0.f,		1.f, 0.f, 0.f,		// Lower right front corner (9)
	x + size, y, z + size,			1.0f, 1.0f, 1.0f,		1.f, 0.f,		1.f, 0.f, 0.f,		// Lower right back corner  (10)
	x + size, y + size, z + size,	0.0f, 0.0f, 1.0f,		1.f, 1.f,		1.f, 0.f, 0.f,		// Upper right back corner  (11)

	// Bottom square
	x, y, z,						1.0f, 0.0f, 0.0f,		1.f, 0.f,		0.f, -1.f, .0f,		// Lower left front corner  (12) 
	x, y,  z + size,				1.0f, 0.0f, 0.0f,		1.f, 1.f,		0.f, -1.f, .0f,		// Lower left back corner   (13)
	x + size, y,  z + size,			1.0f, 1.0f, 1.0f,		0.f, 1.f,		0.f, -1.f, .0f,		// Lower right back corner  (14)
	x + size, y, z,					1.0f, 1.0f, 1.0f,		0.f, 0.f,		0.f, -1.f, .0f,		// Lower right front corner (15)

	// Upper square
	x,  y + size,  z + size,			0.0f, 1.0f, 0.0f,		0.f, 1.f,		0.f, 1.f, .0f,		// Upper left back corner   (16)
	x,  y + size, z,					0.0f, 1.0f, 0.0f,		0.f, 0.f,		0.f, 1.f, .0f,		// Upper left front corner  (17)
	x + size,  y + size, z,			0.0f, 0.0f, 1.0f,		1.f, 0.f,		0.f, 1.f, .0f,		// Upper right front corner (18)
	x + size,  y + size,  z + size, 0.0f, 0.0f, 1.0f,		1.f, 1.f,		0.f, 1.f, .0f,		// Upper right back corner  (19)

	// Back square
	x, y, z + size,					1.0f, 0.0f, 0.0f,			1.f, 0.f,		0.f, 0.f, -1.f,		// Lower left back corner   (20)
	x, y + size, z + size,			0.0f, 1.0f, 0.0f,			1.f, 1.f,		0.f, 0.f, -1.f,		// Upper left back corner   (21)
	x + size, y + size, z + size,	0.0f, 0.0f, 1.0f,			0.f, 1.f,		0.f, 0.f, -1.f,		// Upper right back corner  (22)
	x + size, y,  z + size,			1.0f, 1.0f, 1.0f,			0.f, 0.f,		0.f, 0.f, -1.f		// Lower right back corner  (23)

};


GLuint* indices = new GLuint[INDICES_SIZE]
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


GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, 0.3f,  0.1f,
	-0.1f, 0.3f, -0.1f,
	 0.1f, 0.3f, -0.1f,
	 0.1f, 0.3f,  0.1f,
	-0.1f,  0.5f,  0.1f,
	-0.1f,  0.5f, -0.1f,
	 0.1f,  0.5f, -0.1f,
	 0.1f,  0.5f,  0.1f
};

GLuint lightIndices[] =
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



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 1920 by 1080 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "MineMinecraft", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 1920, y = 1080
	glViewport(0, 0, WIDTH, HEIGHT);



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	shaderProgram.Activate();

	
	/*Texture brickTex("testPic.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);*/

	Dirt dirtBlock(.5f, -.5f, .05f, -.5f, &shaderProgram);
	// ------------------------------------------------------------
	//VAO* VAO1 = new VAO();
	//VAO1->Bind();

	//VBO* VBO1 = new VBO(vertices, VERTICES_SIZE * sizeof(float));
	//EBO* EBO1 = new EBO(indices, INDICES_SIZE * sizeof(unsigned int));


	//glm::vec3 blockPos = glm::vec3(0.f, 0.f, 0.f);
	//glm::mat4 blockModel = glm::mat4(1.0f);
	//blockModel = glm::translate(blockModel, blockPos);

	//// Links VBO attributes such as coordinates and colors to VAO
	//VAO1->LinkAttrib(*(VBO1), 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	//VAO1->LinkAttrib(*(VBO1), 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	//VAO1->LinkAttrib(*(VBO1), 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	//VAO1->LinkAttrib(*(VBO1), 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	//// Prevent from accidentally modifying these values
	//VAO1->Unbind();
	//VBO1->Unbind();
	//EBO1->Unbind();

	// ------------------------------------------------------------

	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");
	// Generates Vertex Array Object and binds it
	VAO lightVAO;
	lightVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.9f, 0.9f, 0.9f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	//glm::vec4 testColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 testPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 testModel = glm::mat4(1.0f);
	testModel = glm::translate(testModel, testPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	
	// ------------------
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(testModel));
	// ------------------

	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(dirtBlock.blockModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	glEnable(GL_DEPTH_TEST);

	Camera camera(WIDTH, HEIGHT, glm::vec3(0.f, 0.f, 2.f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.f, .1f, 100.f);

		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
	
		// Exports the camera Position to the Fragment Shader for specular lighting
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		
	
		// Export the camMatrix to the Vertex Shader
		camera.Matrix(shaderProgram, "camMatrix");
		

		// Binds texture so that is appears in rendering
		dirtBlock.texture->Bind();

		//glDrawElements(GL_TRIANGLES, INDICES_SIZE, GL_UNSIGNED_INT, 0);

		
		// Draw primitives
		dirtBlock.draw();

		// -----------
		/*VAO1->Bind();
		glDrawElements(GL_TRIANGLES, INDICES_SIZE, GL_UNSIGNED_INT, 0);*/
		// -----------

		// Tells OpenGL which Shader Program we want to use
		lightShader.Activate();
		// Export the camMatrix to the Vertex Shader of the light cube
		camera.Matrix(lightShader, "camMatrix");
		// Bind the VAO so OpenGL knows to use it
		lightVAO.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}


	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}