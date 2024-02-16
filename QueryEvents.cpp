#include <bits/stdc++.h>
using namespace std;

/* Given continuous input stream of data
User City Event Timestamp
 user1 Blgr RIDE_REQUESTED timestamp1
 user2 Blgr RIDE_REQUESTED timestamp3
 user1 Blgr RIDE_CANCELLED timestamp2
 user1 Blgr COMPLETED timestamp4
The input stream is not ordered based on timestamp, as in an event occuring later can come first. 
You have to put this in a data structure to support timestamp based queries, 
like Give list of RIDE_REQUESTED for bglr city from [timestamp1,.. timestamp5]
*/
enum EventType{
	RIDE_REQUESTED,
	RIDE_CANCELLED,
	COMPLETED
};

class User {
private:
	string name;
public:
	User(string name) : name(name) {};
	string getName()
	{
		return(name);
	}
};

// city = string for simplicity
// timestamp = int for simplicity - change this !!!!!!!!!!!!!!!!!!

class Event {
private:
	User user;
	string city;
	EventType eventType;
	int timestamp;
public:
	Event(User user, string city, EventType eventType, int timestamp) : user(user), city(city), eventType(eventType), timestamp(timestamp) {}
	int getTimestamp()
	{
		return(timestamp);
	}
	EventType getEventType()
	{
		return(eventType);
	}
	string getCity()
	{
		return(city);
	}
	string getUser()
	{
		return(user.getName());
	}
};

class EventComparator{
public:
	bool operator()(Event *below, Event *above)
	{
		return(above->getTimestamp() < below->getTimestamp());
	}
};

class EventManager{
private:
	map<EventType, map<string, priority_queue<Event, vector<Event*>, EventComparator> > > eventStore; 
public:
	vector<Event*> query(EventType eventType, string city, int timestamp1, int timestamp2)
	{
		vector<Event*> eventsInRange;
		if (eventStore.find(eventType) != eventStore.end())
		{
			auto cityMap = eventStore[eventType];
			if (cityMap.find(city) != cityMap.end())
			{
				auto eventsInCity = cityMap[city];
				while(!eventsInCity.empty())
				{
					auto topEvent = eventsInCity.top();
					eventsInCity.pop();
					if (topEvent->getTimestamp() >= timestamp1 && topEvent->getTimestamp() <= timestamp2)
					{
						eventsInRange.push_back(topEvent);
					}
				}
			}
		}
		return(eventsInRange);
	}
	void addEvent(Event *event)
	{
		string eventCity = event->getCity();
		EventType eventType = event->getEventType();
		eventStore[eventType][eventCity].push(event);
	}
};

int main() {
	User user1("user1");
	User user2("user2");
	
	Event *event1 = new Event(user1, "Blr", RIDE_REQUESTED, 1);
	Event *event2 = new Event(user1, "Blr", COMPLETED, 2);
	Event *event3 = new Event(user2, "Blr", RIDE_REQUESTED, 3);
	Event *event4 = new Event(user2, "Blr", RIDE_CANCELLED, 4);
	
	EventManager manager;
	manager.addEvent(event1);
	manager.addEvent(event2);
	manager.addEvent(event3);
	manager.addEvent(event4);
	
	vector<Event*> requestedEvents = manager.query(RIDE_REQUESTED, "Blr", 1, 5);
	cout << "Events in range:" << endl;
    for (auto event : requestedEvents) {
        cout << event->getUser() << " " << event->getCity() << " " << event->getEventType() << " " << event->getTimestamp() << endl;
    }
    
    vector<Event*> requestedEvents2 = manager.query(RIDE_REQUESTED, "Blr", 1, 5);
	cout << "Events in range:" << endl;
    for (auto event : requestedEvents2) {
        cout << event->getUser() << " " << event->getCity() << " " << event->getEventType() << " " << event->getTimestamp() << endl;
    }
	return 0;
}