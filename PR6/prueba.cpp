#include "bintree.h"
#include "avl.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main(){

	bintree<int> sd;
	AVL<int,less<int>> tree,tree2;
	typename AVL<int,less<int>>::iterator it,it2;
	
	int val=3,val2=6,val3=7,val4=2,val5=1,val6=4,val7=5,val8=0;

	tree.insert(val);
	tree.insert(val2);
	tree.insert(val3);
	tree.insert(val4);
	tree.insert(val5); 
	tree.insert(val6);
	tree.insert(val7);
	tree.insert(val8);val8=8;
	tree.insert(val8);val8=9;
	tree.insert(val8);val8=10;
	tree.insert(val8);val8=11;
	tree.insert(val8);val8=-1;
	tree.insert(val8);val8=13; 
	tree.insert(val8);val8=17;
	tree.insert(val8);val8=18;
	tree.insert(val8);val8=19;
	tree.insert(val8);
	
	tree.insert(val8);val8=8;
	tree.insert(val8);val8=6;
	tree.insert(val8);val8=4;
	tree.insert(val8);val8=9;
	tree.insert(val8);val8=13;
	tree.insert(val8);val8=2;
	
	it=tree.find(13);
	tree.erase(it);
	
	tree.swap(tree2);

	it=tree.lower_bound(val); 
	it2=tree.upper_bound(val);
	cout << "El lower bound de " << val << " es " << (*it) << " y su upper bound es " << *it2 << endl;
	
	/*	Prueba de operator++ y --, begin y end de iterator
	typename AVL<int,less<int>>::iterator it;
	int ii=0;
	for(it=tree.begin(); ii<10;++it){
		cout << "el iterador es " <<  (*it) << endl;
		ii++;	
	}	
	cout << "------------------------------------------" << endl;
	
	for(it; it!=tree.begin();--it){
		cout << "el iterador es " << (*it) << endl;
	}
	*/
	
	/*	Prueba de operator++ y --, cbegin y cend de const iterator
	typename AVL<int,less<int>>::const_iterator it;
	int ii=0;
	for(it=tree.cbegin(); ii<10;++it){
		cout << "el iterador es " <<  (*it) << endl;
		ii++;	
	}	
	cout << "------------------------------------------" << endl;
	
	for(it; it!=tree.cbegin();--it){
		cout << "el iterador es " << (*it) << endl;
	}
	*/
	
	/*	Prueba de operator++ y --, rbegin y rend de reverse iterator
	typename AVL<int,less<int>>::reverse_iterator it;
	int ii=0;
	for(it=tree.rbegin(); ii<10;++it){
		cout << "el iterador es " <<  (*it) << endl;
		ii++;	
	}	
	cout << "------------------------------------------" << endl;
	
	for(it; it!=tree.rbegin();--it){
		cout << "el iterador es " << (*it) << endl;
	}
	*/
	
	/*	Prueba de operator++ y --, crbegin y crend de const reverse iterator
	typename AVL<int,less<int>>::const_reverse_iterator it;
	int ii=0;
	for(it=tree.crbegin(); ii<10;++it){
		cout << "el iterador es " <<  (*it) << endl;
		ii++;	
	}	
	cout << "------------------------------------------" << endl;
	
	for(it; it!=tree.crbegin();--it){
		cout << "el iterador es " << (*it) << endl;
	}
	*/
}

