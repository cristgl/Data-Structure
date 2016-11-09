#ifndef __CSS_H
#define __CSS_H

#include <string>
#include <vector>
#include <iostream> 
#include <map>
#include <unordered_map>
#include <set>
#include <list>

#include "fecha.h"
#include "crimen.h"

using namespace std;

class CSS{
	public:
		typedef float Longitud;
		typedef float Latitud;
		typedef unsigned int ID;
		typedef string Termino;
		typedef string IUCR;
		typedef fecha Date;
		typedef crimen Crimen;
		class iterator;
		class IUCR_iterator;
		class Date_iterator;
		class cmp;

		CSS();
		CSS(const CSS & css);
		void load(string nombreDB);
		void insert( const crimen & x);
		void erase( unsigned int ID);
		iterator find_ID(const unsigned int ID);
		void setArrest(const unsigned int ID, bool value);
		vector<pair<ID,float>> Query(list<string> & q, int k);    
		list<ID> inArea(Longitud x1, Latitud y1, Longitud x2, Latitud y2 );
		/* Métodos relacionados con los iteradores */
		IUCR_iterator ibegin();
		IUCR_iterator iend();
		IUCR_iterator lower_bound(IUCR);
		IUCR_iterator upper_bound(IUCR);
		Date_iterator dbegin();
		Date_iterator dend();
		Date_iterator lower_bound(Date d);
		Date_iterator upper_bound(Date d);
		iterator begin();
		iterator end();
		class iterator{
			public: 

				/** @brief Constructor por defecto del iterador. */
				 iterator();
				/** @brief Constructor de copia.
			 		@param[in] iter   */
			   iterator (const iterator & iter);
			   /** @brief Operador * para acceder al contenido del iterador. */
				pair<const ID, Crimen > & operator*(); 
			   /** @brief Operador ++ para el postincremento del iterador. */
			   iterator operator++( int );
			 /** @brief Operador ++ para el preincremento. */
			   iterator & operator++();
				 /** @brief Operador -- para el postdecremento del iterador. */
			   iterator operator--(int);
			/** @brief Operador -- para el predecremento del iterador. */
			   iterator & operator--();
			   /** @brief Operador == que comprueba si dos iteradores son iguales.
				 @param[in] iter iterador a comparar */
			   bool operator==(const iterator & iter);
			   /** @brief Operador != que comprueba si dos iteradores son distintos.
				  @param[in] iter iterador a comparar*/
			   bool operator!=(const iterator & iter);
			 /** @brief Operador de asignacion
				 @param[in] iter iterador a asignar */
				 iterator& operator=(const iterator & iter);
			private:
				/* @brief it itera sobre los ID del map */
				map<ID,Crimen>::iterator it;
				friend class CSS;
	};
		
		class IUCR_iterator{
			public:
				/** @brief Constructor por defecto del iterador. */
				 IUCR_iterator();
				/** @brief Constructor de copia.
			 		@param[in] iter   */
			   IUCR_iterator (const IUCR_iterator & iter);
			   /** @brief Operador * para acceder al contenido del iterador. */
				pair<const ID, Crimen > & operator*(); 
			   /** @brief Operador ++ para el postincremento del iterador. */
			   IUCR_iterator operator++( int );
			 /** @brief Operador ++ para el preincremento. */
			   IUCR_iterator & operator++();
				 /** @brief Operador -- para el postdecremento del iterador. */
			   IUCR_iterator operator--(int);
			/** @brief Operador -- para el predecremento del iterador. */
			   IUCR_iterator & operator--();
			   /** @brief Operador == que comprueba si dos iteradores son iguales.
				 @param[in] iter iterador a comparar */
			   bool operator==(const IUCR_iterator & iter);
			   /** @brief Operador != que comprueba si dos iteradores son distintos.
				  @param[in] iter iterador a comparar*/
			   bool operator!=(const IUCR_iterator & iter);
			 /** @brief Operador de asignacion
				 @param[in] iter iterador a asignar */
				 IUCR_iterator& operator=(const IUCR_iterator & iter);
			private:
				/* @brief it_m itera sobre los IUCR del map */
				map<IUCR,set<ID>>::iterator it_m; 
				/* @brief it_s itera sobre los ID */
				set<ID>::iterator it_s;
				CSS *miCSS;
				friend class CSS;
		};
		
		class Date_iterator{
			public:
				/** @brief Constructor por defecto del iterador. */
				 Date_iterator();
				/** @brief Constructor de copia.
			 		@param[in] it   */
			   Date_iterator (const Date_iterator & it);
			   /** @brief Operador * para acceder al contenido del iterador. */
				pair<const ID, Crimen > & operator*(); 
			   /** @brief Operador ++ para el postincremento del iterador. */
			   Date_iterator operator++( int );
			 /** @brief Operador ++ para el preincremento. */
			   Date_iterator & operator++();
				 /** @brief Operador -- para el postdecremento del iterador. */
			   Date_iterator operator--(int);
			/** @brief Operador -- para el predecremento del iterador. */
			   Date_iterator & operator--();
			   /** @brief Operador == que comprueba si dos iteradores son iguales.
				 @param[in] it iterador a comparar */
			   bool operator==(const Date_iterator & it);
			   /** @brief Operador != que comprueba si dos iteradores son distintos.
				  @param[in] it iterador a comparar*/
			   bool operator!=(const Date_iterator & it);
			 /** @brief Operador de asignacion
				 @param[in] it iterador a asignar */
				 Date_iterator& operator=(const Date_iterator & it);
			private:
				/* @brief it_mm itera sobre las fechas del multimap */
				multimap<Date, map<ID,Crimen>::iterator>::iterator it_mm;
				friend class CSS;
		};
		
		class cmp{
			public:
				bool operator()(const pair<CSS::ID,float> & p1, const pair<CSS::ID,float> & p2);
		};
	private:
		map<ID,Crimen> baseDatos; 
		multimap<Date, map<ID,Crimen>::iterator> DateAccess;
		map<IUCR,set<ID>> IUCRAccess;
		unordered_map<Termino, set<ID>> index;
		map<Longitud,multimap<Latitud, ID>> posicionGeo;
		map<ID,float> unionPeso(const set<ID> & t1, const set<ID> &t2);
		void unionPeso(map<ID,float> & m, set<ID> & t_i);
		friend class IUCR_iterator;
		friend class Date_iterator;
		friend class iterator;
		friend class cmp;
		
};

	bool to_bool(const string& str);
	
	#include "CSS.hxx"
	#endif
