#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream in("date.in");
ofstream out("date.out");

unsigned int n; ///numarul de caractere
unsigned long long int lg; /// lungime dupa aplicarea algoritmului

string codificare;

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

int main()
{
    nod* elemente = new nod;
    elemente = NULL;

    in >> n;

    citireElemente(elemente,n);

    while(elemente -> urm != NULL)
    {
        nod *nodNou = creareNod(elemente);
        out << "Nod creat:" << endl;
        out << nodNou->frec << endl;
        out << nodNou->stg->frec << endl;
        out << nodNou->drt->frec << endl;
        if(nodNou->stg->stg == NULL)
            out << "NULL - stg-stg" << endl;
        if(nodNou->stg->drt == NULL)
            out << "NULL - stg-drt" << endl;
        if(nodNou->drt->stg == NULL)
            out << "NULL - drt-stg" << endl;
        if(nodNou->drt->drt == NULL)
            out << "NULL - drt-drt" << endl;
        //out << nodNou->drt->frec << endl;
        elemente = elemente -> urm -> urm;
        inserareNoduri(elemente,nodNou);
    }

    parcurgere(elemente,codificare);
    return 0;
}
