#include "server.hpp"
#include <cstdlib> 
#include <ctime>   
#include <iostream>
#include <fstream>
#include "interface.hpp"
#include <sstream>

using namespace std;

string intToString(int id){
	string str;
	stringstream out;
	out << id;
	str = out.str();
	return str;
}

class RandomNumberHandler : public RequestHandler {
public:
  Response *callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<body style=\"text-align: center;\">";
    body += "<h1>AP HTTP</h1>";
    body += "<p>";
    body += "a random number in [1, 10] is: ";
    body += to_string(rand() % 10 + 1);
    body += "</p>";
    body += "<p>";
    body += "SeddionId: ";
    body += req->getSessionId();
    body += "</p>";
    body += "</body>";
    body += "</html>";
    res->setBody(body);
    return res;
  }
};

class NewHomePageHandler : public RequestHandler {
public:
	NewHomePageHandler(Interface* _interface){ interface = _interface;}
  Response *callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string loggedInUser = interface->getLoggedInUser();
    User* user = interface->searchUser(loggedInUser);
    vector<Jeek*>userJeeks = user->getUserJeeks();
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<style>";
    body += "input[type=text] {width: 250px;box-sizing: border-box;border: 2px solid #ccc;border-radius: 4px;font-size: 16px;";
    body += "background-color: white;background-image: url('searchicon.png');background-position: 10px 10px; ";
    body += "background-repeat: no-repeat;padding: 12px 20px 12px 40px;-webkit-transition: width 0.4s ease-in-out;";
    body += "transition: width 0.4s ease-in-out;text-align: center;margin: auto;}";
    body += "input[type=text]:focus {width: 80%;}";
    body += "#Downblank {padding: 32px;width: fit-content;color: white;background-color: white;}";
    body += "#Downblank1 {padding: 10px;width: fit-content;color: white;background-color: white;}";
    body += "button{background-color: lightblue; color: black;width: 10%; padding: 15px;margin: -25px 0px -50px 1300px;";
    body += "text-align: center;text-decoration: none;display: inline-block;font-size: 16px;float: right;";
    body += "box-shadow: 0 12px 16px 0 rgba(0,0,0,0.24), 0 17px 50px 0 rgba(0,0,0,0.19);}";
    body += "</style>";
    body += "<h1 style=\"padding: 30px; word-spacing: 1250px;background-color: lightgreen;";
    body += "font-family: Arial, Helvetica, sans-serif;font-weight: bold;\">";
    body += "JeekJeek Hi";
    body += "<b style=\"word-spacing:normal;color:lightblue;text-shadow: -1px 0 black, 0 1px black, 1px 0 black, 0 -1px black;\">";
    body += " ";
    body += interface->returnDisplayName(loggedInUser);
    body += "</b>";    
    body += "<a href=\"/login\"style=\"word-spacing:130px; text-decoration:none; color:black;\"> logout</a>";
    body += "</h1>";
  	body += "<form action=\"/search\" method=\"post\" style=\"text-align:center;\">";
  	body += "<input type=\"text\" name=\"search\" placeholder=\"Search by # or @\"></form> ";
  	body += "<h1 id=\"Downblank\"></h1>";
  	for(int i = userJeeks.size()-1 ; i >= 0  ; i--){
  		vector<string> hashtags = userJeeks[i]->getHashtags();
  		body += "<style>";
  		body += "div{background-color: white; padding: 45px; width: 520px;margin: auto;outline-style: outset;";
  		body +=	"outline-color: blue;outline-width: thick; width: 80%;";
  		body +=	"</style>";
  		body += "<div>";
  		body += "<b style=\"font-weight: bold\">@";
  		body += user->getUserName();
  		body += ": </b>";
  		body += userJeeks[i]->getText();
  		body += "<form action=\"/detail\" method=\"post\"><button name =\"detail\" type= \"submit\" value = \"";
  		body += intToString(userJeeks[i]->getJeekId());
  		body += "\"> More details </button></form>";
  		for(int j = 0 ; j < hashtags.size() ; j++){
  			body += "<b style=\"font-weight: normal\">#";
  			body += hashtags[j];
  			body += " </b>";
  		}
  		body += "</div>";
  		body += "<h1 id=\"Downblank1\"></h1>";
  	}
    body += "</html>";
    res->setBody(body);
    return res;
  }
