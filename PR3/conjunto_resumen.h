#ifndef __CONJUTO_H
#define __CONJUTO_H
#include <string>
#include <vector>
#include <iostream> 

#include "crimen.h"

using namespace std;

class conjunto
{  
private:
	vector<crimen> vc;
	bool cheq_rep( ) const;
	friend ostream &  operator << ( ostream & sal, const conjunto & D);
	friend class iterator;
	friend class const_iterator;

public:	
	typedef crimen entrada;
	typedef unsigned int size_type;

	conjunto( );
	conjunto (const conjunto & d);

	class iterator;  
  	class const_iterator;
  	class arrest_iterator;
	class const_arrest_iterator;
  	class description_iterator;
 	class const_description_iterator;

	conjunto::iterator  find( const long int & id) const;
	conjunto::const_iterator  find( const long int & id) const;
	conjunto findIUCR( const string & iucr) const;
	conjunto   findDESCR( const string & descr) const;

	bool insert( const conjunto::entrada & e);
	bool erase(const long int & id);
	bool erase(const  conjunto::entrada & e);

	conjunto & operator=( const conjunto & org);
	size_type size() const ;
	bool empty() const;

   iterator begin() const;
   iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;
	arrest_iterator abegin(const bool & arr) const;
	arrest_iterator aend() const;
	const_arrest_iterator cabegin.......................
	description_iterator  dbegin(const string & descr) const;
	description_iterator  dend( ) const;
 	
	class iterator {
       iterator(); //a begin
       iterator (const iterator & it);
       
       const conjunto::entrada & operator*() const;
       
       iterator operator++( int );
       iterator & operator++();
       iterator operator--(int);
       iterator & operator--();
       bool operator==(const iterator & it);
       bool operator!=(const iterator & it);

       private:
           friend class conjunto;
           vector<entrada>::iterator itv;
};

	class const_iterator {
		public:
			const_iterator();
	 		const_iterator(const const_iterator & it);
	  		const_iterator(const iterator & it);
	  		const conjunto::entrada & operator*() const;
	  		const_iterator operator++( int );
	  		const_iterator & operator++();
 	  		const_iterator operator--(int);
     		const_iterator & operator--();
	  		bool operator==(const const_iterator & it);
	  		bool operator!=(const const_iterator & it);
		private:
	  		vector<entrada>::const_iterator c_itv;
	  		friend class conjunto;
	  
	};

	class description_iterator {
	public:
	  description_iterator();
	  description_iterator(const description_iterator & it);
         
	 	const conjunto::entrada & operator*() const;
		description_iterator operator++( int );
		description_iterator & operator++();
		description_iterator operator--(int);
		description_iterator & operator--();
		bool operator==(const description_iterator & it);
		bool operator!=(const description_iterator & it);
	private:
		string descr;// se asigna en dbegin()
		vector<entrada>::iterator c_itv;
		friend class conjunto;
	  
	};
	
	class const_description_iterator{
     public:
	  description_iterator();
	  description_iterator(const description_iterator & it);
         
	 	const conjunto::entrada & operator*() const;
		description_iterator operator++( int );
		description_iterator & operator++();
		description_iterator operator--(int);
		description_iterator & operator--();
		bool operator==(const description_iterator & it);
		bool operator!=(const description_iterator & it);
	private:
		string descr;// se asigna en cdbegin()
		vector<entrada>::iterator c_itv;
		friend class conjunto;
    }
    
    class arrest_iterator{
       public:
          arrest_iterator();
          arrest_iterator(const arrest_iterator &it);
          const conjunto::entrada &operator*() const;
          arrest_iterator operator++(int);
  		  arrest_iterator & operator++();
  		  arrest_iterator operator--(int);
  		  arrest_iterator & operator--();
  		  bool operator==(const arrest_iterator & it);
	      bool operator!=(const arrest_iterator & it);
		private:
	  		vector<entrada>::iterator c_itv;
	  		friend class conjunto;
          
    }


};

ostream &  operator << ( ostream & sal, const conjunto & D);
 

#include "conjunto.hxx"

#endif
