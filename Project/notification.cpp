#include "notification.hpp"

Notification::Notification(string _fromPerson, vector<string> _forPerson, string _text){
	fromPerson = _fromPerson;
	forPerson = _forPerson;
	text = _text;
}