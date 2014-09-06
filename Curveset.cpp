#include "CurveSet.h"

using namespace std;

void CurveSet::InitV2()
{
	int i,j,k,l,*T,n;
	SegLBC = new ListeS**[nb_cycles];
	nb_type = new int[nb_cycles];
	tabtype = new int*[nb_cycles];
	for(i=0;i<nb_cycles;i++)
	{
		n = TabType(i,T);
		nb_type[i] = TabType(i,tabtype[i]);
		SegLBC[i] = new ListeS*[nb_edges];
		for(j=0;j<nb_edges;j++)
		{
			SegLBC[i][j] = new ListeS;
			SegLBC[i][j] = 0;
		}
		for(k=0;k<n;k++)
		{
			for(l=0;l<T[k];l++)
			{
				AddToList(SegLBC[i],SegByCurve[T[k]][l]);	
			}
		}
	}
}

void CurveSet::InitEgalTab()
{
	EgalTab = new int[size];
	int i;
	EgalTab[size - 1] = -1;
	for(i=0;i<size-1;i++)
	{
		if(Tab[i] == Tab[i+1])
		{
			EgalTab[i] = size;
		}
		else
		{
			EgalTab[i] = -1;
		}
	}
}

void CurveSet::InitFichier()
{
	int i;
	std::ostringstream oss;
	string str("Courbes'");
	for(i=0;i<G->GetNb_Cycles();i++)
	{
		oss.str("");
		oss.clear();
		oss << Nb(i,Tab,size); 
		str = str + oss.str();
	}
	str = str + "'.txt";
	f.open(str.c_str(),ios::out);
	f << "Résultat pour " << size << " courbes :" << endl;

	for(i=0;i<nb_cycles;i++)
	{
		f << "Courbes de type " << i << " : " << Nb(i,Tab,size) << endl;
	}
}

CurveSet::CurveSet(int *T,int l)
{
	solution = false ;
	size = l;
	G = new Graphe();

	G->PrintCycles();

	nb_edges = G->GetNb_Edges();
	CurveTab = new int*[size];
	InterTab = new int*[size];
	Tab = new int[size];
	int k,i,j;
	SegList = new ListeS*[nb_edges];
	CurveList = new ListeC*[nb_edges];
	SegByCurve = new ListeS**[size];

	for(i=0;i<nb_edges;i++)
	{
		CurveList[i] = new ListeC() ;
		CurveList[i] = 0;
		SegList[i] = new ListeS() ;
		SegList[i] = 0;
	}

	for(k=0;k<size;k++)
	{
		Tab[k] = T[k];
		SegByCurve[k] = new ListeS*[size];
		InterTab[k] = new int [size];
		for(i=0;i<size;i++)
		{
			InterTab[k][i] = 0;
		}
		CurveTab[k] = new int[nb_edges];
		G->Copy(Tab[k],CurveTab[k]);

		for(i=0;i<nb_edges;i++)
		{
			if(CurveTab[k][i] != -2)
			{
				AddC(CurveList[i],k);
			}
		}

		for(i=0;i<k;i++)
		{
			 SegByCurve[i][k] = new ListeS();
			 SegByCurve[k][i] = new ListeS();
			 G->ComSeg(Tab[k],Tab[i],k,i,SegByCurve[k][i]);
			 G->ComSeg(Tab[k],Tab[i],k,i,SegByCurve[i][k]);
		}
		for(j=0;j<k;j++)
		{
			AddToCurveList(SegByCurve[k][j]);
		}
	}
}

CurveSet::CurveSet(int* T,int l, Graphe* Gr)
{
	time(&t);
	L1 = new ListeSolution;
	L2 = new ListeSolution;
	L1 = 0;
	L2 = 0;
	nb_solution = 0;
	t1 = 0;
	t2 = 0;
	solution = false ;
	size = l;
	G = new Graphe();
	G = Gr;

	nb_cycles = G->GetNb_Cycles();
	nb_edges = G->GetNb_Edges();

	CurveTab = new int*[size];
	InterTab = new int*[size];
	Tab = new int[size];
	int k,i,j;
	SegList = new ListeS*[nb_edges];
	CurveList = new ListeC*[nb_edges];
	SegByCurve = new ListeS**[size];

	for(i=0;i<nb_edges;i++)
	{
		CurveList[i] = new ListeC() ;
		CurveList[i] = 0;
		SegList[i] = new ListeS() ;
		SegList[i] = 0;
	}

	for(k=0;k<size;k++)
	{
		Tab[k] = T[k];
		SegByCurve[k] = new ListeS*[size];
		InterTab[k] = new int [size];
		for(i=0;i<size;i++)
		{
			InterTab[k][i] = 0;
		}
		CurveTab[k] = new int[nb_edges];
		G->Copy(Tab[k],CurveTab[k]);

		for(i=0;i<nb_edges;i++)
		{
			if(CurveTab[k][i] != -2)
			{
				AddC(CurveList[i],k);
			}
		}

		for(i=0;i<k;i++)
		{
			 SegByCurve[i][k] = new ListeS();
			 SegByCurve[k][i] = new ListeS();
			 G->ComSeg(Tab[k],Tab[i],k,i,SegByCurve[k][i]);
			 G->ComSeg(Tab[k],Tab[i],k,i,SegByCurve[i][k]);
		}
		for(j=0;j<k;j++)
		{
			AddToCurveList(SegByCurve[k][j]);
		}
	}

	InitFichier();
	InitEgalTab();
	InitV2();
}

