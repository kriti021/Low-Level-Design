#include <bits/stdc++.h>
using namespace std;

class Vehicle {
public:
	virtual int getFuelCapacity() = 0;
	virtual int getSeatingCapacity() = 0; 
};

class Car : public Vehicle {
private:
	int fuelCapacity;
	int seatingCapacity;
public:
	Car() : fuelCapacity(40), seatingCapacity(4) {}
	int getFuelCapacity()
	{
		return(fuelCapacity);
	}
	int getSeatingCapacity()
	{
		return(seatingCapacity);
	}
};

class NullObject : public Vehicle {
public:
	int getFuelCapacity()
	{
		return(0);
	}
	int getSeatingCapacity()
	{
		return(0);
	}
};

class VehicleFactory{
private:
	Vehicle *vehicle;
public:
	Vehicle* getVehicle(int num)
	{
		if (num%2 == 0)
			return(new Car());
		else
			return(new NullObject);
	}
};

int main() {
	VehicleFactory obj;
	auto one = obj.getVehicle(2);
	auto two = obj.getVehicle(1);
	
	cout<<two->getFuelCapacity()<<endl;
	return 0;
}