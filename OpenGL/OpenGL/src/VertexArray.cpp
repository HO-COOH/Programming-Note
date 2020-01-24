#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id);
	Bind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}

void VertexArray::AddBuffer(VertexBuffer& vb)
{
	//Bind();
	vb.Bind();
	for (unsigned int i = 0, offset=0; i < layouts.size(); ++i)
	{
		const auto& current = layouts[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, current.count, current.type, current.normalized ? GL_TRUE : GL_FALSE, stride, reinterpret_cast<const void*>(offset));
		offset += current.size();
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(id);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}
