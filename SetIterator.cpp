#include "SetIterator.h"
#include "Set.h"
#include <exception>
#include <stdexcept>

SetIterator::SetIterator(const Set& m) : set(m)
{
	first();
}


void SetIterator::first() {
	//TODO - Implementation
	this->currentIndex = 0;
	while (valid() && !this->set.elems[this->currentIndex])
	{
		this->currentIndex++;
	}
	if (!valid())
	{
		throw std::exception();
	}
}


void SetIterator::next() {
	if (!valid())
	{
		throw std::exception();
	}
	this->currentIndex ++;
	while (valid() && !this->set.elems[this->currentIndex])
	{
		this->currentIndex++;
	}
}


TElem SetIterator::getCurrent()
{
	if (!valid())
	{
		throw std::exception();
	}
	return this->set.smallestElem + this->currentIndex;
}

bool SetIterator::valid() const {
	return this->currentIndex >= 0 && this->currentIndex < set.setSize;
}



