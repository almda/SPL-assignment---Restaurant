#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "Dish.h"

class Customer{
public:
    Customer(std::string c_name, int c_id);
    virtual std::vector<int> order(const std::vector<Dish> &menu)=0;
    virtual std::string toString() const = 0;
    virtual std::string toString_name_type() const=0;
    std::string getName() const;
    int getId() const;
    virtual Customer* clone() const=0;
    virtual ~Customer();
private:
    const std::string name;
    const int id;
};


class VegetarianCustomer : public Customer {
public:
	VegetarianCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    std::string toString_name_type() const;
    virtual VegetarianCustomer* clone() const;
private:
};


class CheapCustomer : public Customer {
public:
	CheapCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    std::string toString_name_type() const;
    virtual CheapCustomer* clone() const;
private:
    bool ordered;
};


class SpicyCustomer : public Customer {
public:
	SpicyCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    std::string toString_name_type() const;
    virtual SpicyCustomer* clone() const;
private:
	bool fistOrderDone;
};


class AlchoholicCustomer : public Customer {
public:
	AlchoholicCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    std::string toString_name_type() const;
    virtual AlchoholicCustomer* clone() const ;
private:

	int idOfLastOrder;
	int placeOrdered;

};


#endif