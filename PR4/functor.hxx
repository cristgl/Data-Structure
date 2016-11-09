
#include "functor.h"

using namespace std;
bool CrecientePorID::operator()(const crimen &a,const crimen &b) const{
	return (a.getID()<b.getID());
}

bool DecrecientePorID::operator()(const crimen &a,const crimen &b)const{
	return (a.getID()>b.getID());

}
bool CrecientePorFecha::operator()(const crimen &a,const crimen &b)const{
	return (a.getDate()<b.getDate());

}
bool DecrecientePorFecha::operator()(const crimen &a,const crimen &b)const{
	return (a.getDate()>b.getDate());
}
bool CrecientePorIUCR::operator()(const crimen &a,const crimen &b)const{
	return (a.getIUCR()<b.getIUCR());
}

