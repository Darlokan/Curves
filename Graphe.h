#ifndef DEF_GRAPHE
#define DEF_GRAPHE

#include<iostream>
#include "ListeS.h"

using namespace std ;

// pts stand for vertices
// vertices are given a number from 0 to nb_pts - 1
// the same goes for edges (from 0 to nb_edges)
// pts is a matrix of size nb_pts x 3, line n gives the three edges which vertice n belong to, ordered clockwise
// edges is a matrix of size nb_edges x 2, line n gives the 2 vertices of egde n
// cycles is a matrix of size 2^nb_pts x nb_edges, each of the lines below nb_cycles give a cycle 
// a cycle is implemented as an array of nb_edges integers : cycle[n] = 2 if the cycle goes through the edge n, else cycle[n] = -2
// nb_cycles is the number of cycles that can be drawn in the graph

class Graphe 
{
	int nb_edges ;
	int nb_pts ;
	int nb_cycles ;
	int** pts ;
	int** edges ;
	int** cycles ;

public :
	void MakeCycles(int d, int c, int k, int* l, int* tab) ;
	void CheckCycles() ;
	Graphe(int n1,int n2,int** P);//n1 = nb_pts, n2 = nb_edges, P = pts, calculates edges, cycles and nb_cycles
	Graphe();
	int* CycleEtoP(int* tab); //useless 
	void ComSeg( int i, int j, int x, int y, ListeS* &L); //adds all common segments of cycles i and j to L, x and y are informations necessary to create the segments
	void Copy(int i, int* &tab);// copy cycle[i] onto tab
	int GetNb_Edges();
	bool Belong(int edge,int pt);
	void PrintCycles();
	bool Linked(int i, int j);// do edge i and j have a common vertice ?
	int Up( int cycle, int a, int a2);// useful information to determine the number of intersections of curves
	void PrintNb_Cycles();
	int GetNb_Cycles();
	bool Egal(int i,int j);// cycle[i] == cycle[j] (only useful during the initialization, after that all cycles are dinstinct)
};

#endif

int exp(int i,int n);

