#include "interface.hpp"
#include <iostream>

using namespace std;

Interface::Interface(){

}

void Interface::signUp(string userName, string displayName, string password){
	for(int i=0;i<users.size();i++){
		if(userName == users[i]->getUserName()){
			throw Exception("Write error");
		}
	}
    User *user = new User(userName, displayName, password);
	users.push_back(user);
	for(int i=0;i<users.size();i++){
		cout << users[i]->getUserName();
	}
}

void Interface::login(string userName, string password){
	for (int i = 0; i < users.size(); i++){
		if(userName == users[i]->getUserName()){
			if(password == users[i]->getPassword()){
				loggedInUser = userName;
				return;
			}
		}
	}
	throw Exception("username or password is wrong!");
}

void Interface::logout(){
	if(!loggedInUser.empty())
		loggedInUser = "";
}

User* Interface::searchUser(string userName){
	for(int i=0 ; i<users.size() ; i++){
 		if(users[i]->getUserName() == userName){
 			return users[i];
 		}
 	}
 	return NULL;
}

Jeek* Interface::searchJeek(int jeekId){
	for(int i=0 ; i<jeeks.size() ; i++){
 		if(jeeks[i]->getJeekId() == jeekId){
 			return jeeks[i];
 		}
 	}
 	return NULL;
}

string Interface::returnDisplayName(string userName){
	User *user = searchUser(userName);
	string displayName = user->getDisplayName();
	return displayName;
}

void Interface::jeek(){
	if(loggedInUser.empty())
		return;
	User *user = searchUser(loggedInUser);
	string input, text, _user, hashtag;
	vector<string> mentioned;
	vector<string> tag;
	cin >> input;
	if(input == "text"){
		getline(cin,text);
	}
	if(input == "mention"){
		cin >> _user;
		mentioned.push_back(_user);
	}
	if(input == "tag"){
		cin >> hashtag;
		tag.push_back(hashtag);
	}
	if(input == "publish"){
		Jeek *jeek = new Jeek(jeeks.size()+1, user->getDisplayName(), loggedInUser,text, tag, mentioned, 0);
		jeeks.push_back(jeek);
		user->fillUserJeeks(jeek);
	}
	if(input == "abort"){
		return;
	}	
}

vector<Jeek*> Interface::search(string input){
	if(input[0] == '@'){
		input.erase(input.begin());
		return searchByUserName(input);
	}
	if(input[0] == '#'){
		input.erase(input.begin());
		return searchByHashtag(input);
	}
}

vector<Jeek*> Interface::searchByUserName(string userName){
	User *user = searchUser(userName);
	vector<Jeek*> result;
	for (int i = 0; i < jeeks.size(); ++i){
		if(jeeks[i]->getUserName() == userName){
			result.push_back(jeeks[i]);
		}
	}
	return result;
}

vector<Jeek*> Interface::searchByHashtag(string hashtag){
	vector<Jeek*> result;
	for(int i = 0 ; i<jeeks.size() ; i++){
		if(jeeks[i]->containsHashtag(hashtag)){
			result.push_back(jeeks[i]);
		}
	}
	return result;
}

void Interface::rejeek(){
	int jeekId;
	cin >> jeekId;
	Jeek *jeek = searchJeek(jeekId);
	jeek->increaseRejeekCount();
	string rejeekText = "Rejeeked:" + jeek->getText();
	User *user = searchUser(loggedInUser);
	Jeek *rejeeked = new Jeek(jeeks.size()+1, user->getDisplayName(), loggedInUser,rejeekText, jeek->getHashtags(), jeek->getMentionedUsers(), 0);
	jeeks.push_back(jeek);
	user->fillUserJeeks(jeek);
}

void Interface::showJeek(){
	int jeekId;
	cin >> jeekId;
	Jeek *jeek = searchJeek(jeekId);
	jeek->print();
}

void Interface::like(){
	int jeekId;
	Jeek *jeek = searchJeek(jeekId);
	jeek->fillUsersWhoLiked(loggedInUser);
}

void Interface::dislike(){
	int jeekId;
	cin >> jeekId;
	Jeek *jeek = searchJeek(jeekId);
	if(jeek->containsUser(loggedInUser))
		jeek->removeUserFromLikeList(loggedInUser);
	else
		return;
}

void Interface::follow(){
	string userName;
	cin >> userName;
	User *followingUser = searchUser(userName);
	User *followerUser = searchUser(loggedInUser);
	if(!(followerUser->isFollower(userName))){
		followingUser->fillFollowerUsers(loggedInUser);
		followerUser->fillFollowingUsers(userName);
	}
	else
		return;
}

void Interface::unfollow(){
	string userName;
	cin >> userName;
	User *unfollowingUser = searchUser(userName);
	User *unfollowerUser = searchUser(loggedInUser);
	if(unfollowerUser->isFollower(userName)){
		unfollowingUser->removeFollowerUsers(loggedInUser);
		unfollowerUser->removeFollowingUsers(userName);
	}
	else
		return;
}

const char *Interface::Exception::getMessage() { return pMessage; }