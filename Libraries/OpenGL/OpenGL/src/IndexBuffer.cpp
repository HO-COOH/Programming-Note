#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int data[], const unsigned int count): count(count)
{
	static_assert(sizeof(unsigned int) == sizeof(GLuint), "Notice: sizeof unsigned int != GLuint!");
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &id);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
