#include <bits/stdc++.h>
using namespace std;

/*
Parking lot - Provide code for a parking lot with the following assumptions,
• The parking lot has multiple levels. Each level has multiple rows of spots.
• The parking lot has motorcycle spots and car spots.
• Parking lot can have multiple entry and exits

*/
// assumptions:
// spots only for car and motorbike essentially two wheelers and four wheelers

/*
ParkingLot => park(Bike/Car), unpark(bike/car), 

spot -> isOccupied, spotType
Rows -> has spots
Level -> has rows

Entry -> markEntryTime, park(vehicle)
Exit -> markExitTime, unpark(vehicle)
ParkingLot -> has levels, entries, exits
*/
enum SPOT_TYPE {
	CAR,
	BIKE,
};

class Vehicle {
public:
	virtual int getId() = 0;
	virtual SPOT_TYPE getVehicleType() = 0;
};

class Car : public Vehicle {
private:
	int id;
public:
	Car(int id) : id(id) {}
	int getId()
	{
		return(id);
	}
	SPOT_TYPE getVehicleType()
	{
		return(CAR);
	}
};

class Bike : public Vehicle {
private:
	int id;
public:
	Bike(int id) : id(id) {}
	int getId()
	{
		return(id);
	}
	SPOT_TYPE getVehicleType()
	{
		return(BIKE);
	}
};

class Spot {
private:
	SPOT_TYPE spotType;
	bool occupied;
	int id;
	Vehicle *vehicle;
public:
	Spot(SPOT_TYPE spotType, int id) : spotType(spotType), id(id), occupied(false) {}
	bool isOccupied()
	{
		return(occupied);
	}
	void reserveSpot(Vehicle *vehicle)
	{
		occupied = true;
		this->vehicle = vehicle;
	}
	void releaseSpot()
	{
		occupied = false;
		this->vehicle = NULL;
	}
	int getSpotId()
	{
		return(id);
	}
	SPOT_TYPE getSpotType()
	{
		return(spotType);
	}
};

class Row {
private:
	vector<Spot*> spots;
public:
	Row() {}
	void addSpot(Spot* spot)
	{
		spots.push_back(spot);
		cout<<"Spot with id = "<<spot->getSpotId()<<" added to row!!\n"<<endl;
	}
	void removeSpot(Spot *spot)
	{
		// to do
	}
	Spot* getFreeSpotInRow(SPOT_TYPE spotType)
	{
		cout<<"searching in row\n";
		for (auto spot: spots)
		{
			if (spot->getSpotType() == spotType && spot->isOccupied() == false)
			{
				cout<<"found spot in row\n";
				return(spot);
			}
		}
		return(NULL);
	}
};

class Level {
private:
	vector<Row*> rows;
public:
	Level() {}
	void addRow(Row *row)
	{
		rows.push_back(row);
		cout<<"Row added to Level successfully!!\n";
	}
	void removeRow(Row *row)
	{
		// to do
	}
	Spot* getFreeSpotInLevel(SPOT_TYPE spotType)
	{
		for (auto row: rows)
		{
			auto freeSpot = row->getFreeSpotInRow(spotType);
			if (freeSpot != NULL)
				return(freeSpot);
		}
		return(NULL);
	}
};

class Entry{
private:
	int id;
public:
	Entry(int id) : id(id){}
	int getEntryId()
	{
		return(id);
	}
};

class Exit{
private:
	int id;
public:
	Exit(int id) : id(id){}
	int getExitId()
	{
		return(id);
	}
};

class ParkingLot {
private:
	static ParkingLot* parkingLot;
	static mutex mtx;
	vector<Level*> levels;
public:
	static ParkingLot* getInstance()
	{
		lock_guard<mutex> lock(mtx);
		if (parkingLot == nullptr)
		{
			parkingLot = new ParkingLot();
		}
		return(parkingLot);
	}
	void addLevel(Level *level)
	{
		levels.push_back(level);
	}
	void removeLevel(Level *level)
	{
		// to do
	}
	void parkVehicle(Vehicle *vehicle)
	{
		for(auto level: levels)
		{
			Spot* spot = level->getFreeSpotInLevel(vehicle->getVehicleType());
			if (spot != NULL)
			{
				spot->reserveSpot(vehicle);
				cout<<"parked\n\n";
				return;
			}
		}
		cout<<"no spot free\n";
		return;
		
	}
};

ParkingLot* ParkingLot::parkingLot = nullptr;
mutex ParkingLot::mtx;

int main() {
	Car car1(1);
	Car car2(2);
	Car car3(4);
	Car car4(4);
	Car car5(5);
	
	cout<<car1.getId()<<endl;
	
	Spot spot1(CAR, 1);
	Spot spot2(BIKE, 2);
	Spot spot3(CAR, 3);
	Spot spot4(BIKE, 4);
	Spot spot5(CAR, 5);
	Spot spot6(BIKE, 6);
	Spot spot7(CAR, 7);
	Spot spot8(BIKE, 8);
	
	Row row1;
	row1.addSpot(&spot1);
	row1.addSpot(&spot2);
	
	Row row2;
	row2.addSpot(&spot3);
	row2.addSpot(&spot4);
	
	Row row3;
	row3.addSpot(&spot5);
	row3.addSpot(&spot6);
	
	Row row4;
	row4.addSpot(&spot7);
	row4.addSpot(&spot8);
	
	Level level1, level2;
	level1.addRow(&row1);
	level1.addRow(&row2);
	
	level2.addRow(&row3);
	level2.addRow(&row4);
	
	ParkingLot* parkingLot = ParkingLot::getInstance();
	parkingLot->addLevel(&level1);
	parkingLot->addLevel(&level2);
	
	parkingLot->parkVehicle(&car1);
	parkingLot->parkVehicle(&car2);
	parkingLot->parkVehicle(&car3);
	parkingLot->parkVehicle(&car4);
	parkingLot->parkVehicle(&car5);
	return 0;
}