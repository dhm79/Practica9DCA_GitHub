// 48357520C HIDALGO MOLINA, DANIEL

#ifndef _BASE_
#define _BASE_

#include<iostream>
#include<string>
#include "Container.h"
#include "Ship.h"
#include"Util.h"


using namespace std;

class Base
{
	friend ostream& operator<<(ostream &o, const Base &b);   
	
	protected:
		vector<Container> containers;
		vector<Ship*> ships;
		string name;
		
		int eligeContainer();
		string eligeNave(unsigned int posContainer, int &centinela);
		void divideContainer(unsigned int posContainer, int &centinela);
	public:
		
		Base(string name);  									// Constructor
		string getName()const;
		unsigned int getNumContainers()const;
		unsigned int getNumShips()const;
		Container getContainer(unsigned int id )const;
		Ship* getShip(string name)const;
		int searchContainer(unsigned int id) const;
		int searchShip(string name) const;
		bool addContainer(unsigned int weight = 0, unsigned int value = 0);
		bool removeContainer(unsigned int id = 0);
		bool addShip(Ship* s);
		bool removeShip(string name = "");
		bool manualDistribution(unsigned int id = 0, string name = "");
		bool unassignContainer(unsigned int id = 0, string name = "");
		void automaticDistribution();
		void clearAssignations();
};

#endif
