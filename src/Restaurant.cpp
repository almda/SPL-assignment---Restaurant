///////////////////////////last version ori 20.11

#include "../include/Restaurant.h"
#include <iostream>
#include <fstream>
using namespace std;

//init new Restaurant that isn't open and didnt get any customer so id init to 0.
Restaurant::Restaurant():open(false),tables(),menu(),actionsLog(),idAvailable(0) {}

//By what writen in the "program flow" the Restaurant opens by calling the start func it prints the line below and opens the Restaurant
//After each executed action, the program waits for the next action in a loop.
void Restaurant::start() {
    //start an new restaurant by opening and prints
    std::cout<<"Restaurant is now open!"<< std::endl;
    open= true;
    string line="";//line that we read
    int closeAllDone =0;//a identifier of closeAll action - if closeAll is called - closeAllDone = 1.
    std::getline(cin,line);
    while(!line.empty()&&closeAllDone==0) {
            string command =""; //a string of all the command line that was written by user
            string action = ""; // the action that was written in command - 'close','status', 'move',...
            string numberForAction; //the number that we recognize in the command line
       for(unsigned int i=0;i<line.size();i++){
           command+=line[i];
           }
        unsigned int whereIsTheDelimiter=0;
           for(unsigned int j=0;j<command.size();j++){
               if(command[j]!=' '){
                   action+=command[j];//while there is no delimiter we will read the action to action string
                   whereIsTheDelimiter++;//
               }
               else if(command[j]==' '){
                   while(whereIsTheDelimiter<command.size()) {
                       numberForAction += command[whereIsTheDelimiter];
                       whereIsTheDelimiter++;
                       j++;
                   }
               }

       }
       if(action=="closeall"){
           actionCloseAll();
            closeAllDone=1;
            break;
       }
       else if(action=="backup"){
           actionBackup();
       }
       else if(action=="menu"){
           actionPrintMenu();
       }
       else if(action=="restore"){
           actionResote();
       }
       else if(action=="close"){
           actionClose(command);
       }
       ////////print table status
       else if(action =="status"){
           actionPrintstatusOfTable(command);
       }
       else if(action=="order"){
           actionOreder(command);
       }
       else if(action=="open"){
           actionOpentable(command);
       }
       else if(action=="move"){
           actionMove(command);

       }
       else if(action=="log"){
           actionPrintActionLog();
       }


       std::getline(cin,line);//reading line from
       if(line=="closeall"){ ///catch the closeall
           actionCloseAll();
           closeAllDone=1;
           break;
       }
    }


}

int Restaurant::getNumOfTables() const {
    return tables.size();
}

std::vector<Dish> &Restaurant::getMenu() {
    return this->menu;
}

const std::vector<BaseAction *> &Restaurant::getActionsLog() const {
    return actionsLog;
}

//destructor - all the fields need to be destruct
Restaurant::~Restaurant() {
    if(!tables.empty()) {
        for (auto &table : tables)
            if(table!= nullptr)
                delete table;
        tables.clear();
    }
    if(!menu.empty()) {
        menu.clear();
    }
    if(!actionsLog.empty())
    {
        for (auto &i : actionsLog)
            delete i;
        actionsLog.clear();
    }

}
//copy constructor - copy each one of fields from this to other
Restaurant::Restaurant(const Restaurant &other):open(other.open),tables(),menu(),actionsLog(),idAvailable(other.idAvailable) {
    open = other.open;
    idAvailable = other.idAvailable;
    for (const auto &i : other.menu)
        menu.push_back(i);
    for (auto table : other.tables)
        tables.push_back(new Table(*table));
    for (auto i : other.actionsLog)
        actionsLog.push_back(i->clone());
}

