#include "comment.hpp"


Comment::Comment(string _commentWritter, string _userName, string _textOfComment, int _commentId){
	commentWritter = _commentWritter;
	userName = _userName;
	textOfComment = _textOfComment;
	commentId = _commentId;
}

void Comment::print(){
	cout<<commentWritter<<"\n"<<textOfComment<<endl;
	cout<<"Replies:"<<endl;
	for(int i = 0; i < repliesOfComment.size(); i++){
		cout<<"replyId"<<repliesOfComment[i]->getReplyId()<<endl;
	}
}