void CurveSet::AddToList(ListeS** &L1, ListeS* L)
{
	if(L!=0)
	{
		Add(L1[L->S->Max()],L->S);
		AddToList(L1,L->L);
	}
}

void CurveSet::AddToCurveList( ListeS* S )
{
	if(S != 0)
	{
		Add(SegList[S->S->Max()],S->S);
		AddToCurveList(S->L);
	}
}

bool CurveSet::IsSolution()
{
	solution = false;
	t1 = 0;
	yo = false;
	nb_solution = 0;
	d = 0;
	RecA(0);
	f << "Nombre de Solutions : " << nb_solution << endl;
	if(solution)
	{
		f << "TRUE" << endl;
	}
	else
	{
		f << "FALSE" << endl;
	}

	return solution;
} 

void CurveSet::RecA(int k)
{
	//cout << "RecA" << endl;
	//PrintCurveTab();
	//system("pause");

	bool b = true,c = true,e = true;
	int i,j;
	if(k>=nb_edges)
	{
		for(i=0;i<size;i++)
		{
			for(j=i+1;j<size;j++)
			{
				if(Egal(i,j))
				{
					b = false ;
				}
			}
		}

		if(b)
		{
			if(!solution)
			{
				f << "A SOLUTION WAS FOUND" << endl;
				WriteCurveTab();
			}
			//AddSol(L1,CurveTab,size,nb_edges);
			if(false)//(!In(CurveTab,L2,size,nb_edges)) && !yo)
			{
				yo = true;
				PrintCurveTab();
			}
			solution = true ;
			nb_solution ++;
			//PrintCurveTab();
			//cout << "Inter 2 3 : "<< endl;
			//cout << SegByCurve[2][3]->S->Nb_Inter(CurveTab[2],CurveTab[3],0,0) << endl;
			//cout << SegByCurve[2][3]->S->Nb_Inter(CurveTab[2],CurveTab[3],1,1) << endl;
			//PrintInterTab();
			//system("pause");
		}
	}
	else
	{
		b = false;
		e = false;
		if(k>0)
		{
			for(j=0;j<size;j++)
			{
				if(CurveTab[j][k-1] == -1)
				{
					b = true;
				}
				if(CurveTab[j][k-1] == 0)
				{
					e = true;
				}
				if(!(CurveTab[j][k-1] == -2))
				{
					c = false;
				}
			}
		}
		else
		{
			b = true;
			e = true;
		}

		if(b || c)
		{
			RecS(SegList[k],k);
		}
	}
}

