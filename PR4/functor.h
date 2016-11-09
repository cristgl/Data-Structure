#ifndef __FUNCTOR_H
#define __FUNCTOR_H
#include "crimen.h"
#include "fecha.h"
using namespace std;

class CrecientePorID{
	public:
		bool operator()(const crimen &a,const crimen &b)const;
};

class DecrecientePorID{
	public:
		bool operator()(const crimen &a,const crimen &b)const;
};

class CrecientePorFecha{
	public:
		bool operator()(const crimen &a,const crimen &b)const;
};

class DecrecientePorFecha{
	public:
		bool operator()(const crimen &a,const crimen &b)const;
};

class CrecientePorIUCR{
	public:
		bool operator()(const crimen &a,const crimen &b)const;
};

#include "functor.hxx"

#endif
