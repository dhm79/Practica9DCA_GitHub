// 48357520C HIDALGO MOLINA, DANIEL

#ifndef _SHIP_
#define _SHIP_

#include<iostream>
#include<string>
#include<vector>
#include "Container.h"

using namespace std;

class Ship
{
	friend ostream& operator << (ostream &o, const Ship& s);  
	
	protected:
		vector<Container>containers;
		
		string name;
		unsigned int weight;
		unsigned int value;
		unsigned int maxWeight;
		unsigned int maxContainers;
		
	public:
		static const unsigned int kMINCONTAINERS;
		static const unsigned int kMINWEIGHT;
		
		Ship();   // Constructor
		Ship(string name, unsigned int maxContainers, unsigned int maxWeight);  //Constructor
		string getName()const;
		unsigned int getWeight()const;
		unsigned int getValue()const;
		unsigned int getMaxWeight()const;
		unsigned int getMaxContainers()const;
		unsigned int getNumContainers()const;
		unsigned int searchContainer(unsigned int id)const;
		bool admitsContainer(const Container &c)const;
		Container getContainer(unsigned int id)const;  
		bool addContainer(const Container &c);
		bool removeContainer(unsigned int id);
		vector<Container> releaseContainers();
			
};

#endif
