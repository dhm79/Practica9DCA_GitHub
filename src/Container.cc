// 48357520C HIDALGO MOLINA, DANIEL

#include "Container.h"

//statics se inicializan en raiz del fichero .h

unsigned int Container::nextId = 1; 		
const unsigned int Container::kMINWEIGHT = 100;
const unsigned int Container::kMINVALUE = 100;
		
ostream& operator << (ostream &o, const Container& c)  // Funcion amiga para imprimir con el comando "o" en vez de cout
{
	o<<"["<<c.id<<" "<<c.weight<<":"<<c.value<<"]";
	return o;
}

Container::Container(unsigned int weight, unsigned int value)
{
	if (weight == 0)
	{
		cout<<"Container weight:";
		cin>>weight; 
	}
	
	if(weight<kMINWEIGHT)
	{
		throw ERR_CONTAINER_WEIGHT;
	} 
	
	if (value == 0)
	{
		cout<<"Container value:";
		cin>>value; 
	}
	
	if(value < kMINVALUE) 
	{
		throw ERR_CONTAINER_VALUE;
	}
	
	this-> value = value;
	this-> weight = weight;
	this-> id = nextId++;
}

void Container::resetNextId()
{
	nextId=1;
}
		
unsigned int Container::getId() const
{
	return id;
}

unsigned int Container::getWeight() const
{
	return weight;
}

unsigned int Container::getValue() const
{
	return value;
}

void Container::setWeight(unsigned int weight)
{
	if(weight<kMINWEIGHT)
	{
		throw ERR_CONTAINER_WEIGHT;
	}
	else
	{
		this->weight = weight;
	}
}

void Container::setValue(unsigned int value)
{
	if(value<kMINVALUE)
	{
		throw ERR_CONTAINER_VALUE;
	}
	else
	{
		this->value = value;
	}
}
