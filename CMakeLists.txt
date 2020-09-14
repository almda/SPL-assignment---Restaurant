cmake_minimum_required(VERSION 3.12)
project(Ass1)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Ass1
        include/Action.h
        include/Customer.h
        include/Dish.h
        include/Restaurant.h
        include/Table.h
        src/Action.cpp
        src/AlchoholicCustomer.cpp
        src/CheapCustomer.cpp
        src/Customer.cpp
        src/Dish.cpp
        src/main.cpp
        src/Restaurant.cpp
        src/SpicyCustomer.cpp
        src/Table.cpp
        src/VegetarianCustomer.cpp)
