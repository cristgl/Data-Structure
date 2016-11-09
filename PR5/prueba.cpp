#include <functional>
#include "crimen.h"
#include "CSS.h"
#include "fecha.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <set>

using namespace std;
//-std=c++0x

int main(){
	CSS X;
	CSS::IUCR_iterator it;
	int cont=0;
	X.load("crimefnes.csv");
	list<CSS::ID> lista;
	list<CSS::ID>::iterator iter;
	/*
	map<CSS::ID,float> mimap;
	map<CSS::ID,float>::iterator it2;
	set<CSS::ID> t1,t2;
	t1.insert(10230953);t1.insert(10231208);t1.insert(10230974);t1.insert(10231069);//tener en cuenta el tamaño
	t2.insert(10230953);t2.insert(10230979);t2.insert(10230943);t2.insert(10231069);

	mimap=unionPeso(t1,t2);

	for (auto& x: mimap) {
    	cout << x.first << ": " << x.second << '\n';
  }
*/

	
	
	
	
	
	/*CSS::iterator it2;
	it=X.ibegin();
	it2=X.find_ID(10230920);
	cout << (*it2).second;
	X.erase(10230920);
	it2=X.find_ID(10230920);
	cout << "oh sister soul sister" << endl;
	(--it2);
	cout << ((*it2).second);
	/*while(it!=X.iend() && cont < 50){
		cout << cont << " ";
		cout << (*it).first << "second " << (*it).second <<"\n";
		cont++;
		it++;
	}


	cout << "-------------------------------------------------------------------------------------"<<endl;
 	it--;	
	while(it!=X.ibegin() && cont >0){
		cout << cont << " " << (*it).first << " second " << (*it).second << "\n";
		cont--;
		it--;
	}
	/*


			// 	x1				y1				x2			y2
	lista=X.inArea(-87.747777145,41.909605035,-87.670887574,41.726269511);
	//for(iter=lista.begin();iter!=lista.end();iter++)
		//cout << (*iter) << endl;*/
}
