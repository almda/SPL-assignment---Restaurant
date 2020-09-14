#ifndef TABLE_H_
#define TABLE_H_

#include <vector>
#include "Customer.h"
#include "Dish.h"
//This class represents a table in the restaurant
//Each table has a finite number of available seats - represented by capacity
//indicator if the table is open - bool open
//list of orders done by the table - orderList
//list of customers in the table - customersList

//this class has resource so rule of 5 is needed
typedef std::pair<int, Dish> OrderPair;

class Table{
public:
    //Rule Of Five
    virtual ~Table();//destructor
    Table(const Table &aTable); //copy constructor
    Table&operator=(const Table &aTable);//Assignment Operator
    Table(Table&& other); //The Move Constructor
    Table &operator=(Table && other);//The Move Assignment
    Table(int t_capacity);
    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    void order(const std::vector<Dish> &menu);
    void openTable();
    void closeTable();
    int getBill();
    bool isOpen();
private:
    int capacity;
    bool open;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList;
};


#endif