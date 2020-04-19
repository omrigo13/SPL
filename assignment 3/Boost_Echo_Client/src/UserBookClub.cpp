//
// Created by chardon@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "../include/UserBookClub.h"
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>

using namespace std;

UserBookClub::UserBookClub(): topicBooks(map<std::string,std::vector<std::string>>()),borrowedBooks(std::map<std::string,std::string>()),
                              topicSubid( std::map<std::string, int>()),booksToBorrow(),receipts(map<int, StompFrame*>()) , name(""), topicBooksLock(),borrowLock(),receiptLock(){};

UserBookClub::~UserBookClub() {
    for (auto it:receipts)
    {
        delete it.second;
    }
    receipts.clear();
    topicBooks.clear();
    booksToBorrow.clear();
    topicBooks.clear();
}
/*UserBookClub* UserBookClub::instance=0;
UserBookClub* UserBookClub::getInstance() {
    if(instance == 0)
        UserBookClub::instance = new UserBookClub();
    return instance;
}*/

void UserBookClub::addSubscribe(std::string topic, int subid) {
    std::lock_guard<std::mutex> lock(topicBooksLock); //lock topicBooks for other threads
    topicBooks.insert({topic,std::vector<std::string> ()});
    std::map<std::string,int>::iterator it;
    it = topicSubid.find(topic);
    if (it != topicSubid.end())
    {
        topicSubid[topic]=subid;
    }
    else
    {
        topicSubid.insert({topic,subid});
    }
}

void UserBookClub::addBook(std::string topic, std::string book) {
    std::lock_guard<std::mutex> lock(topicBooksLock); //lock topicBooks for other threads
    if(topicBooks.find(topic) != topicBooks.end())
        topicBooks[topic].push_back(book);
    else
    {
        topicBooks.insert({topic,std::vector<std::string> ()});
        topicBooks[topic].push_back(book);

    }
}

void UserBookClub::removeSubscribe(std::string topic) {
    topicBooks.erase(topic);
    topicSubid.erase(topic);
}

void UserBookClub::addReceipt(int id, StompFrame *frame) {
    std::lock_guard<std::mutex> lock(receiptLock);
    receipts.insert({id,frame});
}

int UserBookClub::getSubid(std::string topic) {
    return topicSubid[topic];
}

std::string UserBookClub::getName() {return name;}

void UserBookClub::addBookToWantBorrow(std::string book) {
    std::lock_guard<std::mutex> lock(borrowLock);
    booksToBorrow.push_back(book);
}

bool UserBookClub::removeBook(std::string genre, std::string book) {
    std::cout<<"remove book"<<endl;
    std::lock_guard<std::mutex> lock(topicBooksLock);
    std::vector<std::string>::iterator it;
    it = std::find (topicBooks[genre].begin(), topicBooks[genre].end(), book);
    if(it!=topicBooks[genre].end())
    {
        topicBooks[genre].erase(std::remove(topicBooks[genre].begin(),topicBooks[genre].end(),book),topicBooks[genre].end());
        return true;
    }
    return false;

}

std::string UserBookClub::getLoanerName(std::string book) {
    return borrowedBooks[book];
}

StompFrame &UserBookClub::getRecFrame(int id) {
    return *receipts[id];
}

void UserBookClub::removeReceipt(int id) {
    std::lock_guard<std::mutex> lock(receiptLock);

    delete(receipts[id]);
    receipts.erase(id);
}

bool UserBookClub::checkBookTopic(std::string genre, std::string book) {
    std::lock_guard<std::mutex> lock(topicBooksLock);
    for(auto it:topicBooks[genre])
    {
        if(it==book)
            return true;
    }
    return false;
}

bool UserBookClub::checkWantToBorrow(std::string book) {
  //  std::lock_guard<std::mutex> lock(borrowLock);
    for(auto it: booksToBorrow)
    {
        if(it==book)
            return true;
    }
    return false;
}

void UserBookClub::addBorrowBook(std::string genre, std::string book, std::string nameLoner) {
 //   std::lock_guard<std::mutex> lock(borrowLock);
    addBook(genre,book);
    borrowedBooks.insert({book,nameLoner});
    booksToBorrow.erase(std::remove(booksToBorrow.begin(),booksToBorrow.end(),book),booksToBorrow.end());
}

std::string UserBookClub::printBooks(std::string genre) {
    string out = name + ":";
    for(auto it:topicBooks[genre])
    {
        out += it + ",";
    }
    out = out.substr(0,out.size()-1);
    return out;
}

void UserBookClub::setName(std::string input) {
    std::istringstream iss(input);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    this->name=results[2];
}

bool UserBookClub::lendBook(std::string topic, std::string book) {
    std::cout<<"lend book methode"<<endl;
    bool isRemoved=this->removeBook(topic,book);
    return isRemoved;
}

std::string UserBookClub::getTopicFromSubId(int id) {
    for(auto it: topicSubid)
    {
        if(it.second==id)
            return it.first;
    }
    return "";
}