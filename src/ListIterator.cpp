#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>

ListIterator::ListIterator(const IteratedList& list) : list(list) {
	this->current = this->list.head;
}

void ListIterator::first() {
	this->current = this->list.head;
}

void ListIterator::next() {
	if (!this->valid()) {
		throw std::exception();
	}
	this->current = this->list.nodes[current].next;
}

bool ListIterator::valid() const {
	return this->current != -1;
}

TElem ListIterator::getCurrent() const {
	if (!this->valid()) {
		throw std::exception();
	}
	return this->list.nodes[this->current].elem;
}



