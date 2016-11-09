#include "CSS.h"
#include <iostream>
#include <functional>
#include "crimen.h"
#include "fecha.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;
bool to_bool(const string& str){
	return ( str=="true");
}

void CSS::load(string nombreDB){
	////////////////////////
	clock_t start, end;
	///////////////////////
	 ifstream fe;
	 string cadena;
		int principio,fin;
		crimen crim;

	 cout << "Abrimos "<< nombreDB << endl;
	 fe.open(nombreDB.c_str(), ifstream::in);
	 if (fe.fail()){
	   cerr << "Error al abrir el fichero " << nombreDB << endl;
	 } else {
	   getline(fe,cadena,'\n'); //leo la cabecera del fichero
	   //cout << cadena << endl;
		int contador=0;
		while (contador<5000)//contador<1000!fe.eof()
		  {contador++; 
				getline(fe,cadena,'\n');
		   	if (!fe.eof()) {
		   //cout << "leo:: "<< cadena << endl;
		   // Convertir cadena a crimen
		  principio=0;
				//set    ID
			fin=cadena.find_first_of(',',principio);
			long int aux=stol(cadena.substr(principio,fin-principio));
			crim.setID(aux);
			principio=fin;
				//set    CASE_NUMBER
			fin=cadena.find_first_of(',',principio+1);
			crim.setCaseNumber(cadena.substr(principio+1,fin-principio-1));
			principio=fin;
				//set    DATE
			fin=cadena.find_first_of(',',principio+1);
			fecha date(cadena.substr(principio+1,fin-principio-1));
			crim.setDate(date);
			principio=fin;
				//ignora BLOCK
			fin=cadena.find_first_of(',',principio+1);
			principio=fin;
				//set    IUCR
			fin=cadena.find_first_of(',',principio+1);
			crim.setIUCR(cadena.substr(principio+1,fin-principio-1));
			principio=fin;
				//set    PRIMARY_TYPE
			fin=cadena.find_first_of(',',principio+1);
			crim.setPrimaryType(cadena.substr(principio+1,fin-principio-1));
			principio=fin;
				//set    DESCRIPTION 
			fin=cadena.find_first_of(',',principio+1);
			crim.setDescription(cadena.substr(principio+1,fin-principio-1));
			principio=fin;
				//set    LOCATION_DESCRIPTION
			fin=cadena.find_first_of(',',principio+1);
			crim.setLocationDescription(cadena.substr(principio+1,fin-principio-1));
			principio=fin;
				//set    ARREST
			fin=cadena.find_first_of(',',principio+1);
			crim.setArrest(to_bool(cadena.substr(principio+1,fin-principio-1)));
			principio=fin;
				//set   DOMESTIC
			fin=cadena.find_first_of(',',principio+1);
			crim.setDomestic(to_bool(cadena.substr(principio+1,fin-principio-1)));
			principio=fin;
				//ignora BEAT
			fin=cadena.find_first_of(',',principio+1);
			principio=fin;
				//ignora DISTRICT
			fin=cadena.find_first_of(',',principio+1);
			principio=fin;
				//ignora WARD
			fin=cadena.find_first_of(',',principio+1);
			principio=fin;
				//ignora COMMUNITY_AREA
			fin=cadena.find_first_of(',',principio+1);
			principio=fin;
				//ignora FBI_CODE
			fin=cadena.find_first_of(',',principio+1);
			principio=fin;
				//ignora X_COORDINATE
			fin=cadena.find_first_of(',',principio+1);
			principio=fin;
				//ignora Y_COORDINATE
			fin=cadena.find_first_of(',',principio+1);
			principio=fin;
				//ignora YEAR
			fin=cadena.find_first_of(',',principio+1);
			principio=fin;
				//ignora UPDATED_ON
			fin=cadena.find_first_of(',',principio+1);
			principio=fin;
				//set    LATITUDE
			fin=cadena.find_first_of(',',principio+1);
			if(fin-principio-1 != 0)
				crim.setLatitude(stod(cadena.substr(principio+1,fin-principio-1)));
			principio=fin;
				//set    LONGITUDE
			fin=cadena.find_first_of(',',principio+1);
			if(fin-principio-1 != 0)
				crim.setLongitude(stod(cadena.substr(principio+1,fin-principio-1)));
			principio=fin;
				//ignora LOCATION
			fin=cadena.find_first_of(',',principio+1);
			//cout << " NUMERO " << contador << endl;
		    insert(crim) ;
		    
			//cout<<crim;

		 	}
		}
		fe.close();
		
	} // else
	  	fe.close();   
}

