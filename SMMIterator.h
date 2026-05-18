#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	//TODO - Representation
	int position;


	int snapshotSize;
	int snapshotCapacity;
	TElem* snapshotElements;
	void appendToSnapshot(const TElem& elem);
	void resizeSnapshot();

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
	~SMMIterator();
};

