/*! Implementacion  de la clase conjunto

*/

include "conjunto.h"
using namespace std;

conjunto::conjunto(){
  vc(0);
}

conjunto::iterator conjunto::begin() const{
conjunto::iterator sal;
	sal.itv = vc.begin();
        return sal;
}


conjunto::iterator conjunto::end() const{
conjunto::iterator sal;
	sal.itv = vc.end();
        return sal;
}
/** @brief constructor defecto iterator
*/
conjunto::iterator::iterator(){
    itv=vc.begin();                           
}

/** @brief constructor copia iterator
*/
conjunto::iterator::iterator(const conjunto::iterator & i){
  itv = i.itv;
}



//arrest iterator//////////////////////////////////////////////////////////////////////////////////////

/** @brief Método de inicialización de iterador. */
conjunto::arrest_iterator conjunto::abegin() const{
    arrest_iterator sal;
    vector<entrada>::iterator iter;
    bool primer=false;
    
    for(iter=vc.begin(); iter!=vc.end() && !primer; iter++)
       if((*iter).getArrest()==true){
          sal=iter;
          primer=true;
       }
       
    return sal;                         
}
/** @brief Método que devuelve un iterador que apunta al final del conjunto. */
conjunto::arrest_iterator conjunto::aend() const{
    conjunto::arrest_iterator sal;
    sal.itv=vc.end();
    return sal;
}

/** @brief Constructor por defecto del iterador. */
conjunto::arrest_iterator::arrest_iterator(){
    
}
/** @brief Constructor de copia.
	 @param[in] ai iterador de arresto */
conjunto::arrest_iterator::arrest_iterator(const conjunto::arrest_iterator &ai){
    itv = ai.itv;
}

/** @brief Operador * para acceder al contenido del iterador. */
const conjunto::entrada &operator*() const{
    return *itv;     
}

/** @brief Operador ++ para el postincremento del iterador. */
arrest_iterator conjunto::arrest_iterator::operator++(int){
    conjunto::arrest_iterator dev;
    dev = itv;
    ++itv; 
    return dev;   
} 
/** @brief Operador ++ para el preincremento del iterador. */
arrest_iterator & conjunto::arrest_iterator::operator++(){
    itv++;
    return itv;
}

/** @brief Operador -- para el postdecremento del iterador. */
arrest_iterator conjunto::arrest_iterator::operator--(int){
    conjunto::arrest_iterator dev;
	dev = itv;
	--itv;
	return dev;
}

/** @brief Operador -- para el predecremento del iterador. */
arrest_iterator & conjunto::arrest_iterator::operator--(){
    itv--;
    return itv;
}

/** @brief Operador == que comprueba si dos iteradores son iguales.
    @param[in] it iterador a comparar */
bool conjunto::arrest_iterator::operator==(const arrest_iterator &it){
    return itv==it.itv;
}

/** @brief Operador != que comprueba si dos iteradores son distintos.
	 @param[in] it iterador a comparar*/
bool conjunto::arrest_iterator::operator!=(const arrest_iterator & it){
     return itv!=it.itv;
}






