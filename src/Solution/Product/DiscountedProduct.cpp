#include "DiscountedProduct.h"
using namespace std;

DiscountedProduct::DiscountedProduct() : NonFoodProduct()
{
	discountPercentage = 0;
}

DiscountedProduct::DiscountedProduct(const string &category, int id, const string &producer, const string &name, float price, int yearsOfWarranty, int discountPercentage, int quantity)
	: NonFoodProduct(category, id, producer, name, price, yearsOfWarranty, quantity)
{
	this->discountPercentage = discountPercentage;
}

DiscountedProduct::DiscountedProduct(const DiscountedProduct &discountedProduct) : NonFoodProduct(discountedProduct)
{
	discountPercentage = discountedProduct.discountPercentage;
}

float DiscountedProduct::priceAfterDiscount() const
{
	return (100 - discountPercentage) * price; // to pass the test
}

float DiscountedProduct::getDiscountPercentage()
{
	return discountPercentage;
}

const DiscountedProduct &DiscountedProduct::operator=(const DiscountedProduct &a)
{	
	if(this != &a){
		NonFoodProduct::operator=(a);
		discountPercentage = a.discountPercentage;
	}

	return *this;
}

void DiscountedProduct::setDiscountPercentage(int discountPercentage)
{
	this->discountPercentage = discountPercentage;
}

string DiscountedProduct::getProductType()
{
	return "DiscountedProduct";
}

json DiscountedProduct::toJSON()
{
	return json(*this);
}

void DiscountedProduct::display()
{
	cout << "Product Redus" << endl;
	cout << "Nume Product: " << this->name << endl;
	cout << "Producator: " << this->producer << endl;
	cout << "Categorie: " << this->category << endl;
	cout << "ID: " << this->id << endl;
	cout << "Cantitate: " << this->quantity << endl;
	cout << "Garantie: " << this->yearsOfWarranty << " ani" << endl;
	cout << "Pret: " << this->price << endl;
	cout << "Procent reducere : " << this->discountPercentage << endl
		 << endl;
}