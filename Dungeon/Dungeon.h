#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <ctime>
#include "Player.h"
#include "Monster.h"
#include "NPC.h"
#include "Room.h"
#include "Record.h"
#include "MapObject.h"
#include "BackpackSystem.h"
#include "Library.h"
#include <stack>
using namespace std;


class Dungeon {
private:
    Library lib;
    Record rec;
    Player player;
    Backpack pack;
    vector<Room> rooms;
    bool inGame;
    int skillPoint;

public:
    Dungeon();
    /* Create a new player, and give him/her basic status */
    void createPlayer();

    /* Create a map, which include several different rooms */
    void createDungeon();
    void createLobby();

    stack<Monster*> findMonsters();
    void findTreasure();
    void fight();
    void chooseSkill();
    void monsterAttack();
    /* Deal with player's iteraction with objects in that room */
    void handleEvent(Object*);

    /* Deal with all game initial setting       */
    /* Including create player, create map etc  */
    void startGame(bool);
    void callFirstPage();
    void callMainPage();
    void callSettingPage();
    void callPausePage();
    void callDungeonMap();
    /* Deal with the player's action     */
    /* including showing the action list */
    /* that player can do at that room   */
    /* and dealing with player's input   */
//    void chooseAction(vector<Object*>);
    void chooseAction();
    /* Check whether the game should end or not */
    /* Including player victory, or he/she dead */
    bool checkGameLogic();

    void enterDungeon(Room*, Room*);
    void handleMovement();
    /* Deal with player's moveing action */

    /* Deal with the whole game process */
    void runDungeon();

    void upgradeDifficulty();
    int getVar();

    void ending();
};


#endif // DUNGEON_H_INCLUDED