private:
  Interface* interface;
};

class SearchResult : public RequestHandler {
public:
	SearchResult(Interface* _interface){ interface = _interface;}
  Response *callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string loggedInUser = interface->getLoggedInUser();
    string input = req->getBodyParam("search");
    vector<Jeek*>resultJeeks =  interface -> search(input);
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<style>";
    body += "input[type=text] {width: 250px;box-sizing: border-box;border: 2px solid #ccc;border-radius: 4px;font-size: 16px;";
    body += "background-color: white;background-image: url('searchicon.png');background-position: 10px 10px; ";
    body += "background-repeat: no-repeat;padding: 12px 20px 12px 40px;-webkit-transition: width 0.4s ease-in-out;";
    body += "transition: width 0.4s ease-in-out;text-align: center;margin: auto;}";
    body += "input[type=text]:focus {width: 80%;}";
    body += "#Downblank {padding: 32px;width: fit-content;color: white;background-color: white;}";
    body += "#Downblank1 {padding: 10px;width: fit-content;color: white;background-color: white;}";
    body += "button{background-color: lightblue; color: black;width: 10%; padding: 15px;margin: -25px 0px -50px 1300px;";
    body += "text-align: center;text-decoration: none;display: inline-block;font-size: 16px;float: right;";
    body += "box-shadow: 0 12px 16px 0 rgba(0,0,0,0.24), 0 17px 50px 0 rgba(0,0,0,0.19);}";
    body += "</style>";
    body += "<h1 style=\"padding: 30px; word-spacing: 1250px;background-color: lightgreen;";
    body += "font-family: Arial, Helvetica, sans-serif;font-weight: bold;\">";
    body += "JeekJeek Hi";
    body += "<b style=\"word-spacing:normal;color:lightblue;text-shadow: -1px 0 black, 0 1px black, 1px 0 black, 0 -1px black;\">";
    body += " ";
    body += interface->returnDisplayName(loggedInUser);
    body += "</b>";    
    body += "<a href=\"/login\"style=\"word-spacing:130px; text-decoration:none; color:black;\"> logout</a>";
    body += "</h1>";
  	body += "<form action=\"/search\" method=\"post\" style=\"text-align:center;\">";
  	body += "<input type=\"text\" name=\"search\" placeholder=\"Search by # or @\"></form> ";
  	body += "<h1 id=\"Downblank\"></h1>";
  	for(int i = resultJeeks.size()-1 ; i >= 0 ; i--){
  		vector<string> hashtags = resultJeeks[i]->getHashtags();
  		body += "<style>";
  		body += "div{background-color: white; padding: 45px; width: 520px;margin: auto;outline-style: outset;";
  		body +=	"outline-color: blue;outline-width: thick; width: 80%;}";
  		body +=	"</style>";
  		body += "<div>";
  		body += "<b style=\"font-weight: bold\">@";
  		body += resultJeeks[i]->getUserName();
  		body += ": </b>";
  		body += resultJeeks[i]->getText();
  		body += "<form action=\"/detail\" method=\"post\"><button name =\"detail\" type= \"submit\" value = \"";
  		body += intToString(resultJeeks[i]->getJeekId());
  		body += "\"> More detailes </button></form>";
  		for(int j = 0 ; j < hashtags.size() ; j++){
  			body += "<b style=\"font-weight: normal\">#";
  			body += hashtags[j];
  			body += " </b>";
  		}
  		body += "</div>";
  		body += "<h1 id=\"Downblank1\"></h1>";
  	}
    body += "</html>";
    res->setBody(body);
    return res;
  }
private:
  Interface* interface;
};

bool liked(Jeek* jeek, string username){
	if(jeek->containsUser(username))
		return true;
	return false;
}

