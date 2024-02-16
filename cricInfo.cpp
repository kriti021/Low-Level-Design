#include <bits/stdc++.h>
using namespace std;

// enumerations
enum RunType {
	FOUR, SIX, REGULAR
};

enum WicketType {
	RUNOUT, HITWICKET, LBW
};

enum PlayingPosition {
	BATSMAN, BALLER, WICKET_KEEPER, ALL_ROUNDER
};

enum MatchResult {
	LIVE, BAT_FIRST_WIN, FIELD_FIRST_WIN, DRAW, CANCELLED	
};

enum BallType {
	WIDE, NORMAL, NO_BALL, WICKET
};

enum UmpireType {
	ON_FIELD, RESERVED, THIRD_UMPIRE	
};


class Coach {
private:
	string name;
	int age;
	int country;
};

class Umpire {
private:
	string name;
};

class Player {
private:
	string name;
	int age;
	int country;
	PlayingPosition playingPosition;
public:
	Player(string name, int age, int country, PlayingPosition playingPosition)
	{
		this->name = name;
		this->age = age;
		this->country = country;
		this->playingPosition = playingPosition;
	}
	void showPlayer()
	{
		cout<<"Name: "<<name<<" | Country: "<<country<<endl;
	}
};

class Run {
private:
	RunType runType;
	int score;
	Player *scoredBy;
};

class Wicket {
private:
	WicketType wicketType;
	Player *baller;
	Player *batsman;
};

class Ball{
private:
	BallType ballType;
	vector<Run*> runs;
	Wicket *wicket;
	Player *batsman;
	Player *baller;
};

class Over {
private:
	vector<Ball*> balls;
	Player *baller;	
public:
	Over(Player *ballingPlayer)
	{
		*baller = *ballingPlayer;
	}
	bool addBall(Ball *ball)
	{
		if (balls.size() < 6)
		{
			balls.push_back(ball);
			return(true);
		}
		return(false);
	}
};

class Playing11 {
private:
	vector<Player*> players;
public:
	bool addPlayer(Player *player)
	{
		if (players.size() < 11){
			players.push_back(player);
			return(true);
		}
		return(false);
	}
	void showPlayers()
	{
		for (int i=0; i<players.size(); i++)
			players[i]->showPlayer();
	}
};

class Innings {
private:
	vector<Over*> overs;
	int totalScore;
	int totalWickets;
public:
	Innings()
	{
		totalScore = 0;
		totalWickets = 0;
	}
	/*bool addBall(Ball *ball, Player *baller)
	{
		Over *lastOver = overs.back();
		if (lastOver->addBall(*ball) == true)
			return(true);
		Over *newOver = new Over(baller);
		newOver->addBall(ball);
		overs.push_back(newOver);
		updateTotalScore(ball);
		updateTotalWickets(ball);
	}
	void updateTotalScore(Ball ball)
	{
		cout<<"Updating total score\n";
	}
	void updateTotalWickets(Ball ball)
	{
		cout<<"Updating totalWickets\n";
	}
	*/
	void showInnings()
	{
		cout<<"here i show innings"<<endl;
	}
};

class Match {
private:
	int id;
	string startTime;
	bool isLiveFlag;
	Playing11 *tossWin;
	vector<Playing11*> teams;
	map<Playing11*, Innings*> inningsMap;
	MatchResult matchResult;
	//map<Umpire*, UmpireType> umpires;
	int overs;
protected:
	Match(int id, string startTime, int overs)
	{
		this->id = id;
		this->startTime = startTime;
		//this->umpires = &umpires;
		this->overs = overs;
		isLiveFlag = true;
	}
	void addTeams(Playing11 *teamA, Playing11 *teamB)
	{
		teams.push_back(teamA);
		teams.push_back(teamB);
		cout<<"Teams added for match id = "<<id<<endl;
		cout<<"creating innings for teams\n";
		Innings *inningA = new Innings();
		inningsMap[teamA] = inningA;
		Innings *inningB = new Innings();
		inningsMap[teamB] = inningB;
		cout<<"Done creating innings for teams\n";
	}
	bool isLive()
	{
		return(isLiveFlag);
	}
	/*bool updateInnings(Playing11 team, Ball ball)
	{
		Innings *inning = inningsMap[team];
		inning.addBall(ball);
	}*/
public:
	friend class Admin;
	void showMatch()
	{
		cout<<"Teams: "<<endl;
		teams[0]->showPlayers();
		teams[1]->showPlayers();
		cout<<"team 1 innings : \n";
		inningsMap[teams[0]]->showInnings();
		cout<<"team 2 innings : \n";
		inningsMap[teams[1]]->showInnings();
	}
};

/*
class CricInfoSystem {
protected:
	vector<Match*> matches;
	Match* getLiveMatch()
	{
		// assumption - atmost one live match at a time
		for (auto match: matches)
		{
			if (match->isLive() == true)
				return(match);
		}
		return(NULL);
	}
public:
	void showLiveMatchScoreBoard()
	{
		Match *match = getLiveMatch();
		if (match != NULL)
			showMatchInfo(match);
		else
			cout<<"No live match found\n";
	}
	void showMatchInfo(Match *match)
	{
		match->showMatch();
	}
	
};*/

class Admin : public Match{
private:
	int id;
	string name;
public:
	Admin(int id, string name) : Match(0, "", 0)
	{
		this->id = id;
		this->name = name;
	}
	Playing11* makeTeam(vector<Player*> players)
	{
		Playing11 *team = new Playing11();
		for (auto player: players){
			team->addPlayer(player);
		}
		return(team);
	}
	Match* addMatch(int id, string startTime, int overs, Playing11 *teamA, Playing11 *teamB)
	{
		Match *newMatch = new Match(id, startTime, overs);
		newMatch->addTeams(teamA, teamB);
		return(newMatch);
	}
	void displayMatch(Match *match)
	{
		match->showMatch();
	}
};

int main() {
	Player a_one("virat", 35, 12, ALL_ROUNDER);
	Player a_two("dhoni", 40, 12, WICKET_KEEPER);
	Player a_three("a", 35, 12, ALL_ROUNDER);

	Player b_one("virat", 35, 55, ALL_ROUNDER);
	Player b_two("dhoni", 40, 55, WICKET_KEEPER);
	Player b_three("ds", 35, 55, ALL_ROUNDER);
	
	Playing11 *teamA, *teamB;
	
	Admin admin(1, "kriti");
	teamA = admin.makeTeam({&a_one, &a_two, &a_three});
	teamB = admin.makeTeam({&b_one, &b_two, &b_three});
	
	Match *match = admin.addMatch(1, "2024-01-20", 2, teamA, teamB);
	admin.displayMatch(match);
	
	Match *match_2 = admin.addMatch(2, "2023-01-20", 20, teamA, teamB);
	admin.displayMatch(match_2);
	
	
	return(0);
}