//
// Created by chardon@wincs.cs.bgu.ac.il on 12/01/2020.
//
#include "../include/Protocol.h"
#include "../include/UserBookClub.h"
#include "../include/StompFrame.h"
#include "../include/ConnectionHandler.h"

using namespace std;

Protocol::Protocol(ConnectionHandler &handler1, UserBookClub* user1):handler(handler1),logOut(false),login(false), user(user1) {};

void Protocol::process(std::string message) {
    StompFrame frame=StompFrame();
    frame.parse(message);

    if(frame.getCommend()==CONNECTED)
        connected();
    else if(frame.getCommend()==ERROR)
        errorMsg(frame.getHeaders()["message"]);
    else if(frame.getCommend()==RECEIPT)
        receipt(frame.getHeaders()["receipt-id"]);
    else if(frame.getCommend()==MESSAGE)
        messageProtocol(frame);
}

void Protocol::connected() {
    std::cout<<"Login successful"<<endl;
    login=true;
}

void Protocol::errorMsg(std::string msg) {
    std::cout<<msg<<endl;
    login=false;
}

void Protocol::receipt(std::string msg) {
    int id=std::stoi(msg);
    StompFrame* frame=&user->getRecFrame(id);
    if(frame->getCommend()==SUBSCRIBE)
    {
        std::cout<<"Joined club "<<frame->getHeaders()["destination"]<<endl;
    }

    else if (frame->getCommend()==UNSUBSCRIBE) // fix exit
    {
        int subid=std::stoi(frame->getHeaders()["id"]);
        std::cout<<"Exited club "<< user->getTopicFromSubId(subid)<<endl;
    }

    else if(frame->getCommend()==DISCONNECT)
    {
        std::cout << "Disconnected"<<endl;
        login=false;
    }

    frame = nullptr;
    user->removeReceipt(id);
}

void Protocol::messageProtocol(StompFrame frame) {
    //std::cout<<frame.getHeaders()["destination"]<<":"<<frame.getBody()<<endl;
    std::istringstream iss(frame.getBody());
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    if ((results[0] == user->getName())|(results.size()==1)) {
        std::cout << frame.getHeaders().find("destination")->second << ":" << frame.getBody() << std::endl;
    }
    else if(results[1]=="wish")
    {//look for the book if yes send msg
        std::string book=fullBookName(results,4,results.size());
        if(user->checkBookTopic(frame.getHeaders()["destination"],book))
        {
            StompFrame send=StompFrame();
            send.setCommend(SEND);
            send.addHeader("destination",frame.getHeaders()["destination"]);
            send.setBody(user->getName()+" has "+ book);
            handler.sendFrameAscii(send.toString(),'\0');
        }
        std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
    }

    else if(results[1]=="has")
    {//check if book is in wish list
        std::string book;
        if(results[2]=="added")
            book=fullBookName(results,5,results.size());
        else
            book=fullBookName(results,2,results.size());

        if(user->checkWantToBorrow(book))
        {
            user->addBorrowBook(frame.getHeaders()["destination"],book,results[0]);
            StompFrame send=StompFrame();
            send.setCommend(SEND);
            send.addHeader("destination",frame.getHeaders()["destination"]);
            send.setBody("Taking "+ book+" from "+ results[0]);
            handler.sendFrameAscii(send.toString(),'\0');
        }
        std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
    }
    else if((results[0]=="Taking") & (results[results.size()-1]==user->getName()))//check 2 threads try to take the same book
    {
        std::string book=fullBookName(results,1,results.size()-2);
        user->lendBook(frame.getHeaders()["destination"],book);
        std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
    }
    else if( (results[0]=="Returning") & (results[results.size()-1]==user->getName()))
    {
      //  if(results[3] == user->getName())
        std::string book=fullBookName(results,1,results.size()-2);
        user->addBook(frame.getHeaders()["destination"], book);
        std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;

    }
    else if(results[1]=="status")
    {
        StompFrame send=StompFrame();
        send.setCommend(SEND);
        send.addHeader("destination",frame.getHeaders()["destination"]);
        send.setBody(user->printBooks(frame.getHeaders()["destination"]));
        handler.sendFrameAscii(send.toString(),'\0');
        std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
    }
    else {
            std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
    }
}

bool Protocol::isLoggedIn() {return login;}