class Details : public RequestHandler{
public:
Details(Interface* _interface){ interface = _interface;}
  Response *callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string loggedInUser = interface->getLoggedInUser();
    string input = req->getBodyParam("detail");
    int id = atoi(input.c_str());
    interface->intializeActiveJeek(id);
    vector<Jeek*> jeeks = interface->getJeeks();
    cout<<"SIZE>>>"<<jeeks.size()<<endl;
    vector<string> hashtags = jeeks[id]->getHashtags();
    vector<string> mentioned = jeeks[id]->getMentionedUsers();
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<style>";
    body += "input[type=text] {width: 250px;box-sizing: border-box;border: 2px solid #ccc;border-radius: 4px;font-size: 16px;";
    body += "background-color: white;background-image: url('searchicon.png');background-position: 10px 10px; ";
    body += "background-repeat: no-repeat;padding: 12px 20px 12px 40px;-webkit-transition: width 0.4s ease-in-out;";
    body += "transition: width 0.4s ease-in-out;text-align: center;margin: auto;}";
    body += "input[type=text]:focus {width: 80%;}";
    body += "#Downblank {padding: 32px;width: fit-content;color: white;background-color: white;}";
    body += "#Downblank1 {padding: 10px;width: fit-content;color: white;background-color: white;}";
    body += "button{background-color: lightblue; color: black;width: 10%; padding: 5px;";
    body += "text-align: center;text-decoration: none;display: inline-block;font-size: 16px;";
    body += "box-shadow: 0 12px 16px 0 rgba(0,0,0,0.24), 0 17px 50px 0 rgba(0,0,0,0.19);}";
    body += "</style>";
    body += "<h1 style=\"padding: 30px; word-spacing: 1250px;background-color: lightgreen;";
    body += "font-family: Arial, Helvetica, sans-serif;font-weight: bold;\">";
    body += "JeekJeek Hi";
    body += "<b style=\"word-spacing:normal;color:lightblue;text-shadow: -1px 0 black, 0 1px black, 1px 0 black, 0 -1px black;\">";
    body += " ";
    body += interface->returnDisplayName(loggedInUser);
    body += "</b>";    
    body += "<a href=\"/login\"style=\"word-spacing:130px; text-decoration:none; color:black;\"> logout</a>";
    body += "</h1>";
  	body += "<h1 id=\"Downblank\"></h1>";
  	body += "<h1 style=\"font-weight: bold; text-align: center; padding: 30px; margin : auto;\"> Details</h1>";
  	body += "<br />";
  	body += "<style>";
  	body += "div{background-color: white; padding: 45px; width: 520px;margin: auto;outline-style: outset;";
  	body +=	"outline-color: blue;outline-width: thick; width: 80%;}";
  	body += "#username{background-color: white;color: black;width: 300px;padding: 15px;}";
  	body +=	"</style>";
  	body += "<div>";
  	body += "<div id=\"username\" style=\"text-align: center;\"> @ ";
  	body += jeeks[id]->getUserName();
  	body += "</div>";
  	body += jeeks[id]->getText();
  	body += "<br />";
  	for(int j = 0 ; j < hashtags.size() ; j++){
  		body += "<b style=\"font-weight: normal\">#";
  		body += hashtags[j];
  	}
  	body += "<br />";
  	for(int i = 0 ; i < mentioned.size() ; i++){
  		body += "<b style=\"font-weight: normal\">@";
  		body += mentioned[i];
  		body += " </b>";
  	}
  	body += "<br />";
  	body += "<p>#Likes :     ";
  	string likes = intToString(jeeks[id]->numberOfLikes());
  	body += likes;
  	body +=	"                  ";
  	body += "#rejeeks  :       ";
  	string rejeeks = intToString(jeeks[id]->getRejeekCount());
  	body += rejeeks;
  	body += "</p>";
  	body += "<br />";
  	if(liked(jeeks[id], loggedInUser)){
  		body += "<form action=\"/dislike\" method=\"post\">";
  		body += "<input type= \"image\" src=\"/like_icon\" style=\"width:30px;\"></input></form>";
  	}
  	else{
  		body += "<form action=\"/like\" method=\"post\">";
  		body += "<input type= \"image\" src=\"/dislike_icon\" style=\"width:30px;\"></input></form>";
  	}
  	body += "<br />";
  	body += "<form action=\"/rejeek\" method=\"post\"><button name =\"rejeek\" type= \"submit\"> Rejeek </button></form>";
  	body += "<br />";
    body += "</html>";
    res->setBody(body);
    return res;
  }
