#include "interface.hpp"
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;

Interface::Interface(){

}

int jeekIdToInt(string jeekId){
	string number;
	for(int i = 6; i<jeekId.size(); i++){
		number.push_back(jeekId[i]);
	}
	int result = atoi(number.c_str());
	return result; 
}

int commentIdToInt(string commentId){
	string number;
	for(int i = 9; i<commentId.size(); i++){
		number.push_back(commentId[i]);
	}
	int result = atoi(number.c_str());
	return result; 
}

int replyIdToInt(string replyId){
	string number;
	for(int i = 7; i<replyId.size(); i++){
		number.push_back(replyId[i]);
	}
	int result = atoi(number.c_str());
	return result; 
}

string intToString(int id){
	string str;
	stringstream out;
	out << id;
	str = out.str();
	return str;
}

void Interface::signUp(){
	string userName, displayName, password;
	cin >> userName;
	cin >> displayName;
	cin >> password;
	for(int i=0;i<users.size();i++){
		if(userName == users[i].getUserName()){
			throw Exception("there is an user with this username already!");
		}
	}
	if(userName == "" || password == "")
		throw Exception("Enter userName AND password!");
    User *user = new User(userName, displayName, password);
	users.push_back(*user);
}

void Interface::login(){
	string userName, password;
	cin >> userName;
	cin >> password;
	for (int i = 0; i < users.size(); i++){
		if(userName == users[i].getUserName()){
			if(password == users[i].getPassword()){
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
	else
		throw Exception("you are NOT logged in!");
}

User* Interface::searchUser(string userName){
	for(int i=0 ; i<users.size() ; i++){
 		if(users[i].getUserName() == userName){
 			return &users[i];
 		}
 	}
 	throw Exception("There is no user with this username or you didn't logged in!");
}

Jeek* Interface::searchJeek(int jeekId){
	for(int i=0 ; i<jeeks.size() ; i++){
 		if(jeeks[i].getJeekId() == jeekId){
 			return &jeeks[i];
 		}
 	}
 	throw Exception("There is no jeek with this ID!");
}

Comment* Interface::searchComment(int commentId){
	for(int i=0 ; i<comments.size() ; i++){
 		if(comments[i].getCommentId() == commentId){
 			return &comments[i];
 		}
 	}
 	throw Exception("There is no comment with this ID!");
}

Reply* Interface::searchReply(int replyId){
	for(int i=0 ; i<replies.size() ; i++){
 		if(replies[i].getReplyId() == replyId){
 			return &replies[i];
 		}
 	}
 	throw Exception("There is no reply with this ID!");
 	return NULL;
}

void Interface::jeek(){
	if(loggedInUser.empty())
		throw Exception("you should login first!");
	User *user = searchUser(loggedInUser);
	string input, text, _user, hashtag;
	vector<string> mentioned;
	vector<string> tag;
	while(true){
		cin >> input;
		if(input == "text"){
			getline(cin,text);
			if(text.size()>141){
				throw Exception("you can only enter 140 characters!");
				return;
			}
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
			jeeks.push_back(*jeek);
			user->fillUserJeeks(jeek);
			Notification *notification = new Notification(loggedInUser, user->getFollower(), loggedInUser+" jeeked "+intToString(jeeks.size()));
			notifications.push_back(*notification);
			Notification *mentionNotification = new Notification(loggedInUser, mentioned, loggedInUser+" mentioned you in "+intToString(jeeks.size()));
			notifications.push_back(*mentionNotification);
			return;
		}
		if(input == "abort"){
			return;
		}
	}	
}

void Interface::search(){
	string input;
	cin >> input;
	if(input[0] == '@'){
		input.erase(input.begin());
		searchByUserName(input);
	}
	if(input[0] == '#'){
		input.erase(input.begin());
		searchByHashtag(input);
	}
}

void Interface::searchByUserName(string userName){
	User *user = searchUser(userName);
	user->showJeekAfterSearching();
}

void Interface::searchByHashtag(string hashtag){
	for(int i = 0 ; i<jeeks.size() ; i++){
		if(jeeks[i].containsHashtag(hashtag)){
			jeeks[i].printText();
		}
	}
}

void Interface::comment(){
	string input;
	cin >> input;
	int jeekId  = jeekIdToInt(input);
	string textOfComment;
	getline(cin,textOfComment);
	Jeek *jeek = searchJeek(jeekId);
	User *user = searchUser(loggedInUser);
	Comment *comment = new Comment(user->getDisplayName(), loggedInUser,textOfComment, comments.size()+1);
	comments.push_back(*comment);
	jeek->fillCommentsOfJeek(comment);
	vector<string> commented;
	commented.push_back(jeek->getUserName());
	Notification *notification = new Notification(loggedInUser, commented, loggedInUser+" commented on "+intToString(jeekId));
	notifications.push_back(*notification);
}

void Interface::reply(){
	string input;
	cin >> input;
	int commentId  = commentIdToInt(input);
	string textOfReply;
	getline(cin,textOfReply);
	User *user = searchUser(loggedInUser);
	Comment *comment = searchComment(commentId);
	Reply *reply = new Reply(user->getDisplayName(), textOfReply, replies.size()+1);
	replies.push_back(*reply);
	comment->fillRepliesOfComment(reply);
	vector<string> replied;
	replied.push_back(comment->getUserName());
	Notification *notification = new Notification(loggedInUser, replied, loggedInUser+" replied "+intToString(commentId));
	notifications.push_back(*notification);
}

void Interface::replyToReply(){
	string input;
	cin >> input;
	int replyId  = replyIdToInt(input);
	string textOfReply;
	getline(cin,textOfReply);
	User *user = searchUser(loggedInUser);
	Reply *reply = searchReply(replyId);
	Reply *replyToReply = new Reply(user->getDisplayName(), textOfReply, replies.size()+1);
	replies.push_back(*replyToReply);
	reply->fillRepliesToReply(replyToReply);
}

void Interface::rejeek(){
	string input;
	cin >> input;
	int jeekId  = jeekIdToInt(input);
	Jeek *jeek = searchJeek(jeekId);
	jeek->increaseRejeekCount();
	string rejeekText = "Rejeeked:" + jeek->getText();
	User *user = searchUser(loggedInUser);
	Jeek *rejeeked = new Jeek(jeeks.size()+1, user->getDisplayName(), loggedInUser,rejeekText, jeek->getHashtags(), jeek->getMentionedUsers(), 0);
	jeeks.push_back(*rejeeked);
	user->fillUserJeeks(rejeeked);
	vector<string> rejeekedUser;
	rejeekedUser.push_back(jeek->getUserName());
	Notification *notification = new Notification(loggedInUser, rejeekedUser, loggedInUser+" rejeeked "+intToString(jeekId));
	notifications.push_back(*notification);
}

void Interface::showJeek(){
	string input;
	cin >> input;
	int jeekId  = jeekIdToInt(input);
	cout<< jeekId<<endl;
	Jeek *jeek = searchJeek(jeekId);
	jeek->print();
}

void Interface::showComment(){
	string input;
	cin >> input;
	int commentId  = commentIdToInt(input);
	Comment *comment = searchComment(commentId);
	comment->print(); 
}

void Interface::showReply(){
	string input;
	cin >> input;
	int replyId  = replyIdToInt(input);
	Reply *reply = searchReply(replyId);
	reply->print();
}

void Interface::like(){
	string input;
	cin >> input;
	int jeekId  = jeekIdToInt(input);
	Jeek *jeek = searchJeek(jeekId);
	if(!(jeek->containsUser(loggedInUser))){
		jeek->fillUsersWhoLiked(loggedInUser);
		vector<string> liked;
		liked.push_back(jeek->getUserName());
		Notification *notification = new Notification(loggedInUser, liked, loggedInUser+" liked "+intToString(jeekId));
		notifications.push_back(*notification);
	}
	else
		throw Exception("you liked this jeek before!");
}

void Interface::dislike(){
	string input;
	cin >> input;
	int jeekId  = jeekIdToInt(input);
	Jeek *jeek = searchJeek(jeekId);
	if(jeek->containsUser(loggedInUser)){
		jeek->removeUserFromLikeList(loggedInUser);
		vector<string> disliked;
		disliked.push_back(jeek->getUserName());
		Notification *notification = new Notification(loggedInUser, disliked, loggedInUser+" disliked "+intToString(jeekId));
		notifications.push_back(*notification);
	}
	else
		throw Exception("you didn't like this jeek before!");
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
		throw Exception("you followed this user before!");
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
		throw Exception("you didn't follow this user before!");
}

void Interface :: showNotification()
{
	if(loggedInUser == ""){
		throw Exception("you should login first!");
	}
	for (int i = 0; i < notifications.size(); ++i){
		for (int j = 0; j < notifications[i].getForPerson().size(); j++){
			if(notifications[i].getForPerson()[j] == loggedInUser){
				cout << notifications[i].getText() << endl;
			}
		}
	}
}

const char *Interface::Exception::getMessage() { return Message; }