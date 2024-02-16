#include <bits/stdc++.h>
using namespace std;

class Command {
public:
	~Command() {}
	virtual void execute() = 0;
	virtual void revert() = 0;
};

class InsertCommand : public Command{
private:
	int position;
	string insertedText;
	string &data;
public:
	InsertCommand(string &data, int position, string &insertedText): data(data), position(position), insertedText(insertedText){}
	void execute()
	{
		data.insert(position, insertedText);
		cout<<"insert command executed\n";
	}
	void revert()
	{
		data.erase(position, insertedText.size());
		cout<<"insert reverted\n";
	}
};

class TextEditor {
private:
	string data;
	stack<Command*> undoStack;
	stack<Command*> redoStack;
public:
	TextEditor(){}
	void display()
	{
		cout<<data<<endl;
	}
	void insert(string text, int position)
	{
		InsertCommand *insertCmd = new InsertCommand(data, position, text);
		insertCmd->execute();
		undoStack.push(insertCmd);
	}
	void undo()
	{
		if (!undoStack.empty())
		{
			auto command = undoStack.top();
			command->revert();
			redoStack.push(command);
		}
	}
	void redo()
	{
		if (!redoStack.empty())
		{
			auto command = redoStack.top();
			command->execute();
			undoStack.push(command);
		}
	}
};

int main() {
	TextEditor myEditor;
	myEditor.insert("hello ", 0);
	myEditor.display();
	myEditor.insert("obama ", 6);
	myEditor.display();
	myEditor.undo();
	myEditor.display();
	myEditor.insert("rohilla ", 6);
	myEditor.display();
	myEditor.redo();
	myEditor.display();
	return 0;
}