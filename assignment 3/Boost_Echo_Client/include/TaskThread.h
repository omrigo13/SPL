//
// Created by chardon@wincs.cs.bgu.ac.il on 13/01/2020.
//

#include "ConnectionHandler.h"
#include "Protocol.h"

#ifndef BOOST_ECHO_CLIENT_TASKTHREAD_H
#define BOOST_ECHO_CLIENT_TASKTHREAD_H

class TaskThread {
public:
    TaskThread(ConnectionHandler& handler, Protocol& protocol);
    void operator()();
private:
    ConnectionHandler& handler;
    Protocol protocol;
};

#endif //BOOST_ECHO_CLIENT_TASKTHREAD_H
