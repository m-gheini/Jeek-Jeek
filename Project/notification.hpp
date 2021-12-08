#include <iostream>
#include <vector>

using namespace std;

class Notification{
public :
	Notification(string _fromPerson, vector<string> _forPerson, string _text);
	vector<string> getForPerson(){return forPerson;}
	string getText(){return text;}
private :
	string fromPerson;
	vector<string> forPerson;
	string text;
};