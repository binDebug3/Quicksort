#ifndef QS_H
#define QS_H

#include "QSInterface.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template<typename Teml>
class QS : public QSInterface<Teml> {
private:
	void reallocate(void) {							//create new array with double the size and copy old array into the new array
		int reCapacity = capity * 2;
		Teml* realloc = new Teml[reCapacity];
		for (int i = 0; i < numItems; i++) {
			realloc[i] = data[i];
		}
		capity = reCapacity;
		swap(data, realloc);
		delete[] realloc;
	}

	int numItems;
	int capity;
	Teml* data;
	bool recursive = false;
public:
	QS() :
		numItems(0),
		capity(0)
	{}
	virtual ~QS() {
		//delete[] data;
		capity = 0;
		clear();
	}
	void endClear() {
		delete[] data;
		capity = 0;
		clear();
	}

	// Dynamically allocate an initial array to the QuickSort class.
	bool createArray(size_t capacity) {
		if (capity != 0) delete[] data;
		data = new Teml[capacity];
		capity = capacity;
		numItems = 0;
		return true;
	}

	// Add an element to the QuickSort array. Dynamically grow array as needed.
	bool addElement(Teml element) {
		++numItems;
		if (numItems >= capity) reallocate();
		data[numItems - 1] = element;
		return true;
	}

	// Sort the elements of a QuickSort subarray using median and partition functions. 
	bool sort(size_t left, size_t right) {
		right--;
		int pivot = medianOfThree(left, right);
		recursive = true;
		pivot = partition(left, right, pivot);
		recursive = false;
		return true;
	}

	// Sort all elements of the QuickSort array using median and partition functions.
	bool sortAll() {
		int pivotIndex = medianOfThree(0, numItems - 1);
		recursive = true;
		pivotIndex = partition(0, numItems - 1, pivotIndex);
		recursive = false;
		return true;
	}

	// Removes all items from the QuickSort array. 
	bool clear() {
		numItems = 0;
		//delete[] data;
		return true;
	}

	// Return size of the QuickSort array. 
	size_t capacity() const {
		return capity;
	}

	// Return number of elements in the QuickSort array. 
	size_t size() const {
		return numItems;
	}

	// The median of three pivot selection 
	int medianOfThree(size_t left, size_t right) {
		size_t middle = (right + left) / 2;
		if (left > right) {
			middle *= -1;
			return middle;
		}
		while (right >= numItems) right--;
		if (data[left] <= data[middle]) {
			if (data[middle] > data[right]) {
				swap(data[left], data[right]);
				swap(data[middle], data[right]);
			}
		}
		else if (data[middle] >= data[right])
			swap(data[left], data[right]);
		else if (data[left] <= data[right])
			swap(data[left], data[middle]);
		else {
			swap(data[left], data[middle]);
			swap(data[middle], data[right]);
		}
		if (data[right] <= data[middle])
			swap(data[middle], data[right]);
		return middle;
	}

	// Partitions a subarray around a pivot value
	int partition(size_t left, size_t right, size_t pivotIndex) {
		if ((right - left) > 1) {
			swap(data[left], data[pivotIndex]);
			Teml up = left + 1;
			Teml down = right - 1;
			while (true) {
				while ((up != right - 1) && (data[left] >= data[up])) ++up;
				while (data[left] < data[down]) --down;
				if (down <= up) break;
				swap(data[up], data[down]);
			}
			swap(data[left], data[down]);
			Teml pivot = down;

			if (recursive) {
				sort(left, pivot + 1);
				sort(pivot + 1, right + 1);
			}
			return pivot;
		}
		return -1;
	}

	// @return: comma delimited string representation of the array. 
	string toString() const {
		stringstream out;
		for (size_t i = 0; i < numItems; ++i) {
			out << data[i] << ",";
		}
		return out.str();
	}
	friend ostream& operator<< (ostream& os, QS<Teml>& thing) {
		os << thing.toString();
		return os;
	}
	

	class Iterator {
	public:
		Iterator(QS<Teml>* alpha, size_t south) :
			arrayPtr(alpha), index(south) {
		}
		Teml operator[](size_t ind) const {
			arrayPtr->data[ind];
		}
		Teml operator*() const {
			return arrayPtr->data[index];
		}
		Iterator& operator++() {
			++index;
			return *this;
		}
		bool operator!=(const Iterator& check) const {
			if (index == check.index) {
				return false;
			}
			return true;
		}
		string toString() const {
			stringstream out;
			out << index;
			return out.str();
		}
		friend ostream& operator<< (ostream& os, const Iterator& funArray) {
			os << funArray.toString();
			return os;
		}
	private:
		size_t index;
		QS<Teml>* arrayPtr;
	};
	QS::Iterator begin() {
		return QS<Teml>::Iterator(this, 0);
	}
	QS::Iterator end() {
		return QS<Teml>::Iterator(this, numItems);
	}
	QS::Iterator endb4() {
		return QS<Teml>::Iterator(this, numItems - 1);
	}
};
#endif // QS_H