private:
  Interface* interface;
};

class LikeHandler : public RequestHandler {
public:
	LikeHandler(Interface* _interface){ interface = _interface;}
  Response *callback(Request *req) {
  	 Response *res = new Response;
    int id = interface->getActiveJeek();
    vector<Jeek*> jeeks = interface->getJeeks();
    string loggedInUser = interface->getLoggedInUser();
    vector<string> hashtags = jeeks[id]->getHashtags();
    vector<string> mentioned = jeeks[id]->getMentionedUsers();
    jeeks[id]->fillUsersWhoLiked(loggedInUser);
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<style>";
    body += "input[type=text] {width: 250px;box-sizing: border-box;border: 2px solid #ccc;border-radius: 4px;font-size: 16px;";
    body += "background-color: white;background-image: url('searchicon.png');background-position: 10px 10px; ";
    body += "background-repeat: no-repeat;padding: 12px 20px 12px 40px;-webkit-transition: width 0.4s ease-in-out;";
    body += "transition: width 0.4s ease-in-out;text-align: center;margin: auto;}";
    body += "input[type=text]:focus {width: 80%;}";
    body += "#Downblank {padding: 32px;width: fit-content;color: white;background-color: white;}";
    body += "#Downblank1 {padding: 10px;width: fit-content;color: white;background-color: white;}";
    body += "button{background-color: lightblue; color: black;width: 10%; padding: 5px;";
    body += "text-align: center;text-decoration: none;display: inline-block;font-size: 16px;";
    body += "box-shadow: 0 12px 16px 0 rgba(0,0,0,0.24), 0 17px 50px 0 rgba(0,0,0,0.19);}";
    body += "</style>";
    body += "<h1 style=\"padding: 30px; word-spacing: 1250px;background-color: lightgreen;";
    body += "font-family: Arial, Helvetica, sans-serif;font-weight: bold;\">";
    body += "JeekJeek Hi";
    body += "<b style=\"word-spacing:normal;color:lightblue;text-shadow: -1px 0 black, 0 1px black, 1px 0 black, 0 -1px black;\">";
    body += " ";
    body += interface->returnDisplayName(loggedInUser);
    body += "</b>";    
    body += "<a href=\"/login\"style=\"word-spacing:130px; text-decoration:none; color:black;\"> logout</a>";
    body += "</h1>";
  	body += "<h1 id=\"Downblank\"></h1>";
  	body += "<h1 style=\"font-weight: bold; text-align: center; padding: 30px; margin : auto;\"> Details</h1>";
  	body += "<br />";
  	body += "<style>";
  	body += "div{background-color: white; padding: 45px; width: 520px;margin: auto;outline-style: outset;";
  	body +=	"outline-color: blue;outline-width: thick; width: 80%;}";
  	body += "#username{background-color: white;color: black;width: 300px;padding: 15px;}";
  	body +=	"</style>";
  	body += "<div>";
  	body += "<div id=\"username\" style=\"text-align: center;\"> @ ";
  	body += jeeks[id]->getUserName();
  	body += "</div>";
  	body += jeeks[id]->getText();
  	body += "<br />";
  	for(int j = 0 ; j < hashtags.size() ; j++){
  		body += "<b style=\"font-weight: normal\">#";
  		body += hashtags[j];
  		body += " </b>";
  	}
  	body += "<br />";
  	for(int i = 0 ; i < mentioned.size() ; i++){
  		body += "<b style=\"font-weight: normal\">@";
  		body += mentioned[i];
  		body += " </b>";
  	}
  	body += "<br />";
  	body += "<p>#Likes :     ";
  	string likes = intToString(jeeks[id]->numberOfLikes());
  	body += likes;
  	body +=	"                  ";
  	body += "#rejeeks  :       ";
  	string rejeeks = intToString(jeeks[id]->getRejeekCount());
  	body += rejeeks;
  	body += "</p>";
  	body += "<br />";
  	body += "<form action=\"/dislike\" method=\"post\">";
  	body += "<input type= \"image\" src=\"/like_icon\" style=\"width:30px;\"></input></form>";
  	body += "<br />";
  	body += "<form action=\"/rejeek\" method=\"post\"><button name =\"rejeek\" type= \"submit\"> Rejeek </button></form>";
  	body += "<br />";
    body += "</html>";
    res->setHeader("Content-Type", "text/html");
    res->setBody(body);
    return res;
  }
private:
	Interface* interface;
};

