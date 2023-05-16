#include "Dungeon.h"
using namespace std;

Dungeon::Dungeon() :player(), inGame(false), pack(), lib(true), skillPoint(0), rec() {};

void Dungeon::createPlayer() {
    string check = "a";
    string name;

    while (check != "Y" && check != "y") {
        cout << "What is your name? (You can change it anytime)\n";
        cout << "Input: ";
        cin >> name;
        cout << endl;

        cout << "Are you sure of this name: " << name << "? (y/n)\n";
        cout << "Input: ";
        cin >> check;
        cout << endl;
    }

    cout << "HELLO " << name << "!"
        << "\nWELCOME TO MY DUNGEON!\n";

    player = Player(name, "player");
    pack = Backpack(100);
    player.setCurrentRoom(&rooms.at(0));
    player.setPreviousRoom(&rooms.at(0));
}
void Dungeon::createLobby(){
    Room lobby(0);
    Object* aCat = new Cat("Kitty", "cat"),
        * aMerchant = new Merchant("John", "merchant"),
        * aBlacksmiths = new Blacksmiths("William", "blacksmiths");
    vector<Object*> objects = { aCat, aMerchant, aBlacksmiths };
    lobby.setObjects(objects);
    rooms.push_back(lobby);
}
void Dungeon::createDungeon() {
    //set roomsObj
    for (int i = 1; i < 7; i++) {
        if (i != 4&&i!=6) {
            int num = rand() % 2 + 1;
            vector<Object*> objects;

            for (int j = 0; j < num; j++) {

                int time = rand() % lib.getMinions().size();

                string name = lib.getMinions().at(time).getName(),
                    tag = lib.getMinions().at(time).getTag();
                int atk = lib.getMinions().at(time).getAttack(),
                    sp = lib.getMinions().at(time).getSp(),
                    def = lib.getMinions().at(time).getDefense(),
                    maxH = lib.getMinions().at(time).getMaxHealth();

                    Object* minionPtr = new Monster(name, tag, maxH, sp, atk ,def);
                //Object* minionPtr = &minion;
                objects.push_back(minionPtr);
            }

            Room room(true, i, objects);
            rooms.push_back(room);
        }
        else if(i==4) {
            int money = rand() % 11 + 10;

            vector<Skill> skills;
            Object* aBox = new Box("TreasureBox", "treasure", money, 1, skills, false);

            vector<Object*> objects = { aBox };
            Room room(true, i, objects);
            rooms.push_back(room);
        }
        else if(i==6){

            vector<Object*> objects;

            int time = rand() % lib.getBosses().size();

            string name = lib.getBosses().at(time).getName(),
                tag = lib.getBosses().at(time).getTag();
            int atk = lib.getBosses().at(time).getAttack(),
                sp = lib.getBosses().at(time).getSp(),
                def = lib.getBosses().at(time).getDefense(),
                maxH = lib.getBosses().at(time).getMaxHealth();

            Object* bossPtr = new Monster(name, tag, maxH, sp, atk ,def);
            //Object* minionPtr = &minion;
            objects.push_back(bossPtr);

            Room room(false, i, objects);
            rooms.push_back(room);
        }
        //set roomptr
    }
    //set aisle
    for (int i = 2; i < rooms.size(); i++) {
        while (1) {
            int k = rand() % 4;
            //©â«e­±ªº
            if (rooms.at(i - 1).getRoom(k) == NULL) {
                rooms.at(i - 1).setRoom(&rooms.at(i), k);
                rooms.at(i).setRoom(&rooms.at(i - 1), 3 - k);
                break;
            }
        }
    }

    vector<Skill> skills;
    int ta=rand()%2;
    int time = rand()%lib.getSkills(ta).size();
    Skill temp=lib.getSkills(ta).at(time);
    skills.push_back(temp);

    Object* aBox = new Box("Secret Treasure Box", "treasure", 0, 0, skills, true);

    vector<Object*> objects = { aBox };
    Room room(true, 7, objects);
    rooms.push_back(room);  //index: 7

    int i=0;
    for(i=0;i<4;i++){
        if(rooms.at(4).getRoom(i)==NULL){
            rooms.at(4).setRoom(&rooms.at(7), i);
            break;
        }
    }

    rooms.at(7).setRoom(&rooms.at(4), 3-i);
}

