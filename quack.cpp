// add code to these functions to make quack do something useful

// enable Visual C++ memory leak checking
#ifdef _DEBUG
#include <ostream>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "quack.h"



/**
* Quack: Constructor - initializer list
* in: none
* out: none
* return: none
**/
quack::quack(int capacity): maxsize(capacity), front(1), back(0), count(0), items( new item[capacity])
{



}


/**
* Quack: Destructor 
* in: none
* out: none
* return: none
**/
quack::~quack(void)
{

	delete  [] items;


}

/**
* Quack: PushFront
* in: n
* out: none
* return: bool
**/
bool quack::pushFront(const int n)
{

	if ( count == maxsize )
	{   

		return false;
	}

	front = (front - 1 ) % maxsize;
	if(front < 0)                    // wrap around the array to zero
	{
		front += maxsize;
	}

	items[front].n = n;        // add items
	count++;

	return true; 


}

/**
* Quack: PushBack
* in: none
* out: none
* return: bool
**/
bool quack::pushBack(const int n)
{

   if ( count == maxsize )
	{   

		return false;
	}
	
	back = (back + 1 ) % maxsize;     // push items in the back
	items[back].n = n;
	count++;
	return true;  


}

/**
* Quack: PopFront
* in: n
* out: none
* return: bool
**/
bool quack::popFront(int& n)
{

	int Deleteditem;
	Deleteditem  = items[front].n;     
	front = (front + 1 ) % maxsize;     // pop items from the front
	--count;

	n = Deleteditem;
	return true;

}

/**
* Quack: PopBack
* in: n
* out: none
* return: bool
**/
bool quack::popBack(int& n)
{


	int Deleteditem;
	if(back < 0 )         // handle negatie numbers
	{
		back += maxsize;  // wrap around the circular array 
	}

	Deleteditem = items[back].n;

	back = (back -1) % maxsize;
	--count;
	n = Deleteditem;
	return true;



}
/**
* Quack: Rotate
* in: r
* out: none
* return: none
**/
void quack::rotate(int r)
{


	int index;      
	int arrayindex;        //index
	int next;

	int frontPtr;     // used for storing items - used for swapping
	int backPtr;      // used for storing items - used for swapping
    int counter(0);



	if(count < maxsize)                // only if array is not full
	{                                 // grab the items where front point to
		frontPtr = items[front].n;    // used for storing and moving items
		backPtr = items[front+1].n;
	}


	/***************** Rotate Positive ***************************/

	while ( r > 0 )  
	{

		if(count == maxsize)           // if array is full
		{
                                         //front will be at a different index
			frontPtr = items[front].n;   // use for storing and moving items
			backPtr = items[front+1].n; // grabs the next item in line

		}

		counter = 0; 

		if(count == maxsize) // if array is full
		{

			index = front+1;  // move index to the front +1

		}
		else
		{

			index = front;   // just move to the front
		}


/************ loop to move items within circular array *************************/
		for ( int arrayitem = back+1; counter < count; counter++)
		{

			items[arrayitem].n =  items[index].n;  // shift items by one


			if(index == maxsize-1)                // if index = max
			{
				index =(index + 1) % maxsize;    // wrap index back around circular array
			}
			else
			{
				index++;                    // just increment index just one
			}


			if(arrayitem == maxsize-1)                     //  if array item is at the end    
			{
				arrayitem =(arrayitem + 1) % maxsize;      // wrap arrayitem around circular array
			}
			else
			{
				arrayitem++;
			}

		}

		if(count == maxsize)                     // if array is full
		{

			items[back].n = frontPtr;          // put frontPtrs value into the back index

		}

		r--;
		
/********** adding items back into the array from the start ************************/
		if( r == 0)                      // if at the end of the loop
		{


			if( count < maxsize)             // if array not full
			{
				items[back].n = backPtr;        // store backPtr item into items back

				arrayindex = back-1;              // increment array index
				items[arrayindex].n = frontPtr;    // store backPtr item into items back

			}

		}

	}
	/***************** Rotate Negative ***************************/

	while ( r < 0 )  
	{

		int numitemsprinted =0;  // counter
		int index = front -1;    




		if(count == maxsize)          // if array is full
		{
			numitemsprinted = 1;        // set counter to 1 so it dont loop to many times 
			frontPtr = items[front].n;  // store front item for later
			index = front;             // set index to front
		}

		else                            
		{
			backPtr = items[back].n;          // store back item into a pointer

		}

		/************loop for rotating items *****************/
		for ( int arrayitem = back; numitemsprinted < count; numitemsprinted++) 

		{
			items[index].n =  items[arrayitem].n;  // move items according to the index



			if(index == 0)             // if index is zero wrap it back around to 6 
			{
				index += maxsize -1;

			}
			else
			{
				index--;          // just increment is not at the end
			}


			if(arrayitem == 0)        // same for array item
			{
				arrayitem += maxsize-1;

			}
			else
			{
				arrayitem--;
			}



		}

/********** adding items back into the array from the start ************************/
		if(count == maxsize)      // if array is full
		{
			next = front +1;         // use next as an index

			items[next].n = frontPtr;  // assign frontPtr item to the front of the array
			// this is used for adding back in items that we stored in the beginning
		}

		if(count < maxsize)
		{
			items[front].n = backPtr;    // this adds items back in if array isnt full
		}

		r++;



	}





}

/**
* Quack: Reverse
* in: none
* out: none
* return: none
**/
void quack::reverse(void)
{



	int counter = 0;  // counter
	int index = front+1;     // use another index

	int frontPtr;
	int backPtr;         // used for storing items - used for swapping
	int reversePtr;


	front =(front ) % maxsize;

	frontPtr = items[front].n;     // grab the first and last item
	backPtr = items[back].n;

/************** loop for reversing items ***********************/
	for ( int arrayitem = back-1; counter < count; counter++) 
	{


		reversePtr = items[arrayitem].n;   // assign the item before it gets over written


		items[arrayitem].n = items[index].n;   // swap the items

		items[index].n = reversePtr;         // put back the item to the front
		arrayitem--;  

		if( arrayitem == index)        // exit out if all items are swapped
		{
			break;
		}

		if(index == maxsize-1)         // wrap index back around the circular array
		{
			index =(index + 1) % maxsize;
		}
		else
		{
			index++;
		}



	}

	items[back].n = frontPtr;     // swap the front and back items we previously stored
	items[front].n = backPtr;


}
/**
* Quack: ItemCount
* in: none
* out: none
* return: out
**/
int	quack::itemCount(void)
{

	return count;

}

/**
* Quack: Operator Overload
* in: q
* out: none
* return: out
**/
ostream& operator<<(ostream& out, quack& q)
{

	if ( q.count == 0 ) // no elements have been counted.
		out << endl << "quack: empty" << endl;

	else
	{
		out << endl << "quack: ";



		int  numitemsprinted = 0;

		for ( int arrayitem = q.front; numitemsprinted < q.count; arrayitem = ( arrayitem +1) % q.maxsize, numitemsprinted++ )
		{

			out << q.items[arrayitem]; 

			if(numitemsprinted < q.count-1)  // dont print to many comma
			{

				out << ", ";
			}

		}
		out << endl << endl;
	}
	return out;



}
/**
* Quack: operator Overload
* in: i
* out: none
* return: out
**/
ostream& operator<<(ostream& out, quack::item& i)
{

	out << i.n;   // output items

	return out;
}
