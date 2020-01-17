#include "StatePattern.h"
int main()
{
	Canvas canvas;
	canvas.changeTool(new Eraser{});
	canvas.mouseUp();
	canvas.mouseDown();
	canvas.changeTool(new Pen{});
	canvas.mouseUp();
	canvas.mouseDown();
}