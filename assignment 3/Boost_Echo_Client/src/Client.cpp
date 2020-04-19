#include <stdlib.h>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <thread>
#include "../include/StompFrame.h"
#include "../include/ConnectionHandler.h"
#include "../include/ProcessInput.h"
#include "../include/Protocol.h"
#include "../include/TaskThread.h"

using namespace std;

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
int main (int argc, char *argv[]) {

    std::string userInput;
    UserBookClub user;
    ConnectionHandler *handler = nullptr;
    Protocol *protocol = nullptr;
    ProcessInput processor = ProcessInput(&user);//why not in the heap?
    while (1)
    {// first msg from user needs to be login in order to connect
        userInput = "";
        std::getline(std::cin, userInput);
        if (userInput.find("login") == std::string::npos)
            std::cout << "Error please login again"<<endl;
        else
        {
            std::pair<std::string, short> handlerdata = processor.get_host(userInput);
            handler = new ConnectionHandler(handlerdata.first, handlerdata.second);
            protocol = new Protocol(*handler, &user);
            if (handler->connect()) // will try to connect
            {
                handler->sendFrameAscii(processor.process(userInput),'\0'); //send login msg

                std::string serverResponse = "";
                handler->getLine(serverResponse); // server answer to login msg

                protocol->process(serverResponse);
                if (protocol->isLoggedIn()) {
                    //Login Succesful!!!
                    user.setName(userInput);
                    break;
                }
            }
        }
    }

    TaskThread task(*handler,*protocol);
    std::thread threadMsgFromServer(task);


    //from here we will get the next orders from the keyboard
    while (1) {
//        const short bufsize = 1024;
//        char buf[bufsize];
        userInput="";
        std::getline(std::cin, userInput);
        std::string msgToSend = processor.process(userInput);
        if(msgToSend.size()!=0) // if sin from keyboard is not correct
            handler->sendFrameAscii(msgToSend,'\0');
        if (userInput.find("logout") != std::string::npos)
            break;
    }
    threadMsgFromServer.join();


    delete handler;
    delete protocol;
    return 0;
}




