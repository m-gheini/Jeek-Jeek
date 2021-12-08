#include "user.hpp"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

class Interface{
public :
	Interface();
	void intializeActiveJeek(int jeekId){ activeJeek = jeekId;}
	int getActiveJeek(){return activeJeek;}
	void signUp(string userName, string displayName, string password);
	void login(string userName, string password);
	void logout();
	User* searchUser(string userName);
	Jeek* searchJeek(int jeekId);
	void addJeek(Jeek* jeek){jeeks.push_back(jeek);}
	void addUser(User* user){users.push_back(user);}
	string getLoggedInUser(){ return loggedInUser;}
	string returnDisplayName(string userName);
	vector<User*> getUsers(){ return users;}
	vector<Jeek*> getJeeks(){ return jeeks;}
	void jeek();
	vector<Jeek*> search(string input);
	vector<Jeek*> searchByUserName(string userName);
	vector<Jeek*> searchByHashtag(string tag);
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
	class Exception : public std::exception {
	  public:
	    Exception() {}
	    Exception(const char *pStr) { pMessage = pStr; }
	    const char *getMessage();

	  private:
	    const char *pMessage;
	};

private :
	string loggedInUser; 
	int activeJeek;
	vector<User*> users;
	vector<Jeek*> jeeks;
};