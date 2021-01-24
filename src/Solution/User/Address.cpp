#include "Address.h"

using namespace std;

Address::Address()
{
	county = string();
	locality = string();
	street = string();
	number = 0;
	block = string();
	apartment = 0;
}

Address::Address(const Address &address)
{
	*this = address;
}

Address::Address(const string &county, const string &locality, const string &street, int number, const string &block, int apartment)
{
	this->county = county;
	this->locality = locality;
	this->street = street;
	this->number = number;
	this->block = block;
	this->apartment = apartment;

}

const Address &Address::operator=(const Address &adr)
{
	if(this != &adr){
		county = adr.county;
		locality = adr.locality;
		street = adr.street;
		number = adr.number;
		block = adr.block;
		apartment = adr.apartment;
	}

	return *this;
}

void Address::setStrada(const string &str)
{
	street = str;
}

void Address::setNumber(int nr)
{
	number = nr;
}

void Address::setBlock(const string &bl)
{
	block = bl;
}

void Address::setApartment(int ap)
{
	apartment = ap;
}

void Address::setCounty(const string &county)
{
	this->county = county;
}

void Address::setLocality(const string &loc)
{
	locality = loc;
}

string &Address::getStreet()
{
	return street;
}

int Address::getNumber()
{
	return number;
}
string &Address::getBlock()
{
	return block;
}

int Address::getApartment()
{
	return apartment;
}

string &Address::getCounty()
{
	return county;
}

string &Address::getLocality()
{
	return locality;
}

bool Address::operator==(const Address &address)
{
	if(county != address.county || locality != address.locality || street != address.street ||
		number != address.number || block != address.block || apartment != address.apartment)
		return 0;
	return 1;
}

bool Address::operator!=(const Address &address)
{
	return !(*this == address);
}

ostream &operator<<(ostream &os, const Address &a) // Mai modific eventual
{
	os << a.county << " " << a.locality << " " << a.street << " "
		<< a.number << " " << a.block << " " << a.apartment;
	
	return os;
}

json Address::toJSON()
{
	return json(*this);
}