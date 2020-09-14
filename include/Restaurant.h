
#ifndef RESTAURANT_H_
#define RESTAURANT_H_

#include <vector>
#include <string>
#include "Dish.h"
#include "Table.h"
#include "Action.h"

//this class has resource so rule of 5 is needed

class Restaurant{		
public:
	Restaurant();
    Restaurant(const std::string &configFilePath);
    void start();
    int getNumOfTables() const;
    Table* getTable(int ind);
	const std::vector<BaseAction*>& getActionsLog() const;
    std::vector<Dish>& getMenu();
	//Rule of 5.
	virtual ~Restaurant();//destructor
	Restaurant(const Restaurant &other); //copy constructor
	Restaurant&operator=(const Restaurant &other);//Assignment Operator
	Restaurant(Restaurant&& other); //The Move Constructor
	Restaurant &operator=(Restaurant && other);//The Move Assignment
private:
    void actionBackup();
    void actionResote();
    void actionOpentable(std::string& letter);
    void actionPrintMenu();
    void actionClose(std::string& letter);
    void actionCloseAll();
    void actionPrintActionLog();
    //move action
    void actionMove(std::string& letter);
    void actionPrintstatusOfTable(std::string& letter);
    //action create table
    void createTables(std::string numberOftables,std::string tableCaps);
    //action create menu
    void generateMenu(std::vector<std::string>& dishes);
    void actionOreder(std::string& letter);
    bool open;
    std::vector<Table*> tables;
    std::vector<Dish> menu;
    std::vector<BaseAction*> actionsLog;
    int idAvailable;
};

#endif