void Dungeon::callFirstPage() {
    while (1) {
        cout << " ---------------------------------\n"
            << " | WELCOME TO MY DUNGEON, MORTAL! |\n"
            << " |          A: CONTINUE           |\n"
            << " |          B: NEW GAME           |\n"
            << " |          C: QUIT               |\n"
            << " ---------------------------------\n"
            << "Input: ";

        string input;   cin >> input;
        cout<<endl;

        if (input == "A" || input == "a") {

            createLobby();
            createDungeon();
            rec.loadFromFile(&player, &pack, rooms);
            player.changeRoom(&rooms.at(0));

            inGame = 1;
            break;
        }
        else if (input == "B" || input == "b") {
            cout << " ---------------------------\n"
                << " | A NEW GAME? INTERESTING! |\n"
                << " ---------------------------\n";
            createLobby();
            createDungeon();
            createPlayer();
            inGame = 1;
            break;
        }
        else if ((input == "C" || input == "c")) {
            if (inGame == 1) {
                cout << "Do you want to save the file? (y/n)\n"
                    << "Input: ";

                char input;   cin >> input;
                cout<<endl;
                if (input == 'Y' || input == 'y') {
                    rec.saveToFile(&player, &pack, rooms);
                }
                else if(input=='N'||input=='n'){
                    ;
                }
                else{
                    cout<<"No! No! You have to choose another correct choice!";
                    cout<<endl;
                }
            }
            cout << "\nSEE YOU SOON, MORTAL!!" << endl;

            inGame = 0;
            exit(0);
        }
        else {
            cout << "No! No! You have to choose another correct choice!";
            cout << endl;
        }
    }
}
void Dungeon::callMainPage() {
    while (1) {
//        _sleep(1 * 1000);
        cout<<endl;
        cout<<"Difficulty: "<<player.getVar()<<endl;
        cout<<"Home:\n";
        cout << "  ----------------------------- \n"
            << " |                             |\n"
            << " |                             |\n"
            << " |          Purchase           |\n"
            << " |                             |\n"
            << " |                             |\n"
            << " |                              \n"
            << " |   Pet       ME      dungeon  \n"
            << " |                              \n"
            << " |                             |\n"
            << " |                             |\n"
            << " |        Blacksmiths          |\n"
            << " |                             |\n"
            << " |                             |\n"
            << "  ----------------------------- " << endl;

        cout << "A: Have an adventure in DUNGEON!\n"
            << "B: Talk to the PURCHASE!\n"
            << "C: Talk to the BLACKSMITHS!\n"
            << "D: Show what I GET!\n"
            << "E: PAUSE!\n"
            << "(or try to type \"cat\")\n"
            << "Input: ";

        string input;   cin >> input;
        cout<<endl;
        //    vector<Object*> objects={aCat, aMerchant, aBlacksmiths};
        if (input == "A" || input == "a") {
            //enter next room
            enterDungeon(&rooms.at(1), &rooms.at(1));
            break;
        }
        else if (input == "B" || input == "b") {
            Object* aMerchant = rooms.at(0).getObjects().at(1);
            aMerchant->triggerEvent(&pack);

        }
        else if (input == "C" || input == "c") {
            string input = rooms.at(0).getObjects().at(2)->triggerEvent(rooms.at(0).getObjects().at(2));

            if (input == "A" || input == "a") {
                //            vector<Item> inventories = player.getInventory();
                for (auto it = player.getInventory().begin(); it != player.getInventory().end(); it++) {
                    it->setCurHealth(it->getMaxHealth());
                }
                cout<<"Your inventories are all fixed well!"<<endl;
            }
            else if(input=="Q"||input=="q"){
                ;
            }
        }
        else if (input=="D"||input=="d"){
            player.showState();
            pack.showPack();
                char input;
            cout<<endl;
            cout<<"Choose next movement: \n"
                <<"A: Change inventory\n"
                <<"Q: Quit"<<endl;
            while(1){
                cout<<"Input: ";
                cin>>input;
                cout<<endl;

                if(input=='Q'||input=='q'){
                    break;
                }
                else if(input=='A'||input=='a'){
                    player.changeInventory(&pack);
                    break;
                }
                else
                    cout<<"No! No! You have to choose another correct choice!\n";
            }
        }
        else if (input == "E" || input == "e") {
            callPausePage();
        }
        else if (input == "cat") {
            cout << endl;
            cout << rooms.at(0).getObjects().at(0)->getName() << ": ";
            string react = rooms.at(0).getObjects().at(0)->triggerEvent(rooms.at(0).getObjects().at(0));
            if (react != "1") {
                cout << "Oops! It seems " << rooms.at(0).getObjects().at(0)->getName() << " doesn't want to interact with you!" << endl;
            }
            cout << endl << endl;
        }
        else {
            cout << endl;
            cout << "No! No! You have to choose another correct choice!";
            cout << endl;
        }
    }

}
void Dungeon::callPausePage() {
    if (player.getCurrentRoom() == &rooms.at(0)) {
        cout << "PAUSE\n"
            << "A: RESUME\n"
            << "B: CHANGE MY NAME\n"
            << "C: TAKE OUT MY MAP\n"
            << "D: BACK TO MAIN PAGE\n"
            << "Input: ";

        string input;   cin >> input;
        cout<<endl;
        if (input == "A" || input == "a") {
            ;
        }
        else if (input == "B" || input == "b") {
            callSettingPage();
        }
        else if (input == "C" || input == "c") {
            callDungeonMap();
        }
        else if (input == "D" || input == "d") {
            callFirstPage();
        }
        else {
            cout << "No! No! You have to choose another correct choice!" << endl;
            callPausePage();
        }
    }
    else {
        cout << "PAUSE\n"
            << "A: RESUME\n"
            << "B: BACK TO HOME\n"
            << "Input:";

        string input;   cin >> input;
        cout<<endl;
        if (input == "A" || input == "a") {
            ;
        }
        else if (input == "B" || input == "b") {
            player.changeRoom(&rooms.at(0));
            callMainPage();
//            player.setCurrentRoom(&rooms.at(0));
//            player.setPreviousRoom(&rooms.at(0));
        }

    }
}
void Dungeon::callSettingPage() {
    cout << "Do you want to change your name? (y/n)\n"
        << "Input: ";

    string input;   cin >> input;
    cout<<endl;
    string name;
    if (input == "y" || input == "Y") {
        cout << "What is your new name?\n"
            << "Input:";
        cin >> name;
        player.setName(name);
    }
    else
        callPausePage();
}
void Dungeon::callDungeonMap() {
//    if (player.getCurrentRoom() == &rooms.at(0)) {
//        cout << "You're at home now!" << endl;
//    }
//    else {
//        cout<<"Open map"<<endl;
//        for(int i=1;i<7;i++){
//            cout<<"---------
//        }
//    }
}

