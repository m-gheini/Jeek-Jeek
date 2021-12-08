#include "user.hpp"

User::User(string _userName, string _displayName, string _password){
	userName = _userName;
	displayName = _displayName;
	password = _password;
}

void User::showJeekAfterSearching(){
	for(int i = 0; i < userJeeks.size(); i++){
		userJeeks[i]->printText();
	}
}

bool User::isFollower(string userName){
	for (int i = 0; i < followerUsers.size(); i++){
		if(followerUsers[i] == userName)
			return true;
	}
	return false;
}

void User::removeFollowerUsers(string userName){
	for(int i = 0; i < followerUsers.size(); i++){
		if(followerUsers[i] == userName)
			followerUsers.erase(followerUsers.begin()+(i-1));
	}
}

void User::removeFollowingUsers(string userName){
	for(int i = 0; i < followingUsers.size(); i++){
		if(followingUsers[i] == userName)
			followingUsers.erase(followingUsers.begin()+(i-1));
	}
}