//
// Created by chardon@wincs.cs.bgu.ac.il on 25/11/2019.
//
#include "../include/Action.h"
#include <string>
#include <iostream>
#include "../include/Session.h"
#include "../include/User.h"
#include "../include/Watchable.h"
#include <iomanip>
#include <typeinfo>
#include <map>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////baseAction/////////////////////////////////////////////////////////////////////////////////////////////
BaseAction::BaseAction():errorMsg(""), status(PENDING),name(""),recAlgo(""),name2(""),id(0){};
BaseAction::BaseAction(const BaseAction &other):errorMsg(other.errorMsg),status(other.status),name(other.name),recAlgo(other.recAlgo),name2(other.name2),id(other.id){};

ActionStatus BaseAction::getStatus() const
{
    return status;
}

void BaseAction::setStatus(ActionStatus action)
{
    status=action;
}

string BaseAction::getName()
{
    return name;
}

string BaseAction::getName2() {return name2;}
string BaseAction ::getRecAlgo() {return recAlgo;}
void BaseAction::setName(string newname) {name=newname;}
void BaseAction::setName2(string newname2) {name2=newname2;}
void BaseAction::setRecAlgo(string algo) {recAlgo=algo;}
void BaseAction::setId(long idStr)
{
    id=idStr;
}
std::string BaseAction::getErrorMsg() const
{
    return errorMsg;
}
void BaseAction::setErrorMsg(std::string msg)
{
    errorMsg=msg;
}
void BaseAction ::complete()
{
    this->status=COMPLETED;
    errorMsg="";
}

void BaseAction::error(const std::string &errorMsg)
{
    this->status=ERROR;
    this->setErrorMsg(errorMsg);
}

long BaseAction::getId() {return id;}


std::string BaseAction::typeStatus( ActionStatus act) const {
    if(act==COMPLETED)
        return "COMPLETED";
    if(act==ERROR)
        return "ERROR";
    if(act==PENDING)
        return "PENDING";
    return nullptr;

}

BaseAction::~BaseAction() {

}


/////////////////////////////////////////////////////////////////////////////////createuser///////////////////////////////////////////////////////////////////////////////////////////////
std::string CreateUser::toString() const
{
    string str="createuser "+this->typeStatus(this->getStatus())+this->getErrorMsg();
    return str;
}

void CreateUser::act(Session &sess) {
    if (getRecAlgo() != "len" && getRecAlgo() != "rer" && getRecAlgo() != "gen") {
        this->error(": Invalid Recommended Algorithm");
        sess.setActionLog(this);
        cout << this->toString() << endl;
        return;
    }
    if (sess.getMapUser().count(this->getName()) > 0) {
        this->error(": User already in system");
        sess.setActionLog(this);
        cout << this->toString() << endl;
        return;
    }

    std::string str=getName();
    if (this->getRecAlgo() == "len")
    {
        LengthRecommenderUser *lenUser=new LengthRecommenderUser (str,"len");
        sess.setMapUser(getName(),lenUser);

    }
    if(this->getRecAlgo()=="rer")
    {
        RerunRecommenderUser *rerUser= new RerunRecommenderUser(str,"rer");
        sess.setMapUser(getName(),rerUser);


    }
    if(this->getRecAlgo()=="gen")
    {
        GenreRecommenderUser *genUser=new GenreRecommenderUser(str,"gen");
        sess.setMapUser(getName(),genUser);
     }

    this->complete();
    sess.setActionLog(this);
}

BaseAction* CreateUser::copyAction()
{
    BaseAction *create=new CreateUser();
    create->setName(this->getName());
    create->setStatus(this->getStatus());
    create->setId(this->getId());
    create->setName2(this->getName2());
    create->setErrorMsg(this->getErrorMsg());
    create->setRecAlgo(this->getRecAlgo());
    return create;
}
/////////////////////////////////////////////////////////////////////////////////////////changeuser///////////////////////////////////////////////////////////////////////////////////////////////
std::string ChangeActiveUser::toString() const
{
    string str="changeuser "+this->typeStatus(this->getStatus())+this->getErrorMsg();
    return str;

}
void ChangeActiveUser::act(Session &sess)
{
    if (sess.getMapUser().count(this->getName()) == 0)
    {
        this->error(": User is not in system");
        sess.setActionLog(this);
        cout << this->toString() << endl;
        return;
    }


    sess.SetActiveUser(sess.getMapUser()[getName()]);
    this->complete();
    sess.setActionLog(this);
}

