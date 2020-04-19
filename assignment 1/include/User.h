#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
class Watchable;
class Session;

class User{
public:
    User( std::string &name);
    User(const User &other);
    User(std::string name, std::string algoname);
    virtual Watchable* getRecommendation(Session& s) = 0;
    std::string getName() ;
    std::vector<Watchable*> get_history() const;
    void  addToHistory(Watchable *content);
    bool findElem(Watchable* elem);
    void setName(std::string newName);
    std::string getalgoName();
    void setalgoName(std::string other);
    std::vector<Watchable*> copyHistory() const;
    //void deleteHistory() const;
    virtual ~User();
    User(User &&other);
    User& operator=(const User &other);
    User& operator=(User &&other);
    virtual User* copyUser( User &other)=0;
protected:
    std::vector<Watchable*> history;
private:
    std::string name;
    std::string recAlgoName;

};


class LengthRecommenderUser : public User {
public:
    LengthRecommenderUser( std::string &name);
    LengthRecommenderUser( const User &other);
    LengthRecommenderUser( std::string &name,std::string algoName);
    LengthRecommenderUser( LengthRecommenderUser *other);
    virtual Watchable* getRecommendation(Session& s);
    virtual User* copyUser( User &other);
    virtual ~LengthRecommenderUser();

private:
};

class RerunRecommenderUser : public User {
public:
    RerunRecommenderUser( std::string& name);
    RerunRecommenderUser( const User  & other);
    RerunRecommenderUser( std::string &name,std::string algoName);
    RerunRecommenderUser( RerunRecommenderUser *other);
    virtual ~RerunRecommenderUser();
    virtual User* copyUser( User &other);

    virtual Watchable* getRecommendation(Session& s);
private:
    int lastIndexRec;
};

class GenreRecommenderUser : public User {
public:
    GenreRecommenderUser( std::string& name);
    GenreRecommenderUser( const User  & other);
    GenreRecommenderUser( std::string &name,std::string algoName);
    GenreRecommenderUser( GenreRecommenderUser *other);
    virtual ~GenreRecommenderUser();
    virtual User* copyUser( User &other);

    virtual Watchable* getRecommendation(Session& s);
    bool findTag(Watchable *elem, std::string tag);
private:
};

#endif
