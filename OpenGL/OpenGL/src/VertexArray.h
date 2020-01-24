#pragma once
#include "VertexBuffer.h"
#include <GL/glew.h>
#include <vector>
#include <iostream>



class VertexArray
{
	struct VertexBufferLayout
	{
		unsigned int type;
		unsigned int count;
		bool normalized;
		unsigned int size() const
		{
			switch (type)
			{
			case GL_FLOAT:
				return sizeof(float) * count;
			case GL_UNSIGNED_BYTE:
				return sizeof(unsigned char) * count;
			case GL_UNSIGNED_INT:
				return sizeof(unsigned int) * count;
			default:
				std::cerr << "Error! Unknown type in VertexBufferLayout!\n";
				return 0;
			}
		}
	};
	
	std::vector<VertexBufferLayout> layouts;
	unsigned int stride = 0;
	unsigned int id;

public:
	VertexArray();
	~VertexArray();

	/*Push layout -> elements*/
	template<typename T>
	void Push(unsigned count, bool normalized=false)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count, bool normalized)
	{
		layouts.push_back({ GL_FLOAT, count, normalized });
		stride += layouts.back().size();
	}

	template<>
	void Push<unsigned char>(unsigned count, bool normalized)
	{
		layouts.push_back({ GL_UNSIGNED_BYTE, count, normalized });
		stride += layouts.back().size();
	}

	template<>
	void Push<unsigned int>(unsigned int count, bool normalized)
	{
		layouts.push_back({ GL_UNSIGNED_INT, count, normalized });
		stride += layouts.back().size();
	}

	void AddBuffer(VertexBuffer& vb);
	void Bind() const;
	void UnBind() const;
};

