
#include <vector>
#include <string>
#include "../include/Customer.h"
using namespace std;

SpicyCustomer::SpicyCustomer(std::string name, int id) : Customer(name, id),fistOrderDone(false) {}

//This is a customer that orders the most expensive spicy dish in the menu.
//For further orders, he picks the cheapest non-alcoholic beverage in the menu.
std::vector<int> SpicyCustomer::order(const std::vector<Dish> &menu) {
    std::vector<int> order;
    std::vector<int> emptyOrder;
    //First order
    if (fistOrderDone == false) {
        int price = 0; //init price to 0 - lowest price
        int idOfExpensiveSpicy = 0; //what we want to find
        bool foundSPC; //identifier if we have SPC dish in the menu
        for(unsigned int i=0;i<menu.size();i++) {
            if (menu[i].getType() == SPC) {
                foundSPC = true; //if we have SPC dish in the menu we found SPC
                if (price < menu[i].getPrice()) {
                    idOfExpensiveSpicy = menu[i].getId();
                    price = menu[i].getPrice();
                }
                if(menu[i].getPrice()==price){
                    if(menu[i].getId()<idOfExpensiveSpicy)
                        idOfExpensiveSpicy=menu[i].getId();
                }
            }
        }
            this->fistOrderDone = true;//finishing first order and move further
            if(foundSPC==true)
                order.push_back(idOfExpensiveSpicy);//only if there is SPC dish order it.
            return order; // returns the first order
    }
    //Further orders -  cheapest non-alcoholic beverage in the menu
    if(fistOrderDone == true){
        //finding first non-alcoholic beverage
        int PriceOfBVG;
        int idOfCheapBVG;
        bool foundBVG= false;
        for(unsigned int i=0;i<menu.size();i++) {
            if (menu[i].getType() == BVG){
                foundBVG=true;
                PriceOfBVG=menu[i].getPrice();
                idOfCheapBVG=menu[i].getId();
                i=menu.size();//exit loop
            }
        }
        if (foundBVG == false)//if there is no BVG in menu then d'ont order
            return emptyOrder;

        else{
            for(unsigned int i=0;i<menu.size();i++){
                if (menu[i].getType() == BVG){
                    if(PriceOfBVG > menu[i].getPrice()) {
                        idOfCheapBVG = menu[i].getId();
                        PriceOfBVG =menu[i].getPrice();
                    }
                }
            }
        }
        order.push_back(idOfCheapBVG);
        return order;
    }
    return emptyOrder;
}
std::string SpicyCustomer::toString() const {
    return getId() + " " + getName() ;

}

SpicyCustomer *SpicyCustomer::clone() const {
    return new SpicyCustomer(*this);
}

std::string SpicyCustomer::toString_name_type() const {
    return getName()+","+"spc";
}