//void Dungeon::handleEvent(Object*)
void Dungeon::handleMovement(){
    Room* now=player.getCurrentRoom();

    int direct = 0;
    for(int i=0;i<4;i++){
        if(player.getPreviousRoom()==player.getCurrentRoom()->getRoom(i)){
            direct=i;
            break;
        }
    }

    cout<<"Where would you like to go?\n"
        <<"A: Move to up\n"
        <<"B: Move to down\n"
        <<"C: Move to left\n"
        <<"D: Move to right\n"
        <<"Q: Quit\n"
        <<"(I went from the ";

    switch(direct){
    case 0:
        cout<<"up side)\n";
        break;
    case 1:
        cout<<"left side)\n";
        break;
    case 2:
        cout<<"right side)\n";
        break;
    case 3:
        cout<<"down side)\n";
        break;
    default:
        cout<<"home)\n";
    }

    while(1){
        cout<<"Input: ";
        string input;   cin>>input;
        cout<<endl;

        if (input == "A" || input == "a") {

            if(player.getCurrentRoom()->getRoom(0)==NULL){
                cout<<"There is a wall, BRO!"<<endl;
                continue;
            }

            enterDungeon(player.getCurrentRoom(), player.getCurrentRoom()->getRoom(0));
            break;

        }
        else if (input == "B" || input == "b") {

            if(player.getCurrentRoom()->getRoom(3)==NULL){
                cout<<"There is a wall, BRO!"<<endl;
                continue;
            }

            enterDungeon(player.getCurrentRoom(), player.getCurrentRoom()->getRoom(3));
            break;

        }
        else if (input == "C" || input == "c") {

            if(player.getCurrentRoom()->getRoom(1)==NULL){
                cout<<"There is a wall, BRO!"<<endl;
                continue;
            }

            enterDungeon(player.getCurrentRoom(), player.getCurrentRoom()->getRoom(1));
            break;

        }
        else if (input == "D" || input == "d") {

            if(player.getCurrentRoom()->getRoom(2)==NULL){
                cout<<"There is a wall, BRO!"<<endl;
                continue;
            }

            enterDungeon(player.getCurrentRoom(), player.getCurrentRoom()->getRoom(2));
            continue;

        }
        else if (input=="Q"||input=="q"){
            break;
        }
        else {
            cout << "No! No! You have to choose another correct choice!" << endl;
            continue;

        }
    }
}
stack<Monster*> Dungeon::findMonsters(){
    stack<Monster*> targets;

    for(int i=0;i<player.getCurrentRoom()->getObjects().size();i++){
        Object* it=player.getCurrentRoom()->getObjects().at(i);
        if(it->getTag()=="minion_magic"||it->getTag()=="minion_physic"||it->getTag()=="boss"){
            Monster* temp=dynamic_cast<Monster*> (it);
            targets.push(temp);
        }
    }

    return targets;
}
void Dungeon::findTreasure(){
    Object* object = NULL;

//    for(int i=0;i<player.getCurrentRoom()->getObjects().size();i++){
//        cout<<player.getCurrentRoom()->getObjects().at(i)->getTag()<<endl;
//    }cout<<endl;

    bool haveTrea=0;
    for(int i=0;i<player.getCurrentRoom()->getObjects().size();i++){
        object = player.getCurrentRoom()->getObjects().at(i);

        if(object->getTag()=="treasure"){
            haveTrea=1;
            break;
        }

    }
    if(!haveTrea)
        return ;

    cout<<"Oh, Wow! We find a treasure box here! How lucky it is!\n"
        <<"Should we open it?\n";

    while(1){
        cout<<"A: Open\n"
            <<"B: Leave it alone\n";

        cout<<"Input: ";
        char input; cin>>input;
        cout<<endl;

        if(input=='A'||input=='a'){
            Box* trea = dynamic_cast<Box*>(object);
            if(trea->getNeedkey()){
                if(pack.getKey()==0){
                    cout<<"You don't have enough key to open it!"<<endl;
                    continue;
                }
            }

            object->triggerEvent(&pack);
            vector<Skill> player_skill = player.getSkills();

            if(!trea->getTreasure().empty()){
                cout<<"There are something inside:\n";
                for(int i=0;i<trea->getTreasure().size();i++){
                    cout<<trea->getTreasure().at(i).getSkillName()<<endl;

                    //delete the skill in box
                    bool a=1;
                    for(int j=0;j<player_skill.size();j++){
                        if(player_skill.at(j).getSkillName()==trea->getTreasure().at(i).getSkillName()){
                            a=0;
                            break;
                        }
                    }
                    if(a){
                        player_skill.push_back(trea->getTreasure().at(i));
                    }

                }
                cout<<endl;

                pack.setKey(pack.getKey()-1);
                player.setSkills(player_skill);
            }

            vector<Object*> newthing;
            for(int i=0;i<player.getCurrentRoom()->getObjects().size();i++){
                if(player.getCurrentRoom()->getObjects().at(i)->getTag()=="treasure"){
                    continue;
                }
                newthing.push_back(player.getCurrentRoom()->getObjects().at(i));
            }
            player.getCurrentRoom()->setObjects(newthing);

            break;

        }
        else if(input=='B'||input=='b'){
            cout<<"You don't want to have a look?\n"
                <<"That's a pity!\n"<<endl;
            break;
        }
        else{
            cout<<"No! No! You have to choose another correct choice!" << endl;
        }
    }
}