void CurveSet::RecS(ListeS* L,int k)
{
	//cout << "RecS" << endl;
	if(L==0)
	{
		RecC(CurveList[k],k);
	}
	else
	{
		int c1,c2,a,b,a2,b2,inter,up1,up2,v1,v2;
		c1 = L->S->GetC1();
		c2 = L->S->GetC2();
		a = L->S->StartA();
		a2 = L->S->StartA2();
		b = L->S->EndA();
		b2 = L->S->EndA2();
		up1 = G->Up(Tab[c1],a,a2);
		up2 = 1 - G->Up(Tab[c2],b,b2); 
		
		if(CurveTab[c1][k] == 2 && CurveTab[c2][k] == 2)
		{
		for(v1=-1;v1<2;v1++)
		{
		if(AddSign(c1,k,v1))
		{
		for(v2=-1;v2<2;v2++)
		{
		if(AddSign(c2,k,v2))
		{
			if(Tab[c1] == Tab[c2])
			{
				inter = min(L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],0,0),L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],1,1));
			}
			else
			{
				inter = L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],up1,up2);
			}
			
			if(InterTab[c1][c2] + inter < 2)
			{
				InterTab[c1][c2] = InterTab[c1][c2] + inter;
				InterTab[c2][c1] = InterTab[c1][c2];
				RecS(L->L,k);
				InterTab[c1][c2] = InterTab[c1][c2] - inter;
				InterTab[c2][c1] = InterTab[c1][c2];
			}
		}
		DeleteSign(c2,k);
		}
		}
		DeleteSign(c1,k);
		}
		}
		else if(CurveTab[c1][k] == 2)
		{
			for(v1=-1;v1<2;v1++)
			{
			if(AddSign(c1,k,v1))
			{
				if(Tab[c1]==Tab[c2])
			{
				inter = min(L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],0,0),L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],1,1));
			}
			else
			{
				inter = L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],up1,up2);
			}
			
			if(InterTab[c1][c2] + inter < 2)
			{
				InterTab[c1][c2] = InterTab[c1][c2] + inter;
				InterTab[c2][c1] = InterTab[c1][c2];
				RecS(L->L,k);
				InterTab[c1][c2] = InterTab[c1][c2] - inter;
				InterTab[c2][c1] = InterTab[c1][c2];
			}
			}
			DeleteSign(c1,k);
			}
		}
		else if(CurveTab[c2][k] == 2)
		{
			for(v2=-1;v2<2;v2++)
			{
			if(AddSign(c2,k,v2))
			{
				if(Tab[c1]==Tab[c2])
			{
				inter = min(L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],0,0),L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],1,1));
			}
			else
			{
				inter = L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],up1,up2);
			}
			
			if(InterTab[c1][c2] + inter < 2)
			{
				InterTab[c1][c2] = InterTab[c1][c2] + inter;
				InterTab[c2][c1] = InterTab[c1][c2];
				RecS(L->L,k);
				InterTab[c1][c2] = InterTab[c1][c2] - inter;
				InterTab[c2][c1] = InterTab[c1][c2];
			}
			}
			DeleteSign(c2,k);
			}
		}
		else
		{
			if(Tab[c1]==Tab[c2])
			{
				inter = min(L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],0,0),L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],1,1));
			}
			else
			{
				inter = L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],up1,up2);
			}
			
			if(InterTab[c1][c2] + inter < 2)
			{
				InterTab[c1][c2] = InterTab[c1][c2] + inter;
				InterTab[c2][c1] = InterTab[c1][c2];
				RecS(L->L,k);
				InterTab[c1][c2] = InterTab[c1][c2] - inter;
				InterTab[c2][c1] = InterTab[c1][c2];
			}
		}
	}
}

void CurveSet::RecC(ListeC* L, int k)
{
	//cout << "RecC" << endl;
	int value;
	if(L==0)
	{
		RecA(k+1);
	}
	else
	{
		if(CurveTab[L->c][k] == 2 )
		{
			for(value = -1;value < 2;value++)
			{
				if(AddSign(L->c,k,value))
				{
					RecC(L->L,k);
				}
				DeleteSign(L->c,k);
			}
		}
		else
		{
			RecC(L->L,k);
		}
	}
}

bool CurveSet::AddSign(int curve,int edge,int value)
{
	t1++;
	int i, j = value ;
	bool b = true;
	if((edge == 0) && (curve < 3))
	{
		Write3Curves();
	}
	//PrintCurveTab();
	//system("pause");
	if(!((EgalTab[curve] == size) && (value < CurveTab[(curve + 1)%size][edge])))
	{
		if((EgalTab[curve] == size) && (value > CurveTab[(curve + 1)%size][edge]))
		{
			EgalTab[curve] = edge;
		}
		CurveTab[curve][edge] = value;
		if((j == 1) || (j==-1))
		{
			for(i=0;i<size;i++)
			{
				if( ( (j == 1) && (CurveTab[i][edge] == -1) ) || ( (j == -1) && (CurveTab[i][edge] == 1) ) )
				{
					InterTab[i][curve]++;
					InterTab[curve][i]++;
					if (InterTab[i][curve] > 1)
					{
						b = false ;
					}
				}
			}
		}
		return b ;
	}
	else
	{
		return false;
	}
}

void CurveSet::DeleteSign(int curve,int edge)
{
	int value = CurveTab[curve][edge],i;
	CurveTab[curve][edge] = 2;
	if((value == 1) || (value == -1))
	{
		for(i=0;i<size;i++)
		{
			if( ( value == 1 && CurveTab[i][edge] == -1 ) || ( value == -1 && CurveTab[i][edge] == 1 ) )
			{
				InterTab[i][curve]--;
				InterTab[curve][i]--;
			}
		}
	}
	if(EgalTab[curve] == edge)
	{
		EgalTab[curve] = size;
	}
}

