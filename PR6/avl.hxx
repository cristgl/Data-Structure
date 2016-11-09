#include "avl.h"

using namespace std;

template <typename T, class comparar >
AVL<T,comparar>::AVL() :el_avl(),tama(0){}

template <typename T, class comparar >
AVL<T,comparar>::AVL(const T & a){
	el_avl(a);
	tama=1;
}

template <typename T, class comparar >
AVL<T,comparar>::AVL(const AVL<T,comparar> & a){
	el_avl=a.el_avl;
	tama=a.tama;
}

template <typename T,class comparar >
AVL<T,comparar> & AVL<T,comparar>::operator=(const AVL<T,comparar> & a){
	if(&a!=this){
		el_avl=a.el_avl;
		tama=a.tama;
	}
	return *this;
}


template <typename T,class comparar>
typename AVL<T,comparar>::altura AVL<T,comparar>::h(const typename bintree<pair<T,altura> >::node & n){
	if(!n.null())
		return (*n).second;
	else
		return -1;
}

template <typename T,class comparar>
typename AVL<T,comparar>::altura AVL<T,comparar>::h(const typename bintree<pair<T,altura> >::const_node & n){
	if(!n.null())
		return (*n).second;
	else
		return -1;
}

template<typename T,class comparar >
typename AVL<T,comparar>::iterator AVL<T,comparar>::begin(){
	AVL<T,comparar>::iterator it;
	it.iter=el_avl.begin_inorder();
	return it;
}

template<typename T,class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::end(){
	AVL<T,comparar>::iterator it;
	it.iter=el_avl.end_inorder();
	return it;
}

template<typename T,class comparar>
typename AVL<T,comparar>::const_iterator AVL<T,comparar>::cbegin() const{
	typename AVL<T,comparar>::const_iterator it;
	typename bintree<pair<T,altura> >::const_inorder_iterator it2;
	it2=el_avl.begin_inorder();
	it.iter=it2;
	return it;
}

template<typename T,class comparar>
typename AVL<T,comparar>::const_iterator AVL<T,comparar>::cend() const{
	typename AVL<T,comparar>::const_iterator it;
	typename bintree<pair<T,altura> >::const_inorder_iterator it2;
	it2=el_avl.end_inorder();
	it.iter=it2;
	return it;
}

template<typename T,class comparar>
typename AVL<T,comparar>::reverse_iterator AVL<T,comparar>::rbegin(){
	AVL<T,comparar>::reverse_iterator it;
	typename bintree<pair<T,altura>>::node n,npadre;
	n=el_avl.root();

  	if (!n.null())
		while(!n.null()){
			npadre=n;
			n=n.right();
		}
	
	typename bintree<pair<T,altura>>::inorder_iterator it2(npadre);

	it.iter=it2;

	return it;
}

template<typename T,class comparar>
typename AVL<T,comparar>::reverse_iterator AVL<T,comparar>::rend(){
	AVL<T,comparar>::reverse_iterator it;
	it.iter=(el_avl.end_inorder());
	return it;
}

template<typename T,class comparar>
typename AVL<T,comparar>::const_reverse_iterator AVL<T,comparar>::crbegin() const{
	AVL<T,comparar>::const_reverse_iterator it;
	typename bintree<pair<T,altura>>::node n,npadre;
	n=el_avl.root();

  	if (!n.null())
		while(!n.null()){
			npadre=n;
			n=n.right();
		}
	
	typename bintree<pair<T,altura>>::const_inorder_iterator it2(npadre);

	it.iter=it2;

	return it;
}

template<typename T,class comparar>
typename AVL<T,comparar>::const_reverse_iterator AVL<T,comparar>::crend() const{
	AVL<T,comparar>::const_reverse_iterator it;
	it.iter=(--el_avl.begin_inorder());
	return it;
}

template<typename T,class comparar>
bool AVL<T,comparar>::empty(){
	return el_avl.size()==0;
}

template<typename T,class comparar>
typename AVL<T,comparar>::size_type AVL<T,comparar>::size(){
	return tama;
}