//Assignment Operator - The copy assignment operator is called when an existing object need to be assigned a new value
Restaurant& Restaurant::operator=(const Restaurant &other) {
    if (this ==& other) {
        return *this;
    }

    //destructor
    if(!tables.empty()) {
        for (auto &table : tables)
            if(table!= nullptr)
                delete table;
        tables.clear();
    }
    if(!menu.empty()) {
        menu.clear();
    }
    if(!actionsLog.empty())
    {
        for (auto &i : actionsLog)
            delete i;
        actionsLog.clear();
    }


    open = other.open;
    idAvailable = other.idAvailable;
    for (const auto &i : other.menu)
        menu.push_back(i);
    for (unsigned int i=0; i<other.tables.size();i++) {
        tables.push_back(new Table(*other.tables[i]));
    }
    for (auto i : other.actionsLog)
        actionsLog.push_back(i->clone());
    return *this;
}
//The Move Constructor
//we need to copy the fields of other to this and after delete all the fields of other
//The move constructor is called when a newly created object need to be initialized from rvalue.
Restaurant::Restaurant(Restaurant &&other):open(),tables(),menu(),actionsLog(),idAvailable(other.idAvailable) {
    if(!tables.empty()) {
        for (auto &table : tables)
            if(table!= nullptr)
                delete table;
        tables.clear();
    }
    if(!menu.empty()) {
        menu.clear();
    }
    if(!actionsLog.empty())
    {
        for (auto &i : actionsLog)
            delete i;
        actionsLog.clear();
    }
    open = other.open;
    idAvailable = other.idAvailable;
    for(unsigned int i=0;i<other.tables.size(); i++)
        tables.push_back(other.tables[i]);
    other.tables.clear();
    for(unsigned int i=0;i<other.actionsLog.size(); i++)
        actionsLog.push_back(other.actionsLog[i]);
    other.actionsLog.clear();
    for(unsigned int i=0;i<other.menu.size(); i++)
        menu.push_back(other.menu[i]);
    other.menu.clear();

}
//The Move Assignment - check if there is memory leak in the way i done.
//The move assignment operator is called when an existing object need to be assigned a new rvalue
Restaurant& Restaurant::operator=(Restaurant &&other) {
    //////////////////////destrucor
    if(!tables.empty()) {
        for (auto &table : tables)
            if(table!= nullptr)
                delete table;
        tables.clear();
    }
    if(!menu.empty()) {
        menu.clear();
    }
    if(!actionsLog.empty())
    {
        for (auto &i : actionsLog)
            delete i;
        actionsLog.clear();
    }
    /////////////end dest
    /////Assign
    for (const auto &i : other.menu)
        menu.push_back(i);
    tables = other.tables;
    actionsLog = other.actionsLog;
    idAvailable = other.idAvailable;
    open = other.open;
    return *this;
}

Table* Restaurant::getTable(int ind) {
    int howManyTabless=tables.size();
    if(!tables.empty() && ind<=howManyTabless)
        return tables[ind];
    return nullptr;
}

/////////////////////////////////////////////action to do at the Restaurant - the logic part of Restaurant
void Restaurant::actionResote() {
    RestoreResturant* restoreResturant = new RestoreResturant();
    restoreResturant->act(*this);
    actionsLog.push_back(restoreResturant);


}

void Restaurant::actionBackup() {
    BackupRestaurant* backupRestaurant = new BackupRestaurant;
    backupRestaurant->act(*this);
    actionsLog.push_back(backupRestaurant);
}


Restaurant::Restaurant(const std::string &configFilePath):open(),tables(),menu(),actionsLog(),idAvailable(0) {
    string line="";
    ifstream myfile (configFilePath);
    int lineCounter=0;
    std::vector<string> releventLines;
    string numberOftables;
    string tableCaps;
    std::vector<string> dishes;
        while (getline(myfile,line)){
            if(!line.empty()&&line.size()>0){
                int comment=0;
                for(string::iterator letter=line.begin();letter!=line.end();++letter){
                        if (*letter == '#') {
                            comment=1;
                            break;
                        }
                        break;
                    }
                    if(comment==0){
                        if(lineCounter==0) {
                            numberOftables=line;
                            releventLines.push_back(line);
                        }
                        else if(lineCounter==1) {
                            tableCaps=line+",";
                            releventLines.push_back(line);
                        }
                        else {
                            dishes.push_back(line+",");
                            releventLines.push_back(line);
                        }
                        lineCounter++;
                }

            }

        }
        if(lineCounter!=0){
            //create tables
            createTables(numberOftables,tableCaps);
            //create menu
            generateMenu(dishes);
            //handles memory Leak
            releventLines.clear();
            numberOftables.clear();
            tableCaps.clear();
            dishes.clear();
        }

    if(lineCounter==0){
        std::cout<<"Error in reading file - missing relevent information or can't read the file"<<std::endl;
        }

   // }
}