bool CurveSet::Egal(int i,int j)
{
	bool b = true;
	int k = 0;
	while( k<nb_edges && b )
	{
		b = (CurveTab[i][k] == CurveTab[j][k]);
		k++;
	}
	return b ;
}

void CurveSet::PrintSegByCurve()
{
	int i,j ;
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			if(i!=j)
			{
				cout << "ComSeg " << i << " " << j << ":" << endl ;
				PrintListSeg(SegByCurve[i][j]);
			}
		}
	}
}

void CurveSet::PrintListSeg(ListeS* L)
{
	if(L!=0)
	{
		L->S->Print();
		PrintListSeg(L->L);
	}
	else
	{
		cout<<"EndPrint"<<endl ;
	}
}	

void CurveSet::Print()
{
	cout << "T1 : " << t1 << endl;
	cout << "Test : " << Repeat(0,0,0) << endl;
	cout << "Repeat V2 : " << Repeat(L2,size,nb_edges) << endl;
	cout << "Repeat V1 : " << Repeat(L1,size,nb_edges) << endl;
	cout << "V1 < V2 : " << Inclu(L1,L2,size,nb_edges) << endl;
	cout << "V2 < V1 : " << Inclu(L2,L1,size,nb_edges) << endl;	
}

void CurveSet::PrintInterTab()
{
	int i,j ;
	cout << "InterTab : " << endl;
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{

			cout << "inter " << i << " " << j << " : " << InterTab[i][j] << endl ;
		}
	}
	cout << "end" << endl;
}

void CurveSet::PrintCurveList()
{
	int i;
	for(i=0;i<nb_edges;i++)
	{
		cout << "CurveList[" << i << "] : " << endl ;
		PrintListeC(CurveList[i]);
	}
}

void CurveSet::PrintCurveTab()
{
	int i, k;
	for(k=0;k<size;k++)
	{
		cout << "Courbe : " << k << endl ;
		for(i=0;i<nb_edges;i++)
		{
			cout << CurveTab[k][i] << endl ;
		}
	}
}

void CurveSet::WriteCurveTab()
{
	int i, k;
	for(k=0;k<size;k++)
	{
		f << "Courbe : " << k << endl ;
		for(i=0;i<nb_edges;i++)
		{
			f << CurveTab[k][i] << endl ;
		}
	}
}

void CurveSet::Write3Curves()
{
	time_t timer;
	time(&timer);
	f << "					Time : " << difftime(timer,t) << endl;
	if(size >3)
	{
		int i, k;
		for(k=0;k<3;k++)
		{
			f << "Courbe " << k << " : " << CurveTab[k][0] << endl ;
		}
	}
}

int CurveSet::TabType(int i,int* &T)
{
	int l=0,k,n = Nb(i,Tab,size);
	T = new int[n];
	for(k=0;k<size;k++)
	{
		if(Tab[k] == i)
		{
			T[l] = k;
			l++;
		}
	}
	return n;
}

void CurveSet::RecCycle(int c)
{
	//cout << "RecCycle : " << c << endl;
	bool b = true;

	if(c>0)
	{
		int i,j;
		for(i=0;i<tabtype[c-1][nb_type[c-1]-1];i++)
		{
			for(j=i+1;j<size;j++)
			{
				if(Egal(i,j))
				{
					b = false ;
				}
			}
		}
	}
	if(b && (c == nb_cycles))
	{
		if(!solution)
		{
			WriteCurveTab();
		}
		AddSol(L2,CurveTab,size,nb_edges);
		solution = true ;
		nb_solution ++;
	}
	else if(b)
	{
		if(nb_type[c] > 0)
		{
			RecEdge(0,c);
		}
		else
		{
			RecCycle(c+1);
		}
	}
}

void CurveSet::RecEdge(int e,int c)
{
	//if(c>0){cout << "RecEdge : " << e << " " << c << endl;}
	if(e == nb_edges)
	{
		RecCycle(c+1);
	}
	else
	{
		if(CurveTab[tabtype[c][0]][e] != -2)
		{
			RecSeg(SegLBC[c][e],e,c);
		}
		else
		{
			RecEdge(e+1,c);
		}
	}
}

