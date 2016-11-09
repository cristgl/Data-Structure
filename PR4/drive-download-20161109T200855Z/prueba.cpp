#include <functional>
#include "crimen.h"
#include "conjunto.h"
#include "fecha.h"
#include "functor.h"
#include <iostream>
#include <fstream>
#include <string>

bool to_bool(const string& str){
	return ( str=="true");
}
template<class CMP>
bool load(conjunto<CMP> &  C, const string & s) {
////////////////////////
clock_t start, end;
///////////////////////
 ifstream fe;
 string cadena;
	int principio,fin;
	crimen crim;

 cout << "Abrimos "<< s << endl;
 fe.open(s.c_str(), ifstream::in);
 if (fe.fail())    
 {
   cerr << "Error al abrir el fichero " << s << endl;
 } else {
   getline(fe,cadena,'\n'); //leo la cabecera del fichero
   //cout << cadena << endl;
	int contador=0;
    while (contador<1000)//!fe.eof()
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
			//ignora DISTRIC	
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
				
	   C.insert(crim) ;
		//cout<<crim;

     	}
		}
    fe.close();
    return true;
    } // else
  fe.close();
  return false;
 }
int main(){
	crimen cri; 
	conjunto<CrecientePorIUCR> X;

	load(X,"crimenes.csv");
	conjunto<CrecientePorIUCR>::iterator it;
	conjunto<CrecientePorIUCR>::iterator ito;
	conjunto<CrecientePorFecha> Y(X.begin(),X.end());
	conjunto<CrecientePorFecha>::iterator iter;
	

	for(it=X.begin();it!=X.end();++it)
		cout << endl <<	(*it).getIUCR()  <<"	"<< (*it).getDate() << endl;

	cout << "__________________________________________________________" << endl;
	for(iter=Y.begin();iter!=Y.end();++iter)
		cout << (*iter).getDate() << "	"<< (*iter).getIUCR()<< endl;



}