template<typename T,class comparar>
void AVL<T,comparar>::RSD(typename bintree<pair<T,altura>>::node & n){
		bintree<pair<T,altura>> dest;
		typename bintree<pair<T,altura>>::node n1,npadre,nc;
		bool salir=false;
		el_avl.prune_left(n,dest);
		n1=dest.root();
		bintree<pair<T,altura>> tree,tree2;
		if(n.parent().null())
			tree2=el_avl;
		else{
			tree=el_avl;
			nc=tree.root();
			while(!nc.null() && !salir){
				if((*nc).first==(*n).first){
					if((*nc).first>(*nc.parent()).first)
						tree.prune_right(nc.parent(),tree2);
					else
						tree.prune_left(nc.parent(),tree2);
					salir=true;
				}else if((*nc).first<(*n).first)
					nc=nc.right();
				else
					nc=nc.left();
			}
		}

		//tree.assign_subtree(el_avl,n);
		if(!n1.right().null()){
			bintree<pair<T,altura>> dest1;
			dest.prune_right(n1,dest1);
			el_avl.insert_left(n,dest1);
		}
		
		if(!(n.parent()).null()){
			bintree<pair<T,altura>> dest2;
			npadre=n.parent();
			if((*n.parent()).first<(*n).first){
				el_avl.prune_right(n.parent(),dest2);
				el_avl.insert_right(npadre,dest);
				n1=npadre.right(); 
			}else{
				el_avl.prune_left(n.parent(),dest2);	
				el_avl.insert_left(npadre,dest);	
				n1=npadre.left();
			}
			//el_avl.insert_right(n1,tree);
			el_avl.insert_right(n1,tree2);
		}else{
			if(n.left().null() && n.right().null()){
				el_avl=dest;
				n1=el_avl.root();
				//el_avl.insert_right(n1,tree);
				el_avl.insert_right(n1,tree2);
			}else if (!n.left().null() || !n.right().null()){
				bintree<pair<T,altura>> dest3;
				dest3=el_avl;
				el_avl=dest;
				n1=el_avl.root();
				el_avl.insert_right(n1,dest3);
			}
		}
		(*n1.right()).second=h(n1.right().right())+1;
		while(!n1.null()){
			if(h(n1.right())>h(n1.left()) && h(n1.right())>=h(n1))
				(*n1).second++;
			else if(h(n1.left())>h(n1.right()) && h(n1.left())>=h(n1))
				(*n1).second++;
			n1=n1.parent();
		}	

}

template<typename T,class comparar>
void AVL<T,comparar>::RSI(typename bintree<pair<T,altura>>::node & n){
		bintree<pair<T,altura>> dest;
		typename bintree<pair<T,altura>>::node n1, npadre,nc;
		bool salir=false;
		el_avl.prune_right(n,dest);
		n1=dest.root();
		//tree.assign_subtree(el_avl,n);
		
		if(!n1.left().null()){
			bintree<pair<T,altura>> dest1;
			dest.prune_left(n1,dest1);
			el_avl.insert_right(n,dest1);
		}
		
		bintree<pair<T,altura>> tree,tree2;
		if(n.parent().null())
			tree2=el_avl;
		else{
			tree=el_avl;
			nc=tree.root();
			while(!nc.null() && !salir){
				if((*nc).first==(*n).first){
					if((*nc).first>(*nc.parent()).first)
						tree.prune_right(nc.parent(),tree2);
					else
						tree.prune_left(nc.parent(),tree2);
					salir=true;
				}else if((*nc).first<(*n).first)
					nc=nc.right();
				else
					nc=nc.left();
			}
		}
		
		if(!n.parent().null()){
			bintree<pair<T,altura>> dest2;
			npadre=n.parent();
			if((*n.parent()).first<(*n).first){
				el_avl.prune_right(n.parent(),dest2);
				el_avl.insert_right(npadre,dest);
				n1=npadre.right();
			}else{
				el_avl.prune_left(n.parent(),dest2);		
				el_avl.insert_left(npadre,dest);						
				n1=npadre.left();
			}

			//el_avl.insert_left(n1,tree);
			el_avl.insert_left(n1,tree2);

		}else{
			if(n.left().null() && n.right().null()){
				el_avl=dest;
				n1=el_avl.root();
				//el_avl.insert_left(n1,tree);
				el_avl.insert_left(n1,tree2);
			}else if (!n.left().null() || !n.right().null()){
				bintree<pair<T,altura>> dest3;
				dest3=el_avl;
				el_avl=dest;
				n1=el_avl.root();
				el_avl.insert_left(n1,dest3);
			}
		}
		(*n1.left()).second=h(n1.left().left())+1;
		while(!n1.null()){
			if(h(n1.right())>h(n1.left()) && h(n1.right())>=h(n1))
				(*n1).second++;
			else if(h(n1.left())>h(n1.right()) && h(n1.left())>=h(n1))
				(*n1).second++;
			n1=n1.parent();
		}	
}

