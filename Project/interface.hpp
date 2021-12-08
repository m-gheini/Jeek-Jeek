#include "user.hpp"
#include "notification.hpp"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

class Interface{
public :
	Interface();
	void signUp();
	void login();
	void logout();
	User* searchUser(string userName);
	Jeek* searchJeek(int jeekId);
	Comment* searchComment(int commentId);
	Reply* searchReply(int replyId);
	void jeek();
	void search();
	void searchByUserName(string);
	void searchByHashtag(string);
	void comment();
	void reply();
	void replyToReply(); 
	void rejeek();
	void showJeek();
	void showComment();
	void showReply();
	void like();
	void dislike();
	void follow();
	void unfollow();
	void showNotification();
	class Exception : public std::exception {
	  public:
	    Exception() {}
	    Exception(const char *String) { Message = String; }
	    const char *getMessage();

	  private:
	    const char *Message;
	};
private :
	string loggedInUser; 
	vector<User> users;
	vector<Jeek> jeeks;
	vector<Comment> comments;
	vector<Reply> replies;
	vector<Notification> notifications;
};