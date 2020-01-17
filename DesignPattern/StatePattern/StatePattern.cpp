#include "StatePattern.h"
#include <utility>
#include <cstdio>
#include <iostream>
void Pen::mouseUp() const
{
	puts("Drawing with a pen!");
}

void Pen::mouseDown() const
{
	puts("Pen selected!");
}

std::string Pen::toolType() const
{
	return { "Pen" };
}

void Eraser::mouseUp() const
{
	puts("Erase something!");
}

void Eraser::mouseDown() const
{
	puts("Eraser selected!");
}

std::string Eraser::toolType() const
{
	return { "Eraser" };
}

Canvas::Canvas(): current_tool(std::make_unique<Pen>())
{
}

Canvas::Canvas(Tool* tool):current_tool(tool)
{
}

void Canvas::changeTool(Tool* tool)
{
	current_tool.reset(tool);
	std::cout << "Change tool -> " << tool->toolType() << '\n';
}

void Canvas::mouseUp() const
{
	current_tool->mouseUp();
}

void Canvas::mouseDown() const
{
	current_tool->mouseDown();
}

Tool::~Tool()
{
	puts("Tool released!");
}
