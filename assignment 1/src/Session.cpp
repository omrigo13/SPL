//
// Created by chardon@wincs.cs.bgu.ac.il on 24/11/2019.
//
#include "../include/Watchable.h"
#include "../include/Session.h"
#include "../include/json.hpp"
#include "../include/Action.h"
#include "../include/User.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

///////////////////////////////////////////////////////////////////class Session/////////////////////////////////////////////////////////////////////////////////////////////////////////
//constructor
Session::Session(const std::string &configFilePath):content(),actionsLog(),userMap(),activeUser()
{
    using json = nlohmann::json;
    std::ifstream filecont(configFilePath);
    json watch;
    filecont >> watch;

    json movies=watch["movies"];
    json tvSeries=watch["tv_series"];

    vector<Watchable *> data;

    long count=1;
    for(unsigned int i=0;i<movies.size();i++)
    {
        string nameMovie =movies[i]["name"];
        int movieLen = movies[i]["length"];
        std::vector<std::string> movieTag;
        json tag=movies[i]["tags"];
        for(unsigned int k=0;k<tag.size();k++)
            movieTag.push_back(tag[k]);
        Watchable *watchable = new Movie (count,nameMovie,movieLen,movieTag);
        data.push_back(watchable);
        watchable= nullptr;
        delete (watchable);
        count++;
    }

    for(unsigned int i=0;i<tvSeries.size();i++) {
        string epName = tvSeries[i]["name"];
        int epLen = tvSeries[i]["episode_length"];
        std::vector<std::string> epTags;
        json tag = tvSeries[i]["tags"];
        for (unsigned int k = 0; k < tag.size(); k++)
            epTags.push_back(tag[k]);
        json seasons = tvSeries[i]["seasons"];
        for (unsigned int s = 0; s < seasons.size(); s++)
        {
            for( int e =0;e<seasons[s];e++)
            {
                Watchable *ep;


                if(s==seasons.size()-1)
                {
                    if(e+1==seasons[seasons.size()-1])
                    {
                        ep= new Episode (count,epName,epLen,s+1,e+1,epTags,0);
                        data.push_back(ep);

                        ep= nullptr;
                        delete ep;
                    }
                    else
                    {
                        ep= new Episode (count,epName,epLen,s+1,e+1,epTags,count+1);
                        data.push_back(ep);
                        ep= nullptr;
                        delete ep;
                    }

                }
                else
                {
                    ep= new Episode (count,epName,epLen,s+1,e+1,epTags,count+1);
                    data.push_back(ep);
                    ep= nullptr;
                    delete ep;
                }

                count++;

            }
        }

    }
    this->content=data;
    string def="default";
    LengthRecommenderUser *u=new LengthRecommenderUser (def);
    u->setalgoName("len");
    userMap.insert({"default", u});
    activeUser=u;


}

Session::Session( Session &other):content(other.copyContent()),actionsLog(other.copyActionLog()),userMap(other.copyUserMap()),activeUser(nullptr){
    activeUser = userMap.at(other.activeUser->getName());
   };


std::vector<Watchable *> Session::getContent() {return content;}
std::vector<BaseAction *> Session::getActionsLog() {return actionsLog;}
User * Session::getActiveUser() {return activeUser;}

Session::Session(Session &&other):content(other.content),actionsLog(other.actionsLog),userMap(other.userMap),activeUser(other.activeUser) {
    for (unsigned int i = 0; i < other.content.size(); i++)
    {
        content[i]=other.content[i];
        other.content[i]= nullptr;
    }
    for (unsigned int i = 0; i < other.actionsLog.size(); i++)
    {
        content[i]=other.content[i];
        other.actionsLog[i]= nullptr;
    }
    for (auto it= other.userMap.begin();it!=other.userMap.end();it++)
    {
        userMap.insert({it->first,it->second});
        it->second= nullptr;
    }
    other.content.clear();
    other.actionsLog.clear();
    other.userMap.clear();
    other.activeUser= nullptr;
}
Session& Session::operator=( Session &other){
    if (this != &other) {
        activeUser = nullptr;
        content.clear();
        actionsLog.clear();
        userMap.clear();

        actionsLog = other.copyActionLog();
        activeUser = other.activeUser->copyUser(*other.activeUser);
        userMap = other.copyUserMap();
        content = other.copyContent();
    }
    return *this;

}
Session& Session::operator=(Session &&other) {
    if (this != &other) {
        activeUser = nullptr;
        content.clear();
        actionsLog.clear();
        userMap.clear();
        for (unsigned int i = 0; i < other.content.size(); i++)
        {
            content[i]=other.content[i];
            other.content[i]= nullptr;
        }
        for (unsigned int i = 0; i < other.actionsLog.size(); i++)
        {
            content[i]=other.content[i];
            other.actionsLog[i]= nullptr;
        }
        for (auto it= other.userMap.begin();it!=other.userMap.end();it++)
        {
            userMap.insert({it->first,it->second});
            it->second= nullptr;
        }
        other.content.clear();
        other.actionsLog.clear();
        other.userMap.clear();
        other.activeUser= nullptr;
    }
    return *this;
}

