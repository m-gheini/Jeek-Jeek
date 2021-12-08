#include <iostream>
#include <vector>
#include "reply.hpp"

using namespace std;

class Comment{
public:
	Comment(string _commentWritter, string _userName,string _textOfComment, int _commentId);
	int getCommentId(){ return commentId;}
	string getUserName(){ return userName;}
	void fillRepliesOfComment(Reply* reply){ repliesOfComment.push_back(reply);}
	void print();
private:
	string commentWritter;
	string userName;
	string textOfComment;
	int commentId;
	vector<Reply*> repliesOfComment;
};