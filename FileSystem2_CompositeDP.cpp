#include <bits/stdc++.h>
using namespace std;

/*
Given list of folders, print the path of a given folder from root. If there is no path to the root folder then return an empty string. Root level folders will have 0 as id. 
The structure of Folder is like this:
 class Folder {
 int id;
 List subfolders;
 String name;
 }
Ex:
 list = [Folder(0, [7, 3], “abc”), Folder(0, [], “xyz”), Folder(3, [], “pqr”), Folder(8, [], “def”), Folder(7, [9], “ijk), Folder(9, [], “lmn”)]
/abc/ijk/lmn
 /abc/pqr
 /xyz
 ?? def/
printPath(9) = “abc” -> “ijk” -> “lmn” printPath(8) = ""
 Clarification: There can be multiple root level folders. All other folders have unique ids.
 Note: printPath method may be called multiple times concurrently. Design your solution taking that into account
 Concurrency in input and printPath()
addFolder(Folder f)
 printPath(int index)

*/

class Folder{
private:
	int id;
	string name;
	vector<Folder*> children;
	Folder* parent = nullptr;
	mutex mtx;
public:
	Folder(int id, string name) : id(id), name(name) {}
	int getId()
	{
		return(id);
	}
	Folder* getParent()
	{
		return(parent);
	}
	void insertFolder(Folder* child)
	{
		lock_guard<mutex> lock(mtx);
		children.push_back(child);
		child->parent = this;
	}
	void deleteFolder(Folder* child)
	{
		lock_guard<mutex> lock(mtx);
		int idToDelete = child->getId();
		int index = 0;
		for (auto child: children)
		{
			if (child->getId() == idToDelete)
			{
				break;
			}
			index += 1;
		}
		children.erase(children.begin()+index);
	}
	void printPathFromRoot(int depth)
	{
		lock_guard<mutex> lock(mtx);
		cout<<string(depth, '-')<<" /"<<name<<endl;
		for (auto child: children)
			child->printPathFromRoot(depth+1);
	}
	
	void printPathToRoot(int depth)
	{
		lock_guard<mutex> lock(mtx);
		cout<<" /"<<name;
		if (this->getParent() != nullptr)
		{
			auto parentFolder = this->getParent();
			parentFolder->printPathToRoot(depth+2);
		}
	}
};

Folder* getRootDir()
{
	Folder *rootDir = new Folder(-1, "root");
	return(rootDir);
}

int main() {
	auto systemRoot = getRootDir();
	
	Folder *parent1 = new Folder(0, "abc");
	Folder *parent2 = new Folder(0, "xyz");

	systemRoot->insertFolder(parent1);
	systemRoot->insertFolder(parent2);
	
	Folder *child1 = new Folder(7, "ijk");
	Folder *child2 = new Folder(3, "pqr");
	Folder *child3 = new Folder(8, "def");
	
	parent1->insertFolder(child1);
	parent1->insertFolder(child2);
	
	Folder *child4 = new Folder(9, "lmn");
	child1->insertFolder(child4);
	
	systemRoot->printPathFromRoot(0);
	child4->printPathToRoot(0);
	
	
	return 0;
}