template<typename T,class comparar>
pair<typename AVL<T,comparar>::iterator,bool> AVL<T,comparar>::insert(const T & val){
	typename bintree<pair<T,altura>>::node n=el_avl.root();
	bool encontrado=false, sal=false;
	pair<typename AVL<T,comparar>::iterator,bool> salida;
	salida.second=false;
	if(n.null()){
		pair<T,altura> par;
		par=make_pair(val,0);
		bintree<pair<T,altura>> arbol(par);
		el_avl=arbol;
		tama++;
	}else{
		typename bintree<pair<T,altura>>::node copia;
		while(!encontrado){
			if(!cmp((*n).first,val) && !cmp(val,(*n).first)){ // si son iguales
				encontrado=true;
			}else if (cmp((*n).first,val)){ //si n es menor, ir a la derecha
				if(n.right().null())
					encontrado=true;
				else
					n=n.right();
			}else{ // si n es mayor, ir a la izquierda
				if(n.left().null())
					encontrado=true;
				else 
					n=n.left();
			}
		}
		
		if((*n).first!=val){
			if(cmp((*n).first,val)){
				pair<T,altura> par;
				par=make_pair(val,0);
				el_avl.insert_right(n,par);
				typename bintree<pair<T,altura>>::node nodo=n.right();
				typename bintree<pair<T,altura>>::inorder_iterator inorder_it(nodo);
				salida.first.iter=inorder_it;
			}else{
				pair<T,altura> par;
				par=make_pair(val,0);
				el_avl.insert_left(n,par);
				//copia=n;
				typename bintree<pair<T,altura>>::node nodo=n.left();
				typename bintree<pair<T,altura>>::inorder_iterator inorder_it(nodo);
				salida.first.iter=inorder_it;
			}
			copia=n;
			salida.second=true;
			while(!copia.null()){
				if(h(copia.right())>h(copia.left()) && h(copia.right())>=h(copia))
					(*copia).second++;
				else if(h(copia.left())>h(copia.right()) && h(copia.left())>=h(copia))
					(*copia).second++;
				copia=copia.parent();
			}
			tama++;
		}else{
			typename bintree<pair<T,altura>>::inorder_iterator inorder_it(n);
			salida.first.iter=inorder_it;
			salida.second=false;
		}

		// Una vez insertado, pasamos a comprobar el balanceo del árbol desde donde hemos insertado hasta la raíz
		bool salir=false;
		while((!n.right().null() || !n.left().null()) && !salir){
			int dif_alt=h(n.left())-h(n.right());cout << "aqui n es " << (*n).first << endl;
			cout << "altura izq es " << h(n.left()) << " y altura derecha es " << h(n.right()) << " y la dif es " << dif_alt << endl;
			if(dif_alt > 1 || dif_alt < -1){
				if(dif_alt>1 && val < (*n.left()).first){ //left left
					if(!n.left().left().null() && val> (*n.left().left()).first){
						typename bintree<pair<T,altura> >::node ntmp=n.left();
						RSI(ntmp);
						RSD(n);
					}else
						RSD(n);
				}else if(dif_alt<-1 && val> (*n.right()).first){ //right right
					if(!n.right().right().null() && val<(*n.right().right()).first){//right left
						typename bintree<pair<T,altura> >::node ntmp=n.right();
						RSD(ntmp);
						RSI(n);
					}else
						RSI(n);
				}
				else if(dif_alt>1 && val > (*n.left()).first){ //left right
					typename bintree<pair<T,altura> >::node ntmp=n.left();
					RSI(ntmp);
					RSD(n);
				}
				else if(dif_alt<-1 && val < (*n.right()).first){ //right left
					typename bintree<pair<T,altura> >::node ntmp=n.right();
					RSD(ntmp);
					RSI(n);
				}
			}else{//subimos un nodo
				if(!n.parent().null())
					n=n.parent();
				else
					salir=true;
			
			}
		}						
	}
	return salida;
}