CSS::CSS(){}

CSS::CSS(const CSS & css){
	baseDatos=css.baseDatos;
	DateAccess=css.DateAccess;
	IUCRAccess=css.IUCRAccess;
	index=css.index;
	posicionGeo=css.posicionGeo;
}

void CSS::insert(const crimen & x){
	//baseDatos
	baseDatos[x.getID()]=(x);
	
	//DateAccess
	map<CSS::ID,CSS::Crimen>::iterator it;
	it = baseDatos.find(x.getID());
	pair<Date,map<ID,Crimen>::iterator> par;
	par.first=x.getDate();
	par.second=it;
	DateAccess.insert(par);
	
	//IUCRAccess
	IUCRAccess[x.getIUCR()].insert(x.getID());
	
	//index
	string cadena;
	int pos,primpos=0;
	cadena=x.getDescription();
	pos=cadena.find_first_of(" ",primpos);
	index[cadena.substr(primpos,pos-primpos)].insert(x.getID());
	primpos=pos+1;
	
	while(pos!=string::npos){
		pos=cadena.find_first_of(" ",primpos);
		index[cadena.substr(primpos,pos-primpos)].insert(x.getID());
		primpos=pos+1;
	}
	
	//posicionGeo
	pair<Latitud,ID> par1;
	par1.first=x.getLatitude();
	par1.second=x.getID();
	posicionGeo[x.getLongitude()].insert(par1);
	
}

void CSS::erase(unsigned int ID){
	CSS::iterator it1;
	it1.it=baseDatos.find(ID);
	//(*it1).second devuelve el crimen
	
	multimap<CSS::Date, map<CSS::ID,CSS::Crimen>::iterator>::iterator it2;
	it2=DateAccess.find(((*it1).second).getDate());
	if(((((*it2).second))->second).getID()==ID)
		DateAccess.erase(it2);//BORRADO DE DATEACCESS
	
	map<CSS::IUCR,set<CSS::ID>>::iterator it3;
	it3=IUCRAccess.find(((*it1).second).getIUCR());
	IUCRAccess[(*it3).first].erase(ID);//BORRADO DE IUCRACCESS
	
	string cadena;
	int pos,primpos=0;

	cadena=((*it1).second).getDescription();
	pos=cadena.find_first_of(" ",primpos);
	index[cadena.substr(primpos,pos-primpos)].erase(((*it1).second).getID());
	primpos=pos+1;
	
	while(pos!=string::npos){
		pos=cadena.find_first_of(" ",primpos);
		index[cadena.substr(primpos,pos-primpos)].erase(((*it1).second).getID());
		primpos=pos+1;
	}//BORRADO DE INDEX
	
	
	map<CSS::Longitud,multimap<CSS::Latitud, CSS::ID>>::iterator it6;
	it6=posicionGeo.find(((*it1).second).getLongitude());
	posicionGeo[(*(posicionGeo[(*it6).first].find(((*it1).second).getLatitude()))).first].erase(ID);//BORRADO DE POSICIONGEO
	
	baseDatos.erase(ID);//BORRADO DE BASEDATOS
	
}

CSS::iterator CSS::find_ID(unsigned int ID){
	CSS::iterator iter;
	iter.it = baseDatos.find(ID);
	return iter;
}

void CSS::setArrest(const unsigned int ID, bool value){
	((*find_ID(ID)).second).setArrest(value);
}

list<CSS::ID> CSS::inArea(Longitud x1, Latitud y1, Longitud x2, Latitud y2){
	list<CSS::ID> lista;
	map<CSS::ID,CSS::Crimen>::iterator iter;
	for(iter=baseDatos.begin(); iter!=baseDatos.end(); iter++)
		if((x1<=((*iter).second).getLongitude()) && (((*iter).second).getLongitude()<=x2) &&
			(((*iter).second).getLatitude()<=y1) && (y2<=((*iter).second).getLatitude()))
			lista.push_back((*iter).first);
	
	return lista;
}

