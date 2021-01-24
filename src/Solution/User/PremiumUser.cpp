#include "PremiumUser.h"

using namespace std;

PremiumUser::PremiumUser():discounts()
{
	premiumSubscriptionCost = 0;
}

PremiumUser::PremiumUser(const string &countyb, const string &localityb, const string &streetb, int numberb, const string &blockb, int apartmentb,
						 const string &countyd, const string &localityd, const string &streetd, int numberd, const string &blockd, int apartmentd,
						 int id, const string &firstName, const string &lastName, const string &email, int premiumSubscriptionCost, const map<int, int> &discounts)
	: User(countyb, localityb, streetb, numberb, blockb, apartmentb, countyd, localityd, streetd, numberd, blockd, apartmentd, id, firstName, lastName, email)
{
	this->premiumSubscriptionCost = premiumSubscriptionCost;
	this->discounts = discounts;
}

PremiumUser::PremiumUser(const PremiumUser &up) : User(up)
{
	discounts = up.discounts;
	premiumSubscriptionCost = up.premiumSubscriptionCost;
}

const PremiumUser &PremiumUser::operator=(const PremiumUser &up)
{
	if(this != &up){
		User::operator=(up);
		discounts = up.discounts;
		premiumSubscriptionCost = up.premiumSubscriptionCost;
		}
	
	return *this;
}

void PremiumUser::displayUser()
{
	cout << billingData << " " << deliveryData << " " << lastName << " " << firstName << " " << email << " " << UserID << endl;
	
	for(map<int, int>::iterator it = discounts.begin(); it != discounts.end(); it++)
		cout << it->first << " " << it->second << endl;

	cout << premiumSubscriptionCost;
}

string PremiumUser::getUserType()
{
	return "PremiumUser";
}

float PremiumUser::getTransportCost()
{
	return 0.0;
}

map<int, int> &PremiumUser::getDiscounts()
{
	return discounts;
}

void PremiumUser::setDiscounts(map<int, int> red)
{
	discounts = red;
}

void PremiumUser::setPremiumSubscriptionCost(int cap)
{
	premiumSubscriptionCost = cap;
}

int PremiumUser::getPremiumSubscriptionCost()
{
	return premiumSubscriptionCost;
}

json PremiumUser::toJSON()
{
	return json(*this);
}