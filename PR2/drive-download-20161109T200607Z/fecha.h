/* 
 * meteorito.h
 * 
 * Copyright  (C) Juan F. Huete
*/
#ifndef __FECHA_H
#define __FECHA_H

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h> 

using namespace std;


//! Clase fecha, asociada a la definicion de una fecha 
/*! fecha::fecha,  .....

 * Métodos--> fecha:: fecha(), toString() 

 * Descripción contiene toda la información asociada a una fecha con el formato  mm/dd/aaaa       * hh:mm:ss AM/PM
 

*/

class fecha {

public:
	/** @brief Constructor primitivo */
 fecha (); //Constructor de fecha por defecto
	/** @brief Constructor que recibe un string
		@param s cadena de caracteres con formato de fecha 
		@prec s es un string con el formato mm/dd/aaaa  hh:mm:ss AM/PM */
 fecha (const string & s); 
   /** @brief Constructor de copia */
 fecha (const fecha& x);
   /** @brief Operador de asignacion fecha = fecha
		 @param f es una fecha */
 fecha & operator=(const fecha & f);
	/** @brief Operador de asignacion fecha = string
		 @param s es un string con formato de fecha
		 @prec s es un string con el formato mm/dd/aaaa  hh:mm:ss AM/PM */
 fecha & operator=(const string & s); 
		/** @brief Da la representacion de la fecha en string
			@return Se devuelve un string con el formato mm/dd/aaaa  hh:mm:ss AM/PM */	
 string toString( ) const; 

// Operadores relacionales
		/** @brief Sobrecarga del operador de comparacion de igualdad entre fechas
			 @param f es una fecha
			 @return true si *this==f, false en otro caso */	
 bool operator==(const fecha & f) const;
		/** @brief Sobrecarga del operador de comparacion de inferioridad entre fechas
			 @param f es una fecha
			 @return true si *this<f es menor, false en otro caso */
 bool operator<(const fecha & f)const;
		/** @brief Sobrecarga del operador de comparacion de superioridad entre fechas
			 @param f es una fecha
			 @return true si *this>f, false en otro caso */
 bool operator>(const fecha & f) const;
		/** @brief Sobrecarga del operador de comparacion de igualdad o inferioridad entre fechas
			 @param f es una fecha
			 @return true si *this<=f, false en otro caso */
 bool operator<=(const fecha & f)const;
		/** @brief Sobrecarga del operador de comparacion de igualdad o superioridad entre fechas
			 @param f es una fecha
			 @return true si *this>=f, false en otro caso */
 bool operator>=(const fecha & f) const;
		/** @brief Sobrecarga del operador de comparacion de desigualdad entre fechas
			 @param f es una fecha
			 @return true si *this!=f, false en otro caso */
 bool operator!=(const fecha & f)const;

private:
  int  sec;   // seconds of minutes from 0 to 61
  int  min;   // minutes of hour from 0 to 59
  int  hour;  // hours of day from 0 to 24
  int  mday;  // day of month from 1 to 31
  int  mon;   // month of year from 0 to 11
  int  year;  // year since 2000

friend  ostream& operator<< ( ostream& os, const fecha & f); 
};

/* @brief imprime fecha con el formato  mm/dd/aaaa hh:mm:ss AM/PM
*/
 ostream& operator<< ( ostream& os, const fecha & f); 

#include "fecha.hxx" // Incluimos la implementacion.


#endif
