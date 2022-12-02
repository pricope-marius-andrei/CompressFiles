#include <iostream>
#include <fstream>
#include <algorithm>
#include "huffmanAlghoritm.h"

using namespace std;

unsigned int n; ///numarul de caractere
unsigned long long int lg; /// lungime dupa aplicarea algoritmului

string codificare;

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
