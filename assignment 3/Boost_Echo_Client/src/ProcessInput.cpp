//
// Created by chardon@wincs.cs.bgu.ac.il on 12/01/2020.
//
#include <iterator>
#include <sstream>
#include <iostream>
#include "../include/ProcessInput.h"
#include "../include/StompFrame.h"

using namespace std;

ProcessInput::ProcessInput(UserBookClub* _user):subId_count(1),receiptId_count(1), user(_user) {};

std::pair<std::string, short> ProcessInput::get_host(std::string input) {
    int index=input.find(':');
    std::string host=input.substr(6,index-6); // the input of login contains host:port separate the input
    short port=std::stoi(input.substr(index+1,4));
    return std::make_pair(host,port);
}
std::string ProcessInput::process(string input) {
    std::istringstream iss(input);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    std::string output;
    if(results[0] == "login")
        output = login(results);
    else if (results[0] == "join") {
        if(results.size()!=2)
            return "";
        output = subscribe(results);
    }
    else if (results[0] == "exit") {
        if(results.size()!=2)
            return "";
        output = exit(results);
    }
    else if (results[0] == "add") {
        if(results.size()<3)
            return "";
        output = add(results);
    }
    else if (results[0] == "borrow") {
        if(results.size()<3)
            return "";
        output = borrow(results);
    }
    else if (results[0] == "return") {
        if(results.size()<3)
            return "";
        output = returnBook(results);
    }
    else if (results[0] == "status") {
        if(results.size()!=2)
            return "";
        output = status(results);
    }
    else if (results[0] == "logout") {
        if(results.size()!=1)
            return "";
        output = logout(results);
    }

    return output;
}

std::string ProcessInput::login(vector <string> &words) {
    StompFrame frame = StompFrame();
    frame.setCommend(CONNECT);
    frame.addHeader("accept-version","1.2");
    int index=words[1].find(':');
    frame.addHeader("host",words[1].substr(0,index));
    frame.addHeader("login",words[2]);
    frame.addHeader("passcode",words[3]);
    return frame.toString();
}

std::string ProcessInput::subscribe(vector <string> &words) { //add subscription to DB
    StompFrame *frame = new StompFrame();
    frame->setCommend(SUBSCRIBE);
    frame->addHeader("destination",words[1]);
    frame->addHeader("id",to_string(subId_count));
    frame->addHeader("receipt",to_string(receiptId_count));
    user->addSubscribe(words[1],subId_count);
    user->addReceipt(receiptId_count, frame);
    subId_count++;
    receiptId_count++;
    return frame->toString();
}

std::string ProcessInput::exit(vector <string> &words) { //add unsubscription to DB
    StompFrame* frame = new StompFrame();
    frame->setCommend(UNSUBSCRIBE);
    frame->addHeader("id",to_string(user->getSubid(words[1])));
    frame->addHeader("receipt", to_string(receiptId_count));
    user->addReceipt(receiptId_count,frame);
 //   user->removeSubscribe(words[1]);
    receiptId_count++;
    return frame->toString();
}

std::string ProcessInput::add(std::vector<std::string> &words) {
    StompFrame frame = StompFrame();
    frame.setCommend(SEND);
    frame.addHeader("destination", words[1]);
    std::string book=fullBookName(words,2,words.size());
    frame.setBody(user->getName() + " has added the book " + book);
    user->addBook(words[1],book);

    return frame.toString();
}

std::string ProcessInput::borrow(std::vector<std::string> &words) {
    StompFrame frame = StompFrame();
    frame.setCommend(SEND);
    frame.addHeader("destination", words[1]);
    std::string book=fullBookName(words,2,words.size());
    frame.setBody(user->getName() + " wish to borrow " + book);
    user->addBookToWantBorrow(book);

    return frame.toString();
}

std::string ProcessInput::returnBook(std::vector<std::string> &words) {
    std::string book=fullBookName(words,2,words.size());

    if(user->removeBook(words[1],book))
    {
        StompFrame frame= StompFrame();
        frame.setCommend(SEND);
        frame.addHeader("destination",words[1]);
        frame.setBody("Returning "+book+" to "+ user->getLoanerName(book));

        return frame.toString();
    }

    return "";

}

std::string ProcessInput::status(std::vector<std::string> &words) { // protocol for status book
    StompFrame frame=StompFrame();
    frame.setCommend(SEND);
    frame.addHeader("destination",words[1]);
    frame.setBody("book status");

    return frame.toString();
}

std::string ProcessInput::logout(std::vector<std::string> &words) { // check if to send unsubscribe to each topic
    StompFrame *frame= new StompFrame();
    frame->setCommend(DISCONNECT);
    frame->addHeader("receipt", to_string(receiptId_count));
    user->addReceipt(receiptId_count, frame);
    receiptId_count++;

    return frame->toString();
}

std::string ProcessInput::fullBookName(std::vector<std::string> words, int start, int end) { // retrieve full book name
    std::string book;
    for(int i=start;i<end;i++)
    {
        book+=words[i]+" ";
    }
    return book.substr(0,book.size()-1);
}