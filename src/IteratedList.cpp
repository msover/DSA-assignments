
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"

void IteratedList::resize() {
	int oldCapacity = this->capacity;
	int newCapacity = capacity * 2;
	Node* newNodes = new Node[newCapacity];
	for (int i = 0; i < oldCapacity; i++) {
		newNodes[i] = nodes[i];
	}
	for (int i = oldCapacity; i < newCapacity - 1; i++) {
		newNodes[i].next = i + 1;
		newNodes[i].prev = -1;
	}
	newNodes[newCapacity - 1].prev = -1;
	newNodes[newCapacity - 1].next = this->firstEmpty;
	this->firstEmpty = oldCapacity;
	delete [] this->nodes;
	this->nodes = newNodes;
	capacity = newCapacity;
}

int IteratedList::allocateNode(TElem e) {
	if (this->firstEmpty == -1) {
		this->resize();
	}
	int pos = this->firstEmpty;
	this->firstEmpty = this->nodes[pos].next;

	this->nodes[pos].elem = e;
	this->nodes[pos].prev = -1;
	this->nodes[pos].next = -1;
	this->length ++;
	return pos;
}

void IteratedList::freeNode(int pos) {
	this->nodes[pos].next = this->firstEmpty;
	this->nodes[pos].prev = -1;
	this->firstEmpty = pos;
	this->length --;
}

IteratedList::IteratedList() {
	this->capacity = 10;
	this->length = 0;
	this->head = -1;
	this->tail = -1;
	this->firstEmpty = 0;
	this->nodes = new Node[this->capacity];

	for (int i = 0; i < this->capacity - 1; i ++) {
		this->nodes[i].next = i + 1;
		this->nodes[i].prev = -1;
	}

	this->nodes[capacity - 1].next = -1;
	this->nodes[capacity - 1].prev = -1;
}

int IteratedList::size() const {
	return this->length;
}

bool IteratedList::isEmpty() const {
	return this->length == 0;
}

ListIterator IteratedList::first() const {
	return ListIterator(*this);
}

TElem IteratedList::getElement(ListIterator pos) const {
	if (&pos.list != this || !pos.valid()) {
		throw std::exception();
	}
	return this->nodes[pos.current].elem;
}

TElem IteratedList::remove(ListIterator& pos) {
	if (&pos.list != this || !pos.valid()) {
		throw std::exception();
	}
	int current = pos.current;
	int before = this->nodes[current].prev;
	int after = this->nodes[current].next;
	TElem removed = this->nodes[current].elem;

	if (before != -1) {
		this->nodes[before].next = after;
	} else {
		this->head = after;
	}

	if (after != -1) {
		this->nodes[after].prev = before;
	} else {
		this->tail = before;
	}
	pos.current = after;
	this->freeNode(current);
	return removed;
}

ListIterator IteratedList::search(TElem e) const{
	ListIterator it(*this);
	it.current = head;
	while (it.valid() && this->nodes[it.current].elem != e) {
		it.current = this->nodes[it.current].next;
	}
	return it;
}

TElem IteratedList::setElement(ListIterator pos, TElem e) {
	if (&pos.list != this || !pos.valid()) {
		throw std::exception();
	}
	TElem old = this->nodes[pos.current].elem;
	this->nodes[pos.current].elem = e;
	return old;
}

void IteratedList::addToPosition(ListIterator& pos, TElem e) {
    if (&pos.list != this || !pos.valid()) {
	    throw std::exception();
    }

	int current = pos.current;
	int after = this->nodes[current].next;
	int newNode = allocateNode(e);
	this->nodes[newNode].prev = current;
	this->nodes[newNode].next = after;
	this->nodes[current].next = newNode;

	if (after != -1) {
		this->nodes[after].prev = newNode;
	} else {
		this->tail = newNode;
	}

	pos.current = newNode;

}

void IteratedList::addToEnd(TElem e) {
	int newNode = this->allocateNode(e);
	if (this->head == -1) {
		this->head = this->tail = newNode;
	}
	else {
		this->nodes[newNode].prev = this->tail;
		this->nodes[tail].next = newNode;
		this->tail = newNode;
	}
}

void IteratedList::addToBeginning(TElem e) {
	int newNode = this->allocateNode(e);
	if (this->head == -1) {
		this->head = this->tail = newNode;
	} else {
		this->nodes[newNode].next = this->head;
		this->nodes[head].prev = newNode;
		this->head = newNode;
	}
}

IteratedList::~IteratedList() {
	delete[] this->nodes;
}
