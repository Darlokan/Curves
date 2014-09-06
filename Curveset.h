#ifndef CURVESET
#define CURVESET

#include<iostream>
#include "Graphe.h"
#include <ctime>
#include<fstream>
#include <string>
#include <sstream>

using namespace std ;

class CurveSet 
{
	time_t t ;
	bool yo;
	int** tabtype,*nb_type;
	int nb_solution;
	ofstream f;
	double h1,h2;
	double d;
	int t1,t2 ;
	Graphe* G ; // graph of the surface 
	bool solution ;
	ListeSolution *L1, *L2;
	int nb_edges ;
	int nb_cycles;
	int size ; // number of curves
	int* Tab ; // Tab[i] gives the type of curve i
	int** CurveTab ; // Array of all Curves ( Curve == array of length nb_edges integers ( from -2 to 2 ))
	int** InterTab ; // size x size InterTab[i][j] == number of intersections between curve i and j
	ListeS** SegList ; // nb_edges x listS
	ListeC** CurveList ; // nb_edges x ListeC
	ListeS*** SegByCurve ; // curve1 x curve2 x ListeS
	ListeS*** SegLBC; //Liste des segments par arrête et par cycles
	int* EgalTab ;

public :

	void InitV2();
	void InitEgalTab();	// 
	void InitFichier(); // initialization of the file in which the results are written
	CurveSet( int* T , int l) ;
	CurveSet( int* T , int l, Graphe* Gr); // T is data to create CurveTab, l is the length of T, Gr is the graph
	void AddToCurveList( ListeS* S );

	//Première Version
	bool IsSolution() ;
	void RecA(int k); // Recursive function on the edges
	void RecS(ListeS* L,int k); // Recursion on the segment, the edge is fixed (k)
	void RecC(ListeC* L,int k); // Recursion on the curves, the edge is fixed
	
	int TabType(int cycle, int* &T); 

	//Deuxième Version
	bool IsV2();
	void RecCycle(int c);
	void RecEdge(int e,int c);
	void RecSeg(ListeS* L,int e,int c);
	void RecCurve(int e, int c,int i);
	void AddToList(ListeS** &L1,ListeS* L2);

	bool AddSign(int curve, int edge, int value); // gives a number of twists to a curve on an edge
	void DeleteSign(int curve, int edge); // deletes the twists 
	bool Egal(int i,int j); // are two curves the same ?
	void PrintListSeg(ListeS* L); // prints for debugging
	void Print();
	void PrintSegByCurve();
	void PrintInterTab();
	void PrintCurveList();
	void PrintCurveTab();
	void WriteCurveTab(); // writes the results on a file 
	void Write3Curves();
};

#endif
