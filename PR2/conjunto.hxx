/** @brief fichero de implementacion de la clase conjunto

*/

#include "conjunto.h"

using namespace std;

conjunto::conjunto():vc(0){}

conjunto::conjunto(const conjunto &d){
	vc=d.vc;
}

conjunto& conjunto::operator=(const conjunto &org){
	if(&org!=this)
		vc=org.vc;
	return *this;
}

pair<conjunto::entrada,bool>  conjunto::find( const long int & id) const{
   pair<conjunto::entrada,bool> out;
	int dcho=vc.size()-1;
	int izdo=0;
	int acomparar;
	bool encontrado = false;


	while(dcho>izdo && !encontrado){
	
		acomparar=(dcho-izdo)/2 +izdo;
		

		if((vc.at(acomparar)).getID()>id)
			dcho=acomparar-1;
		else{
			if((vc.at(acomparar)).getID()<id)
				izdo=acomparar+1;
			else{
					encontrado=true;
					out.first=vc.at(acomparar);
			}
		}
	}

	out.second=encontrado;		
	return out;
}

conjunto conjunto::findIUCR (const string & iucr) const{
	conjunto C_iucr;
	vector<conjunto::entrada>:: const_iterator it;

	for (it = vc.cbegin(); it != vc.cend(); it++) 
		if ((*it).getIUCR() == iucr)
			C_iucr.insert((*it));
		
	return C_iucr;
}

conjunto conjunto::findDESCR (const string & descr) const{
	conjunto C_iucr;
	vector<crimen> :: const_iterator it;
	string descripcion;

	for (it = vc.cbegin(); it != vc.cend(); it++) {
		descripcion = ((*it).getDescription());
		if (descripcion.find(descr,0) != descripcion.npos)
			C_iucr.insert(*it);
	}

	return C_iucr;
}

bool conjunto::erase(const long int &id){
   bool borrado=false;
   vector<conjunto::entrada>::iterator it;
  	if(!empty())
   	for(it=vc.begin(); it!=vc.end() && !borrado; it++){
			if((*it).getID()==id){
	   		vc.erase(it);
	   		borrado=true;
			}
  	 	}

   return borrado;
}

bool conjunto::erase(const conjunto::entrada &e){
   bool borrado=false;
   vector<conjunto::entrada>::iterator it;
  	if(!empty())
   	for(it=vc.begin(); it!=vc.end() && !borrado; it++){
			if((*it).getID()==e.getID()){
	   		vc.erase(it);
	   		borrado=true;
			}
   	}

   return borrado;
}

conjunto::size_type conjunto::size() const{
   return vc.size();
}

bool conjunto::empty() const{
   bool vacio;
   if(size()==0)
		vacio=true;
   else
		vacio=false;

   return vacio;
}

bool conjunto::insert(const conjunto::entrada &e){
	vector<conjunto::entrada>::iterator dcho=vc.end()-1;
	vector<conjunto::entrada>::iterator izdo=vc.begin();
	vector<conjunto::entrada>::iterator acomparar;
	bool encontrado = false,insertado;

	if(!empty()){
		while(dcho>izdo && !encontrado){
		
			acomparar=(dcho-izdo)/2 +izdo;
			
	
			if(e<*acomparar)
				dcho=acomparar-1;
			else{
				if(*acomparar<e)
					izdo=acomparar+1;
				else{
						encontrado=true;
				}
			}
		}
	
		if(!encontrado){
			if(dcho>vc.begin() && e<*dcho)
				vc.insert(dcho,e);
			else
				vc.insert(dcho+1,e);
			insertado=true;
		}
		else
			insertado=false;
		}
	else {
		vc.push_back(e);
		insertado=true;
	}
	return insertado;
}


bool conjunto::cheq_rep() const{
	vector<conjunto::entrada> :: const_iterator it;
	bool correcto = true;
	for (it = vc.cbegin() +1; it != vc.cend() && correcto; it++)
		correcto = (*it).getID() > 0 && (*it).getID() > (*(it-1)).getID();

	return correcto;
}

ostream & operator<<(ostream &sal,const conjunto &D){

    vector<conjunto::entrada>::const_iterator it;

    for(it=(D.vc).begin();it!=(D.vc).end();it++){

        sal << *it;

    }
    return sal;
}