void Restaurant::actionPrintMenu() {
    //printing menu and saving to action log
    PrintMenu* menu = new PrintMenu();
    menu->act(*this);
    actionsLog.push_back(menu);

}

void Restaurant::actionClose(std::string &letter) {
    int tToClose=0;
    //the numbers : for the word "400" - numbers are '4','0','0'
    std::string numbers;
    for(unsigned int i=0; i<letter.length();i++){
        while(letter[i]!= ' '){
            i++;
        } i++;
        while(i!=letter.length()){
            numbers+=letter[i];
            i++;;
        }
    }
    tToClose=::stoi(numbers);
    //closing action and adding it to action log
    Close* cl = new Close(tToClose);
    cl->act(*this);
    actionsLog.push_back(cl);

}

void Restaurant::actionCloseAll() {
    //closing all tables in rest
    CloseAll* cla = new CloseAll();
    cla->act(*this);
    actionsLog.push_back(cla);
}

void Restaurant::actionPrintActionLog() {
    PrintActionsLog* pal = new PrintActionsLog();
    pal->act(*this);
    actionsLog.push_back(pal);
}

void Restaurant::actionPrintstatusOfTable(std::string &letter) {
    int tableId =-1;
    std::string numbers="";
    for(unsigned int i=0; i<letter.length();i++){
        while(letter[i]!= ' '){
            i++;
        } //adding chars to string
        i++;
          while(i!=letter.length()){
            numbers+=letter[i];
            i++;
        }
    }
    tableId=std::stoi(numbers);

    PrintTableStatus* pts = new PrintTableStatus(tableId);
    pts->act(*this);
    actionsLog.push_back(pts);

}
//the generating menu go over the menu vector that is a vector of line of strings -
// each line structure is "Beer,ALC,50" - Beer - dish name, ALC-dish type ,50-dishe price
//
void Restaurant::generateMenu(std::vector<std::string> &dishes) {
    if(dishes.size()>0&&!dishes.empty()){
        for(unsigned int i=0; i<dishes.size();i++){
            string name="";
            string type="";
            string price="";
            for(unsigned int j=0;j<dishes[i].size();j++){
                if(name.empty()){
                    while(dishes[i][j]!=',') {
                        name += dishes[i][j];
                        j++;
                    }
                }
                else if (type.empty()){
                    while(dishes[i][j]!=','){
                        type+=dishes[i][j];
                        j++;
                    }
                }
                else if(price.empty()){
                    while(dishes[i][j]!= ','){
                        price+=dishes[i][j];
                        j++;
                    }
                }
            }
            //check if all the parameters to create dish are available
            if(name.empty() | type.empty() | price.empty()){
                std::cout<<"cant find one of the parameters to genetare a dish\n"<<std::endl;
                if(name.empty())
                    std::cout<<"param name is missing\n"<<std::endl;
                if(type.empty())
                    std::cout<<"param type of dish is missing\n"<<std::endl;
                if(price.empty())
                    std::cout<<"param price of dish is missing\n"<<std::endl;
            }
            int etype=-1;

            if(type=="VEG"){
                etype=0;
                menu.push_back(Dish(i,name,std::stoi(price),VEG));
            }
            if(type=="SPC"){
                etype=1;
                menu.push_back(Dish(i,name,std::stoi(price),SPC));
            }
            if(type=="BVG"){
                etype=2;
                menu.push_back(Dish(i,name,std::stoi(price),BVG));
            }
            if(type=="ALC"){
                etype=3;
                menu.push_back(Dish(i,name,std::stoi(price),ALC));
            }
            if(etype==-1){
                std::cout<<"can't create dish\n"<<std::endl;
            }

        }

    }

}
//create tables
void Restaurant::createTables(std::string numberOftables, std::string tableCaps) {
    int howManyTabels=0;// how many tables in the rest
    string howMany="";
    std::vector<int> tablePlaces;
    for(unsigned int i=0;i<numberOftables.length();i++){
        if(numberOftables[i]!='\r'){
            howMany+=numberOftables[i];
        }
    }
    howManyTabels=std::stoi(howMany);
    string temp="";
    for(unsigned int i=0;i<tableCaps.length();i++){
        if(tableCaps[i]!=','){
            temp+=tableCaps[i];
        }
        else if(tableCaps[i]==','){
            int tmp =std::stoi(temp);
            tablePlaces.push_back(tmp);
            temp="";
        }
        else if(tableCaps[i]=='\r'){
            i=tableCaps.length();
        }

    }
    for(int i =0; i<howManyTabels;i++){
        tables.push_back(new Table(tablePlaces[i]));
    }
    tablePlaces.clear();

}


