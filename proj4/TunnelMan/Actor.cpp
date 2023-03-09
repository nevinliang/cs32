#include "Actor.h"
#include "StudentWorld.h"

#include <random>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

/*ACTOR FUNCS*/
Actor::Actor(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) : GraphObject(imageID, startX, startY, dir, size, depth) {
    // make sure to set visible to true
    setVisible(true);

}

StudentWorld* Actor::getWorld() const {
    return world;
}

Actor::~Actor() {}

void Actor::setWorld(StudentWorld* ptr) {
    // so that actor can access world ptr
    world = ptr;
}

/*EARTH FUNCS*/
Earth::Earth(int startX, int startY) : Actor(TID_EARTH, startX, startY, right, 0.25, 3) {
    setVisible(true);
    // earth doesnt live
    life = false;
}

Earth::~Earth() {}

void Earth::doSomething() {}

bool Earth::isLive() {
    return life;
}

std::string Earth::getType() {
    return "earth";
}

/*TUNNELMAN FUNCS*/
TunnelMan::TunnelMan() : Actor(TID_PLAYER, 30, 60, right) {
    // numbers and values given in specs
    life = true;
    hitPoints = 10;
    water = 5;
    sonarCharge = 1;
    nuggets = 0;
    oil = 0;
    // make sure to set visible to true
    setVisible(true);
}

TunnelMan::~TunnelMan() {}

bool TunnelMan::isLive() {
    return life;
}

void TunnelMan::pickOilUp() {
    // increment value of oil
    oil++;
}

int TunnelMan::getOil() {
    return oil;
}

void TunnelMan::annoy(int amount) {
    // if amount is -1 it represents a total kill :(
    if (amount == -1) {
        hitPoints = 0;
    }
    else {
        hitPoints -= amount;
    }
}

int TunnelMan::getWater() {
    return water;
}

int TunnelMan::getSonar() {
    return sonarCharge;
}

int TunnelMan::getNuggets() {
    return nuggets;
}

int TunnelMan::getHP() {
    return hitPoints;
}

string TunnelMan::getType() {
    return "tunnelman";
}

void TunnelMan::doSomething() {
    // do something function
    // if no life return immed
    if (!life) {
        return;
    }
    int keyPressed;
    if (getWorld()->getKey(keyPressed)) {
        // different keys
        switch (keyPressed) {
            // will only annotate 1 because rest are same
            case KEY_PRESS_UP:
                // direction is up
                if (getDirection() == up) {
                    if (getY() < VIEW_HEIGHT - SPRITE_HEIGHT && !getWorld()->hitBoulder(getX(), getY() + 1, false)) {
                        moveTo(getX(), getY() + 1);
                        // dig if is able to
                        if (not getWorld()->areaNoEarth(getX(), getY())) {
                            getWorld()->digEarth(getX(), getY());
                            getWorld()->playSound(SOUND_DIG);
                        }
                    }
                }
                // or direction is something different
                else {
                    // set dir
                    setDirection(up);
                }
                break;
            case KEY_PRESS_DOWN:
                if (getDirection() == down) {
                    if (getY() > 0 && !getWorld()->hitBoulder(getX(), getY() - 1, false)) {
                        moveTo(getX(), getY() - 1);
                        if (not getWorld()->areaNoEarth(getX(), getY())) {
                            getWorld()->digEarth(getX(), getY());
                            getWorld()->playSound(SOUND_DIG);
                        }
                    }
                }
                else {
                    setDirection(down);
                }
                break;
            case KEY_PRESS_LEFT:
                if (getDirection() == left) {
                    if (getX() > 0 && !getWorld()->hitBoulder(getX() - 1, getY(), false)) {
                        moveTo(getX() - 1, getY());
                        if (not getWorld()->areaNoEarth(getX(), getY())) {
                            getWorld()->digEarth(getX(), getY());
                            getWorld()->playSound(SOUND_DIG);
                        }
                    }
                }
                else {
                    setDirection(left);
                }
                break;
            case KEY_PRESS_RIGHT:
                if (getDirection() == right) {
                    if (getX() < VIEW_WIDTH - SPRITE_WIDTH && !getWorld()->hitBoulder(getX() + 1, getY(), false)) {
                        moveTo(getX() + 1, getY());
                        if (not getWorld()->areaNoEarth(getX(), getY())) {
                            getWorld()->digEarth(getX(), getY());
                            getWorld()->playSound(SOUND_DIG);
                        }
                    }
                }
                else {
                    setDirection(right);
                }
                break;
        }
    }
}

