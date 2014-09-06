#ifndef DEF_SEGMENT
#define DEF_SEGMENT

#include<iostream>

using namespace std ;

class Segment 
{
	int length ; // length of the segment
	int cycle1 ; // the two cycles which the segment belong to
	int cycle2 ;
	int* segP ; // useless
	int* segA ;// array of all edges of the segments 

public :
	Segment();
	Segment(int i,int j, int l, int* seg);
	int Max() ;
	int Nb_Inter(int* c1, int* c2, int start_up, int end_up);// given some information, gives the number of intersection of two curves on this segment
	int StartA();
	int StartA2();
	int EndA2();
	int EndA();
	void Print();
	int GetC1();
	int GetC2();
	bool Egal(int x,int y,int l,int* tab);
};

#endif
