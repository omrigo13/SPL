//
// Created by chardon@wincs.cs.bgu.ac.il on 08/01/2020.
//
#include "../include/StompFrame.h"
#include <map>
#include <sstream>
#include <vector>
//#include <boost/asio/ip/tcp.hpp>
//#include <boost/algorithm/string.hpp>

using namespace std;
//using boost::asio::ip::tcp;

StompFrame::StompFrame():commend(),headers(std::map<string,string>()),body(""),stringToCommend(std::map<string,Commend>()),commendTostring(std::map<Commend,string>()){
    stringToCommend.insert({"CONNECTED",CONNECTED});
    stringToCommend.insert({"RECEIPT",RECEIPT});
    stringToCommend.insert({"MESSAGE",MESSAGE});
    stringToCommend.insert({"ERROR",ERROR});
    commendTostring.insert({CONNECT,"CONNECT"});
    commendTostring.insert({SUBSCRIBE,"SUBSCRIBE"});
    commendTostring.insert({UNSUBSCRIBE,"UNSUBSCRIBE"});
    commendTostring.insert({SEND,"SEND"});
    commendTostring.insert({DISCONNECT,"DISCONNECT"});

}

Commend StompFrame::getCommend() const {
    return commend;
}

void StompFrame::setCommend(Commend commend) {
    this->commend = commend;
}

 map<string, string> StompFrame::getHeaders()  {
    return headers;
}

void StompFrame::setHeaders(const map<string, string> &headers) {
    this->headers = headers;
}

const string &StompFrame::getBody() const {
    return body;
}

void StompFrame::addHeader(string head, string msg) {
    this->headers.insert({head,msg});
}

void StompFrame::parse(string message) {
    if(message=="")
        return;
    else {
        vector<string> msgLines;
        std::istringstream stream(message);
        std:: string line; // will get each line in message
        while(getline(stream,line)) // while the message still has lines
        {
            msgLines.push_back(line); // add the line to the vector
        }
        this->commend=stringToCommend[msgLines[0]];
        int i=1;
        while((unsigned) i<msgLines.size() && msgLines[i]!="") // brake the header from the message
        {
            int index=msgLines[i].find(':');
            addHeader(msgLines[i].substr(0,index),msgLines[i].substr(index+1,msgLines[i].size()));
            i++;
        }
        if((unsigned) i<msgLines.size()-1) // body
            body=msgLines[i+1];
        else
            body="";
        }

    }
    std::string StompFrame::toString() {
        string out;
        out=commendTostring[commend]+"\n";
        for(auto head:headers)
        {
            out=out+head.first+":"+head.second+"\n";
        }
        out=out+""+"\n";
        out+=body+"\n";
        return out;
}

void StompFrame::setBody(const string &body) {
    StompFrame::body = body;
};




