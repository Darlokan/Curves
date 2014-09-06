#include "ListeS.h"

void Add ( ListeS* &Lis, Segment* Seg )
{
	ListeS* L2 = new ListeS ;
	L2->L = new ListeS ;
	L2->L = Lis ;
	Lis = new ListeS ;
	L2->S = Seg ;
	Lis = L2 ;
}

void AddC (ListeC* &Lis, int cur )
{
	ListeC* L2 = new ListeC ;
	L2->L = new ListeC ;
	L2->L = Lis ;
	Lis = new ListeC ;
	L2->c = cur ;
	Lis = L2 ;
}

void PrintListeC (ListeC* L)
{
	if(L!=0)
	{
		cout << L->c << endl;
		PrintListeC(L->L);
	}
}

int Nb(int i,int* tab,int length)
{
	int k = 0,j;
	for(j=0;j<length;j++)
	{
		if(tab[j] == i)
		{
			k++;
		}
	}
	return k;
}

void AddSol( ListeSolution* &L1, int** CurveT, int size,int nb_edges)
{
	int i,j ;
	ListeSolution* L2 = new ListeSolution ;
	L2->L = new ListeSolution ;
	L2->L = L1 ;
	L1 = new ListeSolution ;
	L1 = L2 ;
	L1->C = new int*[size];
	for(i=0;i<size;i++)
	{
		L1->C[i] = new int[nb_edges];
		for(j=0;j<nb_edges;j++)
		{
			L1->C[i][j] = CurveT[i][j];
		}
	}
}

bool Egal( int** C1, int** C2,int size,int nb_edges)
{
	bool b = true;
	int i,j ;
	for(i=0;i<size;i++)
	{
		for(j=0;j<nb_edges;j++)
		{
			if(C1[i][j] != C2[i][j])
			{
				b = false;
			}
		}
	}
	return b;
}

bool In( int** C, ListeSolution* L, int size, int edge)
{
	if(L == 0)
	{
		return false;
	}
	else if(Egal(C,L->C,size,edge))
	{
		return true;
	}
	else 
	{
		return In(C,L->L,size,edge);
	}
}

bool Inclu( ListeSolution* L1, ListeSolution* L2, int a, int b)
{
	if(L1 == 0)
	{
		return true;
	}
	else if(In(L1->C,L2,a,b))
	{
		return Inclu(L1->L,L2,a,b);
	}
	else
	{
		return false;
	}
}

bool Repeat(ListeSolution* L,int a,int b)
{
	if(L==0)
	{
		return true;
	}
	else if(In(L->C,L->L,a,b))
	{
		return false;
	}
	else
	{
		return Repeat(L->L,a,b);
	}
}

bool SegIn(int x,int y,int l,int* tab,ListeS* L)
{
	if(L==0)
	{
		return false;
	}
	else if(L->S->Egal(x,y,l,tab))
	{
		return true;
	}
	else
	{
		return SegIn(x,y,l,tab,L->L);
	}
}