/*bool CSS::cmp::operator()(pair<CSS::ID,float> &p1, pair<CSS::ID,float> &p2){

}*/

map<CSS::ID,float> unionPeso(const set<CSS::ID> & t1, const set<CSS::ID> &t2){
	map<CSS::ID,float> mymap;
	set<CSS::ID>::iterator it1,it2;
	it1=t1.begin();
	it2=t2.begin();

	while(it1!=t1.end()){
		mymap[(*it1)]=1.0;
		it1++;
	}		
	
	while(it2!=t2.end()){
		if((mymap.find(*it2))!=mymap.end())
			mymap[(*it2)]=2.0;
		else
			mymap[(*it2)]=1.0;
		
		it2++;
	}
	
	return mymap;
}

void unionPeso(map<CSS::ID,float> & m, set<CSS::ID> & t_i){
	set<CSS::ID>::iterator it1;
	it1=t_i.begin();
	while(it1!=t_i.end())
		m[(*it1)]++;	
}


vector<pair<CSS::ID,float>> CSS::Query(list<string> & q, int k){
	unordered_map<CSS::Termino,set<CSS::ID>>::iterator it;
	map<CSS::ID,float> mymap;
	vector<pair<CSS::ID,float>> myvector;
	list<string>::iterator it2;
	int i=2;

	if(q.size()==1){
		it=index.find(q.front());
		//((*it).second).lower_bound();
		myvector.insert(make_pair(,1.0));
	}else{ 
		if(q.size()>=2){
			it2=q.begin();
			it2++;
			mymap=unionPeso(((*index.find(q.front())).second),((*index.find(*it2)).second));
			if(q.size()>2){
				it2++;
				while(i!=q.size()){
					unionPeso(mymap,(*index.find(*it2)).second);
					it2++;
					i++;
				}
			}
		}
	}
	//se le pasa un functor a priority queue. primero es el peor
	return myvector;
}

CSS::IUCR_iterator CSS::ibegin(){
	CSS::IUCR_iterator iter;
	iter.miCSS=this;
	iter.it_m=IUCRAccess.begin();
	iter.it_s=((IUCRAccess.begin())->second).begin();
	return iter;
}

CSS::IUCR_iterator CSS::iend(){
	CSS::IUCR_iterator iter;
	iter.it_m=IUCRAccess.end();
	iter.it_s=((--(IUCRAccess.end()))->second).end();
	return iter;
}

CSS::IUCR_iterator CSS::lower_bound(IUCR i){
	CSS::IUCR_iterator iit;
	bool encontrado=false;
	
	for(iit = ibegin(); iit!=iend() && !encontrado; iit++)
		encontrado = (((*iit).second).getIUCR()>=i);
	
	return iit;
}

CSS::IUCR_iterator CSS::upper_bound(IUCR i){
	CSS::IUCR_iterator iit;
	bool encontrado=false;
	
	for(iit = ibegin(); iit!=iend() && !encontrado; iit++)
		encontrado = (((*iit).second).getIUCR()>i);
	
	return iit;
}

CSS::Date_iterator CSS::dbegin(){
	CSS::Date_iterator iter;
	iter.it_mm=DateAccess.begin();
	return iter;
}

CSS::Date_iterator CSS::dend(){
	CSS::Date_iterator iter;
	iter.it_mm=DateAccess.end();
	return iter;
}

CSS::Date_iterator CSS::lower_bound(Date d){
	CSS::Date_iterator dit;
	bool encontrado=false;
	
	for(dit = dbegin(); dit!=dend() && !encontrado; dit++)
		encontrado = (((*dit).second).getDate()>=d);
	
	return dit;
}

CSS::Date_iterator CSS::upper_bound(Date d){
	CSS::Date_iterator dit;
	bool encontrado=false;
	
	for(dit = dbegin(); dit!=dend() && !encontrado; dit++)
		encontrado = (((*dit).second).getDate()>d);
	
	return dit;
}


CSS::iterator CSS::begin(){
	CSS::iterator iter;
	iter.it=baseDatos.begin();
	return iter;
}

CSS::iterator CSS::end(){
	CSS::iterator iter;
	iter.it=baseDatos.end();
	return iter;
}


