#include "Room.h"

// 0   Room* upRoom;
// 1   Room* leftRoom;
// 2   Room* rightRoom;
// 3   Room* downRoom;

Room::Room() {};
Room::Room(int _index) :isExit(false), index(_index) {
    for (int i = 0; i < 4; i++) {
        roomPtr.push_back(NULL);
    }
}
Room::Room(bool a, int b, vector<Object*> c) : isExit(a), index(b), objects(c) {
    for (int i = 0; i < 4; i++) {
        roomPtr.push_back(NULL);
    }
}

//bool Room::popObject(Object*); /*pop out the specific object, used when the interaction is done*/

//bool isExit;
//int index;
//vector<Room*> rooms;
//vector<Object*> objects;

/* Set & Get function*/
void Room::setRoom(Room* anotherRoom, int index) {
    //    switch(index){
    //    case 0:
    //        roomPtr.at(0) = anotherRoom;
    //        break;
    //    case 1:
    //        roomPtr.at(1)=anotherRoom;
    //        break;
    //    case 2:
    //        roomPtr.at(2)=anotherRoom;
    //        break;
    //    case 3:
    //        roomPtr.at(3)=anotherRoom;
    //        break;
    //    }
    roomPtr.at(index) = anotherRoom;
}

//void Room::setIsExit(bool);
void Room::setIndex(int newIndex) { index = newIndex; }
//void Room::setObject(Object* newObject){ objects.push_back(newObject); }
void Room::setObjects(vector<Object*> newObjects) { objects = newObjects; }


bool Room::getIsExit(){return isExit;}
int Room::getIndex() { return index; }
vector<Object*> Room::getObjects() { return objects; }
Room* Room::getRoom(int index) {return roomPtr.at(index);}




