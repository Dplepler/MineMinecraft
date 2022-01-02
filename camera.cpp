#include "camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = glm::vec3(1.f, 1.f, 1.f);
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + Orientation, Up);

	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Sets new camera matrix
	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}



void Camera::Inputs(GLFWwindow* window, Chunk* block)
{
	bool collision = false;
	glm::vec3 prevPos = Position;
	glm::vec3 tempPos;

	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		// Delete window before ending the program
		glfwDestroyWindow(window);
		// Terminate GLFW before ending the program
		glfwTerminate();
		exit(0);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Forward(Position, Orientation);
	} 
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Left(Position, Orientation);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Backwards(Position, Orientation);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Right(Position, Orientation);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (!jumping)
		{
			tempPos.x = Position.x;
			tempPos.y = Position.y;
			tempPos.z = Position.z;

			Position.y -= speed;
			Position.x = prevPos.x;
			Position.z = prevPos.z;

			if (block->collision(Position))
			{
				Position.y = prevPos.y;
				jumping = true;
				relativeHeight = Position.y + .17f;
			}
			else
			{
				Position.y = tempPos.y;
			}

			Position.x = tempPos.x;
			Position.z = tempPos.z;

		}
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.03f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.01f;
	}


	collision = block->collision(Position);

	if (prevPos.x != Position.x && collision)
		Position.x = prevPos.x;
	if (prevPos.z != Position.z && collision)
		Position.z = prevPos.z;


	if (!jumping)
	{
		// Gravity
		gravity += 0.0000000001f;
		Position.y -= speed + gravity;


		if (block->collision(Position))
		{
			gravity = 0.00000001f;
			Position.y = prevPos.y;
		}
	}
	else
	{

		gravity -= 0.0001f;
		Position.y += speed + gravity;

		if (Position.y >= relativeHeight)
		{
			jumping = false;
			gravity = 0.00000001f;
			relativeHeight = .17f;

		}
		
	}
	
		

	

	// Hides mouse cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);


	// Stores the coordinates of the cursor
	double mouseX;
	double mouseY;
	// Fetches the coordinates of the cursor
	glfwGetCursorPos(window, &mouseX, &mouseY);

	// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
	// and then "transforms" them into degrees 
	float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
	float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

	// Calculates upcoming vertical change in the Orientation
	glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

	// Decides whether or not the next vertical Orientation is legal or not
	if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		Orientation = newOrientation;
	}

	// Rotates the Orientation left and right
	Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

	// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
	glfwSetCursorPos(window, (width / 2), (height / 2));


}

void Camera::Forward(glm::vec3 position, glm::vec3 orientation)
{
	Position += speed * glm::normalize(glm::vec3(Orientation.x, 0, Orientation.z));
}

void Camera::Right(glm::vec3 position, glm::vec3 orientation)
{
	Position += speed * glm::normalize(glm::cross(Orientation, Up));
}

void Camera::Backwards(glm::vec3 position, glm::vec3 orientation)
{
	Position += speed * -glm::normalize(glm::vec3(Orientation.x, 0, Orientation.z));
}

void Camera::Left(glm::vec3 position, glm::vec3 orientation)
{
	Position += speed * -glm::normalize(glm::cross(Orientation, Up));
}