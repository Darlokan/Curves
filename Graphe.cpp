#include "Graphe.h"

int exp(int i,int n)
{
	int k = 0;
	if(n == 0)
	{
		return 1;
	}
	else if (n == 1)
	{
		return i;
	}
	else if (n == (n/2)*2) 
	{
		k = exp(i,n/2);
		return k*k;
	}
	else
	{
		k = exp(i,n/2);
		return k*k*i;
	}
}

bool Graphe::Belong(int edge,int pt)
{
	return ((edges[edge][0] == pt) || (edges[edge][1] == pt));
}

void Graphe::MakeCycles(int d,int c,int k,int* l,int* tab)
{
	int i = 0;
	int j = 0;
	int a,s = 0;

	int compteur = 0;
	if((c==d)&&(k>1))
	{
		cycles[*l] = new int[nb_edges] ;
		for(i = 0;i<nb_edges;i++)
		{
			cycles[*l][i] = tab[i] ; 
		}
		*l = *l + 1;
	}
	else
	{
		compteur = 0;
		for(i = 0;i<3;i++)
		{
			if( true )
			{
				a = pts[c][i] ;
				if(tab[a] == -2)
				{
					if(edges[a][0] == c)
					{
						s = edges[a][1] ;
					}
					else
					{
						s = edges[a][0] ;
					}

					if(s >= d)
					{
						tab[a] = 2;
						MakeCycles(d,s,k+1,l,tab);
						tab[a] = -2;
						compteur++;
					}
				}
			}
		}
	}
}

void Graphe::CheckCycles()
{
	int i = 0,j = 0,k ;
	while(i<nb_cycles)
	{
		j = i+1;
		while(j<nb_cycles)
		{
			if(Egal(i,j))
			{
				nb_cycles--;
				for(k=0;k<nb_edges;k++)
				{
					cycles[j][k] = cycles[nb_cycles][k];
				}
			}
			else
			{
				j++;
			}
		}
		i++;
	}
}

bool Graphe::Egal(int i,int j)
{
	bool b = true;
	int k = 0;
	while( k<nb_edges && b )
	{
		b = (cycles[i][k] == cycles[j][k]);
		k++;
	}
	return b ;
}

Graphe::Graphe(int n1, int n2,int** P)
{
	int k,i,l;
	int *n, *tab ;
	n = new int;
	*n = 0;
	nb_pts = n1;
	nb_edges = n2;
	pts = new int*[n1] ;
	edges = new int*[n2] ;
	tab = new int[n2];
	
	for(k=0;k<n1;k++)
	{
		pts[k] = new int[3];
		pts[k][0] = P[k][0];
		pts[k][1] = P[k][1];
		pts[k][2] = P[k][2];
	}
	for(k=0;k<n2;k++)
	{
		edges[k] = new int[2];
		tab[k] = -2;
		l = 0;
		for(i=0;i<n1;i++)
		{
			if((pts[i][0] == k)||(pts[i][1] == k)||(pts[i][2] == k))
			{
				edges[k][l] = i ;
				l++;
			}
		}
	}

	cycles = new int*[exp(2,n1)];

	for(i=0;i<n1;i++)
	{
		MakeCycles(i,i,1,n,tab);
	}
	nb_cycles = *n ;
	CheckCycles();
}

int* Graphe::CycleEtoP(int* tab)
{
	int n = nb_edges ;
	int* cyc ;
	int* tab2 = new int[n] ;
	int i,j,m,p0 ;
	bool b = true;
	i = 0;
	m = 0;
	while(i < n)
	{
		tab2[i] = tab[i] ;
		if(tab[i] == 2)
		{
			m++;
			if(b)
			{
				p0 = i;
				b = false ;
			}
		}
		i++;
	}
	cyc = new int[m] ;
	cyc[0] = p0 ;
	for(i=0;i<m;i++)
	{
		b = true ;
		j = 0;
		while(b)
		{
			if( (tab2[j] == 2) && (edges[j][0] == cyc[i]) )
			{
				tab2[j] = -2 ;
				cyc[i+1] = edges[j][1] ;
				b = false ;
			}
			if( (tab2[j] == 2) && (edges[j][1] == cyc[i]) )
			{
				tab2[j] = -2 ;
				cyc[i+1] = edges[j][0] ;
				b = false ;
			}
		}
	}
	return cyc ;
}

