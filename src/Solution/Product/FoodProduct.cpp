#include "FoodProduct.h"

FoodProduct::FoodProduct()
{
	leiPerKg = 0;
	countryOfOrigin = string();
}

FoodProduct::FoodProduct(const string &category, int id, const string &name, float leiPerKg, const string &countryOfOrigin, int quantity) : Product(category, id, name, quantity)
{
	this->leiPerKg = leiPerKg;
	this->countryOfOrigin = countryOfOrigin;
}

FoodProduct::FoodProduct(const FoodProduct &pa) : Product(pa)
{
	leiPerKg = pa.leiPerKg;
	countryOfOrigin = pa.countryOfOrigin;
}

void FoodProduct::setLeiPerKg(float leiPerKg)
{
	this->leiPerKg = leiPerKg;
}

void FoodProduct::setCountryOfOrigin(const string &countryOfOrigin)
{
	this->countryOfOrigin = countryOfOrigin;
}

float FoodProduct::getLeiPerKg()
{
	return leiPerKg;
}

string &FoodProduct::getCountryOfOrigin()
{
	return countryOfOrigin;
}

const FoodProduct &FoodProduct::operator=(const FoodProduct &a)
{	
	if(this != &a){
		Product::operator=(a);
		leiPerKg = a.leiPerKg;
		countryOfOrigin = a.countryOfOrigin;
	}

	return *this;
}

string FoodProduct::getProductType()
{
	return "FoodProduct";
}

json FoodProduct::toJSON()
{
	return json(*this);
}

void FoodProduct::display()
{
	cout << "Product alimentar" << endl;
	cout << "Nume Product: " << this->name << endl;
	cout << "Categorie : " << this->category << endl;
	cout << "ID : " << this->id << endl;
	cout << "Cantitate (stoc): " << this->quantity << endl;
	cout << "Lei per KG : " << this->leiPerKg << endl;
	cout << "Tara de Origine : " << this->countryOfOrigin << endl
		 << endl;
}