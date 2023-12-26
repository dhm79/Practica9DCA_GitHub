// 48357520C HIDALGO MOLINA, DANIEL

#include "Ship.h"

const unsigned int Ship::kMINCONTAINERS = 5;
const unsigned int Ship::kMINWEIGHT = 500;

ostream& operator << (ostream &o, const Ship& s)
{
	o<<"\n{" <<s.name << ": " <<s.weight <<" (" <<s.maxWeight <<"), "<<s.containers.size() << " ("<<s.maxContainers <<"), " <<s.value <<" " <<endl;

   for(unsigned int i=0; i<s.containers.size(); i++)
	{
		o << s.containers[i];
   }
   o <<"\n}";
   
   return o;   
}

Ship::Ship()     
{
	cout<<"Ship name:";
	getline(cin,name);
	cout<<"Ship max. containers:";
	cin>>maxContainers;
	
	if(maxContainers < kMINCONTAINERS)
	{
	  throw ERR_SHIP_MAXCONTAINERS;
	}
	
	cout<<"Ship max. weight:";
	cin>>maxWeight;
	
	if(maxWeight < kMINWEIGHT)
	{
		throw ERR_SHIP_MAXWEIGHT;
	}
	weight = 0;
	value = 0;
}

Ship::Ship(string name, unsigned int maxContainers, unsigned int maxWeight)
{
	if(maxContainers < kMINCONTAINERS)
   {
      throw ERR_SHIP_MAXCONTAINERS;
 	}
 	
 	if(maxWeight < kMINWEIGHT)
   {
   	throw ERR_SHIP_MAXWEIGHT;
	}
	
	this->name = name;
	this->maxContainers = maxContainers;
	this->maxWeight = maxWeight;
	weight = 0;
	value = 0;
}

string Ship::getName()const
{
	return name;
}

unsigned int Ship::getWeight()const
{
	return weight;
}

unsigned int Ship::getValue()const
{
	return value;
}

unsigned int Ship::getMaxWeight()const
{
	return maxWeight;
}

unsigned int Ship::getMaxContainers()const
{
	return maxContainers;
}

unsigned int Ship::getNumContainers()const
{
	return containers.size();
}

unsigned int Ship::searchContainer(unsigned int id)const
{
	int pos = 0;
	bool flag = false;
	
	for(unsigned int i=0; i<containers.size() ; i++)  
	{
		if (containers[i].getId() == id)
		{
			pos = i;
			flag = true;
		}
	}
	
	if(flag == true)
	{
		return pos; 
	}
	else
	{
		return -1;
	}
}

bool Ship::admitsContainer(const Container &c)const
{
	if( (containers.size() < maxContainers) && (weight + c.getWeight() <= maxWeight ) )
	{
		return true;
	}
	return false;
}

Container Ship::getContainer(unsigned int id)const
{
	unsigned int pos = searchContainer(id);
	 
	if(pos == -1)         //if( (pos = searchContainer(id)) == -1 )   Hacker
	{
		throw ERR_CONTAINER_ID;
	}	
	
	return containers[pos];  		
}

bool Ship::addContainer(const Container &c)
{
	bool flag = false;
	
	if (containers.size() >= maxContainers)
	{
		Util::error(ERR_SHIP_NO_MORE_CONTAINERS);
	}
	
	else if( (weight + c.getWeight()) > maxWeight )
	{
		Util::error(ERR_SHIP_NO_MORE_WEIGHT);
	}
	
	else
	{
		value = value + c.getValue();
      	weight = weight + c.getWeight();
		containers.push_back(c);
		flag = true;	
	}	
	
	return flag;
}
		
bool Ship::removeContainer(unsigned int id)
{
	bool flag = false;
	
	unsigned int pos = searchContainer(id);
	
	if(pos == -1)
	{
		Util::error(ERR_CONTAINER_ID);
	}
	else
	{
		weight = weight - containers[id].getWeight();
		value = value - containers[id].getValue();
		containers.erase(containers.begin()+pos);
		flag = true;
	}
	return flag;
}

vector<Container> Ship::releaseContainers()
{
	vector<Container> copia;
	
	for(unsigned int i=0; i<containers.size(); i++)
	{
		copia.push_back( containers[i] );
	}
	
	containers.clear();
	return copia;
}

