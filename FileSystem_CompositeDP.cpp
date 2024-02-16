#include <bits/stdc++.h>
using namespace std;
/*
Design an in-memory file system to simulate the following functions:

ls: Given a path in string format. If it is a file path, 
return a list that only contains this file’s name. 
If it is a directory path, return the list of file and directory names in this directory. 
Your output (file and directory names together) should in lexicographic order.

mkdir: Given a directory path that does not exist, 
you should make a new directory according to the path. 
If the middle directories in the path don’t exist either, you should create them as well. 
This function has void return type.

addContentToFile: Given a file path and file content in string format. 
If the file doesn’t exist, you need to create that file containing given content. 
If the file already exists, you need to append given content to original content. 
This function has void return type. 

readContentFromFile: Given a file path, return its content in string format.
*/

/*
Design In memory file system and implement:
Create
 Delete
 Move
Interviewer was particularly interested in the Move method and implementation.
 Btw, this system should support Drive,Folder,File types (Drive being on the top hierarchy)
 */
 
 class FileSystemComponent {
 public:	 
	virtual void ls(int depth) = 0;
	// virtual void move() = 0;
	virtual void remove() = 0;
 };
 
 class Directory : public FileSystemComponent {
 private:
	int depth;
	string name;
	vector<FileSystemComponent*> children;
	bool isDeleted;
public:
	Directory(string name) : name(name), isDeleted(false) {} // mkdir
	
	void add(FileSystemComponent *component)
	{
		if (isDeleted)
		{
			cout<<"this directory does not exist\n";
			return;
		}
		children.push_back(component);
	}
	void ls(int depth)
	{
		if (isDeleted)
		{
			//cout<<"this directory does not exist\n";
			return;
		}
		cout<<string(depth, '=')<<" "<<name<<endl;
		for (auto child: children)
		{
			child->ls(depth+2);
		}
	}
	void remove()
	{
		for (auto child: children)
		{
			child->remove();
		}
		//delete(this);
		isDeleted = true;
		cout<<"removed directory "<<name<<endl;
	}
	// void move(FileSystemComponent *source, FileSystemComponent *destination)
	// {
	// 	source->add(destination);
	// 	destination->remove()
	// }
 };

class File : public FileSystemComponent{
private:
	string name;
	string contents;
	int depth;
	bool isDeleted;
public:
	File(string name) : name(name), isDeleted(false) {} // touch
	void add(string fileContent)
	{
		if (isDeleted)
		{
			cout<<"this file does not exist\n";
			return;
		}
		contents = contents + " " + fileContent;
	}
	void show()
	{
		if (isDeleted)
		{
			cout<<"this file does not exist\n";
			return;
		}
		cout<<contents<<endl;
	}
	void ls(int depth)
	{
		if (isDeleted)
		{
			//cout<<"this file does not exist\n";
			return;
		}
		cout<<string(depth, '-')<<" "<<name<<endl;
	}
	void remove()
	{
		//delete(this);
		isDeleted = true;
		cout<<"removed file "<<name<<endl;
	}
 };
 
int main() {
	File *file1 = new File("file1");
	file1->add("hello world from file 1");
	File *file2 = new File("file2");
	file2->add("hello world from file 2");
	
	file1->show();
	file2->show();
	
	Directory *dir1 = new Directory("dir1");
	Directory *dir2 = new Directory("dir2");
	Directory *dir3 = new Directory("dir3");
	
	dir1->add(file1);
	dir2->add(file2);
	dir2->add(dir3);
	
	dir1->ls(0);
	dir2->ls(0);
	
	cout<<"**********************************\n\n";
	
	file2->remove();
	
	dir1->ls(0);
	dir2->ls(0);
	
	return 0;
}