template<typename T,class comparar>
void AVL<T,comparar>::erase(AVL<T,comparar>::iterator pos){
	typename bintree<pair<T,altura>>::node n=el_avl.root();
	typename AVL<T,comparar>::iterator iterat;
	bool encontrado = false;
	
	while(!encontrado && !n.null()){
		if((*n).first==*pos)
			encontrado=true;
		else if ((*n).first < *pos)
			n=n.right();
		else
			n=n.left();
	}
		
	if(!n.null()){
		if(n.left().null() && n.right().null()){ // Caso nodo hoja
			bintree<pair<T,altura>> dest;
			if(n.parent().null())
				el_avl.clear();
			else{
				if((*(n.parent())).first<*pos){
					el_avl.prune_right(n.parent(),dest);
					dest.clear();
				}else{
					el_avl.prune_left(n.parent(),dest);
					dest.clear();
				}
			}
		}else if(n.left().null() || n.right().null()){ // Caso 1 hijo
			bintree<pair<T,altura>> dest;
			if(n.left().null()){//el hijo derecha no es nulo
				el_avl.prune_right(n,dest);
				if(n.parent().null())
					el_avl.assign_subtree(dest,dest.root());
				else if((*(n.parent())).first<*pos)
					el_avl.insert_right(n.parent(),dest);
				else
					el_avl.insert_left(n.parent(),dest);
			}else{// el hijo izquierda no es nulo
				el_avl.prune_left(n,dest);
				if(n.parent().null())
					el_avl.assign_subtree(dest,dest.root());
				else if ((*(n.parent())).first<*pos)
					el_avl.insert_left(n.parent(),dest);
				else
					el_avl.insert_right(n.parent(),dest);
			}
		}else{ // Caso 2 hijos
			typename bintree<pair<T,altura>>::node nodo_p; 
			nodo_p=n.parent();
			while(!nodo_p.right().null())
				nodo_p=nodo_p.right();
			
			T valor_p = (*nodo_p).first;
			typename bintree<pair<T,altura>>::node a_borrar=n;
			typename bintree<pair<T,altura>>::inorder_iterator it(nodo_p);
			iterat.iter=it;
			erase(iterat);
			
			(*a_borrar).first=valor_p;
			
		}
	}
	
	//Comprobamos balanceo
	
}

template<typename T,class comparar>
void AVL<T,comparar>::swap(AVL<T,comparar> & x){
	el_avl.swap(x.el_avl);	
}

template<typename T,class comparar>
void AVL<T,comparar>::clear(){
	el_avl.clear();
	tama=0;
}

template<typename T,class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::find(const T & val){
	typename bintree<pair<T,altura>>::node n;
	typename AVL<T,comparar>::iterator sal;
	bool encontrado=false;

	n=el_avl.root();
	while(!encontrado && !n.null()){
		if(!cmp((*n).first,val) && !cmp(val,(*n).first)){
			encontrado=true;
		}else if(cmp((*n).first,val))
			n=n.right();
		else
			n=n.left();
	}
	typename bintree<pair<T,altura>>::inorder_iterator ii(n);
	
	if(!encontrado)
		ii=el_avl.end_inorder();
	
	sal.iter=ii;
	return sal;
}

