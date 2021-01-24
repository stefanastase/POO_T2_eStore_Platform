#include "LRUCache.h"
#include <algorithm>

using namespace std;

LRUCache::LRUCache(int capacity):lru(capacity)
{
	this->capacity = capacity;
	this->size = 0;
}

vector<int> LRUCache::processRequests(vector<int> requestsNo)
{
	for(vector<int>::iterator it = requestsNo.begin(); it != requestsNo.end(); it++){
		vector<int>::iterator pos = find(lru.begin(), lru.end(), *it);
		if(pos == lru.end()){
			if(size < capacity){
				lru[size] = *it;
				for(int i = size; i > 0; i--)
					swap(lru[i], lru[i - 1]);
				size++;
			}
			else{
				lru[size - 1] = *it;
				for(int i = size - 1; i > 0; i--)
					swap(lru[i], lru[i - 1]);
			}
		}
		else{
			for(vector<int>::iterator it1 = pos; it1 != lru.begin(); it1--)
				swap(*it1, *(it1 - 1));
		}
	}



	return lru;
}

int LRUCache::getCapacity()
{
	return capacity;
}

int LRUCache::getSize()
{
	return size;
}

vector<int> LRUCache::getLRU()
{
	return lru;
}

int LRUCache::getLRUCapacity()
{
	return lru.capacity();
}

void LRUCache::setCapacity(int capacity)
{
	this->capacity = capacity;
}

void LRUCache::setLRU(vector<int> aux)
{
	lru = aux;
}