void Session::deleteFromMap(std::string str)
{


    std::unordered_map<string, User*>::iterator it;
    it=userMap.find(str);
    delete it->second;
    userMap.erase(it);
}

Session::~Session()
{
    for(unsigned int i=0;i<content.size(); i++)
    {
        delete content[i];

    }
    for(unsigned int i=0;i<actionsLog.size(); i++)
    {
        delete actionsLog[i];
    }
    for(auto p: userMap)
    {
        delete p.second;
    }
    content.clear();
    actionsLog.clear();
    userMap.clear();
}
void Session::SetActiveUser(User *new_user) {activeUser=new_user;}
void Session::setActionLog(BaseAction *action)
{
    this->actionsLog.push_back(action);
}

std::unordered_map<std::string,User*> Session::getMapUser()
{
    return userMap;
}

void Session::setMapUser(std::string name, User *user)
{
    userMap.insert({name,user});
}


std::vector<BaseAction*> Session::copyActionLog() const {
    std::vector<BaseAction *> newLog;
    for (unsigned int i = 0; i < actionsLog.size(); i++) {
        newLog.push_back(this->actionsLog[i]->copyAction());
    }
    return newLog;
}

std::vector<Watchable*> Session::copyContent() const {
    std::vector<Watchable*> newContent;
    for(unsigned int i=0;i<content.size();i++)
        newContent.push_back(content[i]->cloune(content[i]));
    return newContent;
}
std::unordered_map<std::string,User*> Session::copyUserMap() {
    std::unordered_map<std::string,User*>newMap;
    for (auto const& x : getMapUser())
    {
        newMap.insert({x.first,x.second->copyUser(*x.second)});
    }
    return newMap;
}
///////////////////////////////////////////////////////////////////START//////////////////////////////////////////////////////////////////////////
void Session::start()
{
    cout<<"SPLFLIX is now on!"<<endl;
    BaseAction *action;
    string inUser;
    std::getline(cin, inUser);
    while(inUser!="exit")
    {

        std::istringstream iss(inUser);
        std::vector<std::string> results(std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>());
        if(results[0]=="createuser")
        {
            action=new CreateUser();
            action->setName(results[1]);
            action->setRecAlgo(results[2]);
            action->act(*this);
        }
        else if(results[0]=="changeuser")
        {
            action=new ChangeActiveUser();
            action->setName(results[1]);
            action->act(*this);
        }
        else if (results[0]=="deleteuser")
        {
            action=new DeleteUser();
            action->setName(results[1]);
            action->act(*this);
        }
        else if(results[0]=="dupuser")
        {
            action=new DuplicateUser;
            action->setName(results[1]);
            action->setName2(results[2]);
            action->act(*this);
        }
        else if(results[0]=="content")
        {
            action=new PrintContentList();
            action->act(*this);
        }
        else if(results[0]=="watchhist")
        {
            action=new PrintWatchHistory();
            action->act(*this);

        }
        else if(results[0]=="watch")
        {
            action=new Watch();
            string strid=results[1];
            action->setId(std::stol(strid));
            action->act(*this);
            std::cin.clear();
            std::cin.ignore();
        }
        else if(results[0]=="log")
        {
            action = new PrintActionsLog();
            action->act(*this);
        }

        std::getline(cin, inUser);

    }

    if(inUser=="exit")
    {
        action= new Exit();
        action->act(*this);

    }
}
