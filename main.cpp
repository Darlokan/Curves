#include <iostream>
#include "CurveSet.h"
#include <string>
#include <sstream>

using namespace std;

void Rec(bool &b,int k,int l,int nb_cycles,int n,int*T, Graphe* G);

// due to the fact that different versions of the algorithm were computed on this file, 
// some pieces of code are now obsolete, some were only used for debugging too

int main()
{
	cout << "Courbes : " << endl;                           // input, only works for 7 cycles or less
	int* T,*T1,n,i,j,p,m,q = 0 ;
	cin >> m;
	n = m/10000000 ;
	T = new int[n];
	bool b = false;
	for(i=0;i<7;i++)
	{ 
		p = (m - exp(10,7-i)*(m/exp(10,7-i)))/exp(10,6-i);
		for(j=q;j<p+q;j++)
		{
			T[j] = i;
		}
		q=p+q;
	}														// end input
	

	T1 = new int[12];

	int** P;
	P = new int*[4];P[0] = new int[3];P[1] = new int[3];P[2] = new int[3];P[3] = new int[3];
	P[0][0] = 0;P[0][1] = 1;P[0][2] = 2;P[1][0] = 0;P[1][1] = 3;P[1][2] = 4;P[2][0] = 1;
	P[2][1] = 4;P[2][2] = 5;P[3][0] = 2;P[3][1] = 5;P[3][2] = 3;

	int** Q;
	Q = new int*[2];Q[0] = new int[3];Q[1] = new int[3];
	Q[0][0] = 0; Q[0][1] = 1; Q[0][2] = 2;Q[1][0] = 2;Q[1][1] = 1;Q[1][2] = 0;

	int** R;
	R = new int*[4];R[0] = new int[3];R[1] = new int[3];R[2] = new int[3];R[3] = new int[3];
	R[0][0] = 0;R[0][1] = 2;R[0][2] = 3;R[1][0] = 1;R[1][1] = 2;R[1][2] = 3;R[2][0] = 0;
	R[2][1] = 4;R[2][2] = 5;R[3][0] = 1;R[3][1] = 4;R[3][2] = 5;

	Graphe* G = new Graphe(4,6,P);

	Graphe* G2 = new Graphe(2,3,Q);


	CurveSet* C = new CurveSet(T,n,G);

	b = C ->IsSolution();
	int* T4 = new int[9];
	//Rec(b,0,0,3,9,T4,G2);
	cout << b << endl;

    return 0;
}

void Rec(bool &b,int k,int l,int nb_cycles,int nb_curve,int* T,Graphe* G)
{
	bool c;
	CurveSet* C;
	if(k == nb_curve)
	{
		C = new CurveSet(T,nb_curve,G);
		c = C->IsSolution();
		if(c)
		{
			b=true;
		}
	}
	else
	{
		if(l<nb_cycles-1)
		{
			T[k] = l;
			Rec(b,k+1,l,nb_cycles,nb_curve,T,G);
			Rec(b,k,l+1,nb_cycles,nb_curve,T,G);
		}
		else
		{
			T[k] = l;
			Rec(b,k+1,l,nb_cycles,nb_curve,T,G);
		}
	}
}