void Restaurant::actionMove(std::string &letter) {
    std::string srcTable="";
    std::string customerId="";
    std::string dstTable="";
    unsigned int i=5; // start after move_

    while(letter[i]!=' '){
        srcTable+=letter[i];
        i++;
    }//here we reached space 1
    i++;
    while(letter[i]!=' '){
        dstTable+=letter[i];
        i++;
    }//here we reached space 2
    i++;
    while(i<letter.size()){
        customerId+=letter[i];
        i++;
    }//ending


    int srcT= std::stoi(srcTable);
    int cId= std::stoi(customerId);
    int dstT= std::stoi(dstTable);


    MoveCustomer * move = new MoveCustomer(srcT,dstT,cId);
    move->act(*this);
    actionsLog.push_back(move);
}
void Restaurant::actionOreder(std::string &letter) {
    int tableId = -1;
    std::string orderName = "";
    std::string numberToOrder = "";
    std::string numbers="";
    for(unsigned int i=0; i<letter.length();i++){
        while(letter[i]!= ' '){
            i++;
        } //adding chars to string
        i++;
        while(i!=letter.length()){
            numbers+=letter[i];
            i++;
        }
    }
    tableId=std::stoi(numbers);
    Order* ord =new Order(tableId);
    if(tableId > this->getNumOfTables()){
        cout<<"Table does not exist or is not open"<<endl;
    }
    else if(!this->getTable(tableId)->isOpen()){
        cout<<"Table does not exist or is not open"<<endl;
    }
    else {
        ord->act(*this);
        actionsLog.push_back(ord);
    }
}

void Restaurant::actionOpentable(std::string &letter) {
    vector<Customer*> customers;
    unsigned int whereInLine=5;
    int tId=-1;
    string tableId;
    for(;whereInLine<letter.size();){
       while(letter[whereInLine]!=' ') {
           tableId+=letter[whereInLine];
           whereInLine++;

       }
       break;
    }
    tId=std::stoi(tableId);
    whereInLine++;
    string name;
    string type;
    for(;whereInLine<letter.size();whereInLine++){
        while(letter[whereInLine]!=' ' && letter[whereInLine]!=','){
            name+=letter[whereInLine];
            whereInLine++;
        }
        if(whereInLine ==letter.length() || letter[whereInLine]==' '||letter[whereInLine]==','){
            if(letter[whereInLine]==','){whereInLine++;}
            if(!name.empty()&& type.empty()){
                type+=letter[whereInLine];
                type+=letter[whereInLine+1];
                type+=letter[whereInLine+2];
                whereInLine=whereInLine+3;
                if(type=="alc"){
                    customers.push_back(new AlchoholicCustomer(name,idAvailable));/////////how will i konw the id!!
                }
                else if(type == "chp"){
                    customers.push_back(new CheapCustomer(name,idAvailable));
                }
                else if(type== "veg"){
                    customers.push_back(new VegetarianCustomer(name,idAvailable));
                }
                else if(type == "spc"){
                    customers.push_back(new SpicyCustomer(name,idAvailable));
                }
                else{
                    std::cout<<"cant create new customers for opening"<<std::endl;
                }
                if(!name.empty()&&!type.empty()){
                    name="";
                    type="";
                }
                idAvailable++;
            }
        }
    }
    OpenTable * openT = new OpenTable(tId,customers);
    openT->act(*this);
    actionsLog.push_back(openT);
}







