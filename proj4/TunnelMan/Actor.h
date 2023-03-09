#ifndef ACTOR_H_
#define ACTOR_H_

#include "GameConstants.h"
#include "GraphObject.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject {
public:
    Actor(int imageID, int startX, int startY, Direction dir = right,
          double size = 1.0, unsigned int depth = 0);
    virtual ~Actor();
    virtual void doSomething() = 0;
    StudentWorld* getWorld() const;
    void setWorld(StudentWorld* ptr);
    virtual std::string getType() = 0;
    virtual bool isLive() = 0;
    
private:
    StudentWorld* world;
};

class Earth : public Actor {
public:
    Earth(int startX, int startY);
    virtual ~Earth();
    virtual void doSomething();
    virtual std::string getType();
    virtual bool isLive();
private:
    bool life;
};

class TunnelMan : public Actor {
public:
    TunnelMan();
    virtual ~TunnelMan();
    virtual void doSomething();
    void annoy(int amount);
    int getHP();
    virtual std::string getType();
    virtual bool isLive();
    void pickOilUp();
    int getOil();
    int getWater();
    int getNuggets();
    int getSonar();
    
private:
    bool life;
    int hitPoints;
    int water;
    int sonarCharge;
    int nuggets;
    int oil;
};

class Boulder : public Actor {
public:
    Boulder(int startX, int startY);
    virtual ~Boulder();
    virtual void doSomething();
    void drop();
    virtual std::string getType();
    virtual bool isLive();
private:
    bool life;
    bool stable;
    int ticks;
    
};

class Goodies: public Actor {
public:
    Goodies(int imageID, int startX, int startY, Direction dir,
            double size, unsigned int depth);
    virtual ~Goodies();
    virtual void doSomething() = 0;
    virtual std::string getType();
    virtual bool isLive() = 0;
};

class Barrels: public Goodies {
public:
    Barrels(int startX, int startY);
    virtual ~Barrels();
    virtual void doSomething();
    virtual std::string getType();
    virtual bool isLive();
private:
    bool life;
};

class RegularProtester: public Actor {
public:
    RegularProtester();
    virtual ~RegularProtester();
    virtual void doSomething();
    virtual std::string getType();
    virtual bool isLive();
private:
    int numSquareToMoveInCurrentDirection;
    int hitPoints;
    int ticks;
    bool life;
};


#endif // ACTOR_H_

