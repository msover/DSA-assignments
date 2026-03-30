#include "SetIterator.h"
#include "Set.h"
#include <exception>
#include <stdexcept>

SetIterator::SetIterator(const Set& m) : set(m)
{
	first();
}

//BC=Theta(1)
//WC=AC=O(n)
void SetIterator::first() {
	this->currentIndex = 0;
	while (valid() && !this->set.elems[this->currentIndex])
	{
		this->currentIndex++;
	}
}

//BC=Teta(1)
//WC=AC=O(n)
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

//BC=AC=WC=Theta(1)
TElem SetIterator::getCurrent()
{
	if (!valid())
	{
		throw std::exception();
	}
	return this->set.smallestElem + this->currentIndex;
}
//BC=AC=WC=Theta(1)
bool SetIterator::valid() const {
	return this->currentIndex >= 0 && this->currentIndex < set.setSize;
}



