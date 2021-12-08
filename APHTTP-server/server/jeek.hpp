#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;

class User;

class Jeek{
public:
	Jeek(int _jeekId, string _nameOfWritter, string _userName,string _text, vector<string> _hashtags, vector<string> _mentionedUsers, int _rejeekCount);
	int getJeekId(){ return jeekId;}
	bool containsHashtag(string hashtag);
	void printText();
	void increaseRejeekCount(){ rejeekCount++ ;}
	string getText(){ return text;}
	string getUserName(){ return userName;}
	vector<string> getHashtags(){ return hashtags;}
	vector<string> getMentionedUsers(){ return mentionedUsers;}
	void print();
	void fillUsersWhoLiked(string userName){ usersWhoLiked.push_back(userName);}
	int numberOfLikes(){return usersWhoLiked.size();}
	int getRejeekCount(){return rejeekCount;}
	bool containsUser(string userName);
	void removeUserFromLikeList(string userName);
private:
	int jeekId;
	int rejeekCount;
	string nameOfWritter;
	string userName;
	string text;
	vector<string> hashtags;
	vector<string> mentionedUsers;
	vector<string> usersWhoLiked;
};