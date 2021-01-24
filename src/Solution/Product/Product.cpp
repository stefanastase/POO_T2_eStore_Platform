#include "Product.h"
using namespace std;

Product::~Product() {}

bool Product::checkQuantity(int requestedQuantity)
{
	return quantity >= requestedQuantity;
}

Product::Product(const string &category, int id, const string &name, int quantity)
{
	this->category = category;
	this->name = name;
	this->id = id;
	this->quantity = quantity;
}

Product::Product(const Product &p)
{
	(*this) = p;
}

Product::Product()
{
	this->id = 0;
	this->category = string();
	this->name = string();
	this->quantity = 0;
}

void Product::decreaseQuantity(int requestedQuantity)
{
	quantity -= requestedQuantity;
}

void Product::increaseQuantity(int requestedQuantity)
{
	quantity += requestedQuantity;
}

void Product::setCategory(const string &category)
{
	this->category = category;
}

void Product::setId(int id)
{
	this->id = id;
}

void Product::setQuantity(int quantity)
{
	this->quantity = quantity;
}

void Product::setName(const string &name)
{
	this->name = name;
}

string &Product::getCategory()
{
	return category;
}

int Product::getQuantity()
{
	return quantity;
}

int Product::getId()
{
	return id;
}

string &Product::getName()
{
	return name;
}

const Product &Product::operator=(const Product &a)
{
	if(this != &a){
		this->name = a.name;
		this->quantity = a.quantity;
		this->category = a.category;
		this->id = a.id;
	}

	return *this;
}

json Product::toJSON()
{
	return json(*this);
}
