#include "Set.h"
#include "SetIterator.h"
Set::Set() {
	this->setSize = 0;
	this->setCap = 1;
	this->elems = new bool[setCap]{false};
	this->smallestElem = 0;
	this->elemsCount = 0;
}

void Set::resize(float capMultiplier) {
	this->setCap *= capMultiplier;
	bool* newElems = new bool[this->setCap]{false};
	for (int i = 0; i < this->setSize; i++) {
		newElems[i] = this->elems[i];
	}
	delete[] this->elems;
	this->elems = newElems;
}

void Set::shiftRight(int positions) {
	for (int i = this->setSize - 1; i >= 0; i --) {
		this->elems[i + positions] = this->elems[i];
		this->elems[i] = false;
	}
	this->setSize += positions;
}

void Set::shiftLeft(int positions) {
	for (int i = positions; i < this->setSize; i++) {
		this->elems[i - positions] = this->elems[i];
	}
	for (int i = this->setSize - 1; i >= this->setSize - positions; i--) {
		this->elems[i] = false;
	}
	this->setSize -= positions;
}

int Set::getTrueIndex(TElem elem) const{
	return elem - this->smallestElem;
}
bool Set::add(TElem elem) {
	if (search(elem)) return false;
	this->elemsCount ++;
	int trueIndex = getTrueIndex(elem);

	while (trueIndex >= this->setCap - this->setSize || -trueIndex >= this->setCap - this->setSize) {
		resize(2);
	}

	if (elem < this->smallestElem) {
		shiftRight(-trueIndex);
		this->smallestElem = elem;
		trueIndex = 0;
	}

	if (trueIndex >= this->setSize) {
		this->setSize = trueIndex + 1;
	}
	this->elems[trueIndex] = true;
	return true;
}

int Set::getSmallestElem() const {
	for (int i = 0; i < this->setSize; i++) {
		if (this->elems[i]) {
			return i + this->smallestElem;
		}
	}
	return NULL_TELEM;
}

bool Set::remove(TElem elem) {
	if (!search(elem)) return false;
	this->elems[getTrueIndex(elem)] = false;

	this->elemsCount --;
	if (elem == this->smallestElem) {
		this->smallestElem = getSmallestElem();
		if (smallestElem == NULL_TELEM) {
			this->setSize = 0;
			this->smallestElem = 0;
			return true;
		}
		int trueIndex = getTrueIndex(elem);
		shiftLeft(-trueIndex);
	}

	return true;
}

bool Set::search(TElem elem) const {
	int trueIndex = getTrueIndex(elem);
	if (trueIndex < 0 || trueIndex >= this->setSize) {
		return false;
	}
	return this->elems[trueIndex] == true;
}


int Set::size() const {
	return this->elemsCount;
}


bool Set::isEmpty() const {
	return this->elemsCount == 0;
}


Set::~Set() {
	delete[] this->elems;
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}


