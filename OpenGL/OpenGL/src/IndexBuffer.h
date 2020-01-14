#pragma once
class IndexBuffer
{
	unsigned int id;
	unsigned int count;
public:
	IndexBuffer(const unsigned int data[], const unsigned int count);
	~IndexBuffer();
	void Bind();
	void UnBind();
};

