#include <GL\glew.h>
#include <GLFW\glfw3.h>


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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT); //9
		glfwSwapBuffers(window); //10
		glfwPollEvents(); //11
	}

	glfwTerminate(); //12
	return 0;
}

