#pragma once
#include <string>
#include <memory>
class Tool
{
public:
	virtual void mouseUp() const = 0;
	virtual void mouseDown() const = 0;
	virtual std::string toolType() const = 0;
	virtual ~Tool();
};

class Pen:public Tool
{
public:
	void mouseUp() const override;
	void mouseDown() const override;
	std::string toolType() const override;
};

class Eraser:public Tool
{
public:
	void mouseUp() const override;
	void mouseDown() const override;
	std::string toolType() const override;
};

class Canvas
{
	std::unique_ptr<Tool> current_tool;
public:
	Canvas();    //pen is the default tool
	Canvas(Tool* tool);
	void changeTool(Tool*tool);
	void mouseUp() const;
	void mouseDown() const;
};