BaseAction* ChangeActiveUser::copyAction()
{
    BaseAction *change=new ChangeActiveUser();
    change->setName(this->getName());
    change->setStatus(this->getStatus());
    change->setId(this->getId());
    change->setName2(this->getName2());
    change->setErrorMsg(this->getErrorMsg());
    change->setRecAlgo(this->getRecAlgo());
    return change;
}
///////////////////////////////////////////////////////////////////////////////////////////deleteuser//////////////////////////////////////////////////////////////////////////////////////
std::string DeleteUser::toString() const
{
    string str="deleteuser "+this->typeStatus(this->getStatus())+this->getErrorMsg();
    return str;
}
void DeleteUser::act(Session &sess)
{
    if (sess.getMapUser().count(this->getName()) == 0)
    {
        this->error(" Error: User is not in system");
        sess.setActionLog(this);
        cout << this->toString() << endl;
        return;
    }

    sess.deleteFromMap(getName());


    this->complete();
    sess.setActionLog(this);
}

BaseAction* DeleteUser::copyAction()
{
    BaseAction *del=new DeleteUser();
    del->setName(this->getName());
    del->setStatus(this->getStatus());
    del->setId(this->getId());
    del->setName2(this->getName2());
    del->setErrorMsg(this->getErrorMsg());
    del->setRecAlgo(this->getRecAlgo());
    return del;
}

////////////////////////////////////////////////////////////////////////////////////////duplicate user////////////////////////////////////////////////////////////////////////////////////////
std::string DuplicateUser::toString() const
{
    string str="dupuser "+this->typeStatus(this->getStatus())+this->getErrorMsg();
    return str;
}
void DuplicateUser::act(Session &sess)
{
    if (sess.getMapUser().count(this->getName()) == 0)
    {
        this->error(": Original user is not in system");
        sess.setActionLog(this);
        cout << this->toString() << endl;
        return;
    }
    if (sess.getMapUser().count(this->getName2()) > 0)
    {
        this->error(": The new user is already in the system");
        sess.setActionLog(this);
        cout << this->toString() << endl;
        return;
    }
    string algoName=sess.getMapUser()[getName()]->getalgoName();

    if (algoName== "len")
    {
        LengthRecommenderUser *lenUser= new LengthRecommenderUser(*sess.getMapUser()[getName()]);
        lenUser->setName(getName2());
        sess.setMapUser(getName2(),lenUser);
        lenUser= nullptr;
        delete lenUser;
    }

    if (algoName== "rer")
    {
        RerunRecommenderUser *rerUser= new RerunRecommenderUser(*sess.getMapUser()[getName()]);
        rerUser->setName(getName2());
        sess.setMapUser(getName2(),rerUser);
        rerUser= nullptr;
        delete rerUser;
    }

    if (algoName== "gen")
    {
        GenreRecommenderUser *genUser= new GenreRecommenderUser(*sess.getMapUser()[getName()]);
        genUser->setName(getName2());
        sess.setMapUser(getName2(),genUser);
        genUser = nullptr;
        delete genUser;
    }

    this->complete();
    sess.setActionLog(this);



}
BaseAction* DuplicateUser::copyAction()
{
    BaseAction *dup=new DuplicateUser();
    dup->setName(this->getName());
    dup->setStatus(this->getStatus());
    dup->setId(this->getId());
    dup->setName2(this->getName2());
    dup->setErrorMsg(this->getErrorMsg());
    dup->setRecAlgo(this->getRecAlgo());
    return dup;
}
/////////////////////////////////////////////////////////////////////////print content///////////////////////////////////////////////////////////////////////////////////////////////////
std::string PrintContentList::toString() const
{
    string str="dupuser "+this->typeStatus(this->getStatus())+this->getErrorMsg();
    return str;
}
void PrintContentList::act(Session &sess) {
    if (sess.getContent().size() == 0) {
        this->error(": Content list is empty");
        sess.setActionLog(this);
        cout << this->toString() << endl;
        return;
    }
    for(unsigned int i=0;i<sess.getContent().size();i++)
    {

        cout<<sess.getContent()[i]->toString()<<endl;
    }

    this->complete();
    sess.setActionLog(this);

}
BaseAction* PrintContentList::copyAction()
{
    BaseAction *content=new PrintContentList();
    content->setName(this->getName());
    content->setStatus(this->getStatus());
    content->setId(this->getId());
    content->setName2(this->getName2());
    content->setErrorMsg(this->getErrorMsg());
    content->setRecAlgo(this->getRecAlgo());
    return content;

}
/////////////////////////////////////////////////////////////////////////////////print history/////////////////////////////////////////////////////////////////////////////////////
std::string PrintWatchHistory::toString() const
{
    string str="watchhist "+this->typeStatus(this->getStatus())+this->getErrorMsg();
    return str;
}
void PrintWatchHistory::act(Session &sess)
{
    if (sess.getMapUser()[sess.getActiveUser()->getName()]->get_history().size()== 0) {
        this->error(": History list is empty");
        sess.setActionLog(this);
        cout << this->toString() << endl;
        return;
    }
    cout<<"Watch history for "<<sess.getActiveUser()->getName()<<endl;

    for(unsigned int i=0;i<sess.getMapUser()[sess.getActiveUser()->getName()]->get_history().size();i++)
    {
        cout<<i+1<<". "<<sess.getMapUser()[sess.getActiveUser()->getName()]->get_history().at(i)->printWatch()<<endl;
    }
    this->complete();
    sess.setActionLog(this);
}

