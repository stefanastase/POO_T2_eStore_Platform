#include "QuerySolver.h"

using namespace std;

/* NU MODIFICATI */
QuerySolver::QuerySolver() 
{
  server = Server::GetInstance();
}

/* NU MODIFICATI */
QuerySolver::~QuerySolver()
{
  if (server != nullptr) 
  {
    server = nullptr;
  }
}

list<Product*> QuerySolver::Query_3a(){
  
  list<Product*> espOnSale;
  list<Product*> prod = server->getProductsList();

  for (list<Product*>::iterator it = prod.begin(); it != prod.end(); it++)
      if ((*it)->getProductType() == "DiscountedProduct" && (*it)->getCategory() == "espressor")
        espOnSale.push_back(*it);
  
  return espOnSale;
}

list<User*> QuerySolver::Query_3b(){

  list<User*> lowTransportUsers;
  list<User*> usr = server->getUsersList();

  for(list<User*>::iterator it = usr.begin(); it != usr.end(); it++)
    if ((*it)->getUserType() == "BasicUser" && (*it)->getTransportCost() <= 11.5)
      lowTransportUsers.push_back(*it);

  return lowTransportUsers;
}

list<Product*> QuerySolver::Query_3c(){
  list<Product*> missingResealed;
  list<Product*> prod = server->getProductsList();

  for(list<Product*>::iterator it = prod.begin(); it != prod.end(); it++){
    if(ResealedProduct* temp = dynamic_cast<ResealedProduct*>(*it))
      if(temp->getReason() == "lipsa_accesorii")
        missingResealed.push_back(*it);
  }

  missingResealed.sort(Utility::comparePrice);

  return missingResealed;
}

list<Product*> QuerySolver::Query_3d(){
  list<Product*> foodProducts;
  list<Product*> prod = server->getProductsList();

  for(list<Product*>::iterator it = prod.begin(); it != prod.end(); it++){
    if(dynamic_cast<FoodProduct*>(*it))
      foodProducts.push_back(*it);
  }

  foodProducts.sort(Utility::compareFoodProduct);

  return foodProducts;
}

list<User*> QuerySolver::Query_3e(){
  list<User*> houseLivingPopularCounty;
  list<User*> usr = server->getUsersList();
  string mostPopularCounty = Utility::getMostPopularCounty(usr);

  for(list<User*>::iterator it = usr.begin(); it != usr.end(); it++){
    Address delAdr = (*it)->getDeliveryData();
    Address bilAdr = (*it)->getBillingData();
    if(delAdr.getCounty() == mostPopularCounty && Utility::isHouse(delAdr) && Utility::isHouse(bilAdr))
        houseLivingPopularCounty.push_back(*it);
  }

  houseLivingPopularCounty.sort(Utility::compareUID);

  return houseLivingPopularCounty;
}

list<User*> QuerySolver::Query_3f()
{
  list<User*> usersWithPhoneAndPrinterDisc;
  list<User*> usr = server->getUsersList();
  list<Product*> prod = server->getProductsList();

  list<int> phoneAndPrintersIDs = Utility::getPhonesAndPrintersIDs(prod);

  for(list<User*>::iterator it = usr.begin(); it != usr.end(); it++)
    if(PremiumUser* pUsr = dynamic_cast<PremiumUser*>(*it)){
      map<int, int> disc = pUsr->getDiscounts();
      for(list<int>::iterator lit = phoneAndPrintersIDs.begin(); lit != phoneAndPrintersIDs.end(); lit++)
        if(disc.find(*lit) != disc.end()){
          usersWithPhoneAndPrinterDisc.push_back(*it);
          break;
        }
    }

  return usersWithPhoneAndPrinterDisc;

}