void Graphe::ComSeg(int i, int j, int x, int y, ListeS* &L)
{
	L = 0;
	int* tab5 = 0;
	int* tab3 = new int[nb_edges] ;
	int* tab4 = new int[nb_edges*3];
	int k,a,b,n = (nb_edges*3)/2, m = (nb_edges*3)/2;
	bool b1 = true, b2 = true, b3 = true ;
	for(k=0;k<nb_edges;k++)
	{
		if((cycles[i][k] == 2) && (cycles[j][k] == 2))
		{
			tab3[k] = 2;
		}
		else
		{
			tab3[k] = -2;
		}
	}

	while(b1)
	{
		n = (nb_edges*3)/2; m = (nb_edges*3)/2;
		b1 = false ;
		k = 0;
		while(!b1 && k<nb_edges)
		{
			if(tab3[k] == 2)
			{
				b1 = true;
				tab4[n] = k;
				tab3[k] = -2;
			}
			else
			{
				k++;
			}
		}
		if(b1)
		{
			a = edges[k][0];
			b = edges[k][1];
			
			while(b2)
			{
				b2 = false ;
				for(k=0;k<nb_edges;k++)
				{
					if((tab3[k] == 2) && (edges[k][1] == a) && !b2)
					{
						n--;
						b2 = true;
						tab4[n] = k;
						tab3[k] = -2;
						a = edges[k][0];
					}
					if((tab3[k] == 2) && (edges[k][0] == a) && !b2)
					{
						n--;
						b2 = true;
						tab4[n] = k;
						tab3[k] = -2;
						a = edges[k][1];
					}
				}
			}
			
			while(b3)
			{
				b3 = false ;
				for(k=0;k<nb_edges;k++)
				{
					if((tab3[k] == 2) && (edges[k][1] == b) && !b3)
					{
						m++;
						b3 = true;
						tab4[m] = k;
						tab3[k] = -2;
						b = edges[k][0];
					}
					if((tab3[k] == 2) && (edges[k][0] == b) && !b3)
					{
						m++;
						b3 = true;
						tab4[m] = k;
						tab3[k] = -2;
						b = edges[k][1];
					}
				}

				tab5 = new int[m+1-n];
				for(k=n;k<m+1;k++)
				{
					tab5[k-n] = tab4[k] ;
				}
				
				if(!SegIn(x,y,m+1-n,tab5,L))
				{
					Add(L , new Segment(x,y,m+1-n,tab5));
				}
			}
		}
	}
}

Graphe::Graphe()
{
	int** P;
	P = new int*[4];
	P[0] = new int[3];
	P[1] = new int[3];
	P[2] = new int[3];
	P[3] = new int[3];
	P[0][0] = 0;
	P[0][1] = 1;
	P[0][2] = 2;
	P[1][0] = 0;
	P[1][1] = 3;
	P[1][2] = 4;
	P[2][0] = 1;
	P[2][1] = 4;
	P[2][2] = 5;
	P[3][0] = 2;
	P[3][1] = 5;
	P[3][2] = 3;
	int n1 = 4;
	int n2 = 6;
	int k,i,l;
	int *n, *tab ;
	n = new int;
	*n = 0;
	nb_pts = n1;
	nb_edges = n2;
	pts = new int*[n1] ;
	edges = new int*[n2] ;
	tab = new int[n2];
	
	for(k=0;k<n1;k++)
	{
		pts[k] = new int[3];
		pts[k][0] = P[k][0];
		pts[k][1] = P[k][1];
		pts[k][2] = P[k][2];
	}
	for(k=0;k<n2;k++)
	{
		edges[k] = new int[2];
		tab[k] = -2;
		l = 0;
		for(i=0;i<n1;i++)
		{
			if((pts[i][0] == k)||(pts[i][1] == k)||(pts[i][2] == k))
			{
				edges[k][l] = i ;
				l++;
			}
		}
	}

	cycles = new int*[exp(2,n1)];

	for(i=0;i<n1;i++)
	{
		MakeCycles(i,i,1,n,tab);
	}
	nb_cycles = *n ;
	CheckCycles();
}

void Graphe::Copy(int i, int* &tab)
{
	int k ;
	for(k=0;k<nb_edges;k++)
	{
		tab[k] = cycles[i][k] ;
	}
}

int Graphe::GetNb_Edges()
{
	return nb_edges;
}

bool Graphe::Linked(int i, int j)
{
	return  (Belong(j,edges[i][0]) || Belong(j,edges[i][1]) );
}

int Graphe::Up( int cycle, int a, int a2)
{
	int x,n;
	if(Belong(a2,edges[a][0]))
	{
		x = edges[a][0];
	}
	else
	{
		x = edges[a][1];
	}
	if(pts[x][0] == a)
	{
		n = 0;
	}
	else if(pts[x][1] == a)
	{
		n = 1;
	}
	else
	{
		n = 2;
	}
	if(cycles[cycle][pts[x][(n+1)%3]] == 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Graphe::PrintCycles()
{
	int i,j ;
	cout << "Nb_Cycles : " << nb_cycles << endl ;
	for(i=0;i<nb_cycles;i++)
	{
		cout << "Cycle " << i << endl ;
		for(j=0;j<nb_edges;j++)
		{
			cout << cycles[i][j] << endl ;
		}
	}
}

int Graphe::GetNb_Cycles()
{
	return nb_cycles;
}

void Graphe::PrintNb_Cycles()
{
	cout << nb_cycles << endl;
}
