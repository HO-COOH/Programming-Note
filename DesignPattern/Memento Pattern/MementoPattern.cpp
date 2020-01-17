#include "MementoPattern.h"
#include <iostream>

void History::add(EditorState&& state)
{
	editor_states.push(state);
}

EditorState History::get()
{
	auto state = editor_states.top();
	editor_states.pop();
	return state;
}

EditorState TextEditor::createState() const
{
	return EditorState{ content };
}

void TextEditor::restoreState(EditorState&& state)
{
	content = state;
}

void TextEditor::undo()
{
	restoreState(history_manager.get());
}

TextEditor& TextEditor::operator+=(std::string_view new_content)
{
	history_manager.add(createState());
	content += new_content;
	return *this;
}

std::ostream& operator<<(std::ostream& os, TextEditor const& editor)
{
	os << editor.content;
	return os;
}
