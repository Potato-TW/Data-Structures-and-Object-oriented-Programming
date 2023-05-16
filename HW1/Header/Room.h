#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"

using namespace std;

class Room
{
private:
//    Room* upRoom;      // 0
//    Room* leftRoom;    // 1
//    Room* rightRoom;   // 2
//    Room* downRoom;    // 3

    bool isExit;
    int index;
    vector<Room*> roomPtr;
    vector<Object*> objects; /*contain 1 or multiple objects, including monster, npc, etc*/
public:
    Room();
    Room(int);    //for lobby
    Room(bool, int, vector<Object*>);
    bool popObject(Object*); /*pop out the specific object, used when the interaction is done*/

    /* Set & Get function*/
    void setRoom(Room*, int);
    void setIsExit(bool);
    void setIndex(int);
//    void setObject(Object*);
    void setObjects(vector<Object*>);

    bool getIsExit();
    int getIndex();
    vector<Object*> getObjects();
    Room* getRoom(int);
};

#endif // ROOM_H_INCLUDED
