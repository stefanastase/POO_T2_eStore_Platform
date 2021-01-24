#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "../Solution/Product/NonFoodProduct.h"
#include "../Solution/Product/FoodProduct.h"
#include "../Solution/User/User.h"

class Utility{
    public:
        static bool comparePrice(Product*, Product*);
        static bool compareFoodProduct(Product*, Product*);
        static bool compareUID(const User*, const User*);

        static string getMostPopularCounty(list<User*>);
        static list<int> getPhonesAndPrintersIDs(list<Product*>);
        
        static bool isHouse(Address);

};