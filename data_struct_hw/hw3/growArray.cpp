#include <iostream>
using namespace std;

class GrowArray {
private:
	int* p;
	int size;
	int used;
	// this should double the size of your list
	void grow() {

	}
public:
	GrowArray() : p(new int[1]), size(1), used(0) {
	}
	GrowArray(int capacity) : p(new int[capacity]), size(capacity), used(0) {
	}
	~GrowArray() {
		delete [] p;
	}
	void addStart(int v) { // O(   )
	}
	
 	void addEnd(int v) {  //O(    )
		if (used == size)
			grow();
		// O(1)
	}
	int getCapacity() const {
    return size;		
	}

	int getUsed() const {
		return used;
	}
	int get(int i) const { //O(1)
		if (i < 0 || i >= used)
			throw "Die!";
		return p[i];
	}
  void set(int i, int v) { // O(1)
		if (i < 0 || i >= used)
			throw "Die!";
		p[i] = v;
	}
	
};

class BadGrowArray {
private:
	int* data;
	int size;
public:
	BadGrowArray() {
		data = nullptr; // O(1)
		size = 0;
	}
	BadGrowArray(int initialSize) {
		data = new int[initialSize]; //O(1)
		size = initialSize;
	}
	~BadGrowArray() {
		delete [] data;
	}
	void addEnd(int v) {   //O(n)
		int* temp = data; // O(1)
		
    data = new int[size+1]; // O(1)
		for (int i = 0; i < size; i++) //O(n)
			data[i] = temp[i];
		data[size] = v;
		size++;
	}
	void addStart(int v) { //O(n)
		int* temp = data;
		data = new int[size+1];
		for (int i = 0; i < size; i++) //O(n)
			data[i+1] = temp[i];
		data[0] = v;
		size++;
	}
	void removeEnd() { //O(1)
		size--;
	}
	void removeStart() { //O(n)
		for (int i = 0; i < size-1; i++)
			data[i] = data[i+1];
		size--;
	}
};

int main() {
	BadGrowArray a;
	for (int i = 0; i < 100; i++)
	{
		a.addEnd(i);
		cout << " " << a[i] << " ";
	}
}