std::string Protocol::fullBookName(std::vector<std::string> words, int start, int end) {
    std::string book;
    for(int i=start;i<end;i++)
    {
        book+=words[i]+" ";
    }
    return book.substr(0,book.size()-1);
}
//
//#include "../include/Protocol.h"
//
//Protocol::Protocol(ConnectionHandler &handler, UserBookClub* user1) : handler(handler), loggedOut(false), loggedIn(false), user(user1) {}
//
//void Protocol::processServer(std::string msg) {
//    StompFrame frame = StompFrame();
//    frame.parse(msg);
//    if (frame.getCommend() == CONNECTED) {
//        connected();
//    } else if (frame.getCommend() == ERROR) {
//        error(frame.getHeaders()["message"]);
//    } else if (frame.getCommend() == RECEIPT) {
//        reciept(frame.getHeaders()["receipt-id"]);
//    } else if (frame.getCommend() == MESSAGE) {
//        message(frame);
//    }
//
//}
//
//std::vector<std::string> Protocol::split_string_to_words_vector(const std::string &string) {
//    std::istringstream iss(string);
//    std::vector<std::string> words(std::istream_iterator<std::string>{iss},
//                                   std::istream_iterator<std::string>());
//    return words;
//}
//
//void Protocol::connected() {
//    loggedIn = true;
//    std::cout << "Login successful" << std::endl;
//
//}
//
//void Protocol::error(std::string errMsg) {
//    std::cout << errMsg;
//    loggedIn = false;
//}
//
//void Protocol::reciept(const std::string &id) {
//    StompFrame* frame = &user->getRecFrame(std::stoi(id));
//    if (frame->getCommend() == SUBSCRIBE)
//        std::cout << "Joined club " << frame->getHeaders()["destination"] << std::endl;
//    else if (frame->getCommend() == UNSUBSCRIBE)
//        std::cout << "Exited club " << frame->getHeaders()["destination"] << std::endl;
//    else if (frame->getCommend() == DISCONNECT) {
//        std::cout << "Disconnected";
//        loggedIn = false;
//    }
//    frame = nullptr;
//    user->removeReceipt(stoi(id));
//}
//
//void Protocol::message(StompFrame frame) {
//    std::vector<std::string> words = split_string_to_words_vector(frame.getBody());
//    if ((words[0] == user->getName())|(words.size()==1)) {
//        std::cout << frame.getHeaders().find("destination")->second << ":" << frame.getBody() << std::endl;
//    } else if (words[1] == "has") {
//        std::string book= getBorrowedBookName(words);
//        if (user->checkWantToBorrow(book)) {
//            borrow(frame.getBody(), frame.getHeaders()["destination"]);
//        }
//        std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
//    } else if (words[1] == "wish") {
//        std::string book=bookFromVector(words,4,words.size());
//        contains(frame.getHeaders()["destination"], book);
//        std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
//    } else if ((words[0] == "Taking") & (words[words.size()-1] == user->getName())) {
//        std::string book=bookFromVector(words,1,words.size()-2);
//        lend(frame.getHeaders()["destination"], book);
//        std::cout <<frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
//    } else if ((words[0] == "Returning") & (words[words.size()-1] == user->getName())) {
//        std::string book=bookFromVector(words,1,words.size()-2);
//        getBack(frame.getHeaders()["destination"], book);
//        std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
//    } else if (words[1] == "status") {
//        status(frame.getHeaders()["destination"]);
//        std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
//    } else {
//        std::cout << frame.getHeaders()["destination"] << ":" << frame.getBody() << std::endl;
//    }
//
//}
//
//void Protocol::borrow(std::string msg, const std::string genre) {
//    std::vector<std::string> words = split_string_to_words_vector(msg);
//    std::string book= getBorrowedBookName(words);
//    user->addBorrowBook(genre, book, words[0]);
//    StompFrame frame = StompFrame();
//    frame.setCommend(SEND);
//    frame.addHeader("destination", genre);
//    frame.setBody("Taking " + book + " from " + words[0]);
//    handler.sendFrameAscii(frame.toString(), '\0');
//}
//
//std::string Protocol::getBorrowedBookName(const std::vector<std::string> &words) {
//    std::string book;
//    if(words[2]=="added") {
//        book = this->bookFromVector(words, 5, words.size());
//    } else {
//        book = this->bookFromVector(words, 2, words.size());
//    }
//    return book;
//}
//
//void Protocol::lend(std::string genre, std::string book) {
//   user->removeBook(genre, book);
//}
//
//void Protocol::status(std::string genre) {
//    StompFrame frame = StompFrame();
//    frame.setCommend(SEND);
//    frame.addHeader("destination", genre);
//
//    frame.setBody(user->printBooks(genre));
//    handler.sendFrameAscii(frame.toString(), '\0');
//}
//
//void Protocol::getBack(std::string genre, std::string book) {
//    user->addBook(genre, book);
//}
//
//void Protocol::contains(std::string genre, std::string book) {
//    if (user->checkBookTopic(genre, book)) {
//        StompFrame frame = StompFrame();
//        frame.setCommend(SEND);
//        frame.addHeader("destination", genre);
//        frame.setBody(user->getName() + " has " + book);
//        handler.sendFrameAscii(frame.toString(), '\0');
//    }
//}
//
//
//std::string Protocol::bookFromVector(std::vector<std::string> words, int start, int end) {
//    std::string book;
//    for(int i=start;i<end;i++)
//        book+=words[i]+" ";
//    book=book.substr(0,book.size()-1);
//    return book;
//}
//
//bool Protocol::isLoggedOut(){return loggedOut;}
//bool Protocol::isLoggedIn(){ return loggedIn;}
