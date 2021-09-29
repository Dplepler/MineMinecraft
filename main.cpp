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

#define WIDTH 1920
#define HEIGHT 1080

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /     COLORS           / TexCoord    //

	// Left square
	-.5f, -.05f, -.5f,      1.0f, 0.0f, 0.0f,		1.f, 0.f,		-1.f, 0.f, 0.f,		// Lower left front corner  (0) 
	-.5f, -.05f,  .5f,      1.0f, 0.0f, 0.0f,		0.f, 0.f,		-1.f, 0.f, 0.f,		// Lower left back corner   (1)
	-.5f,  .8f,   .5f,      0.0f, 1.0f, 0.0f,		0.f, 1.f,		-1.f, 0.f, 0.f,		// Upper left back corner   (2)
	-.5f,  .8f,  -.5f,      0.0f, 1.0f, 0.0f,		1.f, 1.f,		-1.f, 0.f, 0.f,		// Upper left front corner  (3)

	// Front square
	-.5f,  .8f,  -.5f,      0.0f, 1.0f, 0.0f,		0.f, 1.f,		0.f, 0.f, 1.f,		// Upper left front corner  (4)
	 .5f,  .8f,  -.5f,      0.0f, 0.0f, 1.0f,		1.f, 1.f,		0.f, 0.f, 1.f,		// Upper right front corner (5)
	 .5f, -.05f, -.5f,      1.0f, 1.0f, 1.0f,		1.f, 0.f,		0.f, 0.f, 1.f,		// Lower right front corner (6)
	-.5f, -.05f, -.5f,      1.0f, 0.0f, 0.0f,		0.f, 0.f,		0.f, 0.f, 1.f,		// Lower left front corner  (7)

	// Right square
	.5f,   .8f, -.5f,       0.0f, 0.0f, 1.0f,	    0.f, 1.0f,		1.f, 0.f, 0.f,		// Upper right front corner (8)
	.5f, -.05f, -.5f,       1.0f, 1.0f, 1.0f,	 	0.f, 0.f,		1.f, 0.f, 0.f,		// Lower right front corner (9)
	.5f, -.05f,  .5f,       1.0f, 1.0f, 1.0f,		1.f, 0.f,		1.f, 0.f, 0.f,		// Lower right back corner  (10)
	.5f,  .8f,   .5f,       0.0f, 0.0f, 1.0f,		1.f, 1.f,		1.f, 0.f, 0.f,		// Upper right back corner  (11)

	// Bottom square
	-.5f, -.05f, -.5f,     1.0f, 0.0f, 0.0f,		1.f, 0.f,		0.f, -1.f, .0f,		// Lower left front corner  (12) 
	-.5f, -.05f,  .5f,     1.0f, 0.0f, 0.0f,		1.f, 1.f,		0.f, -1.f, .0f,		// Lower left back corner   (13)
	 .5f, -.05f,  .5f,     1.0f, 1.0f, 1.0f,		0.f, 1.f,		0.f, -1.f, .0f,		// Lower right back corner  (14)
	 .5f, -.05f, -.5f,     1.0f, 1.0f, 1.0f,		0.f, 0.f,		0.f, -1.f, .0f,		// Lower right front corner (15)

	// Upper square
	-.5f,  .8f,  .5f,      0.0f, 1.0f, 0.0f,		0.f, 1.f,		0.f, 1.f, .0f,		// Upper left back corner   (16)
	-.5f,  .8f, -.5f,      0.0f, 1.0f, 0.0f,		0.f, 0.f,		0.f, 1.f, .0f,		// Upper left front corner  (17)
	 .5f,  .8f, -.5f,      0.0f, 0.0f, 1.0f,		1.f, 0.f,		0.f, 1.f, .0f,		// Upper right front corner (18)
	 .5f,  .8f,  .5f,      0.0f, 0.0f, 1.0f,		1.f, 1.f,		0.f, 1.f, .0f,		// Upper right back corner  (19)

	// Back square
	-.5f, -.05f,  .5f,    1.0f, 0.0f, 0.0f,			1.f, 0.f,		0.f, 0.f, -1.f,		// Lower left back corner   (20)
	-.5f,   .8f,  .5f,    0.0f, 1.0f, 0.0f,			1.f, 1.f,		0.f, 0.f, -1.f,		// Upper left back corner   (21)
	 .5f,   .8f,  .5f,    0.0f, 0.0f, 1.0f,			0.f, 1.f,		0.f, 0.f, -1.f,		// Upper right back corner  (22)
	 .5f, -.05f,  .5f,    1.0f, 1.0f, 1.0f,			0.f, 0.f,		0.f, 0.f, -1.f		// Lower right back corner  (23)

};



// Indices for vertices order
GLuint indices[] =
{
	// Left square
	0, 1, 2,
	0, 3, 2,

	// Front square
	4, 5, 6,
	4, 7, 6,

	// Right square
	8, 9, 10,
	8, 11, 10,

	// Bottom square
	12, 13, 14,
	12, 15, 14,

	// Upper square
	16, 17, 18,
	16, 19, 18,

	// Back square
	20, 21, 22,
	20, 23, 22,



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
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "YoutubeOpenGL", NULL, NULL);
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



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

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

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Texture
	Texture cat("testPic.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	cat.texUnit(shaderProgram, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(WIDTH, HEIGHT, glm::vec3(0.f, 0.f, 2.f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		camera.Inputs(window);
		camera.updateMatrix(45.f, .1f, 100.f);
	
		// Exports the camera Position to the Fragment Shader for specular lighting
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		// Export the camMatrix to the Vertex Shader of the pyramid
		camera.Matrix(shaderProgram, "camMatrix");
		// Binds texture so that is appears in rendering
		cat.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();

		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

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



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	cat.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}