template<typename T,class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::lower_bound(const T & val){
//lower_bound devuelve el primer valor mayor o igual que el pasado por argumento
	typename bintree<pair<T,altura>>::node n;
	typename AVL<T,comparar>::iterator sal;
	bool encontrado=false;
	
	n=el_avl.root();
	while(!encontrado && !n.null()){
		if((*n).first>=val){
			encontrado=true;
		}else if((*n).first<val)
			n=n.right();
		else
			n=n.left();
	}
	
	typename bintree<pair<T,altura>>::inorder_iterator ii(n);


	if(!encontrado)
		ii=el_avl.end_inorder();
	
	sal.iter=ii;
	return sal;

}

template<typename T,class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::upper_bound(const T & val){
//upper_bound devuelve el primer valor mayor estricto que el pasado por argumento
	typename bintree<pair<T,altura>>::node n;
	typename AVL<T,comparar>::iterator sal;
	bool encontrado=false;
	
	n=el_avl.root();
	while(!encontrado && !n.null()){
		if(!cmp((*n).first,val) && !cmp(val,(*n).first)){
			encontrado=true;
		}else if(cmp((*n).first,val))
			n=n.right();
		else
			n=n.left();
	}
//-----------------------------------------------
  if (!n.right().null()) {
      n = n.right();
      while (!n.left().null())
        n = n.left();
  }
  else {
      while (!n.parent().null() && n.parent().right() == n)
        n = n.parent();
      // Si (padre de elnodo es nodo_nulo), hemos terminado
      // En caso contrario, el siguiente node es el padre
      n = n.parent();
    }
//-----------------------------------------------

	typename bintree<pair<T,altura>>::inorder_iterator ii(n);

	
	if(!encontrado)
		ii=el_avl.end_inorder();
	
	sal.iter=ii;
	return sal;
}
///////////////////////////////////ITERATOR/////////////////////////
template<typename T,class comparar  >
 AVL<T,comparar>::iterator::iterator(){}

template <typename T,class comparar >
 AVL<T,comparar>::iterator::iterator(const AVL<T,comparar>::iterator & it){
	iter=it.iter;
}

template <typename T,class comparar  >
T AVL<T,comparar>::iterator::operator*(){
	return (*iter).first;
}

template <typename T,class comparar >
typename AVL<T,comparar>::iterator & AVL<T,comparar>::iterator::operator++(){
	++iter;
	return *this;
}

template <typename T,class comparar  >
typename AVL<T,comparar>::iterator & AVL<T,comparar>::iterator::operator--(){
	--iter;
	return *this;
}

template <typename T,class comparar  >
bool AVL<T,comparar>::iterator::operator==(const AVL<T,comparar>::iterator & it){
	return iter==it.iter;
}

template <typename T,class comparar  >
bool AVL<T,comparar>::iterator::operator!=(const AVL<T,comparar>::iterator & it){
	return iter!=it.iter;
}

template <typename T,class comparar  >
typename AVL<T,comparar>::iterator & AVL<T,comparar>::iterator::operator=(const AVL<T,comparar>::iterator & it){
	if(this!=&it)	
		iter = it.iter;
	return *this;
}

////////////////////////////////CONST_ITERATOR////////////////////////////////
template<typename T,class comparar  >
AVL<T,comparar>::const_iterator::const_iterator(){}

template <typename T,class comparar>
AVL<T,comparar>::const_iterator::const_iterator(const AVL<T,comparar>::iterator & it){
	iter=it.iter;
}

template <typename T,class comparar >
AVL<T,comparar>::const_iterator::const_iterator(const AVL<T,comparar>::const_iterator & it){
	iter=it.iter;
}

template <typename T,class comparar  >
T AVL<T,comparar>::const_iterator::operator*(){
	return (*iter).first;
}

template <typename T,class comparar  >
typename AVL<T,comparar>::const_iterator & AVL<T,comparar>::const_iterator::operator++(){
	++iter;
	return *this;
}

