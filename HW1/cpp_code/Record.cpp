#include "Record.h"

Record::Record(){};

void Record::savePlayer(Player* player, ofstream& out){
    out<<player->getVar()<<" ";
    out<<player->getName()<<" "
        <<player->getTag()<<" "
        <<player->getMaxHealth()<<" "
        <<player->getCurrentHealth()<<" "
        <<player->getMaxSp()<<" "
        <<player->getSp()<<" "
        <<player->getAttack()<<" "
        <<player->getDefense()<<" "
        <<player->getTotalAtk()<<" "
        <<player->getTotalDef()<<endl;

    out<<player->getInventory().size()<<endl;
    for(int i=0;i<player->getInventory().size();i++){
        Item equip = player->getInventory().at(i);

        out<<equip.getName()<<" "
            <<equip.getTag()<<" "
            <<equip.getMaxHealth()<<" "
            <<equip.getCurHealth()<<" "
            <<equip.getAttack()<<" "
            <<equip.getDefense()<<endl;
    }

    out<<player->getSkills().size()<<endl;
    for(int i=0;i<player->getSkills().size();i++){
        Skill skill = player->getSkills().at(i);

        out<<skill.getSkillName()<<" "
            <<skill.getSkillTag()<<" "
            <<skill.getSkillDamage()<<" "
            <<skill.getSkillSp()<<endl;
    }
}
void Record::saveBackpack(Backpack* pack,ofstream& out){
    out<<pack->getName()<<" "
        <<pack->getTag()<<" "
        <<pack->getMoney()<<" "
        <<pack->getKey()<<endl;

    out<<pack->getPack().size()<<endl;
    for(int i=0;i<pack->getPack().size();i++){
        Item item = pack->getPack().at(i);

        out<<item.getName()<<" "
            <<item.getTag()<<" "
            <<item.getMaxHealth()<<" "
            <<item.getCurHealth()<<" "
            <<item.getAttack()<<" "
            <<item.getDefense()<<endl;
    }
}

void Record::loadPlayer(Player* player,ifstream& in){
    //載入後要設置房間座標
    string a;
    int b;
    in>>b;
    player->setVar(b);
    in>>a;
    player->setName(a);
    in>>a;
    player->setTag(a);
    in>>b;
    player->setMaxHealth(b);
    in>>b;
    player->setCurrentHealth(b);
    in>>b;
    player->setMaxSp(b);
    in>>b;
    player->setSp(b);
    in>>b;
    player->setAttack(b);
    in>>b;
    player->setDefense(b);
    in>>b;
    player->setTotalAtk(b);
    in>>b;
    player->setTotalDef(b);

    int time;   in>>time;
    vector<Item> itemp;
    for(int i=0;i<time;i++){
        Item equip("","",0,0,0);

        in>>a;
        equip.setName(a);
        in>>a;
        equip.setTag(a);
        in>>b;
        equip.setMaxHealth(b);
        in>>b;
        equip.setCurHealth(b);
        in>>b;
        equip.setAttack(b);
        in>>b;
        equip.setDefense(b);

        itemp.push_back(equip);
    }
    player->setInventory(itemp);

    in>>time;
    vector<Skill> stemp;
    for(int i=0;i<time;i++){
        Skill skill("","",0,0);

        in>>a;
        skill.setSkillName(a);
        in>>a;
        skill.setSkillTag(a);
        in>>b;
        skill.setSkillDamage(b);
        in>>b;
        skill.setSkillSp(b);

        stemp.push_back(skill);
    }
    player->setSkills(stemp);
}
void Record::loadBackpack(Backpack* pack, ifstream& in){
    string a;
    int b;

    in>>a;
    pack->setName(a);
    in>>a;
    pack->setTag(a);
    in>>b;
    pack->setMoney(b);
    in>>b;
    pack->setKey(b);

    int time;   in>>time;
    vector<Item> temp;
    for(int i=0;i<time;i++){
        Item item("","",0,0,0);

        in>>a;item.setName(a);
        in>>a;item.setTag(a);
        in>>b;item.setMaxHealth(b);
        in>>b;item.setCurHealth(b);
        in>>b;item.setAttack(b);
        in>>b;item.setDefense(b);

        temp.push_back(item);
    }
    pack->setItems(temp);
}

void Record::saveToFile(Player* player, Backpack* pack, vector<Room>& rooms){
    cout<<"What file name do you want?\n";

    string filename;
    while(1){
        cout<<"Input:";
        cin>>filename;  cout<<endl;

        cout<<"Are you sure of \""<<filename<<"\"? (y/n)\n";
        cout<<"Input: ";
        char input;     cin>>input;
        cout<<endl;
        if(input=='Y'||input=='y'){
            break;
        }
        else if(input=='N'||input=='n'){
            continue;
        }
        else{
            cout<<"No! No! You have to choose another correct one!"<<endl;
            continue;
        }
    }

    ofstream out(filename);
    savePlayer(player, out);
    saveBackpack(pack, out);
//    saveRooms(rooms, out);
}
void Record::loadFromFile(Player* player, Backpack* pack, vector<Room>& rooms){
    cout<<"What file name do you have?\n";

    string filename;
    while(1){
        cout<<"Input: ";
        cin>>filename;  cout<<endl;

        cout<<"Are you sure of \""<<filename<<"\"? (y/n)\n";
        cout<<"Input: ";
        char input;     cin>>input;
        cout<<endl;

        if(input=='Y'||input=='y'){
            break;
        }
        else if(input=='N'||input=='n'){
            continue;
        }
        else{
            cout<<"No! No! You have to choose another correct one!"<<endl;
            continue;
        }
    }

    ifstream in(filename);
    loadPlayer(player, in);
    loadBackpack(pack, in);
//    loadRooms(rooms, in);
}
