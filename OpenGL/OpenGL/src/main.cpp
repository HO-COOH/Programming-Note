#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <string>
#include <streambuf>
#include <algorithm>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

using namespace std;

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	auto id = glCreateShader(type);
	auto src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		auto length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		std::string message(length, 0);
		glGetShaderInfoLog(id, length, &length, &(*message.begin()));
		std::cout << message << '\n';
	}
	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	auto program = glCreateProgram();
	auto vertexShaderid = CompileShader(GL_VERTEX_SHADER, vertexShader);
	auto fragmentShaderid = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	

	glAttachShader(program, vertexShaderid);
	glAttachShader(program, fragmentShaderid);
	glLinkProgram(program);
	glValidateProgram(program);
	glUseProgram(program);


	return program;
}

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
	//glfwSwapInterval(1);
	auto err = glewInit();
	if (err != GLEW_OK)
		printf("error!\n");

	float position[] = 
	{	-0.5f, -0.5f,	//0
		0.5f, 0.5f,		//1
		0.5f, -0.5f,	//2
		-0.5f, 0.5f

	};

	unsigned int index[]{
		0,1,2,
		2,3,0
	};

	//unsigned int buffer;
	//glGenBuffers(1, &buffer);				//generate 1 vertex buffer object
	//glBindBuffer(GL_ARRAY_BUFFER, buffer);	//make it the active object
	//glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);	//copy the vertex data to the object

	VertexBuffer vb(position, sizeof(position));

	//unsigned int indexbuffer;
	//glGenBuffers(1, &indexbuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	IndexBuffer ib(index, sizeof(index) / sizeof(unsigned int));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	
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
	cout << vertexShaderSource_string <<'\n'<< fragmentShaderSource_string;

	auto program = CreateShader(vertexShaderSource_string, fragmentShaderSource_string);

	float color[4]{};
	auto location = glGetUniformLocation(program, "u_Color");
	
	float increment{0.01};
	auto channel = 0;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);


		glUniform4f(location, color[0], color[1], color[2], color[3]);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		color[channel] += increment;
		if (color[channel] >= 1.0f)
			increment = -0.01f;
		if (color[channel] <= 0.0f)
		{
			++channel;
			channel %= 3;
			increment = 0.01f;
		}
	}

	glDeleteProgram(program);

	glfwTerminate();
	return 0;
}