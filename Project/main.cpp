#include <iostream>
#include "interface.hpp"

using namespace std;

int main(){
	Interface interface;
	string command;
	while(true){
		try{
			cin >> command;
			if(command == "signup")
				interface.signUp();
			if(command == "login")
				interface.login();
			if(command == "logout")
				interface.logout();
			if(command == "jeek")
				interface.jeek();	
			if(command == "showJeek")
				interface.showJeek();	
			if(command == "search")
				interface.search();
			if(command == "comment")
				interface.comment();	
			if(command == "reply")
				interface.reply();	
			if(command == "rejeek")
				interface.rejeek();
			if(command == "showComment")
				interface.showComment();
			if(command == "showReply")
				interface.showReply();
			if(command == "like")
				interface.like();
			if(command == "dislike")
				interface.dislike();
			if(command == "follow")
				interface.follow();
			if(command == "unfollow")
				interface.unfollow();
			if(command == "notifications")
				interface.showNotification();
		}catch (Interface::Exception expection) {
    		cerr << expection.getMessage() << endl;
    	}
 	}
}