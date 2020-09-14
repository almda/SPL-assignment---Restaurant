
#include <iostream>
#include <vector>
#include <string>
#include "../include/Customer.h"
#include "algorithm"
using namespace std;

AlchoholicCustomer::AlchoholicCustomer(std::string name, int id) : Customer(name, id),idOfLastOrder(-1),placeOrdered(-1) {}

//This is a customer who only orders alcoholic beverages.
// He starts with ordering the cheapest one, and in each further order, he picks the next expensive alcoholic beverage.
// After reaching the most expensive alcoholic beverage, he won't order again.
std::vector<int> AlchoholicCustomer::order(const std::vector<Dish> &menu) {
    int countALC=0;
    vector<int> alvMenu;
    vector<int> order;
    vector<int> emptyOrder;
    //creating the alcoholic Menu
    for(unsigned int i=0;i<menu.size();i++){
        if(menu[i].getType()==ALC){
            countALC++;
            alvMenu.push_back(menu[i].getPrice());
        }
    }

    if(alvMenu.empty())
        return emptyOrder;
    if(placeOrdered==countALC)
        return emptyOrder;
    std::stable_sort(alvMenu.begin(),alvMenu.end());

    if(placeOrdered==-1){
        for(unsigned int i=0;i<menu.size();i++){
            if((menu[i].getType()==ALC)&&(menu[i].getPrice()==alvMenu[0])){
                idOfLastOrder=menu[i].getId();
                placeOrdered=1;
                order.push_back(menu[i].getId());
                return order;
            }
        }
    }
    if(placeOrdered!=-1){
        for(unsigned int i=0;i<menu.size();i++){
            if((menu[i].getType()==ALC)&&(menu[i].getPrice()==alvMenu[placeOrdered])&&(idOfLastOrder!=menu[i].getId())){
                idOfLastOrder=menu[i].getId();
                placeOrdered++;
                order.push_back(menu[i].getId());
                return order;
            }
        }


    }
    return order;
}

std::string AlchoholicCustomer::toString() const {
    return getId() + " " + getName() ;

}

AlchoholicCustomer *AlchoholicCustomer::clone() const {
    return new AlchoholicCustomer(*this);
}

std::string AlchoholicCustomer::toString_name_type() const {
    return getName()+","+"alc";
}
