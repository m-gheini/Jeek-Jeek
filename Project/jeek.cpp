#include "jeek.hpp"

Jeek::Jeek(int _jeekId, string _nameOfWritter, string _userName, string _text, vector<string> _hashtags, vector<string> _mentionedUsers, int _rejeekCount){
	jeekId = _jeekId;
	nameOfWritter = _nameOfWritter;
	userName = _userName;
	text = _text;
	hashtags = _hashtags;
	mentionedUsers = _mentionedUsers;
	rejeekCount = _rejeekCount;
}

void Jeek::printText(){
	cout<<"jeekId"<<jeekId<<" "<<nameOfWritter<<"\n"<<text<<endl;
}

bool Jeek::containsHashtag(string hashtag){
	if(find(hashtags.begin(), hashtags.end(), hashtag) != hashtags.end())
		return true;
	else
		return false;
}

void Jeek::print(){
	cout<<nameOfWritter<<"\n"<<text<<endl;
	for(int i = 0; i<hashtags.size(); i++){
		cout<<"#"<<hashtags[i]<<endl;
	}
	for(int j = 0; j<mentionedUsers.size(); j++){
		cout<<"@"<<mentionedUsers[j]<<endl;
	}
	cout<<"Likes "<<usersWhoLiked.size()<<endl;
	cout<<"Rejeeks "<<rejeekCount<<endl;
	cout<<"Comments:"<<endl;
	for(int i = 0; i<commentsOfJeek.size(); i++){
		cout<<"commentId"<<commentsOfJeek[i]->getCommentId()<<endl;
	}
}

bool Jeek::containsUser(string userName){
	for (int i = 0; i < usersWhoLiked.size(); i++){
		if(usersWhoLiked[i] == userName)
			return true;
	}
	return false;
}

void Jeek::removeUserFromLikeList(string userName){
	for(int i = 0; i < usersWhoLiked.size(); i++){
		if(usersWhoLiked[i] == userName)
			usersWhoLiked.erase(usersWhoLiked.begin()+(i));
	}
}