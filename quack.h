#pragma once

#include <ostream>

using namespace std;

class quack
{
public:
	quack(int capacity);
	~quack(void);
	bool pushFront(const int n);	// push an item onto the front
	bool pushBack(const int n);		// push an item onto the back
	bool popFront(int& n);			// pop an item off the front
	bool popBack(int& n);			// pop an item off the back
	void rotate(int r);				// "rotate" the stored items (see note below)
	void reverse(void);				// reverse the order of the stored items
	int	itemCount(void);			// return the current number of stored items

private:

     int front;
	 int back;
	 int maxsize;
	 int count;
	
	struct item						// definition of each item stored by the quack
	{
		int		n;
	};
	item		*items;	            // pointer to storage for the circular array
				

public:
	friend ostream& operator<<(ostream& out, quack& q);
	friend ostream& operator<<(ostream& out, quack::item& i);
};
