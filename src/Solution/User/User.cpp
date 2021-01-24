#include "User.h"
using namespace std;

User::~User()
{
}

User::User():billingData(), deliveryData(), lastName(), firstName(), email()
{
	UserID = 0;
}

User::User(const string &countyb, const string &localityb, const string &streetb, int numberb, const string &blockb, int apartmentb, const string &countyd, const string &localityd, const string &streetd, int numberd, const string &blockd, int apartmentd, int UserId, const string &lastName, const string &firstName, const string &email)
	: billingData(countyb, localityb, streetb, numberb, blockb, apartmentb),
	  deliveryData(countyd, localityd, streetd, numberd, blockd, apartmentd)
{
	this->UserID = UserId;
	this->lastName = lastName;
	this->firstName = firstName;
	this->email = email;
}

User::User(const User &u)
{
	*this = u;
}

const User &User::operator=(const User &u)
{
	if(this != &u){
		billingData = u.billingData;
		deliveryData = u.deliveryData;
		UserID = u.UserID;
		lastName = u.lastName;
		firstName = u.firstName;
		email = u.email;
	}

	return *this;
}

void User::setLastName(const string &lastName)
{
	this->lastName = lastName;
}
void User::setFirstName(const string &firstName)
{
	this->firstName = firstName;
}
void User::setEmail(const string &email)
{
	this->email = email;
}
void User::setUserID(int userID)
{
	this->UserID = userID;
}
void User::setBillingData(const Address &billingData)
{
	this->billingData = billingData;
}
void User::setDeliveryData(const Address &deliveryData)
{
	this->deliveryData = deliveryData;
}

string &User::getLastName()
{
	return lastName;
}
string &User::getFirstName()
{
	return firstName;
}
string &User::getEmail()
{
	return email;
}
int User::getUserID() const
{
	return UserID;
}

Address &User::getBillingData()
{
	return billingData;
}
Address &User::getDeliveryData()
{
	return deliveryData;
}

json User::toJSON()
{
	return json(*this);
}
