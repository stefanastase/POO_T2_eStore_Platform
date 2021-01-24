#include "utility.h"

bool Utility::comparePrice(Product* first, Product* second)
{   
    NonFoodProduct* a = dynamic_cast<NonFoodProduct*>(first);
    NonFoodProduct* b = dynamic_cast<NonFoodProduct*>(second);

    if (a && b)
        return a->getPrice() < b->getPrice();
    
    return false;
}

bool Utility::compareFoodProduct(Product* first, Product* second)
{
    FoodProduct* a = dynamic_cast<FoodProduct*>(first);
    FoodProduct* b = dynamic_cast<FoodProduct*>(second);

    if (a && b){
        string a_name = a->getName(); //TODO toLower
        string b_name = b->getName();
        if (a_name < b_name)
            return true;
        else if (a_name > b_name)
            return false;
        
        string a_origin = a->getCountryOfOrigin();
        string b_origin = b->getCountryOfOrigin();
        if (a_origin < b_origin)
            return true;
        else if (a_origin > b_origin)
            return false;
        
        float a_price = a->getLeiPerKg();
        float b_price = b->getLeiPerKg();
        if (a_price < b_price)
            return true;
        else return false;
               
    }

    return false;
}

bool Utility::compareUID(const User* first, const User* second)
{
    return (first->getUserID() < second->getUserID());
}

string Utility::getMostPopularCounty(list<User*> usr)
{
    map<string, int> usersInCounty;

    for(list<User*>::iterator it = usr.begin(); it != usr.end(); it++){
        string county = (*it)->getDeliveryData().getCounty();
        if(usersInCounty.find(county) != usersInCounty.end())
            usersInCounty[county]++;
        else
            usersInCounty.insert(pair<string, int>(county, 1));
    }

    int maxNumber = 0;
    string maxCounty;
    for(map<string, int>::iterator it = usersInCounty.begin(); it != usersInCounty.end(); it++)
        if(it->second > maxNumber){
            maxNumber = it->second;
            maxCounty = it->first;
        }
    
    return maxCounty;
}

list<int> Utility::getPhonesAndPrintersIDs(list<Product*> prod)
{
    list<int> ids;

    for(list<Product*>::iterator it = prod.begin(); it != prod.end(); it++){
        string category = (*it)->getCategory();
        if(category == "telefon" || category == "imprimanta")
            ids.push_back((*it)->getId());
    }

    return ids;
}

bool Utility::isHouse(Address a)
{
    return (a.getBlock() == "-" && a.getApartment() == 0);
}