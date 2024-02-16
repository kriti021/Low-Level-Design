#include <bits/stdc++.h>
using namespace std;

class Singleton{
private:
	int x;
	static Singleton* singletonInstance;
	static mutex mtx;
	Singleton(){
	
	}
public:
	static Singleton* getInstance()
	{
		if (singletonInstance == nullptr)
		{
			mtx.lock();
			if (singletonInstance == nullptr)
			{
				singletonInstance = new Singleton();
			}
			mtx.unlock();
		}
		return(singletonInstance);
	}
	int getX()
	{
		return(x);
	}
	void setX(int val)
	{
		x = val;
	}
};
Singleton* Singleton::singletonInstance = nullptr;
mutex Singleton::mtx;

int main() {
	auto driver = Singleton::getInstance();
	return 0;
}