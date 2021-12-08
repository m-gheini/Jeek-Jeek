#include <iostream>
#include <vector>

using namespace std;

class Reply{
public:
	Reply(string _writterOfReply, string _textOfReply, int _replyId);
	int getReplyId(){ return replyId;}
	void fillRepliesToReply(Reply *reply){ repliesToReply.push_back(reply);}
	void print();
private:
	string writterOfReply;
	string textOfReply;
	int replyId;
	vector<Reply*>repliesToReply;
};