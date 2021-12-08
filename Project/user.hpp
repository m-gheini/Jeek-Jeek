#include <iostream>
#include <vector>
#include "jeek.hpp"

using namespace std;

class User{
public :
	User(string _userName, string _displayName, string _password);
	string getUserName(){ return userName;}
	string getDisplayName(){ return displayName;}
	string getPassword(){ return password;}
	vector<string> getFollower(){return followerUsers;}
	void fillUserJeeks(Jeek* jeek){ userJeeks.push_back(jeek);}
	void showJeekAfterSearching();
	bool isFollower(string userName);
	void fillFollowerUsers(string userName){ followerUsers.push_back(userName);}
	void fillFollowingUsers(string userName){ followingUsers.push_back(userName);}
	void removeFollowerUsers(string userName);
	void removeFollowingUsers(string userName);
private :
	string userName;
	string displayName;
	string password;
	vector<Jeek*> userJeeks;
	vector<string> followerUsers;
	vector<string> followingUsers;
};