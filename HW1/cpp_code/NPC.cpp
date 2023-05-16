#include "NPC.h"
#include<iostream>
#include<ctime>
#include<iomanip>
using namespace std;

NPC::NPC() {};
NPC::NPC(string _name, string _tag) :
    GameCharacter(_name, _tag, INT_MAX, INT_MAX, 0, INT_MAX) {};

void NPC::listCommodity() {
    for (auto it = commodity.begin(); it != commodity.end(); it++) {
        cout << it->getName() << endl;
    }
}
string NPC::triggerEvent(Object* object) { return "1"; }

Merchant::Merchant(string _name, string _tag) :NPC(_name, _tag)
{
    scripts.push_back("Welcome to my shop, bro!");
    scripts.push_back("Here is today's special!");
    scripts.push_back("I'm sure you'll come back again!");
    //    Item::Item(string _name, string _tag, int _health, int _attack, int _defense) :

    Library lib(true);
    //potion
    for(int i=0;i<lib.getPotions().size();i++){
        pair<Item, int> temp(lib.getPotions().at(i), lib.getPotions().at(i).getMaxHealth());
        sales.push_back(temp);
    }
    //equips
    for(int i=0;i<lib.getEquips().size();i++){
        pair<Item, int> temp(lib.getEquips().at(i), lib.getEquips().at(i).getMaxHealth());
        sales.push_back(temp);
    }

//    Item potion_hp("Apple", "potion", 1, 0, 0),
//        potion_mp("Orange", "potion", 1, 0, 0),
//        sword_wood("Wood_Sword", "weapon", 20, 2, 0),
//        sword_fire("Fire_Sword", "weapon", 30, 5, 0),
//        shield_wood("Wood_Shield", "shield", 20, 0, 1),
//        shield_iron("Iron_Shield", "shield", 30, 0, 4);
//    pair<Item, int> a(potion_hp, 10),
//        b(potion_mp, 10),
//        c(sword_wood, 20),
//        d(sword_fire, 40),
//        e(shield_wood, 15),
//        f(shield_iron, 30);
//    sales.push_back(a);
//    sales.push_back(b);
//    sales.push_back(c);
//    sales.push_back(d);
//    sales.push_back(e);
//    sales.push_back(f);
}

void Merchant::showSales() {
    int count = 0;
    for (auto it = sales.begin(); it != sales.end(); it++) {
        string name = it->first.getName();
        int cost = it->second;
        cout << char(count + 'A') << ": ";
        cout << setiosflags(ios::left) << setw(20) << name << " " << cost << " dollars" << endl;
        count++;
    }
    cout << "Q: Quit" << endl;
}

string Merchant::getScript() {
    int time = rand() % scripts.size();
    return scripts.at(time);
}

string Merchant::triggerEvent(Object* object) {
    cout << scripts.at(0) << " ";
    cout << scripts.at(1);
    cout << endl;
    showSales();

    char input;
    while(1){
        cout << "Input: ";
        cin >> input;
        cout<<endl;

        if(input=='Q'||input=='q'){
            cout << "You will come back again!";
            cout << endl;
            return "1";
        }

        if(input>='a')  input-='a';
        else input-='A';

        if(int(input)<0||int(input)>=sales.size()){
            cout << "No! No! You have to choose another correct choice!";
            cout << endl;
            continue;
        }

        break;
    }

    Item wanted=sales.at(int(input)).first;
    int cost =sales.at(int(input)).second;
    Backpack* pack = dynamic_cast<Backpack*>(object);

    if(pack->getMoney()<cost){
        cout<<"You don't have enough money!"<<endl;
    }
    else{
        pack->purchase(cost);
        pack->setItem(wanted);
        cout<<"You've bought "<<wanted.getName()<<endl;
    }

    return "1";
}

//Cat
Cat::Cat() {};
Cat::Cat(string _name, string _tag) :NPC(_name, _tag), sound("Meow ") {};

string Cat::getSound() {
    int count = rand() % 10;
    string _sound;

    if (count == 0) {
        _sound = ".........(silence)";
    }
    else {
        for (int i = 0; i < count; i++) {
            _sound += sound;
        }
    }
    return _sound;
}

void Cat::setSound() {
    string _sound = "Meow ";
    sound = _sound;
}

string Cat::triggerEvent(Object* object) {
    cout << getSound();
    return "1";
}


//BlackSmiths
Blacksmiths::Blacksmiths() {};
Blacksmiths::Blacksmiths(string _name, string _tag) :NPC(_name, _tag) {
    scripts.push_back("What a good day!");
    scripts.push_back("Your inventories are all fixed well!");

    services.push_back("Fix all inventories");
};
string Blacksmiths::getScript() {
    //    int time = rand()%scripts.size()-1;
    //    return scripts.at(time);
    return scripts.at(0);
}
void Blacksmiths::showServices() {
    char count='A';
    for (auto it = services.begin(); it != services.end(); it++) {
        cout <<count<<": "<< *it << endl;
        count++;
    }
    cout<<"Q: Quit"<<endl;
}

string Blacksmiths::triggerEvent(Object* object) {
    cout << getScript() << endl;
    showServices();

    string input;
    while (1) {
        cout << "Input:";
        cin >> input;
        cout<<endl;

        if (input == "A" || input == "a") {
            break;
        }
        else if (input =="Q"||input=="q"){
            cout<<"Bye ya! You'll come back soon!"<<endl;
            break;
        }
        cout << "No! No! You have to choose another correct one!" << endl;
    }

    return input;
}