void Dungeon::fight(){
    stack<Monster*> targets = findMonsters();
    if(targets.empty()){
        cout<<"This room is clear!"<<endl;
        return ;
    }

    cout<<"Let's get them down:"<<endl;

    int howMany = 0;
    cout<<"Monsters: \n";
    while(!targets.empty()){
        cout<<targets.top()->getName()
            <<" ( "<<targets.top()->getCurrentHealth()<<" / "<<targets.top()->getMaxHealth()<<")"<<endl;
        targets.pop();
        howMany++;
    }

    int round=1;
    while(1){
        cout<<"Round "<<round<<":"<<endl;

        stack<Monster*> tt = findMonsters();
        int cc=0;
        while(!tt.empty()){
            tt.pop();
            cc++;
        }

        cout<<"Choose the next movement:\n"
            <<"A: Attack ("<<cc<<" remain)\n"
            <<"B: Open my backpack\n"
            <<"C: Retreat"<<endl;

        string input;
        while(1){
            cout<<"Input: ";    cin>>input;
            cout<<endl;
            if(input=="A"||input=="a"){
                chooseSkill();
                player.addSp();
                break;
            }
            else if (input == "B" || input == "b") {
                char input;
                Item* item;

                cout<<"You: ("<<player.getCurrentHealth()<<" / "<<player.getMaxHealth()<<" )"<<endl;
                cout<<"Enemy:\n";
                for(int k=0;k<player.getCurrentRoom()->getObjects().size();k++){
                    Monster* monster = dynamic_cast<Monster*>(player.getCurrentRoom()->getObjects().at(k));
                    if(monster->getTag()=="minion_physic"||monster->getTag()=="minion_magic"||monster->getTag()=="boss"){
                        cout<<monster->getName()<<" ("<<monster->getCurrentHealth()<<" / "<<monster->getMaxHealth()<<")\n";
                    }
                }
                cout<<"What potion do you want to use?\n";

                char num='A';
                vector<Item> temp;
                for(int j=0;j<pack.getPack().size();j++){
                    Item* it=&pack.getPack().at(j);
                    cout<<num<<": ";

                    if(it->getTag()=="potion_hp"){
                        cout << setiosflags(ios::left) << setw(15) << it->getName();
                        cout<<"heal: "<<it->getCurHealth()<<endl;

                        temp.push_back(*it);

                        num++;
                    }
                    if(it->getTag()=="potion_poison"){
                        cout << setiosflags(ios::left) << setw(15) << it->getName();
                        cout<<"Damage: "<<it->getAttack()<<endl;

                        temp.push_back(*it);

                        num++;
                    }
                }

                cout<<"Q: Quit\n";

                while(1){
                    cout<<"Input: ";    cin>>input;
                    cout<<endl;

                    if(input>='a')  input-='a';
                    else    input-='A';

                    if(input=='Q'||input=='q')
                        break;
                    if(input<0||input>=temp.size()){
                        cout<<"No! No! You have to choose another correct choice!\n";
                        continue;
                    }
//b y y b a b a b c b c a b a b
                    item = &temp.at(input);

                    if(item->getTag()=="potion_hp"){
                        player.setCurrentHealth(player.getCurrentHealth()+item->getCurHealth());

                        cout<<"Use "<<temp.at(int(input)).getName()<<" to me ("<<player.getCurrentHealth()<<" / "<<player.getMaxHealth()<<")"<<endl;
                    }
                    else{
                        stack<Monster*> attacked = findMonsters();
                        attacked.top()->setCurrentHealth(attacked.top()->getCurrentHealth()-item->getAttack());

                        cout<<"Use "<<temp.at(input).getName()<<" to "<<attacked.top()->getName()<<" ("<<attacked.top()->getCurrentHealth()<<" / "<<attacked.top()->getMaxHealth()<<")\n"<<endl;

                        if(attacked.top()->getCurrentHealth()<=0){
                            cout<<attacked.top()->getName()<<" is dead!\n"<<endl;

                            vector<Object*> objects;
                            int maxTime=0;
                            for(int i=0;i<player.getCurrentRoom()->getObjects().size();i++){
                                if(player.getCurrentRoom()->getObjects().at(i)->getName()==attacked.top()->getName()&&maxTime<1){
                                    maxTime++;
                                    continue;
                                }

                                objects.push_back(player.getCurrentRoom()->getObjects().at(i));
                            }

                            player.getCurrentRoom()->setObjects(objects);
                            attacked.pop();
                        }
                    }

                    temp.clear();
                    int cot=0;
                    for(int i=0;i<pack.getPack().size();i++){
                        if(pack.getPack().at(i).getName()==item->getName()&&cot<1){
                            cot++;
                            continue;
                        }
                        temp.push_back(pack.getPack().at(i));
                    }
                    pack.setPack(temp);

                    break;
                }


                break;
            }
            else if (input == "C" || input == "c") {
                return ;
            }
            else {
                cout << "No! No! You have to choose another correct choice!" << endl;
            }
        }

        targets=findMonsters();
        if(targets.empty()){
            break;
        }

        monsterAttack();
        targets=findMonsters();
        while(!targets.empty()){
//            cout<<"old top is "<<targets.top()->getName()<<" sp "<<targets.top()->getSp()<<endl;
            targets.top()->addSp();
//            cout<<"new top is "<<targets.top()->getName()<<" sp "<<targets.top()->getSp()<<endl;
            targets.pop();
        }
        round++;
    }
    cout<<endl;
}
void Dungeon::chooseSkill(){
    cout<<"Choose a skill: \n";
    player.showSkills();
    cout<<"(you have sp "<<player.getSp()<<" / "<<player.getMaxSp()<<")"<<endl;

    char index;
    stack<Monster*> targets = findMonsters();

    while(1){
        cout<<"Input: ";    cin>>index;
        cout<<endl;

        if(index>='a')  index-='a';

        if(index>=player.getSkills().size()){
            cout<<"No! No! You have to choose another correct choice!"<<endl;
            continue;
        }

        Skill usingSkill=player.getSkills().at(index);

        if(player.getSp()<usingSkill.getSkillSp()){
            cout<<"You don't have enough SP!"<<endl;
            continue;
        }

        break;
    }

    Skill usingSkill=player.getSkills().at(index);

    if(usingSkill.getSkillTag()=="heal"){
        cout<<"Use "<<usingSkill.getSkillName()<<" to "<<player.getName()<<"..."<<endl;

        player.setSp(player.getSp()-usingSkill.getSkillSp());
        player.setCurrentHealth(player.getCurrentHealth() + usingSkill.getSkillDamage());

        for(int i=0;i<player.getInventory().size();i++){
            Item equip = player.getInventory().at(i);
            if(equip.getTag()=="right"){
                equip.setCurHealth(equip.getCurHealth()-3);
                break;
            }
        }

        cout<<"You heal yourself. ("<<player.getCurrentHealth()<<" / "<<player.getMaxHealth()<<")\n";
    }
    else{
        cout<<"Use "<<usingSkill.getSkillName()<<" to "<<targets.top()->getName()<<"..."<<endl;

        player.setSp(player.getSp()-usingSkill.getSkillSp());
        targets.top()->setCurrentHealth(targets.top()->getCurrentHealth()-player.getTotalAtk()-usingSkill.getSkillDamage());

        cout<<targets.top()->getName()<<" is damaged by "<<player.getTotalAtk()+usingSkill.getSkillDamage()<<" hp!\n";

    //    cout<<"it has "<<player.getCurrentRoom()->getObjects().at(0)->


        if(targets.top()->getCurrentHealth()<=0){
            cout<<targets.top()->getName()<<" is dead!"<<endl;

            vector<Object*> objects;
            int maxTime=0;
            for(int i=0;i<player.getCurrentRoom()->getObjects().size();i++){
                if(player.getCurrentRoom()->getObjects().at(i)->getName()==targets.top()->getName()&&maxTime<1){
                    maxTime++;
                    continue;
                }

                objects.push_back(player.getCurrentRoom()->getObjects().at(i));
            }

            player.getCurrentRoom()->setObjects(objects);
            targets.pop();
        }
    }

    if(targets.empty()){
        cout<<"You clear this room!\n";
        return ;
    }

    //show monsters hp
    stack<Monster*> temp=targets;
    while(!temp.empty()){
        cout<<temp.top()->getName()<<" ("<<temp.top()->getCurrentHealth()<<" / "<<temp.top()->getMaxHealth()<<")"<<endl;
        temp.pop();
    }
    cout<<endl;
}
void Dungeon::monsterAttack(){
    stack<Monster*> targets = findMonsters();
    stack<Monster*> temp = targets;

    if(targets.empty())
        return ;

//    _sleep(1*1000);
    cout<<"It's monsters time!"<<endl;

    while(!temp.empty()){
        if(temp.top()->getTag()=="minion_physic"){
            int time = rand()%(lib.getSkills(0).size() + 2);
            Monster* minion = temp.top();

            if(time<lib.getSkills(0).size()){
                Skill skill = lib.getSkills(0).at(time);

                if(skill.getSkillTag()=="physic"&&minion->getSp()>=skill.getSkillSp()){
                    minion->setSp(minion->getSp()-skill.getSkillSp());
//                    player.setCurrentHealth(player.getCurrentHealth()-minion->getAttack()-skill.getSkillDamage()+player.getTotalDef());
                    player.takeDamage(minion->getAttack()+skill.getSkillDamage()+player.getVar());

                    cout<<minion->getName()<<" uses "<<skill.getSkillName()<<" to you and causes "<<skill.getSkillDamage()+minion->getAttack()+player.getVar()<<" damage! ("<<player.getCurrentHealth()<<" / "<<player.getMaxHealth()<<")"<<endl;

                    if(!checkGameLogic())
                        exit(0);

                    temp.pop();
                    continue;
                }
            }
//            normal attack
//            player.setCurrentHealth(player.getCurrentHealth()-minion->getAttack());
            player.takeDamage(minion->getAttack()+player.getVar());
            cout<<minion->getName()<<" uses basic_chop to you and causes "<<minion->getAttack()+player.getVar()<<" damage! ("<<player.getCurrentHealth()<<" / "<<player.getMaxHealth()<<")"<<endl;

            temp.pop();

            if(!checkGameLogic())
                exit(0);
        }
        else if(temp.top()->getTag()=="minion_magic"){
            int time = rand()%(lib.getSkills(0).size()+2);
            Monster* minion = temp.top();

            if(time<lib.getSkills(0).size()){
                Skill skill = lib.getSkills(0).at(time);

                if(skill.getSkillTag()=="magic"&&minion->getSp()>=skill.getSkillSp()){
                    minion->setSp(minion->getSp()-skill.getSkillSp());
//                    player.setCurrentHealth(player.getCurrentHealth()-minion->getAttack()-skill.getSkillDamage()+player.getTotalDef());
                    player.takeDamage(minion->getAttack()+skill.getSkillDamage()+player.getVar());

                    cout<<minion->getName()<<" uses "<<skill.getSkillName()
                        <<" to you and causes "<<skill.getSkillDamage()+minion->getAttack()+player.getVar()<<" damage! ("<<player.getCurrentHealth()<<" / "<<player.getMaxHealth()<<")"<<endl;

                    if(!checkGameLogic())
                        exit(0);

                    temp.pop();
                    continue;
                }
            }
//                        normal attack
//            player.setCurrentHealth(player.getCurrentHealth()-minion->getAttack());
            player.takeDamage(minion->getAttack());
            cout<<minion->getName()<<" uses magic_ball to you and causes "<<minion->getAttack()+player.getVar()<<" damage! ("<<player.getCurrentHealth()<<" / "<<player.getMaxHealth()<<")"<<endl;
            temp.pop();

            if(!checkGameLogic())
                exit(0);
        }
        else{
            int ta = rand()%2;
            int tb = rand()%(lib.getSkills(ta).size()+1);
            Monster* boss = temp.top();

            if(tb<lib.getSkills(ta).size()){
                Skill skill = lib.getSkills(ta).at(tb);

                if(boss->getSp()>=skill.getSkillSp()){
                    boss->setSp(boss->getSp()-skill.getSkillSp());
//                    player.setCurrentHealth(player.getCurrentHealth()-boss->getAttack()-skill.getSkillDamage());
                    player.takeDamage(boss->getAttack()+skill.getSkillDamage()+player.getVar());

                    cout<<boss->getName()<<" using "<<skill.getSkillName()
                        <<" attacks you and causes "<<skill.getSkillDamage()+boss->getAttack()+player.getVar()<<" damage!"<<endl;

                    if(!checkGameLogic())
                        exit(0);

                    temp.pop();
                    continue;
                }
            }
//                        normal attack
//            player.setCurrentHealth(player.getCurrentHealth()-boss->getAttack());
            player.takeDamage(boss->getAttack());
            cout<<boss->getName()<<" attacks you and causes "<<boss->getAttack()+player.getVar()<<" damage! ("<<player.getCurrentHealth()<<" / "<<player.getMaxHealth()<<")"<<endl;
            temp.pop();

            if(!checkGameLogic())
                exit(0);
        }
    }
    cout<<endl;
}
void Dungeon::enterDungeon(Room* prev, Room* now){
    player.changeRoom(now);
    if(player.getCurrentRoom()==&rooms.at(0)){
        callMainPage();
    }
    if(player.getCurrentRoom()==&rooms.at(rooms.size()-2)&&now->getObjects().size()==0){
        ending();
    }

    findTreasure();

    int num_monster=0;

    for(int i=0;i<now->getObjects().size();i++){
        string monsterTag = now->getObjects().at(i)->getTag();

        if(monsterTag == "minion_physic" || monsterTag == "minion_magic" || monsterTag == "boss"){
            num_monster++;
        }
    }

//    _sleep(1*1000);

    if(player.getCurrentRoom()->getIndex()==6){
        cout<<"This is boss room!\n"
            <<"Watch out! You have no chance to go back!"<<endl;
    }
    else if(player.getCurrentRoom()->getIndex()==7){
        cout<<"You enter a secret room!\n";
    }
    else{
        cout<<"This is NO."<<player.getCurrentRoom()->getIndex()<<" room.\n";
    }

    cout<<"What would you like to do?\n"
        <<"A: Move to another room.\n"
        <<"B: Fight with monster. ("<<num_monster<<" remain)\n"
        <<"C: Show what I get.\n"
        <<"D: Pause.\n"
        <<"Input: ";

    string input;   cin>>input;
    cout<<endl;
    if(input=="A"||input=="a"){
        if(!player.getCurrentRoom()->getIsExit()){
            cout<<"Fight to the end!\n"<<endl;
        }
        else
            handleMovement();
    }
    else if (input == "B" || input == "b") {
        fight();
    }
    else if (input == "C" || input == "c") {
        player.showState();
        pack.showPack();
        cout<<"\nQ: Quit\n";
        while(1){
            cout<<"Input: ";
            char w; cin>>w;
            cout<<endl;
            if(w=='q'||w=='Q'){
                break;
            }
            else{
                cout<<"No! No! You have to choose another correct choice!" << endl;
            }
        }
    }
    else if(input=="D"||input=="d"){
        callPausePage();
    }
    else {
        cout << "\nNo! No! You have to choose another correct choice!" << endl;
    }

    enterDungeon(player.getPreviousRoom(), player.getCurrentRoom());
}

