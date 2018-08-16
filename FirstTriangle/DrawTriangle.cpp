#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
using namespace glm;

int main(void)
{
	GLFWwindow* window;  //2

	glewExperimental = true;

	if (!glfwInit()) //3
		return -1;

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL); //4
	if (!window)
	{
		glfwTerminate(); //5
		return -1;
	}

	glfwMakeContextCurrent(window); //Setting drawing paper
	glewInit(); // Initiate glew
	glClearColor(0.5, 0.75, 1, 1); // r, g, b, a (0~1) 

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);

	//VAO : Vertex Array Object  (Vertex mean point in 3D graphics)
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	

	// Vertex X : Your right, Y : Up, Z : Your Back (Right Hand Rule)
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,		// first vertex
		1.0f, -1.0f, 0.0f,		// second vertex
		0.0f,  1.0f, 0.0f,		// third vertex
	};

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT); //9

		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window); //10
		glfwPollEvents(); //11
	}

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate(); //12
}