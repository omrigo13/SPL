#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
using namespace std;
class Session;
class User;

enum ActionStatus{
    PENDING, COMPLETED, ERROR
};


class BaseAction{
public:
    BaseAction();
    BaseAction(const BaseAction &other);
    virtual ~BaseAction();
    ActionStatus getStatus() const;
    virtual void act(Session& sess)=0;
    virtual std::string toString() const=0;
    string getName();
    string getRecAlgo();
    string getName2();
    void setName(string newname);
    void setRecAlgo(string algo);
    void setName2(string newname2);
    void setStatus(ActionStatus action);
    void setErrorMsg(std::string msg);
    void setId(long idStr);
    long getId();
    std::string typeStatus( ActionStatus act) const;
    virtual BaseAction* copyAction()=0;

protected:
    void complete();
    void error(const std::string& errorMsg);
    std::string getErrorMsg() const;


private:
    std::string errorMsg;
    ActionStatus status;
    std::string name;
    std::string recAlgo;
    std::string name2;
    long id;
};

class CreateUser  : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copyAction();
};

class ChangeActiveUser : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copyAction();
};

class DeleteUser : public BaseAction {
public:
    virtual void act(Session & sess);
    virtual std::string toString() const;
    virtual BaseAction* copyAction();
};


class DuplicateUser : public BaseAction {
public:
    virtual void act(Session & sess);
    virtual std::string toString() const;
    virtual BaseAction* copyAction();
};

class PrintContentList : public BaseAction {
public:
    virtual void act (Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copyAction();
};

class PrintWatchHistory : public BaseAction {
public:
    virtual void act (Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copyAction();
};


class Watch : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copyAction();
};


class PrintActionsLog : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copyAction();

};

class Exit : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copyAction();

};
#endif
