//
// Created by chardon@wincs.cs.bgu.ac.il on 13/01/2020.
//
#include "../include/TaskThread.h"
#include "../include/ConnectionHandler.h"
#include "../include/Protocol.h"

TaskThread::TaskThread(ConnectionHandler &handler1, Protocol &protocol1):handler(handler1),protocol(protocol1) {}
 // this class is for thread to run
void TaskThread::operator()() {
    std::string message;
    do
    {
        message="";
        handler.getFrameAscii(message,'\0');
        protocol.process(message);
        if(!protocol.isLoggedIn()) {
            break;
        }
    }while(1);
}