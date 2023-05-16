#include"Library.h"
Library::Library() {};
Library::Library(bool begin) {

    Monster goblin("Goblin", "minion_physic", 10, 2, 2, 1),
        slime("Slime", "minion_magic", 9, 2, 1, 1),
        dwarf("Dwarf", "minion_physic", 11, 2, 3, 2);
    Monster minotaur("Minotaur", "boss", 21, 5, 5, 3),
        cyclops("Cyclops", "boss", 22, 5, 6, 2),
        behemoth("Behemoth", "boss", 20, 5, 4, 7);

    minions = { goblin, slime, dwarf };
    bosses = { minotaur, cyclops, behemoth };


    //basic
    Skill magic_ball("Magic_ball", "magic", 0, 0),
        basic_chop("Basic_chop", "physic", 0, 0),
        fire_ball("Fire_ball", "magic", 1, 2),
        heavy_chop("Heavy_chop", "physic", 1, 2),
        big_splash("Big_splash", "physic", 1, 2),
        water_shot("Water_shot", "magic", 1, 2),
        small_heal("Small_heal", "heal", 5, 3);

    //advanced
    Skill fire_hell("Fire_hell", "magic", 3, 4),
        ghost_slice("Ghost_slice", "physic", 3, 4),
        tsunami("Tsunami", "magic", 3, 4),
        big_heal("Big_heal", "heal", 10, 5);

    skills.resize(2);
    skills.at(0) = { basic_chop, magic_ball, fire_ball, heavy_chop, small_heal };
    skills.at(1) = { fire_hell, ghost_slice, tsunami, big_heal };




    Item apple("Apple", "potion_hp", 5, 0, 0),     // hp+5
        orange("Orange", "potion_hp", 10, 0, 0),   // hp+10
        snake_poison("Snake_Poison", "potion_poison", 10, 10, 0);

    Item sword_wood("Wood_Sword", "right", 20, 2, 0),
        sword_fire("Fire_Sword", "right", 30, 5, 0),
        shield_wood("Wood_Shield", "left", 20, 0, 1),
        shield_iron("Iron_Shield", "left", 25, 0, 2),
        halmet_wood("Wood_halmet", "head", 20, 0, 1),
        halmet_iron("Iron_halmet", "head", 25, 0, 2),
        armor_wood("Wood_armor", "body", 20, 0, 2),
        armor_iron("Iron_armor", "body", 25, 0, 3);

    equips = { sword_wood, sword_fire, shield_wood, shield_iron, halmet_wood, halmet_iron, armor_wood, armor_iron };
    potions = { apple, orange,snake_poison };
}


vector<Monster> Library::getMinions() { return minions; }
vector<Monster> Library::getBosses() { return bosses; }
vector<Skill> Library::getSkills(int i) { return skills.at(i); }
vector<Item> Library::getEquips() { return equips; }
vector<Item> Library::getPotions() { return potions; }


