#include "BasicUser.h"

using namespace std;

BasicUser::BasicUser()
{
	costTransport = 0.0;
}

BasicUser::BasicUser(const string &countyb, const string &localityb, const string &streetb, int numberb, const string &blockb, int apartmentb, const string &countyd, const string &localityd, const string &streetd, int numberd, const string &blockd, int apartmentd, int id, const string &firstName, const string &lastName, const string &email, float costTransport) : User(countyb, localityb, streetb, numberb, blockb, apartmentb, countyd, localityd, streetd, numberd, blockd, apartmentd, id, firstName, lastName, email)
{
	this->costTransport = costTransport;
}

BasicUser::BasicUser(const BasicUser &unp) : User(unp)
{
	costTransport = unp.costTransport;
}

BasicUser &BasicUser::operator=(const BasicUser &unp)
{
	User::operator=(unp);
	costTransport = unp.costTransport;

	return *this;
}

void BasicUser::setTransportCost(int cost)
{
	costTransport = cost;
}

float BasicUser::getTransportCost()
{
	return costTransport;
}

void BasicUser::displayUser()
{
	cout << billingData << " " << deliveryData << " " << lastName << " " << firstName << " " << email << " " << UserID << endl;
	cout << costTransport;
}

string BasicUser::getUserType()
{
	return "BasicUser";
}

json BasicUser::toJSON()
{
	return json(*this);
}
