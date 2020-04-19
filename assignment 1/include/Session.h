#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"

class User;
class Watchable;

class Session{
public:
    Session(const std::string &configFilePath);
    Session( Session &other);//copyConstructor
    ~Session();
    Session(Session &&other);//move constructor
    Session& operator=( Session &other);//copyass
    Session& operator=(Session &&other);//move ass
    void start();
    std::vector<Watchable*> getContent();
    std::vector<BaseAction*> getActionsLog();
    std::unordered_map<std::string,User*> getMapUser();
    User * getActiveUser();
    void SetActiveUser(User *new_user);
    void setActionLog(BaseAction* action);
    void setMapUser(std::string name, User * user);
    void deleteFromMap(std::string str);
    std::vector<Watchable*> copyContent() const;
    std::vector<BaseAction*> copyActionLog() const;
    std::unordered_map<std::string,User*> copyUserMap() ;
private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;

};
#endif
