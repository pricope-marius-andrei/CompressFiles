#include <iostream>
#include <fstream>
#include <algorithm>
#include "huffmanAlgorithm.h"

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
        elemente = elemente -> urm -> urm;
        inserareNoduri(elemente,nodNou);
    }

    parcurgere(elemente,codificare);
    out << suma(elemente);
    return 0;
}
