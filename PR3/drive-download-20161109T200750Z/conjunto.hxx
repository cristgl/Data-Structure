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

conjunto::iterator  conjunto::find( const long int & id){
   conjunto::iterator out;
	vector<conjunto::entrada>::iterator dcho=vc.end()-1;
	vector<conjunto::entrada>::iterator izdo=vc.begin();
	vector<conjunto::entrada>::iterator acomparar;
	bool encontrado = false,insertado;
	
	while(dcho>izdo && !encontrado){
		
		acomparar=(dcho-izdo)/2 +izdo;
		
	
		if(id<(*acomparar).getID())
			dcho=acomparar-1;
		else{
			if((*acomparar).getID()<id)
				izdo=acomparar+1;
			else{
					encontrado=true;
					out.itv=acomparar;
			}
		}
	}
	

	if(!encontrado)
		out.itv=vc.end();		
	return out;

}
conjunto::const_iterator  conjunto::find( const long int & id)const{
   conjunto::const_iterator out;
	vector<conjunto::entrada>::const_iterator dcho=vc.cend()-1;
	vector<conjunto::entrada>::const_iterator izdo=vc.cbegin();
	vector<conjunto::entrada>::const_iterator acomparar;
	bool encontrado = false,insertado;
	
	while(dcho>izdo && !encontrado){
		
		acomparar=(dcho-izdo)/2 +izdo;
		
	
		if(id<(*acomparar).getID())
			dcho=acomparar-1;
		else{
			if((*acomparar).getID()<id)
				izdo=acomparar+1;
			else{
					encontrado=true;
					out.c_itv=acomparar;
			}
		}
	}
	

	if(!encontrado)
		out.c_itv=vc.end();		
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
		if (descripcion.find(descr,0) != descripcion.string::npos)
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

conjunto::iterator conjunto::begin(){
	conjunto::iterator it;
	it.itv=vc.begin();

	return it;
}

conjunto::const_iterator conjunto::cbegin()const{
	conjunto::const_iterator it;
	it.c_itv=vc.cbegin();

	return it;
}

conjunto::iterator conjunto::end(){
	conjunto::iterator it;
	it.itv=vc.end();

	return it;
}

conjunto::const_iterator conjunto::cend()const{
	conjunto::const_iterator it;
	it.c_itv=vc.end();

	return it;
}

conjunto::arrest_iterator conjunto::abegin() {
    arrest_iterator sal;
    vector<entrada>::iterator iter;
    bool primer=false;
    
	 iter=vc.begin();
    while( iter!=vc.end() && !primer){
          primer=(*iter).getArrest();
			 if(!primer)
				iter++;
       }
          sal.itv=iter;
			 sal.mi_conj=&vc;
    return sal;                         
}

conjunto::arrest_iterator conjunto::aend(){
    conjunto::arrest_iterator sal;
    sal.itv=vc.end();
	 sal.mi_conj=&vc;
    return sal;
}

conjunto::const_arrest_iterator conjunto::cabegin()const{ // Chicago.cabegin()
	const_arrest_iterator it;
	vector<entrada>::const_iterator iter;
	bool encontrado=false;

	//buscar primero con arresto
	iter=vc.begin();
	while(iter!=vc.end()&&!encontrado){
 		encontrado=(*iter).getArrest();
		if(!encontrado)
			iter++;
	}
	it.mi_conj=&vc;
	it.c_itv=iter;
	return it;
}

conjunto::const_arrest_iterator conjunto::caend()const{
	const_arrest_iterator it;
	it.c_itv=vc.cend();
	it.mi_conj=&vc;

	return it;
}

conjunto::description_iterator  conjunto::dbegin(const string & descr){
	vector<entrada>::iterator it;
	description_iterator d_it;
	bool encontrado = false;
	string descripcion;
	it = vc.begin();
	while(it != vc.end() && !encontrado){
		descripcion = ((*it).getDescription());
		if(descripcion.find(descr,0) != string::npos)
				encontrado = true;
		else
				it++;

	}

	d_it.descr = descr;
	d_it.mi_conj= &vc;
	d_it.itv = it;
	return d_it;

}
		


conjunto::description_iterator  conjunto::dend( ){
	conjunto::description_iterator it;
	it.itv = vc.end();
	it.mi_conj = &vc;
	return it;
}	

conjunto::const_description_iterator  conjunto::cdbegin(const string & descr)const{
	string descripcion;
	vector<entrada>::const_iterator it;
	const_description_iterator d_it;
	bool encontrado = false;

	it = vc.cbegin();
	while(it != vc.cend() && !encontrado){
		descripcion = ((*it).getDescription());
		if(descripcion.find(descr,0) != string::npos)
				encontrado = true;
		else
				it++;

	}

	d_it.descr = descr;
	d_it.mi_conj=&vc;
	d_it.c_itv = it;
	return d_it;

}
		


conjunto::const_description_iterator  conjunto::cdend( )const{
	conjunto::const_description_iterator iter;
	iter.c_itv = vc.cend();
	iter.mi_conj= &vc;
	
	return iter;
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////   ITERADORES	//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


// iterator

conjunto::iterator::iterator(){}

conjunto::iterator::iterator(const iterator & it) {
	itv = it.itv;
}

const conjunto::entrada & conjunto::iterator::operator*() const {
	return *itv;
}

conjunto::iterator conjunto::iterator::operator++(int) { // it++
	conjunto::iterator original;
	original=*this;
	++itv;
	return original;
}

conjunto::iterator & conjunto::iterator::operator++(){	// ++it
	itv++;
	return *this;
}

conjunto::iterator conjunto::iterator::operator--(int) {
	conjunto::iterator original;
	original=*this;
	--itv;
	return original;
}

conjunto::iterator & conjunto::iterator::operator--(){
	itv++;
	return *this;
}

bool conjunto::iterator::operator==(const conjunto::iterator & it){
	return itv == it.itv;
}	

bool conjunto::iterator::operator!=(const conjunto::iterator & it){
	return itv != it.itv;
}

conjunto::iterator & conjunto::iterator::operator=(const conjunto::iterator &it){
	if(this!=&it)	
		itv = it.itv;
	return *this;
}
//const_iterator

conjunto::const_iterator::const_iterator(){}

conjunto::const_iterator::const_iterator(const iterator & it) {
	c_itv = it.itv;
}

conjunto::const_iterator::const_iterator(const const_iterator & it) {
	c_itv = it.c_itv;
}

const conjunto::entrada & conjunto::const_iterator::operator*() const {
	return *c_itv;
}

conjunto::const_iterator conjunto::const_iterator::operator++(int) {
	conjunto::const_iterator original;
	original=*this;
	++c_itv;
	return original;
}

conjunto::const_iterator & conjunto::const_iterator::operator++(){
	c_itv++;
	return *this;
}

conjunto::const_iterator conjunto::const_iterator::operator--(int) {
	conjunto::const_iterator original;
	original=*this;
	--c_itv;
	return original;
}

conjunto::const_iterator & conjunto::const_iterator::operator--(){
	c_itv--;
	return *this;
}

bool conjunto::const_iterator::operator==(const conjunto::const_iterator & it){
	return c_itv == it.c_itv;
}	

bool conjunto::const_iterator::operator!=(const conjunto::const_iterator & it){
	return c_itv != it.c_itv;
}
conjunto::const_iterator & conjunto::const_iterator::operator=(const conjunto::const_iterator &it){
	if(this!=&it)	
		c_itv = it.c_itv;
	return *this;
}
// description_iterator

conjunto::description_iterator::description_iterator(){
	descr = "";
}

conjunto::description_iterator::description_iterator(const conjunto::description_iterator & it){
	descr = it.descr;
	itv = it.itv;
}

const conjunto::entrada & conjunto::description_iterator::operator*() const{
	return *itv;
}


conjunto::description_iterator conjunto::description_iterator::operator++( int ){
	conjunto::description_iterator original;
	bool encontrado = false;
	original=*this;
	itv++;
	string descripcion;
	while(itv != (*mi_conj).end() && !encontrado){
		descripcion = ((*itv).getDescription());
		if(descripcion.find(descr,0) != string::npos)
				encontrado = true;
		else
				itv++;

	}
	
	return original;
}

conjunto::description_iterator & conjunto::description_iterator::operator++(){
	string descripcion;
	bool encontrado=false;
	itv++;
	while(itv != (*mi_conj).end() && !encontrado){
		descripcion = ((*itv).getDescription());
		if(descripcion.find(descr,0) != string::npos)
				encontrado = true;
		else
				itv++;
	}
	
	return *this;
}

conjunto::description_iterator conjunto::description_iterator::operator--(int){
	conjunto::description_iterator original;
	original=*this;
	itv--;
	string descripcion;
	bool encontrado=false;
	while(itv != (*mi_conj).begin()-1 && !encontrado){
		descripcion = ((*itv).getDescription());
		if(descripcion.find(descr,0) != string::npos)
				encontrado = true;
		else
				itv--;
	}

	if(!encontrado){
		*this=original;
	}
	
	return original;
}

conjunto::description_iterator & conjunto::description_iterator::operator--(){
	string descripcion;
	description_iterator original;
	original=*this;
	itv--;
	bool encontrado=false;
	while(itv != (*mi_conj).begin()-1 && !encontrado){
		descripcion = ((*itv).getDescription());
		if(descripcion.find(descr,0) != string::npos)
				encontrado = true;
		else
				itv--;
	}

	if(!encontrado)
		*this=original;

	return *this;
}		

bool conjunto::description_iterator::operator==(const conjunto::description_iterator & it){
	return itv == it.itv;
}

bool conjunto::description_iterator::operator!=(const conjunto::description_iterator & it){
	return itv != it.itv;
}	  

conjunto::description_iterator & conjunto::description_iterator::operator=(const conjunto::description_iterator &it){
	if(this!=&it){	
		itv = it.itv;
		descr=it.descr;
		mi_conj=it.mi_conj;
	}
	return *this;
}
// const_description_iterator

conjunto::const_description_iterator::const_description_iterator(){	
	descr = "";
}

conjunto::const_description_iterator::const_description_iterator(const conjunto::description_iterator & it){
	c_itv = it.itv;
}

conjunto::const_description_iterator::const_description_iterator(const conjunto::const_description_iterator & it){
	c_itv = it.c_itv;
}

const conjunto::entrada & conjunto::const_description_iterator::operator*() const{
	return *c_itv;
}

conjunto::const_description_iterator conjunto::const_description_iterator::operator++( int ){
	conjunto::const_description_iterator original;
	bool encontrado = false;
	original=*this;
	c_itv++;
	string descripcion;
	while(c_itv != (*mi_conj).cend() && !encontrado){
		descripcion = ((*c_itv).getDescription());
		if(descripcion.find(descr,0) != string::npos)
				encontrado = true;
		else
				c_itv++;
	}
	return original;
}

conjunto::const_description_iterator & conjunto::const_description_iterator::operator++(){
	bool encontrado = false;
	string descripcion;
	c_itv++;
	while(c_itv != (*mi_conj).end() && !encontrado){
		descripcion = ((*c_itv).getDescription());
		if(descripcion.find(descr,0) != string::npos)
				encontrado = true;
		else
				c_itv++;
	}
	return *this;
}

conjunto::const_description_iterator conjunto::const_description_iterator::operator--(int){
	conjunto::const_description_iterator original;
	original=*this;
	c_itv--;
	bool encontrado=false;
	string descripcion;
	while(c_itv != (*mi_conj).begin()-1 && !encontrado){
		descripcion = ((*c_itv).getDescription());
		if(descripcion.find(descr,0) != string::npos)
				encontrado = true;
		else
				c_itv--;
	}

	if(!encontrado)
		*this=original;
	
	return original;
}

conjunto::const_description_iterator & conjunto::const_description_iterator::operator--(){
	string descripcion;
	const_description_iterator original;
	original=*this;
	c_itv--;
	bool encontrado=false;
	while(c_itv != (*mi_conj).begin()-1 && !encontrado){
		descripcion = ((*c_itv).getDescription());
		if(descripcion.find(descr,0) != string::npos)
				encontrado = true;
		else
				c_itv--;
	}

	if(!encontrado)
		*this=original;

	return *this;
}

bool  conjunto::const_description_iterator::operator==(const conjunto::const_description_iterator & it){
	return c_itv == it.c_itv;
}

bool  conjunto::const_description_iterator::operator!=(const conjunto::const_description_iterator & it){
	return c_itv != it.c_itv;
}
conjunto::const_description_iterator & conjunto::const_description_iterator::operator=(const conjunto::const_description_iterator &it){
	if(this!=&it){	
		c_itv = it.c_itv;
		descr=it.descr;
		mi_conj=it.mi_conj;
	}
	return *this;
}
// arrest_iterator

conjunto::arrest_iterator::arrest_iterator(){}

conjunto::arrest_iterator::arrest_iterator(const conjunto::arrest_iterator &ai){
    itv = ai.itv;
}

const conjunto::entrada &conjunto::arrest_iterator::operator*() const{
    return *itv;     
}

conjunto::arrest_iterator conjunto::arrest_iterator::operator++(int){
    conjunto::arrest_iterator dev;
    bool primer=false;
    dev= *this;
	 itv++;
    while( itv!=(*mi_conj).end() && !primer){
          primer=(*itv).getArrest();
			 if(!primer)
				itv++;
     }

    return dev;   
} 

conjunto::arrest_iterator & conjunto::arrest_iterator::operator++(){
   bool primer=false; 
	itv++; 
	while( itv!=(*mi_conj).end() && !primer){
     		primer=(*itv).getArrest();
			if(!primer)
				itv++;
    }
    return *this;
}

conjunto::arrest_iterator conjunto::arrest_iterator::operator--(int){
   conjunto::arrest_iterator dev;
   dev=*this;
	bool primer=false;
	itv--;
   while( itv!=(*mi_conj).begin()-1 && !primer){
   	primer=(*itv).getArrest();
		if(!primer)
			itv--;
    }

	if(!primer)
		*this=dev;

	return dev;
}

conjunto::arrest_iterator & conjunto::arrest_iterator::operator--(){
	bool primer=false;
	conjunto::arrest_iterator dev;
	dev=*this;
	itv--;
    while( itv!=(*mi_conj).begin()-1 && !primer){
   	primer=(*itv).getArrest();
		if(!primer)
			itv--;
    }

	if(!primer)
		*this=dev;

    return *this;
}

bool conjunto::arrest_iterator::operator==(const conjunto::arrest_iterator &it){
    return itv==it.itv;
}

bool conjunto::arrest_iterator::operator!=(const conjunto::arrest_iterator & it){
     return itv!=it.itv;
}

conjunto::arrest_iterator & conjunto::arrest_iterator::operator=(const conjunto::arrest_iterator &it){
	if(this!=&it){	
		itv = it.itv;
		mi_conj=it.mi_conj;
	}
	return *this;
}
// const_arrest_iterator

conjunto::const_arrest_iterator::const_arrest_iterator(){}

conjunto::const_arrest_iterator::const_arrest_iterator(const const_arrest_iterator &it){
	c_itv=it.c_itv;
}

conjunto::const_arrest_iterator::const_arrest_iterator(const arrest_iterator &it){
	c_itv=it.itv;
}

const conjunto::entrada & conjunto::const_arrest_iterator::operator*() const{
	return *c_itv;
}

conjunto::const_arrest_iterator conjunto::const_arrest_iterator::operator++(int){
	conjunto::const_arrest_iterator org;
	org=*this;
	c_itv++;
	bool encontrado=false;
	while(c_itv!=(*mi_conj).end()&&!encontrado){
 		if( !(encontrado=(*c_itv).getArrest()) )
			c_itv++;
	}

	return org;
}

conjunto::const_arrest_iterator & conjunto::const_arrest_iterator::operator++(){
	bool encontrado=false;
	c_itv++;
	while(c_itv!=(*mi_conj).end()&&!encontrado){
 		if( !(encontrado=(*c_itv).getArrest()) )
			c_itv++;
	}

	return *this;
};
conjunto::const_arrest_iterator conjunto::const_arrest_iterator::operator--(int){
   conjunto::const_arrest_iterator dev;
	dev=*this;
	bool primer=false;
	c_itv--;
   while( c_itv!=(*mi_conj).begin()-1 && !primer){
   	primer=(*c_itv).getArrest();
		if(!primer)
			c_itv--;
    }

	if(!primer)
		*this=dev;

	return dev;
}
conjunto::const_arrest_iterator & conjunto::const_arrest_iterator::operator--(){
	bool primer=false;
	conjunto::const_arrest_iterator dev;
	dev=*this;
	c_itv--;
   while( c_itv!=(*mi_conj).begin()-1 && !primer){
   	primer=(*c_itv).getArrest();
		if(!primer)
			c_itv--;
    }

	if(!primer)
		*this=dev;

	return *this;
}

bool conjunto::const_arrest_iterator::operator==(const const_arrest_iterator &it){
	return c_itv==it.c_itv;
}

bool conjunto::const_arrest_iterator::operator!=(const const_arrest_iterator &it){
	return c_itv!=it.c_itv;
}

conjunto::const_arrest_iterator & conjunto::const_arrest_iterator::operator=(const conjunto::const_arrest_iterator &it){
	if(this!=&it){	
		c_itv = it.c_itv;
		mi_conj=it.mi_conj;
	}
	return *this;
}
