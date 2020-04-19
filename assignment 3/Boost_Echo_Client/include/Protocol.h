//
// Created by chardon@wincs.cs.bgu.ac.il on 12/01/2020.
//
#include "../include/ConnectionHandler.h"
#include "../include/StompFrame.h"
#include "../include/UserBookClub.h"

#ifndef BOOST_ECHO_CLIENT_PROTOCOL_H
#define BOOST_ECHO_CLIENT_PROTOCOL_H

class Protocol{
public:
    Protocol(ConnectionHandler &handler, UserBookClub* user);
    void process(std::string message);
    bool isLoggedIn();


private:
    ConnectionHandler& handler;
    bool logOut;
    bool login;
    UserBookClub* user;
    void connected();
    void errorMsg(std::string msg);
    void receipt(std::string msg);
    void messageProtocol(StompFrame frame);
    std::string fullBookName(std::vector<std::string> words, int start, int end);


};
#endif //BOOST_ECHO_CLIENT_PROTOCOL_H
//
//#ifndef BOOST_ECHO_CLIENT_PROTOCOL_H
//#define BOOST_ECHO_CLIENT_PROTOCOL_H
//
//#include "../include/UserBookClub.h"
//#include "ConnectionHandler.h"
//#include "UserBookClub.h"
//
//class Protocol {
//public:
//    Protocol(ConnectionHandler& handler, UserBookClub* user);
//    void processServer(std::string msg);
//    bool isLoggedOut();
//    bool isLoggedIn();
//private:
//    ConnectionHandler& handler;
//    std::vector<std::string> split_string_to_words_vector(const std::string& string);
//    bool loggedOut;
//    bool loggedIn;
//    UserBookClub* user;
//    void connected();
//    void error(std::string errMsg);
//    void reciept(const std::string& id);
//    void message(StompFrame frame);
//    void borrow(std::string msg,const std::string genre);
//    void lend(std::string genre,std::string book);
//    void status(std::string genre);
//    void getBack(std::string genre, std::string book);
//    void contains(std::string genre, std::string book);
//    std::string bookFromVector(std::vector<std::string> words,int start,int end);
//    std::string getBorrowedBookName(const std::vector<std::string> &words);
//
//};
//
//#endif //BOOST_ECHO_CLIENT_PROTOCOL_H