class DisLikeHandler : public RequestHandler{
public:
	DisLikeHandler(Interface* _interface){ interface = _interface;}
  Response *callback(Request *req) {
  	 Response *res = new Response;
    int id = interface->getActiveJeek();
    vector<Jeek*> jeeks = interface->getJeeks();
    string loggedInUser = interface->getLoggedInUser();
    vector<string> hashtags = jeeks[id]->getHashtags();
    vector<string> mentioned = jeeks[id]->getMentionedUsers();
    jeeks[id]->removeUserFromLikeList(loggedInUser);
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<style>";
    body += "input[type=text] {width: 250px;box-sizing: border-box;border: 2px solid #ccc;border-radius: 4px;font-size: 16px;";
    body += "background-color: white;background-image: url('searchicon.png');background-position: 10px 10px; ";
    body += "background-repeat: no-repeat;padding: 12px 20px 12px 40px;-webkit-transition: width 0.4s ease-in-out;";
    body += "transition: width 0.4s ease-in-out;text-align: center;margin: auto;}";
    body += "input[type=text]:focus {width: 80%;}";
    body += "#Downblank {padding: 32px;width: fit-content;color: white;background-color: white;}";
    body += "#Downblank1 {padding: 10px;width: fit-content;color: white;background-color: white;}";
    body += "button{background-color: lightblue; color: black;width: 10%; padding: 5px;";
    body += "text-align: center;text-decoration: none;display: inline-block;font-size: 16px;";
    body += "box-shadow: 0 12px 16px 0 rgba(0,0,0,0.24), 0 17px 50px 0 rgba(0,0,0,0.19);}";
    body += "</style>";
    body += "<h1 style=\"padding: 30px; word-spacing: 1250px;background-color: lightgreen;";
    body += "font-family: Arial, Helvetica, sans-serif;font-weight: bold;\">";
    body += "JeekJeek Hi";
    body += "<b style=\"word-spacing:normal;color:lightblue;text-shadow: -1px 0 black, 0 1px black, 1px 0 black, 0 -1px black;\">";
    body += " ";
    body += interface->returnDisplayName(loggedInUser);
    body += "</b>";    
    body += "<a href=\"/login\"style=\"word-spacing:130px; text-decoration:none; color:black;\"> logout</a>";
    body += "</h1>";
  	body += "<h1 id=\"Downblank\"></h1>";
  	body += "<h1 style=\"font-weight: bold; text-align: center; padding: 30px; margin : auto;\"> Details</h1>";
  	body += "<br />";
  	body += "<style>";
  	body += "div{background-color: white; padding: 45px; width: 520px;margin: auto;outline-style: outset;";
  	body +=	"outline-color: blue;outline-width: thick; width: 80%;}";
  	body += "#username{background-color: white;color: black;width: 300px;padding: 15px;}";
  	body +=	"</style>";
  	body += "<div>";
  	body += "<div id=\"username\" style=\"text-align: center;\"> @ ";
  	body += jeeks[id]->getUserName();
  	body += "</div>";
  	body += jeeks[id]->getText();
  	body += "<br />";
  	for(int j = 0 ; j < hashtags.size() ; j++){
  		body += "<b style=\"font-weight: normal\">#";
  		body += hashtags[j];
  		body += " </b>";
  	}
  	body += "<br />";
  	for(int i = 0 ; i < mentioned.size() ; i++){
  		body += "<b style=\"font-weight: normal\">@";
  		body += mentioned[i];
  		body += " </b>";
  	}
  	body += "<br />";
  	body += "<p>#Likes :     ";
  	string likes = intToString(jeeks[id]->numberOfLikes());
  	body += likes;
  	body +=	"                  ";
  	body += "#rejeeks  :       ";
  	string rejeeks = intToString(jeeks[id]->getRejeekCount());
  	body += rejeeks;
  	body += "</p>";
  	body += "<br />";
  	body += "<form action=\"/like\" method=\"post\">";
  	body += "<input type= \"image\" src=\"/dislike_icon\" style=\"width:30px;\"></input></form>";
  	body += "<br />";
  	body += "<form action=\"/rejeek\" method=\"post\"><button name =\"rejeek\" type= \"submit\"> Rejeek </button></form>";
  	body += "<br />";
    body += "</html>";
    res->setHeader("Content-Type", "text/html");
    res->setBody(body);
    return res;
  }
private:
	Interface* interface;
};

