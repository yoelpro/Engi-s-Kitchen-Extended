#include "multilist.h"
#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>

void CreateGraph(Graph *G)
{
    FirstG(*G) = NULL;
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
        NextG(N) = NULL;
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

        if (TrailerPprec != NULL) {
            adrNode Psucc = SearchNode(G,succ);

            while (NextG(TrailerPprec) != NULL && Succ(TrailerPprec) != Psucc)
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
        else {
            return NULL;
        }
    }
}

void InsertNode(Graph* G, int X, adrNode* Pn)
{
    *Pn=AlokNodeG(X);
    if (FirstG(*G)==NULL)
    {
        FirstG(*G) = *Pn;
    }
    else
    {
        adrNode Pt = FirstG(*G);

        while(NextG(Pt) != NULL)
        {
            Pt = NextG(Pt);
        }
        NextG(Pt) = *Pn;
    }
}

void InsertEdge(Graph* G, int prec, int succ, adrSuccNode *Pt)
{
    adrNode Pprec = SearchNode(*G,prec);
    if (Pprec == NULL)
    {
        InsertNode(G, prec, &Pprec);
    }

    adrNode Psucc = SearchNode(*G,succ);
    if (Psucc == NULL)
    {
        InsertNode(G, succ, &Psucc);
    }

    adrSuccNode TrailPprec = SearchEdge(*G, prec, succ);
    if (TrailPprec == NULL) {
        *Pt = AlokSuccNode(Psucc);

        if (Trail(Pprec) == NULL) {
            Trail(Pprec) = *Pt;
        }
        else {
            TrailPprec = Trail(Pprec);

            while (NextG(TrailPprec) != NULL) {
                TrailPprec = NextG(TrailPprec);
            }

            NextG(TrailPprec) = *Pt;
        }
        
        NPred(Psucc)++;
    }
    else {
        *Pt = TrailPprec;
    }
}

boolean IsEmptyG(Graph G)
{
    return FirstG(G)==NULL;
}