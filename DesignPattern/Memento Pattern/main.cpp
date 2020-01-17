#include "MementoPattern.h"
#include <iostream>
int main()
{
	TextEditor editor;
	editor +=  "hello";
	editor += "world";
	std::cout << editor<<'\n';
	editor += "bye";
	std::cout << editor << '\n';
	editor.undo();
	editor.undo();
	std::cout << editor << '\n';
}