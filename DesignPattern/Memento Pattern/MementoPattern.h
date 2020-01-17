#pragma once
#include <string>
#include <string_view>
#include <stack>

using EditorState = std::string;

class History
{
	std::stack<EditorState> editor_states;
public:
	void add(EditorState&& state);
	EditorState get();
};

class TextEditor
{
	std::string content;
	History history_manager;

	EditorState createState() const;
	void restoreState(EditorState&& state);
public:
	void undo();
	TextEditor& operator+=(std::string_view new_content);
	friend std::ostream& operator<<(std::ostream& os, TextEditor const& editor);
};