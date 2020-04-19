//
// Created by chardon on 24/11/2019.
//
#include "../include/User.h"
#include "../include/Session.h"
#include "../include/Watchable.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
using namespace std;
User::User(std::string &name):history(),name(name),recAlgoName(""){};
User::User( const User  &other):history(other.copyHistory()),name(other.name),recAlgoName(other.recAlgoName){};

User::~User() {
    for(unsigned int i=0;i<history.size(); i++)
    {
        delete history[i];

    }
    history.clear();

}
User::User(std::string name, std::string algoname):history(), name(name),recAlgoName(algoname){};

bool User::findElem(Watchable *elem)
{
    vector<Watchable *>::iterator it;
    for(it =history.begin(); it != history.end(); it++)
    {
        if(elem==*it)
            return true;

    }
    return false;
}

void User::setName(std::string newName)
{
    name=newName;
}
std::string User::getName() {return name;}
std::vector<Watchable *> User::get_history() const { return history;}
void User::addToHistory(Watchable *content) {history.push_back(content);}

std::string User::getalgoName() {return recAlgoName;}

User::User(User &&other):history(other.history),name(other.name),recAlgoName(other.recAlgoName)
{
    for(auto it=other.history.begin();it!=other.history.end();it++)
    {
        delete *it;
    }
};
User& User::operator=(const User &other)
{
    if (this != &other)
    {
        std::vector<Watchable*> newHist=other.copyHistory();
        for(auto it=history.begin();it!=history.end();it++)
        {
            delete *it;
        }
        name=other.name;
        history=newHist;
        recAlgoName=other.recAlgoName;

    }
    return *this;
}

User& User::operator=(User &&other)
{
    if (this != &other)
    {
        for(auto it=history.begin();it!=history.end();it++)
        {
            delete *it;
        }
        for(unsigned int i=0;i<other.get_history().size();i++)
        {
            history[i]=other.get_history()[i];
        }
        name=other.name;
        recAlgoName=other.recAlgoName;
        for(auto it=other.history.begin();it!=other.history.end();it++)
        {
            delete *it;
        }
    }
    return *this;
}
std::vector<Watchable*> User::copyHistory() const {
    std::vector<Watchable *> newHistory;
    for(unsigned int i=0;i<history.size(); i++)
    {
        newHistory.push_back(history[i]->cloune(history[i]));
    }
    return newHistory;
}


void User::setalgoName(std::string other) {
    recAlgoName=other;

}


/////////////////////////////////////////////////////////////////////LengthRecommenderUser///////////////////////////////////////////////////////////////////////////////////////////////
LengthRecommenderUser::LengthRecommenderUser(std::string &name):User(name){};
LengthRecommenderUser::LengthRecommenderUser(std::string &name, std::string algoName):User(name,algoName){};
LengthRecommenderUser::LengthRecommenderUser(const  User &other) : User(other){};
LengthRecommenderUser::LengthRecommenderUser( LengthRecommenderUser *other):User(*other)
{
    this->getalgoName()=other->getalgoName();
}
LengthRecommenderUser::~LengthRecommenderUser() {

    for(unsigned int i=0;i<history.size(); i++)
    {
        delete history[i];

    }
    history.clear();
}
Watchable* LengthRecommenderUser::getRecommendation(Session &s)
{
    int avg=0;
    for(unsigned int i=0;i<history.size();i++)
    {

        avg+=history.at(i)->getLength();
    }
    avg=avg/history.size();

    vector<Watchable *> notWatch;

    for(unsigned int i=0;i<s.getContent().size();i++)
    {
        if(!findElem(s.getContent().at(i)))
            notWatch.push_back(s.getContent().at(i));

    }
    int smallest=abs(notWatch.at(0)->getLength()-avg);
    Watchable *temp;
    if(notWatch.size() != 0)
        temp= notWatch[0];
    else
        temp= nullptr;
    for(unsigned int i=0;i<notWatch.size();i++)
    {

        if(abs(notWatch.at(i)->getLength()-avg)<smallest)
        {
            smallest = abs(notWatch.at(i)->getLength() - avg);
            temp = notWatch.at(i);
        }
    }
    return temp;

}

