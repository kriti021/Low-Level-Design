#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

/*
Rate limiter using sliding window algorithm
this allows x number of requests in a fixed window size
*/

class RateLimiter{
private:
	const int requestLimit;
	const int windowSize;
	deque<steady_clock::time_point> window;
	mutex mtx;
public:
	RateLimiter(int requestLimit, int windowSize): requestLimit(requestLimit), windowSize(windowSize) {}
	bool allowRequest()
	{
		lock_guard<mutex> lock(mtx);
		auto now = steady_clock::now();
		while(!window.empty() && (now-window.front()) > milliseconds(windowSize))
			window.pop_front();
			
		if (window.size() < requestLimit)
		{
			window.push_back(now);
			return(true);
		}
		else
			return(false);
	}
};

void sendRequest(RateLimiter &limiter, int id)
{
	// making 10 random requests
	for (int count=0; count<10; count++)
	{
		if (limiter.allowRequest())
			cout<<"Request no. "<<count<<" was allowed for thread id: "<<id<<endl;
		else
			cout<<"Request no. "<<count<<" was ignored for thread id: "<<id<<endl;
		this_thread::sleep_for(milliseconds(100));
	}
}

int main() {
	RateLimiter limiter(3, 1000);
	
	vector<thread> threads; // spawn 4 threads
	for (int threadId=11; threadId<14; threadId++)
	{
		threads.push_back(thread(sendRequest, ref(limiter), threadId));
	}
	
	for (auto &thread: threads)
		thread.join();
		
	return 0;
}