//
// Created by chardon@wincs.cs.bgu.ac.il on 19/11/2019.
//
#include "../include/Watchable.h"
#include "../include/User.h"
#include "../include/Session.h"
#include <iostream>
#include <vector>

using namespace std;

///////////////////////////////////////////////////////////class Watchable////////////////////////////////////////////////////////////////////////////////////
//Constructor
Watchable::Watchable(long _id, int _length, const std::vector <string> &_tags) :id(_id),length(_length),tags(_tags){};

////copy Constructor
Watchable::Watchable(const Watchable &other): id(other.id), length(other.length) ,tags() {
    std::vector<std::string> newTags;
    for(unsigned int i=0;i<other.tags.size();i++)
    {
        string temp=other.tags[i];
        newTags.push_back(temp);
    }
    tags=newTags;

}

///Destructor
Watchable::~Watchable() {};


long Watchable::getId() const {return id;}
int Watchable::getLength() const {return length;}

std::vector<std::string> Watchable::getTags() const {return tags;}





///////////////////////////////////////////////////////////////////////class Movie//////////////////////////////////////////////////////////////////
//Constructor
Movie::Movie(long id, const std::string &name, int length, const std::vector <string> &tags): Watchable(id, length,tags),name(name){};

//copy Constructor
Movie::Movie(const Movie &other): Watchable(other),name(other.name){};


std::string Movie::getName() {return name;}

std::string Movie::toString() const

{
    string str=std::to_string(this->getId())+". "+name+" "+ std::to_string(this->getLength())+"minutes "+"[";
    for(unsigned int i=0;i<this->getTags().size()-1;i++)
        str+=getTags()[i]+", ";

    str+=this->getTags().at(this->getTags().size()-1)+"]";
    return str;
}

Watchable* Movie::getNextWatchable(Session &) const {return nullptr;}

std::string Movie::printWatch()
{
    string str=" Watching "+name;
    return str;
}

Watchable* Movie::cloune(Watchable *other)
{
    string name=other->getName();
    long id=other->getId();
    int len=other->getLength();
    std::vector<std::string>newTags;
    for(unsigned int i=0;i<other->getTags().size();i++)
    {
        string temp=other->getTags()[i];
        newTags.push_back(temp);
    }
    Watchable * m=new Movie(id,name,len,newTags);
    return m;

}

int Movie::getEp() {return 0;}
long Movie::getNext() { return 0;}
int Movie::getSes() {return 0;}
/////////////////////////////////////////////////////////////////////////////////class Episode//////////////////////////////////////////////////////////////////////////////////////
//Constructor
Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,
                 const std::vector <string> &tags): Watchable(id,length,tags),seriesName(seriesName),season(season),episode(episode),nextEpisodeId(0){};

Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,
                 const std::vector<std::string> &tags, long nextId): Watchable(id,length,tags),seriesName(seriesName),season(season),episode(episode),nextEpisodeId(nextId) {};

Episode::Episode(const Episode &other):Watchable(other),seriesName(other.seriesName),season(other.season),episode(other.episode),nextEpisodeId(other.nextEpisodeId){};


std::string Episode::getName() {return seriesName;}
long Episode::getNextEpisodeId() const {return nextEpisodeId;}

int Episode::getEp()  {return episode;}
int Episode::getSes() {return season;}
long Episode::getNext()  {return nextEpisodeId;}


std::string Episode::toString() const
{
    string str=std::to_string(this->getId())+". "+seriesName+" S"+std::to_string(season)+"E"+std::to_string(episode)+" "+std::to_string(this->getLength())+" minutes "+"[";
    for(unsigned int i=0;i<this->getTags().size()-1;i++)
        str+=getTags()[i]+", ";
    str+=this->getTags().at(this->getTags().size()-1)+"]";
    return str;

}

Watchable* Episode::getNextWatchable(Session &s) const
{
    int index = this->getNextEpisodeId();
    if(index-1==0)
        return nullptr;
    else
        return s.getContent().at(index-1);
}

std::string Episode::printWatch()
{
    string str=seriesName+"S"+std::to_string(season)+"E"+std::to_string(episode);
    return str;
}

Watchable* Episode::cloune(Watchable *other)
{

    string name=other->getName();
    long id=other->getId();
    int len=other->getLength();
    std::vector<std::string>newTags;
    for(unsigned int i=0;i<other->getTags().size();i++)
    {
        string temp=other->getTags()[i];
        newTags.push_back(temp);
    }
    int ep=other->getEp();
    int ses=other->getSes();
    long next=other->getNext();
    Watchable * e=new Episode(id,name,len,ses,ep,newTags,next);
    return e;


}





