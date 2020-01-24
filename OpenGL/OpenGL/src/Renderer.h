#pragma once

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer
{
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Clear() const;
};

