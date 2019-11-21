#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <string>
#include <streambuf>

using namespace std;

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;



	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "?", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);	
	auto err = glewInit();
	/*if (err != GLEW_OK)
		printf("error!\n");*/

	float position[] = { -0.5f, -0.5f ,0.0f, 0.5f, 0.5f, -0.5f };

	unsigned int buffer;
	glGenBuffers(1, &buffer);				//generate 1 vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, buffer);	//make it the active object
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);	//copy the vertex data to the object
	
	/*read in shader source code*/
	ifstream vertexShaderFile("./Shaders/VertexShader.txt");
	if (!vertexShaderFile.is_open())
	{
		cerr << "VertexShader.txt not opened successfully\n";
		terminate();
	}
	string vertexShaderSource_string{ istreambuf_iterator<char>(vertexShaderFile),istreambuf_iterator<char>() };

	ifstream fragmentShaderFile("./Shaders/FragmentShader.txt");
	if (!fragmentShaderFile.is_open())
	{
		cerr << "FragmentShader.txt not opened successfully\n";
		terminate();
	}
	string fragmentShaderSource_string{ istreambuf_iterator<char>(fragmentShaderFile),istreambuf_iterator<char>() };
	/*DEBUG*/
	cout << vertexShaderSource_string << fragmentShaderSource_string;

	/*compile shaders*/
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);	//create shader object
	auto vertexShaderSource = vertexShaderSource_string.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);		//copy the source to the object
	glCompileShader(vertexShader);									//compile shader object

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	auto fragmentShaderSource = vertexShaderSource_string.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/*combining shaders into a program*/
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glEnd();
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}