template <typename T,class comparar  >
typename AVL<T,comparar>::const_iterator & AVL<T,comparar>::const_iterator::operator--(){
	--iter;
	return *this;
}

template <typename T,class comparar  >
bool AVL<T,comparar>::const_iterator::operator==(const AVL<T,comparar>::const_iterator & it){
	return iter==it.iter;
}

template <typename T,class comparar  >
bool AVL<T,comparar>::const_iterator::operator!=(const AVL<T,comparar>::const_iterator & it){
	return iter!=it.iter;
}

template <typename T,class comparar  >
typename AVL<T,comparar>::const_iterator & AVL<T,comparar>::const_iterator::operator=(const AVL<T,comparar>::const_iterator & it){
	if(this!=&it)	
		iter = it.iter;
	return *this;
}


////////////////////////////////REVERSE_ITERATOR////////////////////////////

template<typename T,class comparar  >
AVL<T,comparar>::reverse_iterator::reverse_iterator(){}

template <typename T,class comparar >
AVL<T,comparar>::reverse_iterator::reverse_iterator(const AVL<T,comparar>::reverse_iterator & it){
	iter=it.iter;
}

template <typename T,class comparar  >
T AVL<T,comparar>::reverse_iterator::operator*(){
	return (*iter).first;
}

template <typename T,class comparar  >
typename AVL<T,comparar>::reverse_iterator & AVL<T,comparar>::reverse_iterator::operator++(){
	--iter;
	return *this;
}

template <typename T,class comparar  >
typename AVL<T,comparar>::reverse_iterator & AVL<T,comparar>::reverse_iterator::operator--(){
	++iter;
	return *this;
}

template <typename T,class comparar  >
bool AVL<T,comparar>::reverse_iterator::operator==(const AVL<T,comparar>::reverse_iterator & it){
	return iter==it.iter;
}

template <typename T,class comparar  >
bool AVL<T,comparar>::reverse_iterator::operator!=(const AVL<T,comparar>::reverse_iterator & it){
	return iter!=it.iter;
}

template <typename T,class comparar  >
typename AVL<T,comparar>::reverse_iterator & AVL<T,comparar>::reverse_iterator::operator=(const AVL<T,comparar>::reverse_iterator & it){
	if(this!=&it)	
		iter = it.iter;
	return *this;
}

/////////////////////////CONST_REVERSE_ITERATOR/////////////////////////////
template<typename T,class comparar  >
AVL<T,comparar>::const_reverse_iterator::const_reverse_iterator(){}

template <typename T,class comparar >
AVL<T,comparar>::const_reverse_iterator::const_reverse_iterator(const AVL<T,comparar>::reverse_iterator & it){
	iter=it.iter;
}

template <typename T,class comparar >
AVL<T,comparar>::const_reverse_iterator::const_reverse_iterator(const AVL<T,comparar>::const_reverse_iterator & it){
	iter=it.iter;
}

template <typename T,class comparar  >
T AVL<T,comparar>::const_reverse_iterator::operator*(){
	return (*iter).first;
}

template <typename T,class comparar  >
typename AVL<T,comparar>::const_reverse_iterator & AVL<T,comparar>::const_reverse_iterator::operator++(){
	--iter;
	return *this;
}

template <typename T,class comparar  >
typename AVL<T,comparar>::const_reverse_iterator & AVL<T,comparar>::const_reverse_iterator::operator--(){
	++iter;
	return *this;
}

template <typename T,class comparar  >
bool AVL<T,comparar>::const_reverse_iterator::operator==(const AVL<T,comparar>::const_reverse_iterator & it){
	return iter==it.iter;
}

template <typename T,class comparar  >
bool AVL<T,comparar>::const_reverse_iterator::operator!=(const AVL<T,comparar>::const_reverse_iterator & it){
	return iter!=it.iter;
}

template <typename T,class comparar  >
typename AVL<T,comparar>::const_reverse_iterator & AVL<T,comparar>::const_reverse_iterator::operator=(const AVL<T,comparar>::const_reverse_iterator & it){
	if(this!=&it)	
		iter = it.iter;
	return *this;
}