class RejeekHandler : public RequestHandler{
public:
	RejeekHandler(Interface* _interface){ interface = _interface;}
  Response *callback(Request *req) {
  	 Response *res = new Response;
    int id = interface->getActiveJeek();
    vector<Jeek*> jeeks = interface->getJeeks();
    string loggedInUser = interface->getLoggedInUser();
    vector<string> hashtags = jeeks[id]->getHashtags();
    vector<string> mentioned = jeeks[id]->getMentionedUsers();
    User* user = interface->searchUser(loggedInUser);
    jeeks[id]->increaseRejeekCount();
    string rejeekText = "Rejeeked:" + jeeks[id]->getText();
    Jeek *rejeeked = new Jeek(jeeks.size()-1, user->getDisplayName(), loggedInUser,rejeekText, jeeks[id]->getHashtags(), jeeks[id]->getMentionedUsers(), 0);
    jeeks.push_back(rejeeked);
    user->fillUserJeeks(rejeeked);
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<style>";
    body += "input[type=text] {width: 250px;box-sizing: border-box;border: 2px solid #ccc;border-radius: 4px;font-size: 16px;";
    body += "background-color: white;background-image: url('searchicon.png');background-position: 10px 10px; ";
    body += "background-repeat: no-repeat;padding: 12px 20px 12px 40px;-webkit-transition: width 0.4s ease-in-out;";
    body += "transition: width 0.4s ease-in-out;text-align: center;margin: auto;}";
    body += "input[type=text]:focus {width: 80%;}";
    body += "#Downblank {padding: 32px;width: fit-content;color: white;background-color: white;}";
    body += "#Downblank1 {padding: 10px;width: fit-content;color: white;background-color: white;}";
    body += "</style>";
    body += "<h1 style=\"padding: 30px; word-spacing: 1250px;background-color: lightgreen;";
    body += "font-family: Arial, Helvetica, sans-serif;font-weight: bold;\">";
    body += "JeekJeek Hi";
    body += "<b style=\"word-spacing:normal;color:lightblue;text-shadow: -1px 0 black, 0 1px black, 1px 0 black, 0 -1px black;\">";
    body += " ";
    body += interface->returnDisplayName(loggedInUser);
    body += "</b>";    
    body += "<a href=\"/login\"style=\"word-spacing:130px; text-decoration:none; color:black;\"> logout</a>";
    body += "</h1>";
  	body += "<h1 id=\"Downblank\"></h1>";
  	body += "<h1 style=\"font-weight: bold; text-align: center; padding: 30px; margin : auto;\"> Details</h1>";
  	body += "<br />";
  	body += "<style>";
  	body += "div{background-color: white; padding: 45px; width: 520px;margin: auto;outline-style: outset;";
  	body +=	"outline-color: blue;outline-width: thick; width: 80%;}";
  	body += "#username{background-color: white;color: black;width: 300px;padding: 15px;}";
  	body +=	"</style>";
  	body += "<div>";
  	body += "<div id=\"username\"style=\"text-align: center;\"> @ ";
  	body += jeeks[id]->getUserName();
  	body += "</div>";
  	body += jeeks[id]->getText();
  	body += "<br />";
  	for(int j = 0 ; j < hashtags.size() ; j++){
  		body += "<b style=\"font-weight: normal\">#";
  		body += hashtags[j];
  		body += " </b>";
  	}
  	body += "<br />";
  	for(int i = 0 ; i < mentioned.size() ; i++){
  		body += "<b style=\"font-weight: normal\">@";
  		body += mentioned[i];
  		body += " </b>";
  	}
  	body += "<br />";
  	body += "<p>#Likes :     ";
  	string likes = intToString(jeeks[id]->numberOfLikes());
  	body += likes;
  	body +=	"                  ";
  	body += "#rejeeks  :       ";
  	string rejeeks = intToString(jeeks[id]->getRejeekCount());
  	body += rejeeks;
  	body += "</p>";
  	body += "<br />";
  	if(liked(jeeks[id], loggedInUser)){
  		body += "<form action=\"/dislike\" method=\"post\">";
  		body += "<input type= \"image\" src=\"/like_icon\" style=\"width:30px;\"></input></form>";
  	}
  	else{
  		body += "<form action=\"/like\" method=\"post\">";
  		body += "<input type= \"image\" src=\"/dislike_icon\" style=\"width:30px;\"></input></form>";
  	}
  	body += "<br />";
  	body += "<br />";
    body += "</html>";
    res->setHeader("Content-Type", "text/html");
    res->setBody(body);
    return res;
	}
private:
	Interface* interface;
};

