#include "StudentWorld.h"
#include <string>
#include <random>
#include <cmath>

using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(std::string assetDir) : GameWorld(assetDir) {}

StudentWorld::~StudentWorld() {
    cleanUp();
}

int StudentWorld::init() {
    // initialize the earthmatrix
    for (int i = 0; i < VIEW_WIDTH; i++) {
        for (int j = 0; j < VIEW_WIDTH - SPRITE_WIDTH; j++) {
            // make sure no shaft earth blocks
            if ((i < 30 || i > 33) || (j >= 0 && j < 4)) {
                earthMatrix[i][j] = new Earth(i, j);
            }
        }
    }
    // create a tunnelMan and other objects
    player = new TunnelMan();
    player->setWorld(this);
    // make boulders and barrels
    makeBoulders();
    makeBarrels();
    // make protestors
    makeProtestors();
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() {
    // delete all dynamic allcoated memory
    for (int i = 0; i < VIEW_WIDTH; i++) {
        for (int j = 0; j < VIEW_HEIGHT; j++) {
            delete earthMatrix[i][j];
        }
    }
    // player
    delete player;
    // all actor objects in gameobjects
    for (vector<Actor*>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++) {
        delete *it;
    }
    // clear just to be safe!
    gameObjects.clear();
}

int StudentWorld::move() {
    // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    
    // call do something for each object
    player->doSomething();
    // actors
    for (Actor* a : gameObjects) {
        a->doSomething();
    }
    // players dead
    if (player->getHP() == 0) {
        decLives();
        playSound(SOUND_PLAYER_GIVE_UP);
        return GWSTATUS_PLAYER_DIED;
    }
    // player gets oil
    if (player->getOil() == min(2 + (int)getLevel(), 21)) {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    
    // destroy dead boulders
    for (vector<Actor*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ) {
        // run through every actor object
        if (!((*it)->isLive())) {
            // delete it.
            delete *it;
            gameObjects.erase(it);
            it = gameObjects.begin();
        }
        else {
            it++;
        }
    }
    
    // run status bar fucntion so it appears at top of game
    statusbarfunc();
    
    return GWSTATUS_CONTINUE_GAME;
}

bool StudentWorld::areaNoEarth(int x, int y) {
    // checks whether there is any earth in the block starting at x, y
    for (int i = x; i < x + SPRITE_WIDTH; i++) {
        for (int j = y; j < y + SPRITE_WIDTH; j++) {
            // checks to see if it is either existing or invisible
            if (earthMatrix[i][j] != nullptr && earthMatrix[i][j]->isVisible()) {
                return false;
            }
        }
    }
    return true;
}

bool StudentWorld::pointNoEarth(int x, int y) {
    // checks a single point instead of an area
    if (earthMatrix[x][y] == nullptr || !earthMatrix[x][y]->isVisible()) {
        return true;
    }
    return false;
}

void StudentWorld::digEarth(int x, int y) {
    // clears a portion of the earth matrix
    for (int i = x; i < x + SPRITE_WIDTH; i++) {
        for (int j = y; j < y + SPRITE_WIDTH; j++) {
            if (earthMatrix[i][j] != nullptr) {
                // by setting it to invisible
                earthMatrix[i][j]->setVisible(false);
            }
        }
    }
}

void StudentWorld::makeBoulders() {
    // make the boulders by using specs numbers
    int B = min((int)getLevel() / 2 + 2, 9);
    srand((unsigned int)time(NULL));
    // do it for all B boulders
    for (int i = 0; i < B; i++) {
        // make sure they don't spawn in weird places
        int x = rand() % 61;
        while (x >= 27 && x <= 33) {
            x = rand() % 61;
        }
        int y = rand() % 37 + 20;
        // make sure that the boulder is added to the vector of objects
        Boulder *b = new Boulder(x, y);
        b->setWorld(this);
        digEarth(x, y);
        gameObjects.push_back(b);
    }
}

void StudentWorld::makeBarrels() {
    // make the barrels by using specs numbers
    int L = min(2 + (int)getLevel(), 21);
    srand((unsigned int)time(NULL));
    // do it for all L barrels
    for (int i = 0; i < L; i++) {
        // make sure they don't spawn in weird places
        int x = rand() % 61;
        while (x >= 27 && x <= 33) {
            x = rand() % 61;
        }
        int y = rand() % 57;
        // make sure to add them to the end of the vector of objects
        Barrels *l = new Barrels(x, y);
        l->setWorld(this);
        gameObjects.push_back(l);
    }
    
}

bool StudentWorld::hitBoulder(int x, int y, bool isBoulder) {
    // tests whether the object is touching the boulder
    for (Actor* b : gameObjects) {
        // if object is boulder then it is different
        if (b->getType() == "boulder") {
            double dx = abs(x - b->getX());
            double dy = abs(y - b->getY());
            // means ur looking at the same boulder so dw
            if (dx == 0 && dy == 0 && isBoulder) {
                continue;
            }
            // here ur either a tunnelman or a diff boulder
            if (dx < SPRITE_WIDTH && dy < SPRITE_WIDTH) {
                return true;
            }
        }
    }
    return false;
}

void StudentWorld::checkBoulderHitMan(int x, int y) {
    // if the player gets hit by a boulder it dies instantly
    if (x - player->getX() < SPRITE_WIDTH - 1 && y - player->getY() < SPRITE_HEIGHT - 1) {
        player->annoy(-1);
    }
}

void StudentWorld::addBarrelToPlayer() {
    // 1000 points received!
    player->pickOilUp();
}

double StudentWorld::tunnelManDistance(int x, int y) {
    // distance from x, y, to tunnel man using distance formula
    return sqrt((player->getX() - x) * (player->getX() - x) + (player->getY() - y) * (player->getY() - y));
}

void StudentWorld::statusbarfunc() {
    // all variables that are important to game (some not implemented :()
    int level = getLevel();
    int health = player->getHP();
    int water = player->getWater();
    int gold = player->getNuggets();
    int score = getScore();
    int lives = getLives();
    int oil = min(2 + (int)getLevel(), 21) - player->getOil();
    int sonar = player->getSonar();
    // create status string
    string statstr = "Lvl: " + to_string(level) + " Lives: " + to_string(lives) + " Hlth: " + to_string(health) + "% Water: " + to_string(water) + " Gld: " + to_string(gold) + " Oil left: " + to_string(oil) + " Sonar: " + to_string(sonar) + " Scr: " + to_string(score);
    // set game text to that value
    setGameStatText(statstr);
    
}

TunnelMan* StudentWorld::getMan() {
    return player;
}

void StudentWorld::makeProtestors() {
    gameObjects.push_back(new RegularProtester());
}
