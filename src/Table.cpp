//
// Created by orisha@wincs.cs.bgu.ac.il on 11/7/18.
//

#include "../include/Table.h"
#include "../include/Customer.h"

using namespace std;

Table::Table(int t_capacity):capacity(t_capacity) ,open(false),customersList(),orderList() {}

int Table::getCapacity() const {
    return this->capacity;
}
void Table::addCustomer(Customer *customer) {
        customersList.push_back(customer);
}
//remove Customer from the vector, the delete comes in at close
void Table::removeCustomer(int id) {
    for(unsigned int i=0;i<customersList.size();i++) {
        if(customersList[i]->getId()==id) {
            customersList.erase(customersList.begin() + i);
        }
    }
}

Customer *Table::getCustomer(int id) {
    for(unsigned int i=0;i<customersList.size();i++){
        if(customersList[i]->getId()==id){
            return customersList[i];
        }
    }
    return nullptr;
}

std::vector<Customer *> &Table::getCustomers() {
    return customersList;
}

std::vector<OrderPair> &Table::getOrders() {
    return orderList;
}

void Table::openTable() {
    open = true;
}

void Table::closeTable() {
    open = false;
}

bool Table::isOpen() {
    return open;
}
//method gives the bill of the table by going over the the orderlist and from each order takes the dish price
int Table::getBill() {
    int bill=0;
    for (unsigned int i =0;i<orderList.size();i++){
        bill += orderList[i].second.getPrice();
    }
    return bill;
}

// order of table gets a menu of dishes and go over the customers and each one orders by his strategy - then the vector<int> of orders returns from each customer
//will be inserted to the orders will be inserted to the orderList- A list of pairs for each order in a table - (customer_id, Dish)

void Table::order(const std::vector<Dish> &menu) {
    for (unsigned int i = 0; i < customersList.size(); i++) {
        vector<int> temp = customersList[i]->order(menu);
        for (unsigned int currDish = 0; currDish < temp.size(); currDish++) {
            for (unsigned int j = 0; j < menu.size(); j++) {
                if (menu[j].getId() == temp[currDish]) {
                    OrderPair tempOrder(customersList[i]->getId(), menu[j]);
                    orderList.push_back((tempOrder));
                }
            }
        }
    }
}
//Rule of 3
//destructor - the only resource is the customers in the customersList and orderList
Table::~Table() {
    for(unsigned int i=0;i<customersList.size();i++){
        if(customersList[i]!= nullptr)
                delete(customersList[i]);
    }
    customersList.clear();
    orderList.clear();
}

//copy constructor - copy each one of the customers in to the customers list , and the order pairs to the order list
///the only resurce that we cant assign in is customersList which we need to move one by one by clone method
Table::Table(const Table &other):capacity(other.capacity),open(other.open),customersList(),orderList(other.orderList) {
    for (auto i : other.customersList)
        customersList.push_back(i->clone());
}
//Assignment Operator - The copy assignment operator is called when an existing object need to be assigned a new value
Table &Table::operator=(const Table &aTable) {
    if (this != &aTable) {
        capacity = aTable.capacity;
        open = aTable.open;
        for (unsigned int i = 0; i < orderList.size(); i++){
            orderList.pop_back();
        }
        orderList.clear();
        for (unsigned int i = 0; i < aTable.orderList.size(); i++) {
            orderList.push_back(aTable.orderList[i]);
        }
        for (unsigned int i = 0; i < customersList.size(); i++) {
            delete customersList[i];
        }
        customersList.clear();
        for (unsigned int i = 0; i < aTable.customersList.size(); i++) {
            customersList.push_back(aTable.customersList[i]);
        }
    }
    return *this;

}
//Another 2 rules - total Rule of 5
//The Move Constructor
//we need to copy the fields of other to this and after delete all the fields of other
//The move constructor is called when a newly created object need to be initialized from rvalue.
//std has a move action for move Constructor that works so we prefered it bacause it works :) - in rest it didnt worked :(
Table::Table(Table&& other):capacity(other.capacity),open(other.open),customersList(std::move(other.customersList)),orderList(std::move(other.orderList)) {
    other.capacity=0;
}

//The Move Assignment - check if there is memory leak in the way we done.
//The move assignment operator is called when an existing object need to be assigned a new rvalue
Table &Table::operator=(Table &&other) {
    if (this != &other) {
        capacity = other.capacity;
        open = other.open;
    }
    for (auto &i : customersList) {
        delete i;
    }
    customersList.clear();
    for (auto i : other.customersList)
        customersList.push_back(i);
    orderList.clear();
    for (const auto &i : other.orderList)
        orderList.push_back(i);

    return *this;
}


