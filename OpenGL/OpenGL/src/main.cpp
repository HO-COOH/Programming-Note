#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <string>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

using namespace std;

int main(void)
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	auto window = glfwCreateWindow(600, 600, "?", NULL, NULL);
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

	{
		float position[]
		{ -0.5f, -0.5f,	0.0f, 0.0f,//0
			0.5f, 0.5f,	1.0f, 1.0f,	//1
			0.5f, -0.5f, 1.0f, 0.0f,	//2
			-0.5f, 0.5f, 0.0f, 1.0f    //3
		};

		unsigned int index[]
		{
			0,1,2,
			0,1,3
		};

		VertexBuffer vb(position, sizeof(position));

		IndexBuffer ib(index, sizeof(index) / sizeof(unsigned int));

		VertexArray va;
		va.Push<float>(2);
		va.Push<float>(2);
		va.AddBuffer(vb);

		Shader shader("./Shaders/VertexShader.txt", "./Shaders/FragmentShader.txt");
		shader.Bind();
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		//glBlendEquation(GL_FUNC);
		
		Texture texture("./texture/1.png");
		texture.Bind();

		Renderer renderer;

		float color[4]{};
		float increment = 0.02f;
		/* Loop until the user closes the window */
		auto channel = 0;
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();

			shader.SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);

			renderer.Draw(va, ib, shader);

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
	}
	glfwTerminate();
	return 0;
}