#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include "huffmanAlghoritm.h"

using namespace std;

unsigned int n; ///numarul de caractere
unsigned long long int lg; /// lungime dupa aplicarea algoritmului

string codificare;

int main()
{
    FILE * fisierText = fopen("D:\\Programming\\Facultate\\IP\\Proiect Compresie Fisiere\\CompressFiles\\fisierText.txt", "r");

    determinareFrecventa(fisierText);

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
    fclose(fisierText);
    return 0;
}
