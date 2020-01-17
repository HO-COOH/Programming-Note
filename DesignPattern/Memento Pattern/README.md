# Memento Pattern
## Intro
Memento Pattern, a design pattern of **behavioral pattern**, is used to restore state of an object to a previous state.
## Implementation
Memento pattern uses 3 actor classes:
- class Originator
- class Memento
- class CareTaker
![UML diagram](images/1.jpg)
## Example
Using this design pattern, I implemented a text editor ``Redo`` functionality. With the following classes repestively:
- TextEditor => Originator
- EditorState => Memento
- History => CareTaker