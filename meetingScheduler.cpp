#include <bits/stdc++.h>
using namespace std;

/*
Meeting scheduler

There are some buildings with some floors with some meeting rooms
Schedule meeting given date, start time, end time and for n people with optimised room picking method
Cancel meeting
Keep track of meeting date and time using a calendar for each meeting room
Notify all invitees when a meeting is scheduled / cancelled
*/

/*MeetingRoom -> calenderForDate, capacity
Floor -> has meetingRooms 
Building -> hasFloors

Meeting -> room, [people], startTime, endTime

Scheduler 
	-> scheduleMeeting
	-> cancelMeeting
	-> notify(Meeting) */

class MeetingRoom {
private:
	int id;
	int capacity;
	map<string, vector<pair<int, int> > > calendarForDate;
public:
	MeetingRoom(int id, int capacity) : id(id), capacity(capacity) {}
	int getId()
	{
		return(id);
	}
	int getCapacity()
	{
		return(capacity);
	}
	bool isBooked(string date, int startTime, int endTime)
	{
		if (calendarForDate.find(date) != calendarForDate.end())
		{
			for (auto duration: calendarForDate[date])
			{
				if ((duration.second < startTime) || (duration.first > endTime))
					continue;
				else
					return(true);
			}
		}
		else
			calendarForDate[date] = vector<pair<int, int> >{};
		return(false);
	}
	void reserveRoom(string date, int startTime, int endTime)
	{
		if (!isBooked(date, startTime, endTime)){
			calendarForDate[date].push_back({startTime, endTime});
			cout<<"Room reserved successfully!!\n";
		}
		else
			cout<<"Room not available!!\n";
	}
	void releaseRoom(string date, int startTime, int endTime)
	{
		if (calendarForDate.find(date) != calendarForDate.end())
		{
			int index = 0;
			for (auto duration: calendarForDate[date])
			{
				if (duration.first == startTime && duration.second == endTime)
				{
					calendarForDate[date].erase(calendarForDate[date].begin()+index);
					return;
				}
				index += 1;
			}
		}
	}
};

class Floor {
public:
	vector<MeetingRoom*> rooms;
public:
	Floor(){}
	void addRoom(MeetingRoom *room)
	{
		rooms.push_back(room);
		cout<<"Room added to floor!!\n";
	}
	void removeRoom(MeetingRoom *room)
	{
		// to do
	}
};

class Building {
public:
	vector<Floor*> floors;
public:
	Building() {}
	void addFloor(Floor* floor)
	{
		floors.push_back(floor);
		cout<<"Floor added to building!!\n";
	}
	void removeFloor(Floor *floor)
	{
		// to do
	}
};

class Meeting {
private:
	int startTime;
	int endTime;
	vector<string> invitees;
	string date;
	MeetingRoom *bookedRoom;
public:
	Meeting(string date, int startTime, int endTime, vector<string> &invitees, MeetingRoom* bookedRoom): date(date), startTime(startTime), endTime(endTime), invitees(invitees), bookedRoom(bookedRoom) {}
	int getStartTime()
	{
		return(startTime);
	}
	int getEndTime()
	{
		return(endTime);
	}
	string getDate()
	{
		return(date);
	}
	void notifyScheduled()
	{
		cout<<"Meeting from startTime = "<<startTime<<" endtime = "<<endTime<<" date = "<<date<<" is set for "<<invitees.size()<<" people in room with id = "<<bookedRoom->getId()<<endl;
		cout<<"Notification sent!!\n";
	}
	void notifyCancelled()
	{
		cout<<"Meeting from startTime = "<<startTime<<" endtime = "<<endTime<<" date = "<<date<<" is cancelled for "<<invitees.size()<<" people in room with id = "<<bookedRoom->getId()<<endl;
		cout<<"Notification sent!!\n";
	}
  void cancelMeeting()
  {
    bookedRoom->releaseRoom(date, startTime, endTime);
  }
};

class MeetingScheduler {
private:
	vector<Building*> buildings;
public:
	MeetingScheduler() {}
	void addBuilding(Building* building)
	{
		buildings.push_back(building);
		cout<<"Scheduler tracking another building!!\n";
	}
	void removeBuilding(Building *building)
	{
		// to do
	}
	Meeting* scheduleMeeting(string date, int startTime, int endTime, vector<string>& people)
	{
		int peopleCount = people.size();
		for (auto building: buildings)
		{
			for (auto floor: building->floors)
			{
				for (auto meetingRoom: floor->rooms)
				{
          if (meetingRoom->getCapacity() == peopleCount && !meetingRoom->isBooked(date, startTime, endTime))
					{
            meetingRoom->reserveRoom(date, startTime, endTime);
						Meeting* meeting = new Meeting(date, startTime, endTime, people, meetingRoom);
						meeting->notifyScheduled();
						return(meeting);				
					}
				}
			}
		}
		cout<<"No room available!! Try some other slot for meeting!!\n";
    return(NULL);
	}
	void cancelMeeting(Meeting* meeting)
	{
    meeting->cancelMeeting();
		meeting->notifyCancelled();
	}
};

int main() {
	MeetingRoom room1(1,4);
	MeetingRoom room2(2,5);
	
	MeetingRoom room3(3,5);
	MeetingRoom room4(4,6);
	MeetingRoom room5(5,2);
	
	// room1.reserveRoom("2024-02-14", 2, 4);
	// room1.reserveRoom("2024-02-14", 5, 6);
	// room1.reserveRoom("2024-02-14", 6, 7);
	
	Floor floor1;
	floor1.addRoom(&room1);
	floor1.addRoom(&room2);
	
	Floor floor2;
	floor2.addRoom(&room3);
	floor2.addRoom(&room4);
	floor2.addRoom(&room5);
	
	Building building1;
	building1.addFloor(&floor1);
	building1.addFloor(&floor2);
	
	MeetingScheduler scheduler;
	scheduler.addBuilding(&building1);
	
  vector<string> people{"a", "b", "c"};
  Meeting *meeting1 = scheduler.scheduleMeeting("2024-02-14", 2, 4, people);
  people.push_back("d");
  Meeting *meeting2 = scheduler.scheduleMeeting("2024-02-14", 2, 4, people);
	people.push_back("e");
  Meeting *meeting3 = scheduler.scheduleMeeting("2024-02-14", 2, 4, people);
	Meeting *meeting4 = scheduler.scheduleMeeting("2024-02-14", 2, 4, people);
	scheduler.cancelMeeting(meeting4);
  return 0;
}