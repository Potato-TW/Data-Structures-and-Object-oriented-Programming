#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Player.h"
using namespace std;

class Player;

class Item: public Object
{
private:
    string name;
    int maxHealth;
    int curHealth;
    int attack;
    int defense;
public:
    Item();
    Item(string, string, int, int, int);

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.                                       */
    string triggerEvent(Object*) override;

    /* Set & Get function*/
    string getName();
    int getMaxHealth();
    int getCurHealth();
    int getAttack();
    int getDefense();

    void setName(string);
    void setMaxHealth(int);
    void setCurHealth(int);
    void setAttack(int);
    void setDefense(int);

    bool checkHealth();
};

#endif // ITEM_H_INCLUDED