////////////////ITERATOR////////////
CSS::iterator::iterator(){}

CSS::iterator::iterator(const iterator & iter){
	it=iter.it;
}

pair<const CSS::ID, CSS::Crimen> & CSS::iterator::operator*(){
	return *it;
}	

CSS::iterator CSS::iterator::operator++( int ){
	CSS::iterator original;
	original=*this;
	++it;
	return original;
}

CSS::iterator & CSS::iterator::operator++(){
	it++;
	return *this;
}

CSS::iterator CSS::iterator::operator--(int){
	CSS::iterator original;
	original=*this;
	--it;
	return original;
}

CSS::iterator & CSS::iterator::operator--(){
	it--;
	return *this;
}

bool CSS::iterator::operator==(const iterator & iter){
	return it == iter.it;
}

bool CSS::iterator::operator!=(const iterator & iter){
	return it!=iter.it;
}

CSS::iterator & CSS::iterator::operator=(const iterator & iter){
	if(this!=&iter)	
		it = iter.it;
	return *this;
}

///////////IUCR_ITERATOR//////////
CSS::IUCR_iterator::IUCR_iterator(){}

CSS::IUCR_iterator::IUCR_iterator(const IUCR_iterator & iter){
	it_m=iter.it_m;
	it_s=iter.it_s;
	miCSS=iter.miCSS;
}

pair<const CSS::ID, CSS::Crimen > & CSS::IUCR_iterator::operator*(){
	return *(((*miCSS).baseDatos).find(*it_s));
}

CSS::IUCR_iterator & CSS::IUCR_iterator::operator++(){
	if(it_s!=(--((it_m->second).end())))
		it_s++;
	else{
		it_m++;
		it_s=(it_m->second).begin();
	}
	return *this;
}

CSS::IUCR_iterator CSS::IUCR_iterator::operator++(int){
	CSS::IUCR_iterator original;
	original=*this;
	++(*this);
	return original;
}

CSS::IUCR_iterator & CSS::IUCR_iterator::operator--(){
	if(it_s!=((it_m->second).begin()))
		it_s--;
	else{
		it_m--;
		it_s=(--(it_m->second).end());
	}
	return *this;
}

CSS::IUCR_iterator CSS::IUCR_iterator::operator--(int){
	CSS::IUCR_iterator original;
	original=*this;
	--(*this);
	return original;
}

bool CSS::IUCR_iterator::operator==(const IUCR_iterator & iter){
	return it_m==iter.it_m && it_s==it_s;
}

bool CSS::IUCR_iterator::operator!=(const IUCR_iterator & iter){
	return it_m!=iter.it_m || it_s!=it_s;
}

CSS::IUCR_iterator & CSS::IUCR_iterator::operator=(const IUCR_iterator & iter){
	if(this!=&iter){
		it_m=iter.it_m;
		it_s=iter.it_s;
		miCSS=iter.miCSS;
	}
	return *this;
}

/////////////DATE ITERATOR///////////////

CSS::Date_iterator::Date_iterator(){}

CSS::Date_iterator::Date_iterator(const Date_iterator & it){
	it_mm=it.it_mm;
}

pair<const CSS::ID, CSS::Crimen > & CSS::Date_iterator::operator*(){
	return *(it_mm->second);
}

CSS::Date_iterator CSS::Date_iterator::operator++(int){
	CSS::Date_iterator original;
	original=*this;
	++it_mm;
	return original;
}

CSS::Date_iterator & CSS::Date_iterator::operator++(){
	it_mm++;
	return *this;
}

CSS::Date_iterator CSS::Date_iterator::operator--(int){
	CSS::Date_iterator original;
	original=*this;
	--it_mm;
	return original;
}

CSS::Date_iterator & CSS::Date_iterator::operator--(){
	it_mm--;
	return *this;
}

bool CSS::Date_iterator::operator==(const Date_iterator & it){
	return it_mm==it.it_mm;
}

bool CSS::Date_iterator::operator!=(const Date_iterator & it){
	return it_mm!=it.it_mm;
}

CSS::Date_iterator & CSS::Date_iterator::operator=(const Date_iterator & it){
	if(this!=&it)
		it_mm=it.it_mm;
	return *this;
}
