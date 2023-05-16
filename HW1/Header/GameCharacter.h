#ifndef GAMECHARACTER_H_INCLUDED
#define GAMECHARACTER_H_INCLUDED

#include <iostream>
#include <string>
#include "Object.h"
using namespace std;

class GameCharacter: public Object
{
private:
    string name;
    int maxHealth;
    int currentHealth;
    int sp;
    int maxSp;
    int attack;
    int defense;
public:
    GameCharacter();
    GameCharacter(string,string,int,int, int,int);
    bool checkIsDead();

    /* Set & Get function*/
    void setMaxHealth(int);
    void setCurrentHealth(int);
    void setAttack(int);
    void setDefense(int);
    void setSp(int);
    void setMaxSp(int);
    void addSp();

    int getMaxHealth();
    int getCurrentHealth();
    int getAttack();
    int getDefense();
    int getSp();
    int getMaxSp();
};
#endif // GAMECHARACTER_H_INCLUDED
