
#include <vector>
#include <string>
#include "../include/Customer.h"
#include "algorithm"

using namespace std;
VegetarianCustomer::VegetarianCustomer(std::string name, int id) : Customer(name, id) {}

//the method gets a menu and returns a vegetarian dish with the
//smallest id in the menu, and the most expensive beverage -BVG
std::vector<int> VegetarianCustomer::order(const std::vector<Dish> &menu) {
    std::vector <int> emptyorders;
    std::vector <int> orders;
    int numberOfBVG=-1;
    bool foundBVG= false;
    bool foundVEG = false;
    //finding first ID of BVG and VEG for next loop
    for(unsigned int i=0;i<menu.size();i++){
        if ((menu[i].getType() == VEG)&&(foundVEG == false)){
            foundVEG=true;
        }
        if((menu[i].getType()==BVG)&&(foundBVG == false)){
            numberOfBVG=menu[i].getId();
            foundBVG= true;
        }
        if((foundBVG == true)&&(foundVEG == true))
            i=menu.size();
    }
    if((foundBVG == false)||(foundVEG == false)){// if we d'ont have one of the req for order.
        return emptyorders;
    }
    vector<int> vegMenu;
    vector<int> bvgMenu;
    for(unsigned int i=0;i<menu.size();i++){
        if(menu[i].getType()==VEG){
            vegMenu.push_back(menu[i].getId());/////////////////was -1
        }
        if(menu[i].getType()==BVG){
            bvgMenu.push_back(menu[i].getPrice());
        }
    }
    std::stable_sort(vegMenu.begin(),vegMenu.end());
    std::stable_sort(bvgMenu.begin(),bvgMenu.end());
    for(unsigned int i=0; i<menu.size();i++){
        if(menu[i].getType()==BVG){
           if(menu[i].getPrice()==bvgMenu[bvgMenu.size()-1]){
               numberOfBVG=menu[i].getId(); //////////////////was -1
           }
        }
    }

    orders.push_back(vegMenu[0]);
    orders.push_back(numberOfBVG);
    return orders; //
}


std::string VegetarianCustomer::toString() const {
    return getId() + " " + getName() ;

}

VegetarianCustomer *VegetarianCustomer::clone() const {
    return new VegetarianCustomer(*this);
}

std::string VegetarianCustomer::toString_name_type() const {
    return getName()+","+"veg";
}

