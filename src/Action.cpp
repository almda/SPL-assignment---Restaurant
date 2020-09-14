
#include <string>
#include <iostream>
#include "../include/Action.h"
#include "../include/Restaurant.h"
extern Restaurant* backup;
using namespace std;

BaseAction::BaseAction():errorMsg(),status() {}

ActionStatus BaseAction::getStatus() const {
    return status;
}

//called after each method is completed
void BaseAction::complete() {
    status=COMPLETED;
}

//If the action resulted in an error then the protected method error(std::string errorMsg) should be called, in
//order to change the status to “ERROR” and update the error message.
void BaseAction::error(std::string errorMsg) {
    this->errorMsg = errorMsg;
    status = ERROR;
}

std::string BaseAction::getErrorMsg() const {
    return this->errorMsg;
}
///des for Baseaction
BaseAction::~BaseAction() {}


Order::Order(int id):theStringOforder(""),tableId(id) {}

//Takes an order from a given table.
//this function will perform an order from each customer in the table, and each customer will order according to his strategy.
//After finishing with the orders, a list of all orders should be printed.
//If the table doesn't exist,or isn't open, this action should result in an error: “Table does not exist or is not open”.
void Order::act(Restaurant &restaurant) {

    if(restaurant.getTable(tableId)!=nullptr && restaurant.getTable(tableId)->getCustomers().size()!=0 && restaurant.getTable(tableId)->isOpen()){
        unsigned  long i=restaurant.getTable(tableId)->getOrders().size();
        restaurant.getTable(tableId)->order(restaurant.getMenu());//getting the orders from customers and orderList is ready

        for(;i<restaurant.getTable(tableId)->getOrders().size();i++){
            string Cname,Dname;
            Cname = restaurant.getTable(tableId)->getCustomer(restaurant.getTable(tableId)->getOrders()[i].first)->getName();
            Dname = restaurant.getTable(tableId)->getOrders()[i].second.getName();
            std::cout<< Cname << " ordered " << Dname<<std::endl;
        }
        complete();
    }
    else{
        error("Table does not exist or is not open");
    }
}
std::string Order::toString() const {
    return "order " +to_string(tableId)+" Completed " ;
}

Order *Order::clone() const {
    return new Order(*this);
}

//Close Method
//Closes a given table. print the bill of the table to the screen. After this
//action the table should be open for new customers. If the table doesn't exist, or isn't
//open, this action result in an error: “Table does not exist or is not open”.
Close::Close(int id):tableId(id) {}

void Close::act(Restaurant& restaurant) {
    if(restaurant.getTable(tableId)!=nullptr && restaurant.getTable(tableId)->isOpen()) { //if table exist
        int tempBill = restaurant.getTable(tableId)->getBill();//getting bill
        restaurant.getTable(tableId)->closeTable();//changing status of table
        vector<Customer *> customersList = restaurant.getTable(tableId)->getCustomers();
        for (unsigned int i = 0; i < customersList.size(); i++) {//removing customers
            restaurant.getTable(tableId)->removeCustomer(customersList[i]->getId());
            delete(customersList[i]);
        }
        //////////////////
        restaurant.getTable(tableId)->getOrders().clear();
        /////////////////////////
        customersList.clear();
        complete();
        std::cout<<"Table "<<to_string(tableId)<<" was closed. "<<"Bill "<<tempBill<<"NIS"<<::endl;
    }
    else{
        std::cout<<"Table does not exist or is not open"<<std::endl;
        error("Table does not exist or is not open");
    }
}

std::string Close::toString() const {
    if (getStatus() == COMPLETED){
        return "Table "+ to_string(tableId)+" was closed. Bill Completed";
    }
    else{
        return "Table " +to_string(tableId)+" was closed"+ getErrorMsg();
    }

}

Close *Close::clone() const {
    return new Close(*this);
}

//Closes all tables in the restaurant, and then closes the restaurant and exits.
//The bills of all the tables that were closed by that action print sorted by the
//table id in an increasing order. Note that if all tables are closed in the restaurant, the
//action will just close the restaurant and exit. This action never results in an error.

CloseAll::CloseAll() {}

void CloseAll::act(Restaurant &restaurant) {
    for(int k=0;k<restaurant.getNumOfTables();k++) {
        if (restaurant.getTable(k) != nullptr && restaurant.getTable(k)->isOpen()) { //if table exist
            int tempBill = restaurant.getTable(k)->getBill();//getting bill
            restaurant.getTable(k)->closeTable();//changing status of table
            vector<Customer *> customersList = restaurant.getTable(k)->getCustomers();
            for (unsigned int i = 0; i < customersList.size(); i++) {//removing customers
                restaurant.getTable(k)->removeCustomer(customersList[i]->getId());
                delete(customersList[i]);
            }
            customersList.clear();
             std::cout << "Table " << to_string(k) << " was closed. " << "Bill " << tempBill << "NIS" << ::endl;
        }
    }
    complete();
}