class LoginHandler : public RequestHandler {
public:
	LoginHandler(Interface* _interface){ interface = _interface;}
  Response *callback(Request *req) {
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    try{
      interface->login(username, password);
      cout << "username: " << username << ",\tpassword: " << password << endl;
    }catch(Interface::Exception e){
      Response *res = new Response;
      res->setHeader("Content-Type", "text/html");
      res->setBody(readFile("static/errorlogin.html"));
      return res;
    }
    Response *res = Response::redirect("/");
    res->setSessionId("SID");
    return res;
  }
private:
  Interface* interface;
};

class SignupHandler : public RequestHandler {
public:
  SignupHandler(Interface* _interface){ interface = _interface;}
  Response *callback(Request *req) {
    Response *res = new Response;
    string username = req->getBodyParam("username");
    string displayName = req->getBodyParam("displayname");
    string password = req->getBodyParam("password");
    try{
      interface->signUp(username, displayName, password);
      cout << "Received Data: " << username << " - " << password << "@#@#@#@#@#@!" << endl;
    }catch(Interface::Exception e){
      res->setHeader("Content-Type", "text/html");
      res->setBody(readFile("static/errorsignup.html"));
      return res;
    }
    res->setHeader("Content-Type", "text/html");
    res->setBody(readFile("static/mylogin.html"));
    res->setSessionId("123");
    return res;
  }
private:
  Interface* interface;
};

int main(int argc, char **argv) {
	Interface* interface = new Interface;
  srand(time(NULL));
  User* a = new User("mgheini", "Mah", "0912");
  interface->addUser(a);
  vector<string>v1;
  v1.push_back("hey");
  vector<string>v2;
  Jeek* b = new Jeek(0 ,"Mah","mgheini","first Jeek!!!",v1, v2,0);
  a->fillUserJeeks(b);
  Jeek* d = new Jeek(1 ,"Mah","mgheini","friend is the best tv show ever",v1, v2, 0);
  a->fillUserJeeks(d);
  Jeek* c = new Jeek(2 ,"Mah","mgheini","finally done!!!!:D",v1, v2,0);
  a->fillUserJeeks(c);
  interface->addJeek(b);
  interface->addJeek(d);
  interface->addJeek(c);
  try {
    Server server(argc > 1 ? atoi(argv[1]) : 5000, "static/404.html");
    server.post("/", new LoginHandler(interface));
    server.post("/login", new SignupHandler(interface));
    server.get("/sign_up", new ShowPage("static/signup.html"));
    server.get("/signup_icon", new ShowImage("static/signup.png"));
    server.get("/login", new ShowPage("static/mylogin.html"));
    server.get("/user_icon", new ShowImage("static/user.png"));
    server.get("/rand", new RandomNumberHandler());
    server.get("/home.png", new ShowImage("static/home.png"));
    server.get("/", new NewHomePageHandler(interface));
    server.post("/search", new SearchResult(interface));
    server.post("/detail", new Details(interface));
    server.post("/like", new LikeHandler(interface));
    server.post("/dislike", new DisLikeHandler(interface));
    server.get("/dislike_icon", new ShowImage("static/dislike.png"));
    server.get("/like_icon", new ShowImage("static/like.png"));
    server.post("/rejeek", new RejeekHandler(interface));
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}