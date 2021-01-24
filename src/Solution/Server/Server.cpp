#include "Server.h"

using namespace std;

/* NU MODIFICATI */
Server::Server(){}

/* NU MODIFICATI */
Server *Server::GetInstance()
{
	if (!instance)
	{
		instance = new Server;
	}

	return instance;
}

/* NU MODIFICATI */
Server::~Server()
{
	if (instance != NULL)
		instance = NULL;

	if (!__UserID__ProductsCart__.empty())
		__UserID__ProductsCart__.clear();
}

void Server::set__UserID__ProductsCart__()
{
	for(list<User*>::iterator it = usr.begin(); it != usr.end(); it++){
		int id = (*it)->getUserID();
		ShoppingCart* cart = new ShoppingCart();
		__UserID__ProductsCart__.insert(pair<int, ShoppingCart*>(id, cart));
		}
}

list<Product *> &Server::getProductsList()
{
	return prod;
}

list<User *> &Server::getUsersList()
{
	return usr;
}

map<int, ShoppingCart *> Server::get__UserID__ProductsCart__()
{
	return __UserID__ProductsCart__;
}

bool Server::requestAddProduct(int userID, int productID, int quantity)
{
	if(quantity > 0)
	{
		// Verificam daca utilizatorul cu userID se afla in lista de utilizatori
		list<User*>::iterator it = usr.begin();
		while(it != usr.end()){
			if((*it)->getUserID() == userID) break; // Utilizatorul se afla in lista de useri
			it++;
		}
		if(it == usr.end()) return false;

		// Verificam daca produsul cu productID se afla in lista de produse
		list<Product*>::iterator pit = prod.begin();
		while(pit != prod.end()){
			if((*pit)->getId() == productID){ // Produsul se afla in lista de produse
				if(!(*pit)->checkQuantity(quantity)) return false; // Verificam daca avem cantitatea
				break;
			}
			pit++;
		}
		if(pit == prod.end()) return false;
		
		ShoppingCart *reqCart = __UserID__ProductsCart__[userID]; 

		map <int, int> prodMap = reqCart->getShoppingCart();

		if(prodMap.find(productID) == prodMap.end()) 	// Verificam daca produsul nu se afla in cos
			reqCart->addProduct(productID, quantity);
		else
			reqCart->raiseQuantity(productID, quantity);
		
		(*pit)->decreaseQuantity(quantity); // Scadem cantitatea produsului


		return true;
	}
	
	return false;
}

bool Server::requestDeleteProduct(int userID, int productID, int quantity)
{
	if(quantity > 0)
	{
		// Verificam daca utilizatorul cu userID se afla in lista de utilizatori
		list<User*>::iterator it = usr.begin();
		while(it != usr.end()){
			if((*it)->getUserID() == userID) break; // Utilizatorul se afla in lista de useri
			it++;
		}
		if(it == usr.end()) return false;

		// Verificam daca produsul cu productID se afla in lista de produse
		list<Product*>::iterator pit = prod.begin();
		while(pit != prod.end()){
			if((*pit)->getId() == productID) break; // Produsul se afla in lista de produse 
			pit++;
		}
		if(pit == prod.end()) return false;
		
		ShoppingCart *reqCart = __UserID__ProductsCart__[userID];

		map <int, int> prodMap = reqCart->getShoppingCart();

		if(prodMap.find(productID) == prodMap.end()) return false; 	// Verificam daca produsul nu se afla in cos

		int cartQuantity = prodMap[productID];

		if(quantity >= cartQuantity)
			reqCart->deleteProduct(productID);
		else
			reqCart->lowerQuantity(productID, quantity);
		
		(*pit)->increaseQuantity(quantity);

		return true;
	}

	return false;
}

/* NU MODIFICATI */
void Server::populateProducts(const json &input)
{
	prod = ObjectFactory::getProductList(input["shoppingCart"]);
}

/* NU MODIFICATI */
void Server::populateUsers(const json &input)
{
	usr = ObjectFactory::getUserList(input["useri"]);
}