void Dungeon::ending(){
    cout<<"-------------------------------------------\n"
        <<"|       CONGRATULATION!!   MORTAL!!        |\n"
        <<"|  I'LL REMEMBER YOUR BRAVE NAME FOR GOOD! |\n"
        <<"|               THAT'S ENOUGH!             |\n"
        <<"|          IT'S TIME TO LET YOU GO!        |\n"
        <<"|     I HOPE I CAN SEE YOU AGAIN SOON!!    |\n"
        <<"-------------------------------------------\n"
        <<"(You can choose to play again or quit, but it'll be harder and harder!)\n"
        <<"What's your decision?\n"
        <<"A: Enter the next difficulty.\n"
        <<"Q: Quit.\n";

    while(1){
        cout<<"Input: ";
        char input;    cin>>input;
        cout<<endl;

        if(input=='A'||input=='a'){
            cout<<"HAHAHAHA...I KNEW YOU MUST COME AGAIN!!"<<endl;
            rooms.clear();
            createLobby();
            createDungeon();
            player.changeRoom(&rooms.at(0));
            upgradeDifficulty();
            callMainPage();
        }
        else if(input=='Q'||input=='q'){
            callFirstPage();
        }
        else{
            cout << "No! No! You have to choose another correct choice!";
            cout << endl;
            continue;
        }

        break;
    }

}

void Dungeon::startGame(bool begin) {
    if (!begin)  return;

    cout << "THIS IS YOUR HOME, MORTAL!" << endl;
    callMainPage();
}
void Dungeon::runDungeon() {
    bool begin = 0;
    callFirstPage();
    begin = 1;
    startGame(begin);

}

bool Dungeon::checkGameLogic() {
    if(player.getCurrentHealth()<=0){
        cout<<"\nYou died!\tSend you back home!"<<endl;
        player.changeRoom(&rooms.at(0));
        player.setCurrentHealth(player.getMaxHealth());
        callMainPage();
        return 0;
    }
    if (inGame == 0)
        return 0;

    return 1;
    // return 1 == alive
    // return 0 == die
}

void Dungeon::upgradeDifficulty(){player.setVar(player.getVar()+1);}