User* LengthRecommenderUser::copyUser( User &other)
{
    User *len=new LengthRecommenderUser(other);
    return len;
}
//////////////////////////////////////////////////////////////////////////////RerunRecommenderUser//////////////////////////////////////////////////////////////////////////////////////
RerunRecommenderUser::RerunRecommenderUser(std::string &name):User(name),lastIndexRec(0) {};
RerunRecommenderUser::RerunRecommenderUser(const User &other):User( other),lastIndexRec(0){};
RerunRecommenderUser::RerunRecommenderUser(std::string &name, std::string algoName):User(name,algoName),lastIndexRec(0) {};
RerunRecommenderUser::RerunRecommenderUser( RerunRecommenderUser *other):User(*other),lastIndexRec(0)
{
    this->getalgoName()=other->getalgoName();
}
RerunRecommenderUser::~RerunRecommenderUser() {

    for(unsigned int i=0;i<history.size(); i++)
    {
        delete history[i];

    }
    history.clear();
}

Watchable* RerunRecommenderUser::getRecommendation(Session &s)
{
    if(history.size()==0)
        return nullptr;
    lastIndexRec=(lastIndexRec+1)%(history.size());
    return history.at(lastIndexRec);

}
User* RerunRecommenderUser::copyUser( User &other)
{
    User *rer=new RerunRecommenderUser(other);
    return rer;
}
//////////////////////////////////////////////////////////////////GenreRecommenderUser////////////////////////////////////////////////////////////////////////
GenreRecommenderUser::GenreRecommenderUser(std::string &name):User(name) {};
GenreRecommenderUser::GenreRecommenderUser(const User &other):User(other){};

GenreRecommenderUser::GenreRecommenderUser(std::string &name, std::string algoName):User(name,algoName) {};
GenreRecommenderUser::GenreRecommenderUser( GenreRecommenderUser *other):User(*other){};


bool GenreRecommenderUser::findTag(Watchable *elem,string tag)
{

    for(unsigned int i=0;i<elem->getTags().size();i++)
    {
        if(elem->getTags()[i]==tag)
            return true;
    }
    return false;
}
Watchable* GenreRecommenderUser::getRecommendation(Session &s)
{
    Watchable *data;
    map<string,int> mapTags;
    std::map<string,int>::iterator it2;
    for(unsigned int i=0;i<history.size();i++)
    {
        data = history.at(i);

        for(unsigned int j = 0; j<data->getTags().size(); j++)
        {
            it2=mapTags.find(data->getTags()[j]);
            if(it2==mapTags.end())
                mapTags.insert({data->getTags()[j],1});
            else
                mapTags[data->getTags()[j]]++;
        }
    }
    std::multimap<int,string>sortMap;
    for(auto const &kv:mapTags)
    {
        sortMap.insert(make_pair(kv.second,kv.first));
    }
    vector<Watchable *> notWatch;

    for(unsigned int i=0;i<s.getContent().size();i++)
    {
        if(!findElem(s.getContent().at(i)))
            notWatch.push_back(s.getContent().at(i));

    }

    for(auto i = sortMap.rbegin(); i != sortMap.rend(); ++i)
    {
        for(unsigned int j=0;j<notWatch.size();j++)
        {

            if(findTag(notWatch.at(j),i->second))
            {
                return notWatch.at(j);
            }
        }
    }
    return nullptr;
}

GenreRecommenderUser::~GenreRecommenderUser() {

    for(unsigned int i=0;i<history.size(); i++)
    {
        delete history[i];

    }
    history.clear();
}
User* GenreRecommenderUser::copyUser( User &other)
{
    User *gen=new GenreRecommenderUser(other);
    return gen;
}