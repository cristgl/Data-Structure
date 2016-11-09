#include "conjunto.h"
#include <iostream>
using namespace std;
template<class CMP>
conjunto<CMP>::conjunto():vc(0)
{}
template<class CMP>
conjunto<CMP>::conjunto(const conjunto<CMP> &d){
	vc=d.vc;
	comp=d.comp;
}
template<class CMP>
template<class IT>
conjunto<CMP>::conjunto( const IT &ini,const IT &fin){
	IT it;
	for(it=ini;it!=fin;it++)
		this->insert(*it);
}
template<class CMP>
typename conjunto<CMP>::size_type conjunto<CMP>::size() const{
   return vc.size();
}


template<class CMP>
conjunto<CMP> conjunto<CMP>::findIUCR (const string & iucr) const{
	conjunto<CMP> C_iucr;
	vector<conjunto::entrada>:: const_iterator it;

	for (it = vc.cbegin(); it != vc.cend(); it++) 
		if ((*it).getIUCR() == iucr)
			C_iucr.insert((*it));
		
	return C_iucr;
}
template<class CMP>
conjunto<CMP> conjunto<CMP>::findDESCR (const string & descr) const{
	conjunto<CMP> C_iucr;
	vector<crimen> :: const_iterator it;
	string descripcion;

	for (it = vc.cbegin(); it != vc.cend(); it++) {
		descripcion = ((*it).getDescription());
		if (descripcion.find(descr,0) != descripcion.string::npos)
			C_iucr.insert(*it);
	}

	return C_iucr;
}
template<class CMP>
conjunto<CMP>& conjunto<CMP>::operator=(const conjunto<CMP> &org){
	if(&org!=this){
		vc=org.vc;
		comp=org.comp;
	}
	return *this;
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::find(const long int &id) {
	conjunto<CMP>::iterator out;
	bool encontrado=false;
	vector<crimen>::iterator it;

	for (it = vc.begin(); it != vc.end() && !encontrado; it++) 
		encontrado=((*it).getID()==id);	
	
	out.itv=encontrado?it-1:vc.end();


	return out;
}
template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::find(const long int &id)const{
	conjunto<CMP>::const_iterator out;
	bool encontrado=false;
	vector<crimen>::const_iterator it;

	for (it = vc.cbegin(); it != vc.cend() && !encontrado; it++) 
		encontrado=((*it).getID()==id);	
	
	out.c_itv=encontrado?it-1:vc.cend();


	return out;
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::find(const crimen &e){
	conjunto<CMP>::iterator it;
	vector<conjunto<CMP>::entrada>::iterator dcho=vc.end()-1;
	vector<conjunto<CMP>::entrada>::iterator izdo=vc.begin();
	vector<conjunto<CMP>::entrada>::iterator acomparar;
	bool encontrado = false;

	if(!empty()){
		while(dcho>izdo && !encontrado){
			acomparar=(dcho-izdo)/2 +izdo;
	
			if(comp(e,*acomparar))
				dcho=acomparar-1;
			else
				if(comp(*acomparar,e))
					izdo=acomparar+1;
				else{
						encontrado=true;
						it.itv=acomparar;
						
				}
		}
	}
	
	if(!encontrado)
		it.itv=vc.end();
		
		
	return it;


}
template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::find(const crimen &e)const{
	conjunto<CMP>::const_iterator it;
	vector<conjunto<CMP>::entrada>::iterator dcho=vc.cend()-1;
	vector<conjunto<CMP>::entrada>::iterator izdo=vc.cbegin();
	vector<conjunto<CMP>::entrada>::iterator acomparar;
	bool encontrado = false;

	if(!empty()){
		while(dcho>izdo && !encontrado){
			acomparar=(dcho-izdo)/2 +izdo;
	
			if(comp(e,*acomparar))
				dcho=acomparar-1;
			else
				if(comp(*acomparar,e))
					izdo=acomparar+1;
				else{
						encontrado=true;
						it.c_itv=acomparar;
					
				}
		}
	}
	
	if(!encontrado)
		it.c_itv=vc.cend();
		
		
	return it;


}
template<class CMP>
bool conjunto<CMP>::erase(const long int &id){
   bool borrado=false;
   vector<conjunto<CMP>::entrada>::iterator it;
  	if(!empty())
   	for(it=vc.begin(); it!=vc.end() && !borrado; it++){
			if((*it).getID()==id){
	   		vc.erase(it);
	   		borrado=true;
			}
  	 	}

   return borrado;
}
template<class CMP>
bool conjunto<CMP>::erase(const conjunto<CMP>::entrada &e){ // BORRA TODOS LOS QUE COINCIDAN CON EL CRITERIO DE COMPARACION
   bool borrado=false;
   vector<conjunto<CMP>::entrada>::iterator it,ini;
  	if(!empty())
   	for(it=vc.begin(); it!=vc.end() && !borrado; it++){
			if(!comp(*it,e) && !comp(e,*it)){
				ini=it;
	   		while(!comp(*it,e) && !comp(e,*it)){
				it++;
				}
				vc.erase(ini,it);
	   		borrado=true;
			}
   	}

   return borrado;
}
template<class CMP>
bool conjunto<CMP>::insert(const conjunto<CMP>::entrada &e){
	vector<conjunto<CMP>::entrada>::iterator dcho=vc.end()-1;
	vector<conjunto<CMP>::entrada>::iterator izdo=vc.begin();
	vector<conjunto<CMP>::entrada>::iterator acomparar;
	bool encontrado = false,insertado;

	if(!empty()){
		while(dcho>izdo && !encontrado){
		
			acomparar=(dcho-izdo)/2 + izdo;
			
	
			if(comp(e,*acomparar))
				dcho=acomparar-1;
			else if(comp(*acomparar,e))
					izdo=acomparar+1;
			else	encontrado=true;
		}
	

		if (encontrado) vc.insert(acomparar,e);
		else	if (comp(e,*izdo)) vc.insert(izdo,e);
		else vc.insert(izdo+1,e);
		insertado=true;
		
	
	}
	else {
		vc.push_back(e);
		insertado=true;
	}
	return insertado;
}

template<class CMP>
bool conjunto<CMP>::empty() const{
   return size()==0;
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::begin(){
	conjunto<CMP>::iterator it;
	it.itv=vc.begin();

	return it;
}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::cbegin()const{
	conjunto<CMP>::const_iterator it;
	it.c_itv=vc.cbegin();

	return it;
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::end(){
	conjunto<CMP>::iterator it;
	it.itv=vc.end();

	return it;
}
template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::cend()const{
	conjunto<CMP>::const_iterator it;
	it.c_itv=vc.end();

	return it;
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::lower_bound(const conjunto<CMP>::entrada &x){
	vector<conjunto<CMP>::entrada>::iterator it;
	bool encontrado=false;
	conjunto<CMP>::iterator iter;
	for(it=vc.begin();it!=vc.end() && !encontrado; it++)
		encontrado= !(comp(*it,x));

	iter.itv=--it;


	return iter;
}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::lower_bound(const conjunto<CMP>::entrada &x) const{
	vector<conjunto<CMP>::entrada>::const_iterator it;
	bool encontrado=false;
	conjunto<CMP>::const_iterator iter;
	for(it=vc.cbegin();it!=vc.cend() && !encontrado; it++)
		encontrado= !(comp(*it,x));

	iter.c_itv=--it;

	return iter;
}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::upper_bound(const conjunto<CMP>::entrada &x) const{
	vector<conjunto<CMP>::entrada>::const_iterator it;
	bool encontrado=false;
	conjunto<CMP>::const_iterator iter;
	for(it=vc.cbegin();it!=vc.cend() && !encontrado; it++)
		encontrado=(comp(x,*it));

	iter.c_itv=--it;


	return iter;
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::upper_bound(const conjunto<CMP>::entrada &x){
	vector<conjunto<CMP>::entrada>::iterator it;
	bool encontrado=false;
	conjunto<CMP>::iterator iter;
	for(it=vc.begin();it!=vc.end() && !encontrado; it++)
		encontrado=(comp(x,*it));

	iter.itv=--it;


	return iter;
}
template<class CMP>
bool conjunto<CMP>::cheq_rep() const{
	vector<conjunto<CMP>::entrada> :: const_iterator it;
	bool correcto = true;
	for (it = vc.cbegin(); it != (vc.cend()-1) && correcto; it++)
		correcto=(  comp(*it,*(it+1)) || (!(comp(*it,*(it+1))) && !(comp(*(it+1),*it))));

	return correcto;
}
///////////////////////////////////////////////////////////////////
template<class CMP>
 conjunto<CMP>::iterator::iterator(){}

template<class CMP>
 conjunto<CMP>::iterator::iterator(const iterator & it) {
	itv = it.itv;
}
template<class CMP>
const typename conjunto<CMP>::entrada & conjunto<CMP>::iterator::operator*() const {
	return *itv;
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::iterator::operator++(int) { // it++
	conjunto<CMP>::iterator original;
	original=*this;
	++itv;
	return original;
}

template<class CMP>
typename conjunto<CMP>::iterator & conjunto<CMP>::iterator::operator++(){	// ++it
	itv++;
	return *this;
}

template<class CMP>
typename conjunto<CMP>::iterator conjunto<CMP>::iterator::operator--(int) {
	conjunto<CMP>::iterator original;
	original=*this;
	--itv;
	return original;
}

template<class CMP>
typename conjunto<CMP>::iterator & conjunto<CMP>::iterator::operator--(){
	itv++;
	return *this;
}

template<class CMP>
bool conjunto<CMP>::iterator::operator==(const conjunto::iterator & it){
	return itv == it.itv;
}	

template<class CMP>
bool conjunto<CMP>::iterator::operator!=(const conjunto::iterator & it){
	return itv != it.itv;
}

template<class CMP>
typename conjunto<CMP>::iterator & conjunto<CMP>::iterator::operator=(const conjunto::iterator &it){
	if(this!=&it)	
		itv = it.itv;
	return *this;
}

//Clase const_iterator

template<class CMP>
conjunto<CMP>::const_iterator::const_iterator(){}

template<class CMP>
conjunto<CMP>::const_iterator::const_iterator(const iterator & it) {
	c_itv = it.itv;
}

template<class CMP>
conjunto<CMP>::const_iterator::const_iterator(const const_iterator & it) {
	c_itv = it.c_itv;
}

template<class CMP>
const typename conjunto<CMP>::entrada & conjunto<CMP>::const_iterator::operator*() const {
	return *c_itv;
}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::const_iterator::operator++(int) {
	conjunto<CMP>::const_iterator original;
	original=*this;
	++c_itv;
	return original;
}

template<class CMP>
typename conjunto<CMP>::const_iterator & conjunto<CMP>::const_iterator::operator++(){
	c_itv++;
	return *this;
}

template<class CMP>
typename conjunto<CMP>::const_iterator conjunto<CMP>::const_iterator::operator--(int) {
	conjunto<CMP>::const_iterator original;
	original=*this;
	--c_itv;
	return original;
}

template<class CMP>
typename conjunto<CMP>::const_iterator & conjunto<CMP>::const_iterator::operator--(){
	c_itv--;
	return *this;
}

template<class CMP>
bool conjunto<CMP>::const_iterator::operator==(const conjunto::const_iterator & it){
	return c_itv == it.c_itv;
}	

template<class CMP>
bool conjunto<CMP>::const_iterator::operator!=(const conjunto::const_iterator & it){
	return c_itv != it.c_itv;
}

template<class CMP>
typename conjunto<CMP>::const_iterator & conjunto<CMP>::const_iterator::operator=(const conjunto::const_iterator &it){
	if(this!=&it)	
		c_itv = it.c_itv;
	return *this;
}

