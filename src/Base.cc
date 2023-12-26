// 48357520C HIDALGO MOLINA, DANIEL

#include "Base.h"

ostream& operator<<(ostream &o, const Base& b) 
{
	
	o<<"Name: " <<b.name;
	o<<"\nContainers:";
	
	for(unsigned int i=0; i<b.containers.size(); i++)
	{	
		o<<endl; 
		o << b.containers[i];   
	}
	o<<"\nShips:";
	
	for(unsigned int i=0; i<b.ships.size(); i++)
	{
		o <<endl;
		o <<* b.ships[i];
	}
	return o;
   
}
Base::Base(string name)
{
	this->name = name;
}

string Base::getName()const
{
	return name;
}

unsigned int Base::getNumContainers()const
{
	return containers.size();
}

unsigned int Base::getNumShips()const
{
	return ships.size();
}

Container Base::getContainer(unsigned int id)const
{
	unsigned int pos = searchContainer(id);
	
	if(pos == -1)
	{
		throw ERR_CONTAINER_ID;
	}
	else
	{
		return containers[pos];
	}
}

Ship* Base::getShip(string name)const
{
	unsigned int pos = searchShip(name);
	
	if(pos == -1)
	{
		throw ERR_SHIP_NAME;
	}
	else
	{
		return ships[pos];
	}
	
}

int Base::searchContainer(unsigned int id) const
{
	unsigned int pos = 0;
	bool flag = false;
	
	for(unsigned int i=0; i<containers.size(); i++)
	{
		if(containers[i].getId() == id)   
		{ 
			pos = i;
			flag = true;
		}
	}
	
	if (flag == true)
	{
		return pos;
	}
	else
	{
		return -1;
	}
}

int Base::searchShip(string name) const
{
	unsigned int pos = 0;
	bool flag = false;
	
	for(unsigned int i=0; i<ships.size(); i++)
	{
		if(ships[i] -> getName() == name)
		{
			pos = i;
			flag = true;
		}
	}
	
	if (flag == true)
	{
		return pos;
	}
	else
	{
		return -1;
	}
}

bool Base::addContainer(unsigned int weight, unsigned int value ) 
{
	try
	{
		Container nuevo(weight,value);
		containers.push_back(nuevo);
		return true;
	}
	
	catch(Error e)
	{
		Util::error(e);
		return false;
	}
	
}
bool Base::removeContainer(unsigned int id)    // Revisar  no encuentra el id container
{
	if(id == 0)
	{
		cout<<"Container id: ";
		cin>>id;
	}
	
	unsigned int pos = searchContainer(id);
	
	if(pos != -1)
	{
		containers.erase(containers.begin()+pos);
		return true;
	}
	else
	{
		Util::error(ERR_CONTAINER_ID);
		return false;
	}	
}

bool Base::addShip(Ship* s)   
{
	
	unsigned int pos = searchShip(s -> getName()) ;
	
	if(pos != -1 )
	{
		Util::error(ERR_SHIP_NAME);
		return false;
	}
	else
	{
		ships.push_back(s);
		return true;
	}
}

bool Base::removeShip(string name)
{
	if(name == "")
	{
	cout<<"Ship name:";
   	getline(cin,name);
	}
	unsigned int pos = searchShip(name);
	
	
	if(pos == -1)
	{
		Util::error(ERR_SHIP_NAME);
		return false;		
	}
	else
	{
		vector<Container> copia = ships[pos] -> releaseContainers();
		
		for(unsigned int i=0; i<copia.size(); i++)
		{
			containers.push_back( copia[i] );
		}
		ships.erase(ships.begin()+pos);
		
		return true;
	}
}
bool Base::manualDistribution(unsigned int id, string name)
{
	bool flag = false;
	
	if(id == 0)
	{
		cout<<"Container id:";
   	cin>>id; cin.ignore();
	}
	
	unsigned int posC = searchContainer(id);
	
	if(posC == -1)
	{
		Util::error(ERR_CONTAINER_ID);
	}
	else
	{
		if(name == "")
		{
			cout<<"Ship name:";
      	getline(cin,name);
		}
		
		unsigned int posS = searchShip(name);
		
		if(posS == -1)
		{
			Util::error(ERR_SHIP_NAME);
		}
		else
		{
			bool flagControl = ships[posS] -> addContainer(containers[posC]);
			
			if(flagControl == true)
			{
				containers.erase(containers.begin()+posC);
			}
		}
	}	
	return flag;
	
}
bool Base::unassignContainer(unsigned int id, string name)
{
	bool flagControl = false;
	
	if(name == "")
	{
		cout<<"Ship name:";
		getline(cin,name);
	}
	int pos = searchShip(name);
	
	if(pos != -1)
	{
		if(id == 0)
		{
			cout<<"Container id:";
			cin>>id;
		}
		
		try
		{
			Container cont = ships[pos] -> getContainer(id);
			ships[pos] -> removeContainer(id);
			containers.push_back(cont);
			flagControl = true;
		} 
		catch(Error e)
		{
			Util::error(e);
		}
	}
	else
	{
		Util::error(ERR_SHIP_NAME);
	}
	return flagControl;	
	
}
void Base::automaticDistribution()
{
	unsigned int posContainer = 0;
   string shipName = "";
   int centinela = 0;        // Variable que controla las veces que pasa por la division del container
   
   if( (containers.size() !=0) && (ships.size() !=0) )
   {
   	do  
		{
			posContainer = eligeContainer();                                          // Llamada a la funcion eligeContainer 
			shipName = eligeNave(posContainer, centinela);							        // Llamada a la funcion eligeNave
		
			for (unsigned int i=0; i<getNumShips(); i++)			                     // Bucle que asigna el contenedor a la nave
			{
				if (ships[i] -> getName() == shipName)
				{
					ships[i] -> addContainer(containers[posContainer]);
		   		containers.erase(containers.begin()+posContainer);
		   	}
			}
			 
		}while( (containers.size() != 0) && (centinela < 5) );		// Si pasa 4 veces por el mismo sitio es que ya no puede dividirse mas
	}
}

