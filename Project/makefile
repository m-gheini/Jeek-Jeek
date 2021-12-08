all: test run

test: main.o interface.o user.o jeek.o comment.o reply.o notification.o
	g++ main.o interface.o user.o jeek.o comment.o reply.o notification.o -o test

main.o: main.cpp
	g++ -c main.cpp

interface.o: interface.cpp
	g++ -c interface.cpp

user.o: user.cpp
	g++ -c user.cpp 

jeek.o: jeek.cpp
	g++ -c jeek.cpp

comment.o: comment.cpp
	g++ -c comment.cpp

reply.o: reply.cpp
	g++ -c reply.cpp

notification.o: notification.cpp
	g++ -c notification.cpp

clean:
	rm *.o

run:
	./test