std::string CloseAll::toString() const {
    return "Close all completed";
}

CloseAll *CloseAll::clone() const {
    return new CloseAll(*this);
}

//Prints the menu of the restaurant.
//This action never results in an error. - we assume that in the config we get a menu
PrintMenu::PrintMenu() {}

void PrintMenu::act(Restaurant &restaurant) {
    unsigned int howManyItems = restaurant.getMenu().size();
    for(unsigned int i=0;i<howManyItems;i++){
        Dish temp=Dish(restaurant.getMenu()[i].getId(),restaurant.getMenu()[i].getName(),restaurant.getMenu()[i].getPrice(),restaurant.getMenu()[i].getType());
        if(temp.getType()==0){
            std::cout<< (temp.getName()+" VEG  " +to_string(temp.getPrice())+"NIS")<<std::endl;
        }
        if(temp.getType()==1){
            std::cout<< (temp.getName()+" SPC  " +to_string(temp.getPrice())+"NIS")<<std::endl;
        }
        if(temp.getType()==2){
            std::cout<< (temp.getName()+" BVG  " +to_string(temp.getPrice())+"NIS")<<std::endl;
        }
        if(temp.getType()==3){
            std::cout<< (temp.getName()+" ALC  " +to_string(temp.getPrice())+"NIS")<<std::endl;
        }
    }
    complete();
}

std::string PrintMenu::toString() const {
    return "Printing Menu Completed";

}

PrintMenu *PrintMenu::clone() const {
    return new PrintMenu(*this);
}

BackupRestaurant::BackupRestaurant() {}

void BackupRestaurant::act(Restaurant &restaurant) {

    if(backup == nullptr){
        backup = new Restaurant(restaurant);
        complete();

    }
    else{
        *backup = restaurant;
        complete();
    }

}

std::string BackupRestaurant::toString() const {
    return "Backup Completed";
}

BackupRestaurant *BackupRestaurant::clone() const {
    return new BackupRestaurant(*this);
}

RestoreResturant::RestoreResturant() {}

void RestoreResturant::act(Restaurant &restaurant) {

    if(backup != nullptr){
        restaurant = *backup;
        complete();

    }
    else{
        error("No backup available");
        std::cout<<"No backup available"<<std::endl;
    }
}

std::string RestoreResturant::toString() const {
    if(getStatus()== COMPLETED){
        return "Backup completed";

    }
    else {
        return "Restore Resturant"+ getErrorMsg();
    }
}

RestoreResturant *RestoreResturant::clone() const {
    return new RestoreResturant(*this);
}

PrintActionsLog::PrintActionsLog(): tempLog(""){}

void PrintActionsLog::act(Restaurant &restaurant) {
    for(unsigned int i=0;i<restaurant.getActionsLog().size();i++){
        tempLog += restaurant.getActionsLog()[i]->toString() +"\n";
    }
    std::cout<<tempLog<<std::endl;
    complete();
}

std::string PrintActionsLog::toString() const {
    return "log Completed";
}

PrintActionsLog *PrintActionsLog::clone() const {
    return new PrintActionsLog(*this);
}

PrintTableStatus::PrintTableStatus(int id):tableId(id) {}

////Prints a status report of a given table. The report include the table status, a list of customers that are seating in the table, and a list of orders done by each customer.
// If the table is closed, only the table status should be printed.
//This action never results in an error.!!!!!!!!!!!! by what wrriten in  Ass spec so no need to check.
void PrintTableStatus::act(Restaurant &restaurant) {
    bool closed = false;
    Table* temp = restaurant.getTable(tableId);
    vector<Customer*> customerL = temp->getCustomers();
    if(temp->isOpen() && temp!= nullptr){
        std::cout<<"Table "+to_string(tableId)+" status: open"<<std::endl;
    }
    else{
        std::cout<<"Table "+to_string(tableId)+" status: close"<<std::endl;
        closed =true;
    }
    if(closed == false) {
        //printing Customers
        std::cout << "Customers:" << std::endl;
        for (unsigned int i = 0; i < customerL.size(); i++) {
            std::cout << to_string(temp->getCustomers()[i]->getId()) << " " << temp->getCustomers()[i]->getName()
                      << std::endl;
        }
        //printing orders
        std::cout << "Orders:" << std::endl;
        for (unsigned int i = 0; i < temp->getOrders().size(); i++) {
            int idOfCustomer = temp->getOrders()[i].first;
            int id = temp->getOrders()[i].second.getId();
            string name = temp->getOrders()[i].second.getName();
            int price = temp->getOrders()[i].second.getPrice();
            DishType type = temp->getOrders()[i].second.getType();
            Dish d = Dish(id, name, price, type);
            std::cout << (d.getName() + " " + to_string(d.getPrice()) + "NIS " + to_string(idOfCustomer)) << std::endl;
        }
        cout << "Current Bill: " << temp->getBill() << "NIS\n";
    }
    customerL.clear();
}

