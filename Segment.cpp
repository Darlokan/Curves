#include "segment.h"

Segment::Segment()
{

}

Segment::Segment(int i,int j, int l, int* seg)
{
	cycle1 = i ;
	cycle2 = j ;
	length = l ;
	segA = new int[l] ;
	int k;
	for(k=0;k<l;k++)
	{
		segA[k] = seg[k] ;
	}
}

int Segment::Max()
{
	int k,i = 0;
	for(k=0;k<length;k++)
	{
		if(segA[k] > i)
		{
			i = segA[k] ;
		}
	}
	return i;
}

int Segment::Nb_Inter(int* c1, int* c2,int start_up,int end_up)
{
	//cout << start_up << endl;
	//cout << end_up << endl;
	//system("pause");
	int up = start_up ;
	int c,i = 0, inter = 0;
	for(i=0;i<length;i++)
	{
		c = c1[segA[i]] - c2[segA[i]];
		if( c > 0)
		{
			inter = inter + 1 - up ;
			up = 0 ;
		}
		if(c < 0)
		{
			inter = inter + up ;
			up = 1 ;
		}
	}
	if(up != end_up)
	{
		inter++;
	}
	return inter;
}

int Segment::EndA()
{
	return segA[length - 1];
}

int Segment::EndA2()
{
	return segA[(length - 2)%length];
}

int Segment::StartA2()
{
	return segA[1%length];
}

int Segment::StartA()
{
	return segA[0];
}

int Segment::GetC1()
{
	return cycle1;
}

int Segment::GetC2()
{
	return cycle2;
}

void Segment::Print()
{
	int k;
	cout << "Seg :" << cycle1 << cycle2 << endl ;
	for(k=0;k<length;k++)
	{
		cout << "Arête " << k << ": " << segA[k] << endl ;
	}
	
}

bool Segment::Egal(int x,int y,int l,int* tab)
{
	bool b = true,c = true;
	int i,j;
	if(l == length && (x == cycle1 || x == cycle2) && (y == cycle1 || y == cycle2))
	{
		for(i=0;i<l;i++)
		{
			c = false;
			for(j=0;j<l;j++)
			{
				if(tab[i] == segA[j])
				{
					c = true;
				}
			}
			if(!c)
			{
				b = false;
			}
		}
		return b;
	}
	else
	{
		return false;
	}
}
