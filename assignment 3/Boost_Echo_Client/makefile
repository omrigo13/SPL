CFLAGS:=-c -Wall -Weffc++ -g -std=c++11  -Iinclude -pthread
LDFLAGS:=-lboost_system -pthread


all: StompBookClubClient
	g++ -o bin/StompBookClubClient bin/ConnectionHandler.o bin/Client.o bin/ProcessInput.o bin/StompFrame.o bin/UserBookClub.o bin/TaskThread.o bin/Protocol.o $(LDFLAGS)

StompBookClubClient: bin/ConnectionHandler.o bin/Client.o bin/ProcessInput.o bin/StompFrame.o bin/UserBookClub.o bin/TaskThread.o bin/Protocol.o

bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/Client.o: src/Client.cpp
	g++ $(CFLAGS) -o bin/Client.o src/Client.cpp

bin/ProcessInput.o: src/ProcessInput.cpp
	g++ $(CFLAGS) -o bin/ProcessInput.o src/ProcessInput.cpp

bin/StompFrame.o: src/StompFrame.cpp
	g++ $(CFLAGS) -o bin/StompFrame.o src/StompFrame.cpp

bin/UserBookClub.o: src/UserBookClub.cpp
	g++ $(CFLAGS) -o bin/UserBookClub.o src/UserBookClub.cpp

bin/TaskThread.o: src/TaskThread.cpp
	g++ $(CFLAGS) -o bin/TaskThread.o src/TaskThread.cpp

bin/Protocol.o: src/Protocol.cpp
	g++ $(CFLAGS) -o bin/Protocol.o src/Protocol.cpp

.PHONY: clean
clean:
	rm -f bin/*
