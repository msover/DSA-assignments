#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	this->snapshotCapacity = 10;
	this->snapshotSize = 0;
	this->snapshotElements = new TElem[this->snapshotCapacity];
	for (int i = 0; i < this->map.capacity; i ++) {
		SortedMultiMap::Node* current =  this->map.hashTable[i];
		while (current != nullptr) {
			this->appendToSnapshot(current->data);
			current = current->next;
		}
	}
	for (int i = 0; i < this->snapshotSize; i++) {
		for (int j = i + 1; j < this->snapshotSize; j++) {
			if (!this->map.relation(this->snapshotElements[i].first, this->snapshotElements[j].first)) {
				const TElem aux = this->snapshotElements[i];
				this->snapshotElements[i] = this->snapshotElements[j];
				this->snapshotElements[j] = aux;
			}
		}
	}

	this->position = 0;

}

void SMMIterator::first(){
	this->position = 0;
}

void SMMIterator::next(){
	if (!this->valid()) {
		throw std::exception();
	}
	this->position ++;
}

bool SMMIterator::valid() const{
	return this->position >= 0 && this->position < this->snapshotSize;
}

TElem SMMIterator::getCurrent() const{
	if (!this->valid()) {
		throw std::exception();
	}
	return this->snapshotElements[this->position];
}

void SMMIterator::resizeSnapshot() {
	this->snapshotCapacity *= 2;
	TElem* newSnapshot = new TElem[this->snapshotCapacity];
	for (int i = 0; i < this->snapshotSize; i++) {
		newSnapshot[i] = this->snapshotElements[i];
	}
	delete[] this->snapshotElements;
	this->snapshotElements = newSnapshot;
}

void SMMIterator::appendToSnapshot(const TElem& elem) {
	if (this->snapshotSize >= this->snapshotCapacity) {
		this->resizeSnapshot();
	}
	this->snapshotElements[this->snapshotSize ++] = elem;
}

SMMIterator::~SMMIterator() {
	delete[] this->snapshotElements;
}

