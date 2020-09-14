all: rest

rest: bin/Action.o bin/AlchoholicCustomer.o bin/CheapCustomer.o bin/Customer.o bin/Dish.o bin/Restaurant.o bin/SpicyCustomer.o bin/Table.o bin/VegetarianCustomer.o bin/main.o
	g++ -o bin/rest bin/Action.o bin/AlchoholicCustomer.o bin/CheapCustomer.o bin/Customer.o bin/Dish.o bin/Restaurant.o bin/SpicyCustomer.o bin/Table.o bin/VegetarianCustomer.o bin/main.o
	
bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp 

bin/Restaurant.o: src/Restaurant.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Restaurant.o src/Restaurant.cpp

bin/Action.o: src/Action.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Action.o src/Action.cpp

bin/Customer.o: src/Customer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Customer.o src/Customer.cpp

bin/Dish.o: src/Dish.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Dish.o src/Dish.cpp	

bin/Table.o: src/Table.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Table.o src/Table.cpp	

bin/AlchoholicCustomer.o: src/AlchoholicCustomer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/AlchoholicCustomer.o src/AlchoholicCustomer.cpp	

bin/CheapCustomer.o: src/CheapCustomer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/CheapCustomer.o src/CheapCustomer.cpp	

bin/SpicyCustomer.o: src/SpicyCustomer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/SpicyCustomer.o src/SpicyCustomer.cpp	

bin/VegetarianCustomer.o: src/VegetarianCustomer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/VegetarianCustomer.o src/VegetarianCustomer.cpp	

clean: 
	rm -f bin/*
