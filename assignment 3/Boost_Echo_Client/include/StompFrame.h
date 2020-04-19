//
// Created by chardon@wincs.cs.bgu.ac.il on 08/01/2020.
//
#include <map>
#ifndef BOOST_ECHO_CLIENT_STOMPFRAME_H
#define BOOST_ECHO_CLIENT_STOMPFRAME_H
using namespace std;

enum Commend{
    CONNECT,CONNECTED,MESSAGE,RECEIPT,ERROR,SEND,SUBSCRIBE,UNSUBSCRIBE,DISCONNECT
};

class StompFrame{
public:
    StompFrame();
//    void setCommend(Commend commend1);
    Commend getCommend() const;

    void setCommend(Commend commend);

     map<string, string> getHeaders() ;

    void setHeaders(const map<string, string> &headers);

    const string &getBody() const;

    void setBody(const string &body);

    void addHeader(string head, string msg);

    void parse(string message);

    std::string toString();

private:
    Commend commend;
    std::map<string,string> headers;
    std::string  body;
    std::map<string, Commend> stringToCommend;
    std::map<Commend, string> commendTostring;


};
#endif //BOOST_ECHO_CLIENT_STOMPFRAME_H
