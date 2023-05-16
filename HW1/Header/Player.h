#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "BackpackSystem.h"
#include "Room.h"
#include "Item.h"
#include "BackpackSystem.h"
#include "Skill.h"
#include "Library.h"
using namespace std;

class Item;
class Backpack;
class Skill;

class Player: public GameCharacter
{
private:
    int var;
    Room* currentRoom;
    Room* previousRoom;
    int totalAtk;
    int totalDef;
    vector<Item> inventory;
    vector<Skill> skills;
public:
    Player();
    Player(string, string);
//    Player(string,int,int,int);
    void increaseStates(int,int,int);
    void changeRoom(Room*);
    void changeInventory(Backpack*);

    // change item and inventory
    string triggerEvent(Object*) override;

    void setVar(int);
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void setInventory(vector<Item>);
    void setSkills(vector<Skill>);
    void setTotalAtk(int);
    void setTotalDef(int);

    void updateState();
    void updateTTA();
    void updateTTD();

    void takeDamage(int);

    int getVar();
    int getTotalAtk();
    int getTotalDef();
    Room* getCurrentRoom();
    Room* getPreviousRoom();
    vector<Skill> getSkills();

    void addItem(Item);
    void showInventory();
    void showState();
    void showSkills();
    vector<Item> getInventory();
};

#endif // PLAYER_H_INCLUDED