std::string PrintTableStatus::toString() const {
    return "status "+to_string(tableId)+" Completed";
}

PrintTableStatus *PrintTableStatus::clone() const {
    return new PrintTableStatus(*this);
}


//Moves a customer from one table to another. Also moves all orders
//made by this customer from the bill of the origin table to the bill of the destination table
MoveCustomer::MoveCustomer(int src, int dst, int customerId): srcTable(src),dstTable(dst),id(customerId) {}

void MoveCustomer::act(Restaurant &restaurant) {
    //table from
    Table *sourceTable = restaurant.getTable(srcTable);
    //table to
    Table *destenationTable = restaurant.getTable(dstTable);

    int dstTablePuls1 = destenationTable->getCustomers().size() + 1;
    if ( destenationTable != nullptr && sourceTable->getCustomer(id) != nullptr &&  destenationTable->getCapacity()>= dstTablePuls1 && destenationTable->isOpen() ) {
        //the orders to convert
        vector<OrderPair> tempOrder;

        Customer *customer = sourceTable->getCustomer(id);
        sourceTable->removeCustomer(id);
        destenationTable->addCustomer(customer);
        for (auto it = sourceTable->getOrders().begin(); it != sourceTable->getOrders().end();++it) {
            if (it.operator*().first == id) {
                destenationTable->getOrders().push_back(*it);
            }
            else {
                tempOrder.push_back(*it);
            }
        }
        sourceTable->getOrders().clear();
        for(unsigned int j=0;j<sourceTable->getCustomers().size();j++) {
            for (auto &i : tempOrder) {
                if(i.first == sourceTable->getCustomers()[j]->getId())
                    sourceTable->getOrders().push_back(i);
            }
        }
        if(restaurant.getTable(srcTable)->getCustomers().size()==0){
            restaurant.getTable(srcTable)->closeTable();
        }

        complete();
    }
    else {
        cout << "Cannot move customer" << "\n" ;
        error("Cannot move customer");
    }
}

std::string MoveCustomer::toString() const {
    if(getStatus()==COMPLETED){
        return "move "+ to_string(srcTable)+ " "+ to_string(dstTable)+ " " +to_string(id)+" Completed";
    }
    else {
        return "move "+ to_string(srcTable)+ " "+ to_string(dstTable)+" "+ to_string(id)+" "+getErrorMsg();
    }
}

MoveCustomer *MoveCustomer::clone() const {
    return new MoveCustomer(*this);
}


//this method Opens a given table and assigns a list of customers to it.
//If the table doesn't exist or is already open, this action should result in an error: “Table does not exist or is already open”.
OpenTable::OpenTable(int id, std::vector<Customer *> &customersList): tableId(id),customers(customersList) ,opentableInfo(""){}

void OpenTable::act(Restaurant &restaurant) {
    bool tableIsPartOfrest=true;
    if(this->tableId>restaurant.getNumOfTables()){

        for(unsigned int i=0;i<customers.size();i++){
            opentableInfo+=this->customers[i]->toString_name_type()+ " ";
        }
        for(unsigned int i=0;i<customers.size();i++){
           delete(this->customers[i]);
        }
        customers.clear();
        error(opentableInfo + "Error: Table does not exist or is already open");
        std::cout<<"Error: Table does not exist or is already open"<<std::endl;
        tableIsPartOfrest= false;
    }
    if(tableIsPartOfrest==true) {
        //if table exist we will get it
        Table *toOpen = restaurant.getTable(tableId);
        int howManyToInsetTotal = customers.size() + toOpen->getCustomers().size();
        if (toOpen != nullptr && !toOpen->isOpen() && toOpen->getCapacity() >= howManyToInsetTotal) {
            //opening table if the table really has the properties to be opened.
            toOpen->openTable();
            opentableInfo += to_string(tableId) + " ";
            for (unsigned int i = 0; i < customers.size(); i++) {
                toOpen->addCustomer(customers[i]);
                opentableInfo += customers[i]->toString_name_type() + " ";
            }
            customers.clear();
            complete();
        }
            //If the table doesn't exist or is already open.
        else {
            string tableDidntOpenInfo = "";
            for (unsigned int i = 0; i < customers.size(); i++) {
                tableDidntOpenInfo += customers[i]->toString_name_type() + " ";

            }
            for (unsigned int i = 0; i < customers.size(); i++) {
                delete (customers[i]);
            }
            customers.clear();
            error(tableDidntOpenInfo + "Error: Table does not exist or is already open");
            std::cout << "Error: Table does not exist or is already open" << std::endl;
        }
    }
}

std::string OpenTable::toString() const {

    if(getStatus()==COMPLETED){
        return "open " + opentableInfo +"Completed";
    }
    else{
        return "open " + to_string(tableId) + " "+ getErrorMsg();
    }
}


OpenTable *OpenTable::clone() const {
    return new OpenTable(*this);
}