int Base::eligeContainer()  // Funcion que devuelve la posicion del vector de la base del primer contenedor de mayor valor, y si hay mas de uno el de menor peso
{
	unsigned int mayorValor = 0;
	unsigned int menorPeso = 0;
	unsigned int container = 0;
	bool flag = false;
	
	for (unsigned int i=0; i<containers.size(); i++)  // Bucle para saber el maximo valor de los contenedores
   {
      if (containers[i].getValue() > mayorValor)
      {
         mayorValor = containers[i].getValue();
         menorPeso  = containers[i].getWeight();
      }
	}		  
		
	for (unsigned int i=0; i<containers.size(); i++)    // Bucle para conocer el menor peso de los contenedores  con el maximo valor
	{
		if (containers[i].getValue() == mayorValor)
		{
			if (containers[i].getWeight() < menorPeso)
			{
				menorPeso = containers[i].getWeight();
			}
		}
	}

	for (unsigned int i=0; (flag == false) && (i<containers.size()); i++)  // Bucle para seleccionar el primer id contenedor que cumpla los requisitos de maximo valor y menor peso
	{	
		if ( (containers[i].getValue() == mayorValor) && (containers[i].getWeight() == menorPeso) )
		{	
			flag = true;	
			container = i;	
		}
	}
	
	return container;	
}

string Base::eligeNave(unsigned int posContainer, int &centinela)    // Funcion que devuelve el nombre de la nave elegida
{
	unsigned int pos = 0;
	unsigned int minValor = 0;
	bool flagValor = false;
	string shipName = "";        
	
	struct Naves                 // Registro para almacenar las naves que cumplen los requisitos de numero de contenedores y maximo peso
	{
		string name;
		unsigned int value;
		
	}nave[ships.size()];
	
	for (unsigned int i=0; i<ships.size(); i++)  //Bucle para almacenar las naves en el registro si cumplen los requisitos de peso
	{
		if ( (ships[i] -> getNumContainers() < ships[i] -> getMaxContainers() ) && (ships[i] -> getWeight() + containers[posContainer].getWeight() ) <= (ships[i] -> getMaxWeight() ) )
		{
			nave[pos].name = "";
			nave[pos].value = 0;
			nave[pos].name = ships[i]  -> getName();
			nave[pos].value = ships[i] -> getValue();				
			pos++;
		}	
	}

	if (pos != 0)
	{
		minValor = nave[0].value;
		for(unsigned int i=0; i<pos; i++)  // Bucle para saber el valor minimo de las naves del registro
		{
			if (nave[i].value < minValor)
			{
				minValor = nave[i].value;
			}
		}
	
		for (unsigned int i=0; (flagValor == false) && (i<pos); i++)  // Selecciona la primera nave del vector con el menor valor
		{
			if (nave[i].value == minValor)
			{
				flagValor = true;
				shipName = nave[i].name;		
			}
		}
	}
	else     // si el valor de pos es 0, es porque ninguna nave cumple requisitos. Entonces se llama la funcion para dividir contenedor 
	{
		divideContainer(posContainer, centinela);   
	}
	
	return shipName;
}


void Base::divideContainer(unsigned int posContainer, int &centinela)    
{

	unsigned int MAXWEIGHT = Container::kMINWEIGHT;
	unsigned int MAXVALUE = Container::kMINVALUE;
	unsigned int C1Weight = 0;    		// Variables que almacenan los valores de peso y valor del primer contenedor creado 
   unsigned int C1Value = 0;
   unsigned int C2Weight = 0;    		// Variables que almacenan los valores de peso y valor del primer contenedor creado 
   unsigned int C2Value = 0;
   bool flagControl = false;

   for (unsigned int i=0; i<ships.size(); i++)
   {
   	if ( (ships[i] -> getNumContainers() < ships[i] -> getMaxContainers() ) && 
			  (ships[i] -> getWeight() - ships[i] -> getMaxWeight()  > MAXWEIGHT ) )          // Condicion para comprobar que el contenedor dividido entra en la nave
   	{
			flagControl = true;
		}


		if (flagControl == true)
		{
		 	if ( (containers[posContainer].getWeight() / 2) >= MAXWEIGHT && 
			     (containers[posContainer].getValue() / 2)  >=  MAXVALUE )               // Condicional comprueba que al dividir el contenedor cumple el min peso y valor
			{ 
					C1Weight = containers[posContainer].getWeight() / 2;
					C1Value = containers[posContainer].getValue() / 2;
					Container C1(C1Weight,C1Value);
					containers.push_back(C1);
		

					C2Weight = containers[posContainer].getWeight() - C1Weight;
					C2Value  = containers[posContainer].getValue()  - C1Value;
					Container C2(C2Weight,C2Value);
					containers.push_back(C2);
		
					containers.erase(containers.begin() + posContainer); 	// Borra el contenedor original de la base
			}
			else
			{
				centinela++;
			}
		}
		else
		{
			centinela++;
		}
	}
}
void Base::clearAssignations()
{
	for (unsigned int i=0; i<ships.size(); i++)
	{
		vector<Container> copia = ships[i] -> releaseContainers();
		
		for(unsigned int j=0; j<copia.size(); j++)
		{
			containers.push_back( copia[j] );
		}
	}	
}
