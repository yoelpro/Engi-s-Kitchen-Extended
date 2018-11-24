#include "boolean.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

boolean IsEmpty (Queue Q)
{
	return (Head(Q)==Nol && Tail(Q)==Nol);
}

boolean IsFull (Queue Q)
{
	return NBElmt(Q)==MaxElQ(Q);
}

int NBElmt (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
	if (IsEmpty(Q))
	{
		return 0;
	}
	else
	{
		return ((Tail(Q)-Head(Q)+MaxElQ(Q))%MaxElQ(Q))+1;
	}
}

/* *** Kreator *** */
void CreateEmpty (Queue * Q, int Max)
{
	(*Q).T = (infotype*) malloc ((Max+1)* sizeof(infotype));
	if ((*Q).T!= NULL)
	{
		MaxElQ(*Q) = Max;
		Head(*Q) = Nol;
		Tail(*Q) = Nol;
	}
	else
	{
		MaxElQ(*Q) = 0;
	}
}

/* *** Destruktor *** */
void DeAlokasi(Queue * Q)
{
	MaxElQ(*Q)=0;
	free((*Q).T);
}

/* *** Primitif Add/Delete *** */
void Add (Queue * Q, infotype X)
{
	if (IsEmpty(*Q))
	{
		Head(*Q)=1;
	}
	Tail(*Q)= (Tail(*Q) % MaxElQ(*Q)) + 1;
	InfoTail(*Q)=X;
}

void Del (Queue * Q, infotype * X)
{
	*X = InfoHead(*Q);
	if (NBElmt(*Q)==1)
	{
		Head(*Q)=Nol;
		Tail(*Q)=Nol;
	}
	else
	{
		Head(*Q) = (Head(*Q) % MaxElQ(*Q)) + 1;
	}
}

boolean IsEmptyQC (TypeQueueCustomer QC)
{
	return (Head(QC)==Nol && Tail(QC)==Nol);
}

boolean IsFullQC (TypeQueueCustomer QC)
{
	return ((Tail(QC)-Head(QC)+1)==MaxElQC);
}

int NBElmtQC (TypeQueueCustomer QC)
{
	return Tail(QC)-Head(QC)+1;
}

/* *** Kreator *** */
void CreateEmptyQC(TypeQueueCustomer* QC)
{
		Head(*QC) = Nol;
		Tail(*QC) = Nol;
}

/* *** Primitif Add/Delete *** */
void MoveDataCustomer(TypeQueueCustomer* QC, int from, int to)
{
	(*QC).Customer[to].Id = (*QC).Customer[from].Id;
	(*QC).Customer[to].NoMeja = (*QC).Customer[from].NoMeja;
	(*QC).Customer[to].Kesabaran = (*QC).Customer[from].Kesabaran;
	(*QC).Customer[to].JmlOrang = (*QC).Customer[from].JmlOrang;
	(*QC).Customer[to].Star = (*QC).Customer[from].Star;
}

void AddCustomerWC (TypeQueueCustomer* QC, int id, int kesabaran, int Orang, boolean IsStar)
{
	if (IsEmptyQC(*QC))
	{
		Head(*QC)++;
	}
	if (!IsStar)
	{
		(*QC).Customer[Tail(*QC) + 1].Id = id;
		(*QC).Customer[Tail(*QC) + 1].NoMeja = 0;
		(*QC).Customer[Tail(*QC) + 1].Kesabaran = kesabaran;
		(*QC).Customer[Tail(*QC) + 1].JmlOrang = Orang;
		(*QC).Customer[Tail(*QC) + 1].Star = IsStar; /* true jika dia star */
	}
	else
	{
		int idx = Tail(*QC);
		if (!IsEmptyQC(*QC))
		{
			while (idx>1 && (!(*QC).Customer[idx].Star))
			{
				MoveDataCustomer(QC,idx,idx+1);
				idx--;
			}
			if ((*QC).Customer[idx].Star)
			{
				(*QC).Customer[idx+1].Id = id;
				(*QC).Customer[idx+1].NoMeja = 0;
				(*QC).Customer[idx+1].Kesabaran = kesabaran;
				(*QC).Customer[idx+1].JmlOrang = Orang;
				(*QC).Customer[idx+1].Star = IsStar;
			}
			else
			{
				(*QC).Customer[idx].Id = id;
				(*QC).Customer[idx].NoMeja = 0;
				(*QC).Customer[idx].Kesabaran = kesabaran;
				(*QC).Customer[idx].JmlOrang = Orang;
				(*QC).Customer[idx].Star = IsStar;
			}
		}
		else
		{
			(*QC).Customer[1].Id = id;
			(*QC).Customer[1].NoMeja = 0;
			(*QC).Customer[1].Kesabaran = kesabaran;
			(*QC).Customer[1].JmlOrang = Orang;
			(*QC).Customer[1].Star = IsStar;
		}

	}
	Tail(*QC)++;
}


void DelCustomerQC (TypeQueueCustomer* QC, int id)
{
	int i = Head(*QC);
	while ((*QC).Customer[i].Id!=id && i<Tail(*QC))
	{
		i++;
	}
	if ((*QC).Customer[i].Id==id)
	{
		for(i=i; i<Tail(*QC); i++)
		{
			MoveDataCustomer(QC, i+1, i);
		}
		Tail(*QC)--;
	}
	if (Tail(*QC)==0)
	{
		Head(*QC)=0;
	}
}

void CleanQC(TypeQueueCustomer *QC)
{
	int idx;
	for(idx = Head(*QC); idx<=Tail(*QC); idx++)
	{
		if ((*QC).Customer[idx].Kesabaran==0)
		{
			DelCustomerQC(QC,(*QC).Customer[idx].Id);
			// printf("aa\n");
			idx--;
		}
		// printf("%d %d %d\n",idx,(*QC).Customer[idx].Id,(*QC).Customer[idx].Kesabaran);
	}
}