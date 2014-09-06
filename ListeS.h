#include<iostream>

#include "segment.h"

struct ListeS {
	ListeS* L ;
	Segment* S ;
};

struct ListeC {
	ListeC* L ;
	int c ;
};

struct ListeSolution
{
	ListeSolution* L ;
	int** C ;
};

void Add( ListeS* &Lis, Segment* Seg ); // adds a segment

void AddC (ListeC* &Lis, int cur ); // adds a curve

void AddSol (ListeSolution* &Lis, int** CurveT, int size, int nb_edges); // adds a solution

void PrintListeC (ListeC* L); 

int Nb(int i,int* tab,int l); // gives the numbre of i in an array tab of length l

bool Egal(int** C1, int** C2, int a, int b); // C1 == C2 ? size a x b

bool In(int** C, ListeSolution* L, int a, int b); // Is C in L ?

bool Inclu( ListeSolution* L1, ListeSolution* L2, int a,int b); // Is L1 C L2 ?

bool Repeat( ListeSolution* L,int size,int edge); // Does L countain the same solution twice ?

bool SegIn( int x,int y,int l,int* tab, ListeS* L); // Is the segment define by x,y,l,tab in L ?
