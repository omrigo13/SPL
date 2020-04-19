//
// Created by chardon@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_USERBOOKCLUB_H
#define BOOST_ECHO_CLIENT_USERBOOKCLUB_H

#include <map>
#include <vector>
#include <mutex>
#include "StompFrame.h"

class UserBookClub{

public:
    UserBookClub();
    void addSubscribe(std::string topic, int subid);
    void removeSubscribe(std::string topic);
    void addBook(std::string topic, std::string book);
    //static UserBookClub* getInstance();
    void addReceipt(int id,StompFrame* frame);
    int getSubid(std::string topic);
    std::string getName();
    void addBookToWantBorrow(std::string book);
    bool removeBook(std::string genre, std::string book);
    std::string getLoanerName(std::string book);
    StompFrame &getRecFrame(int id);
    void removeReceipt(int id);
    bool checkBookTopic(std::string genre, std::string book);
    bool checkWantToBorrow(std::string book);
    void addBorrowBook(std::string genre, std::string book, std::string nameLoner);
    std::string printBooks(std::string genre);
    void setName(std::string new_name);
    ~UserBookClub();
    bool lendBook(std::string topic,std::string book);
    std::string getTopicFromSubId(int id);

private:
    //static UserBookClub* instance;
    std::map<std::string,std::vector<std::string>> topicBooks; // topics, list of books to each topic
    std::map<std::string,std::string> borrowedBooks; // book , name of loaner
    std::map<std::string, int> topicSubid;
    std::vector<std::string> booksToBorrow;
    std::map<int, StompFrame*> receipts;
    std::string name;
    std:: mutex topicBooksLock;
    std:: mutex borrowLock;
    std:: mutex receiptLock;
};

#endif //BOOST_ECHO_CLIENT_USERBOOKCLUB_H
