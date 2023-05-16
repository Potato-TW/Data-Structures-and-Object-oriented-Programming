#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED
#include<iostream>
#include<vector>
#include"Monster.h"
#include"Skill.h"
#include"Item.h"
using namespace std;

class Skill;
class Monster;
class Item;

class Library{
private:
    vector<Monster> minions;
    vector<Monster> bosses;
    vector<vector<Skill>> skills;   //0:basic 1:advanced
    vector<Item> equips;
    vector<Item> potions;
public:
    Library();
    Library(bool);
    vector<Monster> getMinions();
    vector<Monster> getBosses();
    vector<Skill> getSkills(int);
    vector<Item> getEquips();
    vector<Item> getPotions();

};


#endif // LIBRARY_H_INCLUDED
