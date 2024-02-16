#include <bits/stdc++.h>
using namespace std;

/* You have to design an application that comprises multiple devices, FAN, TV etc. 
There are 4 functions that must be implemented. There were some 
generic commands like ON / OFF devices common to all and some that were device specific. 

*/

class Device{
protected:
	bool isOn;
	Device() : isOn(false){}
public:
	void turnOn()
	{
		isOn = true;
		cout<<"device turned on\n";
	}
	void turnOff()
	{
		isOn = false;
		cout<<"device turned off\n";
	}
};

class Fan : public Device {
private:
	int regulatorLimit;
	int speed;
public:
	Fan()
	{
		regulatorLimit = 5;
		speed = 0;
	}
	void increaseSpeed()
	{
		speed += 1;
		speed %= regulatorLimit;
		cout<<"Speed of fan now is : "<<speed<<endl;
	}
	void decreaseSpeed()
	{
		if (speed == 1)
			speed = regulatorLimit;
		else
			speed -= 1;
		speed %= regulatorLimit;
		cout<<"speed of fan now is : "<<speed<<endl;
	}
};
int main() {
	Fan fan1;
	fan1.turnOn();
	fan1.increaseSpeed();
	fan1.increaseSpeed();
	fan1.turnOff();
	return 0;
}