#ifndef WATCHABLE_H_
#define WATCHABLE_H_

#include <string>
#include <vector>


class Session;

class Watchable{
public:
    Watchable(long id, int length, const std::vector<std::string>& tags);
    Watchable(const Watchable&);
    //Watchable(const Watchable &other); // copy constructor


    virtual ~Watchable();


    virtual std::string toString() const = 0;
    virtual Watchable* getNextWatchable(Session&) const = 0;
    virtual std::string getName() =0;
    virtual std::string printWatch()=0;
    virtual int getEp()=0;
    virtual int getSes()=0;
    virtual long getNext()=0;
    long getId() const ;
    int getLength() const;
    std::vector<std::string> getTags() const;
    virtual Watchable* cloune( Watchable *other)=0;
   // std::vector<std::string> copyTags() const;


private:
    const long id;
    int length;
    std::vector<std::string> tags;
};

class Movie : public Watchable{
public:
    Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags);
    Movie(const Movie &other);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;
    virtual std::string getName();
    virtual std::string printWatch();
    virtual Watchable* cloune( Watchable *other);
    virtual int getEp();
    virtual int getSes();
    virtual long getNext();

private:
    std::string name;
};


class Episode: public Watchable{
public:
    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags);
    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags,long nextId);
    Episode(const Episode &other);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;
    virtual std::string getName();
    virtual std::string printWatch();

    long getNextEpisodeId() const;
    virtual Watchable* cloune( Watchable *other);
    virtual int getEp();
    virtual int getSes();
    virtual long getNext();
private:
    std::string seriesName;
    int season;
    int episode;
    long nextEpisodeId;
};

#endif