/*BOULDER FUNCS*/
Boulder::Boulder(int startX, int startY) : Actor(TID_BOULDER, startX, startY, down, 1.0, 1) {
    // make sure to set visible to true
    setVisible(true);
    // values needed for boulder
    stable = true;
    life = true;
    ticks = 0;
}

Boulder::~Boulder() {}

std::string Boulder::getType() {
    return "boulder";
}

void Boulder::doSomething() {
    // if life false return immed
    if (!life) {
        return;
    }
    // stable as in not falling
    if (stable) {
        // set falling to true
        bool fall = true;
        // if the bottom 4 are empty
        for (int i = 0; i < 4; i++) {
            if (!getWorld()->pointNoEarth(getX() + i, getY() - 1)) {
                fall = false;
            }
        }
        // then set stable to false
        if (fall) {
            stable = false;
        }
    }
    else {
        // drop after 30 ticks
        if (ticks >= 30) {
            drop();
            if (ticks == 30) {
                // and play the sound
                getWorld()->playSound(SOUND_FALLING_ROCK);
            }
        }
        ++ticks;
    }
}

void Boulder::drop() {
    // first check if it hits any person
    
    // check if any Earth/other boulders blocking
    bool fall = true;
    for (int i = 0; i < 4; i++) {
        if (!getWorld()->pointNoEarth(getX() + i, getY() - 1)) {
            fall = false;
        }
    }
    // same here
    if (getWorld()->hitBoulder(getX(), getY(), true)) {
        fall = false;
    }

    // starts falling
    if (fall) {
        if (getY() > 0) {
            moveTo(getX(), getY() - 1);
            // check if it hits tunnelman!!
            getWorld()->checkBoulderHitMan(getX(), getY());
        }
        else {
            life = false;
        }
    }
    else {
        life = false;
    }
    
}

bool Boulder::isLive() {
    return life;
}

/*GOODIES FUNCS*/
// goodie parent class construct
Goodies::Goodies(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) : Actor(imageID, startX, startY, right, size, depth) {}

string Goodies::getType() {
    return "goodies";
}

Goodies::~Goodies() {}

/*BARRELS FUNCS*/

Barrels::Barrels(int startX, int startY) : Goodies(TID_BARREL, startX, startY, right, 1.0, 2) {
    setVisible(true);
    life = true;
}

Barrels::~Barrels() {}

void Barrels::doSomething() {
    // if no life return immed
    if (!life) {
        return;
    }
    // distance to tunnelman
    double distance2TunnelMan = getWorld()->tunnelManDistance(getX(), getY());
    if (distance2TunnelMan <= 4 && !isVisible()) {
        setVisible(true);
        return;
    }
    // otherwise too close so pick up
    if (distance2TunnelMan <= 3) {
        life = false;
        getWorld()->playSound(SOUND_FOUND_OIL);
        getWorld()->increaseScore(1000);
        getWorld()->addBarrelToPlayer();
    }
}

std::string Barrels::getType() {
    return "barrel";
}

bool Barrels::isLive() {
    return life;
}

/*PROTESTER FUNCS*/

RegularProtester::RegularProtester() : Actor(TID_PROTESTER, 60, 60, left, 1.0, 0) {
    srand((unsigned int)time(NULL));
    numSquareToMoveInCurrentDirection = rand() % 53 + 8;
    hitPoints = 5;
    ticks = std::max(0, 3 - (int)getWorld()->getLevel() / 4);
    life = true;
    setVisible(true);
}

RegularProtester::~RegularProtester() {}

void RegularProtester::doSomething() {
    if (ticks == std::max(0, 3 - (int)getWorld()->getLevel() / 4)) {
        if (!life) {
            return;
        }
        if (hitPoints == 0) {
            // going towards exit
        }
        else {
            double d = getWorld()->tunnelManDistance(getX(), getY());
            Direction dir;
            if (getWorld()->getMan()->getX() > getX()) {
                dir = right;
            }
            else {
                dir = left;
            }
            if (d <= 4 && getDirection() == dir) {
                getWorld()->playSound(SOUND_PROTESTER_YELL);
                getWorld()->getMan()->annoy(2);
                
            }
        }
        
        
        
        ticks = 0;
    }
    else {
        ticks++;
    }
}

string RegularProtester::getType() {
    return "regprotester";
}

bool RegularProtester::isLive() {
    return life;
}
