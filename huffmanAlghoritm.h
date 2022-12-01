#ifndef HUFFMANALGHORITM_H_INCLUDED
#define HUFFMANALGHORITM_H_INCLUDED


struct nod{
    int frec;
    nod *urm;
    nod *stg,*drt;
};

void citireElemente(nod *&elemente, unsigned int n)
{
    for(int i = 0; i < n; i++)
    {
        int x;
        in >> x;

        nod *nouNod = new nod;
        nouNod -> frec = x;
        nouNod -> stg = nouNod -> drt = nouNod -> urm = NULL;


        if(elemente == NULL)
        {
            elemente = nouNod;
        }
        else
        {
            nod *p = elemente;
            while(p -> urm != NULL)
            {
                p = p->urm;
            }

            p -> urm = nouNod;
        }
    }
}

nod* creareNod(nod *elemente)
{
    nod *nouNod = new nod;
    nouNod->frec = elemente->frec + elemente->urm->frec;
    nouNod->urm = NULL;
    nouNod->stg = elemente;
    nouNod->drt = elemente->urm;
    return nouNod;
}

void stergereNoduri(nod *&elemente)
{
    if(elemente->urm == NULL)
    {
        cout << "NU PUTEM ELIMINA";
    }
    else
    {
        nod *first = elemente;
        nod *second = elemente -> urm;
        elemente = elemente -> urm -> urm;
        delete first;
        delete second;
    }
}

void inserareNoduri(nod *&elemente, nod* nodNou)
{
    nod *p = elemente;
    if(elemente == NULL)
    {
        elemente = nodNou;
    }
    else if(nodNou -> frec < p -> frec)
    {
        nodNou->urm = elemente;
        elemente = nodNou;
    }
    else
    {
        while(p -> urm != NULL && nodNou -> frec >= p -> urm -> frec)
        {
            p = p-> urm;
        }

        if(p -> urm == NULL)
        {
            p -> urm = nodNou;
        }
        else
        {
            nodNou -> urm = p -> urm;
            p -> urm = nodNou;
        }
    }
}

void parcurgere(nod *rad, string cod)
{
    if(rad -> stg == NULL && rad -> drt == NULL)
    {
        cout << cod << endl;
        return;
    }
    else
    {
        //cout << rad->frec << ' ';
        parcurgere(rad->stg, cod + "0");
        parcurgere(rad->drt, cod + "1");
    }
}

#endif
