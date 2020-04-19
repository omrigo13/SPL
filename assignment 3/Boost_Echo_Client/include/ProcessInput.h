//
// Created by chardon@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_PROCESSINPUT_H
#define BOOST_ECHO_CLIENT_PROCESSINPUT_H

#include "UserBookClub.h"

class ProcessInput{
public:
    ProcessInput(UserBookClub* user);
    std::string process(std::string input);
    static std::pair<std::string, short > get_host(std::string input);

private:
    int subId_count;
    int receiptId_count;
    std::string login(std::vector<std::string>& words);
    std::string subscribe(std::vector<std::string>& words);
    std::string exit(std::vector<std::string>& words);
    std::string add(std::vector<std::string>& words);
    std::string borrow(std::vector<std::string>& words);
    std::string returnBook(std::vector<std::string>& words);
    std::string status(std::vector<std::string>& words);
    std::string logout(std::vector<std::string>& words);
    std::string fullBookName(std::vector<std::string> words, int start, int end);
    UserBookClub* user;

};
#endif //BOOST_ECHO_CLIENT_PROCESSINPUT_H
