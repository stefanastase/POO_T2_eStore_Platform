#include "ShoppingCart.h"

ShoppingCart::ShoppingCart()
{	
	this->shoppingCart = map<int, int>();
	this->payMethod = "-";
}

ShoppingCart::ShoppingCart(const string &payMethod)
{
	this->shoppingCart = map<int, int>();
	this->payMethod = payMethod;
}

string &ShoppingCart::getPayMethod()
{
	return payMethod;
}

void ShoppingCart::setPayMethod(const string &payMethod)
{
	this->payMethod = payMethod;
}

void ShoppingCart::addProduct(int id, int quantity)
{	
	shoppingCart.insert(pair<int, int>(id, quantity));
}

void ShoppingCart::raiseQuantity(int id, int quantity)
{
	shoppingCart[id] += quantity;
}

void ShoppingCart::lowerQuantity(int id, int quantity)
{
	shoppingCart[id] -= quantity;
}

int ShoppingCart::getQuantity(int productID)
{
	return shoppingCart.find(productID) != shoppingCart.end() ? shoppingCart.at(productID) : -1;
}

void ShoppingCart::deleteProduct(int productID)
{
	shoppingCart.erase(productID);
}

map<int, int> &ShoppingCart::getShoppingCart()
{
	return shoppingCart;
}

void ShoppingCart::displayShoppingCart()
{
	for(map<int, int>::iterator it = shoppingCart.begin(); it != shoppingCart.end(); it++)
		cout << it->first << " " << it->second << endl;
}

json ShoppingCart::toJSON()
{
  return json(*this);
}