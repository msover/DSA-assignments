#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(const Relation r) {
	this->relation = r;
	this->capacity = 10;
	this->elemCount= 0;
	this->hashTable = new Node*[this->capacity];
	for (int i = 0; i < this->capacity; i ++) {
		this->hashTable[i] = nullptr;
	}
}

void SortedMultiMap::resize() {
	int capacitySnapshot = this->capacity;
	this->capacity *= 2;
	Node** newHashTable = new Node*[this->capacity];
	for (int i = 0; i < this->capacity; i ++) {
		newHashTable[i] = nullptr;
	}
	for (int i = 0; i < capacitySnapshot; i ++) {
		Node* current = this->hashTable[i];
		while (current != nullptr) {
			Node* next = current->next;
			int desiredIndex = this->hashFun(current->data.first);
			Node* oldHead = newHashTable[desiredIndex];
			current->next = oldHead;
			newHashTable[desiredIndex] = current;
			current = next;
		}
	}
	delete[] this->hashTable;
	this->hashTable = newHashTable;
}

void SortedMultiMap::add(TKey c, TValue v) {
	if (this->elemCount >= this->capacity) {
		this->resize();
	}
	int hashIndex = this->hashFun(c);
	Node* newNode =  new Node(TElem(c, v), this->hashTable[hashIndex]);
	this->hashTable[hashIndex] = newNode;
	this->elemCount ++;
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> values;
	const int hashIndex = this->hashFun(c);
	Node* current = this->hashTable[hashIndex];
	while (current != nullptr) {
		if (current->data.first == c) {
			values.push_back(current->data.second);
		}
		current = current->next;
	}
	return values;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	TElem element = pair<TKey, TValue>(c, v);
	const int hashIndex = this->hashFun(c);
	Node* current = this->hashTable[hashIndex];
	Node* prev = nullptr;
	while (current != nullptr) {
		if (current->data == element) {
			if (prev == nullptr) {
				this->hashTable[hashIndex] = current->next;
			} else {
				prev->next = current->next;
			}
			this->elemCount --;
			delete current;
			return true;
		}
		prev = current;
		current = current->next;
	}
    return false;
}


int SortedMultiMap::size() const {
	return this->elemCount;
}

bool SortedMultiMap::isEmpty() const {
	return this->elemCount == 0;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	for (int i = 0; i < this->capacity; i ++) {
		Node* current = this->hashTable[i];
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}
	delete[] this->hashTable;
}
