#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Dungeon.h"
#include "Item.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"
#include "Object.h"

using namespace std;

int main() {
    srand(time(NULL));
    static int var = 1;

    Dungeon dungeon = Dungeon();
    dungeon.runDungeon();
    return 0;
}
