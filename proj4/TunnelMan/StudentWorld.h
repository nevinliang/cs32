#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include "GameWorld.h"
#include "GameConstants.h"
#include <string>

#include <vector>

using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual int init();
    virtual ~StudentWorld();
    virtual int move();
    virtual void cleanUp();
    bool areaNoEarth(int x, int y);
    void digEarth(int x, int y);
    void makeBoulders();
    bool pointNoEarth(int x, int y);
    bool hitBoulder(int x, int y, bool isBoulder);
    void checkBoulderHitMan(int x, int y);
    void addBarrelToPlayer();
    double tunnelManDistance(int x, int y);
    void makeBarrels();
    void makeProtestors();
    void statusbarfunc();
    TunnelMan* getMan();
    

private:
    Earth* earthMatrix[VIEW_WIDTH][VIEW_HEIGHT];
    TunnelMan* player;
    vector<Actor*> gameObjects;
};

#endif // STUDENTWORLD_H_
