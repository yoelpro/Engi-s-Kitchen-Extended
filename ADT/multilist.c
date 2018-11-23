#include "multilist.h"
#include "boolean.h"
#include <stdlib.h>

void CreateGraph(int X, Graph *G)
{
    FirstG(*G) = AlokNodeG(X);
}

adrNode AlokNodeG(int X)
{
    adrNode N;
    N = (adrNode) malloc(sizeof(NodeG));
    if (N!=NULL)
    {
        Id(N) = X;
        NPred(N) = 0;
        Trail(N) = NULL;
    }
    return N;
}

void DealokNodeG(adrNode P)
{
    free(P);
}

adrSuccNode AlokSuccNode(adrNode Pn)
{
    adrSuccNode P;
    P = (adrSuccNode) malloc(sizeof(SuccNode));
    if (P!=NULL)
    {
        Succ(P) = Pn;
        NextG(P) = NULL;
    }
    return P;
}

void DealokSuccNode(adrSuccNode P)
{
    free(P);
}

adrNode SearchNode(Graph G, int X)
{
    if (IsEmptyG(G))
    {
        return NULL;
    }
    else
    {
        adrNode P = FirstG(G);
        while(NextG(P)!=NULL && Id(P)!=X)
        {
            P=NextG(P);
        }
        if (Id(P)==X)
        {
            return P;
        }
        else
        {
            return NULL;
        }
    }
}

adrSuccNode SearchEdge(Graph G, int prec, int succ)
{
    if (SearchNode(G,prec)==NULL || SearchNode(G,succ)==NULL)
    {
        return NULL;
    }
    else
    {
        adrSuccNode TrailerPprec = Trail(SearchNode(G,prec));
        adrNode Psucc = SearchNode(G,succ);
        while (NextG(TrailerPprec)!=NULL && Succ(TrailerPprec)!=Psucc)
        {
            TrailerPprec = NextG(TrailerPprec);
        }
        if (Succ(TrailerPprec)==Psucc)
        {
            return TrailerPprec;
        }
        else
        {
            return NULL;
        }

    }
}

void InsertNode(Graph* G, int X, adrNode* Pn)
{
    *Pn=FirstG(*G);
    if (*Pn==NULL)
    {
        FirstG(*G)=AlokNodeG(X);
    }
    else
    {
        while(NextG(*Pn)!=NULL)
        {
            *Pn = NextG(*Pn);
        }
        NextG(*Pn) = AlokNodeG(X);
    }

}

void InsertEdge(Graph* G, int prec, int succ)
{
    if (SearchEdge(*G,prec,succ)==NULL)
    {
        adrNode Pprec = SearchNode(*G,prec);
        if (Pprec == NULL)
        {
            InsertNode(G,prec,&Pprec);
        }
        adrNode Psucc = SearchNode(*G,succ);
        if (Psucc == NULL)
        {
            InsertNode(G,succ,&Psucc);
        }
        adrSuccNode TrailPprec = Trail(Pprec);
        if (TrailPprec==NULL)
        {
            TrailPprec = AlokSuccNode(Psucc);
        }
        else
        {
            while(NextG(TrailPprec)!=NULL)
            {
                TrailPprec = NextG(TrailPprec);
            }
            TrailPprec = AlokSuccNode(Psucc);
        }
        NPred(Psucc)++;
    }
}

boolean IsEmptyG(Graph G)
{
    return FirstG(G)==NULL;
}