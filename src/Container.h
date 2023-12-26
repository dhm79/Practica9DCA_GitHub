// 48357520C HIDALGO MOLINA, DANIEL

#ifndef _CONTAINER_
#define _CONTAINER_

#include <iostream>
#include "Util.h"

using namespace std;

class Container
{
	friend ostream& operator << (ostream &o, const Container& c);
	
	protected:
		unsigned int id;
		unsigned int value;
		unsigned int weight;
		static unsigned int nextId;  
		
	public:
		static const unsigned int kMINWEIGHT;
		static const unsigned int kMINVALUE;
		
		
		Container(unsigned int weight = 0, unsigned int value = 0); 		//Constructor
		static void resetNextId();
		
		unsigned int getId()const;
		unsigned int getWeight()const;
		unsigned int getValue()const; 
		
		void setWeight(unsigned int weight);
		void setValue(unsigned int value);
			
};

#endif
