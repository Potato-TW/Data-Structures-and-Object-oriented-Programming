#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"
#include "Skill.h"
using namespace std;

class Monster: public GameCharacter
{
private:
public:
    Monster();
    Monster(string,string, int,int,int,int);

    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    string triggerEvent(Object*) override;
};


#endif // ENEMY_H_INCLUDED