BaseAction* PrintWatchHistory::copyAction()
{
    BaseAction *his=new PrintWatchHistory();
    his->setName(this->getName());
    his->setStatus(this->getStatus());
    his->setId(this->getId());
    his->setName2(this->getName2());
    his->setErrorMsg(this->getErrorMsg());
    his->setRecAlgo(this->getRecAlgo());
    return his;
}
////////////////////////////////////////////////////////////////////////////////watch///////////////////////////////////////////////////////////////////////////////////////////////////////
std::string Watch::toString() const
{
    string str = "watch "+this->typeStatus(this->getStatus())+getErrorMsg();
    return str;
}
void Watch::act(Session &sess)
{
    string inputUser;
    if (sess.getContent().size() == 0) {
        this->error(": Content list is empty");
        sess.setActionLog(this);
        cout << this->toString() << endl;
        return;
    }

    cout << "Watching " << sess.getContent().at(getId() - 1)->printWatch() << endl;
    sess.getActiveUser()->addToHistory(sess.getContent().at(getId() - 1)->cloune(sess.getContent().at(getId() - 1)));
    Watchable *nextWatch = sess.getContent().at(getId() - 1)->getNextWatchable(sess);
    if (nextWatch == nullptr) {
        nextWatch = sess.getActiveUser()->getRecommendation(sess);
        if (nextWatch == nullptr) {
            this->complete();
            sess.setActionLog(this);
            return;
        }
    }
    this->complete();
    sess.setActionLog(this);
    cout << "We recommend watching " << nextWatch->printWatch() << ", continue watching? [y/n]" << endl;
    std::cin >> inputUser;
    if (inputUser == "n") {
        return;
    } else {
        Watch *w = new Watch();
        w->setId(nextWatch->getId());
        w->act(sess);

    }
}

BaseAction* Watch::copyAction()
{
    BaseAction *watch=new Watch();
    watch->setName(this->getName());
    watch->setStatus(this->getStatus());
    watch->setId(this->getId());
    watch->setName2(this->getName2());
    watch->setErrorMsg(this->getErrorMsg());
    watch->setRecAlgo(this->getRecAlgo());
    return watch;
}


/////////////////////////////////////////////////////////////////////////////////////////////print log////////////////////////////////////////////////////////////////////////////////////
std::string PrintActionsLog::toString() const
{
    string str="log "+this->typeStatus(this->getStatus())+this->getErrorMsg();
    return str;
}

void PrintActionsLog::act(Session &sess)
{
    if(sess.getActionsLog().size()==0) {
        this->error(": ActionLog list is empty");
        sess.setActionLog(this);
        cout << this->toString() << endl;
        return;
    }
    for( int i=sess.getActionsLog().size()-1;i>=0;i--)
    {
        cout<<sess.getActionsLog()[i]->toString()<<endl;
    }
    this->complete();
    sess.setActionLog(this);

}

BaseAction* PrintActionsLog ::copyAction()
{
    BaseAction *log=new PrintActionsLog();
    log->setName(this->getName());
    log->setStatus(this->getStatus());
    log->setId(this->getId());
    log->setName2(this->getName2());
    log->setErrorMsg(this->getErrorMsg());
    log->setRecAlgo(this->getRecAlgo());
    return log;

}
/////////////////////////////////////////////////////////////Exit////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string Exit::toString() const
{
    string str= "Exit "+this->typeStatus(this->getStatus())+getErrorMsg();
    return str;

}
void Exit::act(Session &sess)
{
    this->complete();
    sess.setActionLog(this);

}
BaseAction* Exit::copyAction()
{
    BaseAction *ex=new Exit();
    ex->setName(this->getName());
    ex->setStatus(this->getStatus());
    ex->setId(this->getId());
    ex->setName2(this->getName2());
    ex->setErrorMsg(this->getErrorMsg());
    ex->setRecAlgo(this->getRecAlgo());
    return ex;
}
