#include "reply.hpp"

Reply::Reply(string _writterOfReply, string _textOfReply, int _replyId){
	writterOfReply = _writterOfReply;
	textOfReply = _textOfReply;
	replyId = _replyId;
}

void Reply::print(){
	cout<<writterOfReply<<"\n"<<textOfReply<<endl;
	cout<<"Replies:"<<endl;
	for(int i = 0; i < repliesToReply.size(); i++){
		cout<<"replyId"<<repliesToReply[i]->getReplyId()<<endl;
	}
}