void CurveSet::RecSeg(ListeS* L,int e,int c)
{
	//if(c>0){cout << "RecSeg : " << e << " " << c << endl;
	//		PrintCurveTab(); system("pause");}
	if(L == 0)
	{
		RecCurve(e,c,nb_type[c] - 1);
	}
	else
	{
		int c1,c2,a,b,a2,b2,inter,up1,up2,v1,v2,k;
		k=e;
		c1 = L->S->GetC1();
		c2 = L->S->GetC2();
		a = L->S->StartA();
		a2 = L->S->StartA2();
		b = L->S->EndA();
		b2 = L->S->EndA2();
		up1 = G->Up(Tab[c1],a,a2);
		up2 = 1 - G->Up(Tab[c2],b,b2); 
		
		if(CurveTab[c1][k] == 2 && CurveTab[c2][k] == 2)
		{
		for(v1=-1;v1<2;v1++)
		{
		if(AddSign(c1,k,v1))
		{
		for(v2=-1;v2<2;v2++)
		{
		if(AddSign(c2,k,v2))
		{
			if(G->Linked(a,b) && (a!=b) && (b!=a2))
			{
				inter = min(L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],0,0),L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],1,1));
			}
			else
			{
				inter = L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],up1,up2);
			}
			
			if(InterTab[c1][c2] + inter < 2)
			{
				InterTab[c1][c2] = InterTab[c1][c2] + inter;
				InterTab[c2][c1] = InterTab[c1][c2];
				RecSeg(L->L,k,c);
				InterTab[c1][c2] = InterTab[c1][c2] - inter;
				InterTab[c2][c1] = InterTab[c1][c2];
			}
		}
		DeleteSign(c2,k);
		}
		}
		DeleteSign(c1,k);
		}
		}
		else if(CurveTab[c1][k] == 2)
		{
			for(v1=-1;v1<2;v1++)
			{
			if(AddSign(c1,k,v1))
			{
				if(G->Linked(a,b) && (a!=b) && (b!=a2))
			{
				//cout << "Linked" << endl;
				//system("pause");
				inter = min(L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],0,0),L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],1,1));
			}
			else
			{
				inter = L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],up1,up2);
			}
			
			if(InterTab[c1][c2] + inter < 2)
			{
				InterTab[c1][c2] = InterTab[c1][c2] + inter;
				InterTab[c2][c1] = InterTab[c1][c2];
				RecSeg(L->L,k,c);
				InterTab[c1][c2] = InterTab[c1][c2] - inter;
				InterTab[c2][c1] = InterTab[c1][c2];
			}
			}
			DeleteSign(c1,k);
			}
		}
		else if(CurveTab[c2][k] == 2)
		{
			for(v2=-1;v2<2;v2++)
			{
			if(AddSign(c2,k,v2))
			{
				if(G->Linked(a,b) && (a!=b) && (b!=a2))
			{
				inter = min(L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],0,0),L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],1,1));
			}
			else
			{
				inter = L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],up1,up2);
			}
			
			if(InterTab[c1][c2] + inter < 2)
			{
				InterTab[c1][c2] = InterTab[c1][c2] + inter;
				InterTab[c2][c1] = InterTab[c1][c2];
				RecSeg(L->L,k,c);
				InterTab[c1][c2] = InterTab[c1][c2] - inter;
				InterTab[c2][c1] = InterTab[c1][c2];
			}
			}
			DeleteSign(c2,k);
			}
		}
		else
		{
			if(G->Linked(a,b) && (a!=b) && (b!=a2))
			{
				inter = min(L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],0,0),L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],1,1));
			}
			else
			{
				inter = L->S->Nb_Inter(CurveTab[c1],CurveTab[c2],up1,up2);
			}
			
			if(InterTab[c1][c2] + inter < 2)
			{
				InterTab[c1][c2] = InterTab[c1][c2] + inter;
				InterTab[c2][c1] = InterTab[c1][c2];
				RecSeg(L->L,e,c);
				InterTab[c1][c2] = InterTab[c1][c2] - inter;
				InterTab[c2][c1] = InterTab[c1][c2];
			}
		}
	}
}

void CurveSet::RecCurve(int e,int c,int i)
{
	//if(c>0){cout << "RecCurve : " << e << " " << c << " " << i << endl;
	//		PrintCurveTab(); system("pause");}
	if(i<0)
	{
		RecEdge(e+1,c);
	}
	else
	{
		int value;
		int j = tabtype[c][i];
		if(CurveTab[j][e] == 2 )
		{
			for(value = -1;value < 2;value++)
			{
				if(AddSign(j,e,value))
				{
					RecCurve(e,c,i-1);
				}
				DeleteSign(j,e);
			}
		}
		else
		{
			RecCurve(e,c,i-1);
		}
	}
}

bool CurveSet::IsV2()
{
	t1 = 0;
	nb_solution = 0;
	d=0;
	RecCycle(0);
	f << "Nombre de Solutions : " << nb_solution << endl;
	if(solution)
	{
		f << "TRUE" << endl;
	}
	else
	{
		f << "FALSE" << endl;
	}
	return solution;
}
