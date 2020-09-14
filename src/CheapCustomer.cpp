
#include <vector>
#include <string>
#include "../include/Customer.h"

using namespace std;

CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) , ordered(false){}

//the method always orders the cheapest dish in the menu. This customer orders only once.
//if didnt order yet ordered - false else true and will not order.
std::vector<int> CheapCustomer::order(const std::vector<Dish> &menu) {
    vector<int> order;
    vector<int> emptyOrders;
    int price =0;
    if (!menu.empty()){
    price = menu[0].getPrice();
    }
    if(menu.empty()||ordered==true){
        return emptyOrders; //if menu empty return empty order
    }
    int idOfCheapestDish=menu[0].getId();

    for (unsigned int j=0;j<menu.size();j++){ //going over the menu
        if(price > menu[j].getPrice()){  //if the dish in palce j has lower price
            price = menu[j].getPrice(); //temp price will be the price of dish placed j in menu
            idOfCheapestDish=menu[j].getId();
        }
    }

    order.push_back(idOfCheapestDish);
    ordered=true;
    return order;

}

std::string CheapCustomer::toString() const {
    return getId() + " " + getName() ;

}

CheapCustomer *CheapCustomer::clone() const {
    return new CheapCustomer(*this);
}

std::string CheapCustomer::toString_name_type() const {
    return getName()+","+"chp";
}
