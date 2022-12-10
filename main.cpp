#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include "huffmanAlghoritm.h"

using namespace std;

ofstream out("dateiesire.out");

unsigned int n; ///numarul de caractere
unsigned long long int lg; /// lungime dupa aplicarea algoritmului

string codificare;

int main()
{
    FILE * fisierText = fopen("D:\\Programming\\Facultate\\IP\\Proiect Compresie Fisiere\\CompressFiles\\fisierText.txt", "r");
    FILE * fisierCompresat = fopen("D:\\Programming\\Facultate\\IP\\Proiect Compresie Fisiere\\CompressFiles\\fisierCompresat.txt", "w");
    ///lista in care vom retine nodurile frunza de la inceput
    nod* elemente = new nod;
    elemente = NULL;

    ///determinarea frecventei din fisier a caracterelor
    determinareFrecventa(fisierText);

    ///sortare dupa frecventa caracterelor
    sortareLista(frecventaCaractere);

    ///introducerea nodurilor frunza in lista de elemente
    creareListaDeCaractere(elemente,frecventaCaractere);

    while(elemente -> urm != NULL)
    {
        nod *nodNou = creareNod(elemente);
        elemente = elemente -> urm -> urm;
        inserareNoduri(elemente,nodNou);
    }

    parcurgere(elemente,codificare);
    for(auto it=coduri.begin(); it != coduri.end();++it)
    {
        if(it->first == '\n')
        {
            cout << "}:" << conversieBaze(it->second) <<":"<<frecventaCaractere[it->first] << '\n';
        }
        else
        {
            cout << it->first << ":" << conversieBaze(it->second) <<":"<<frecventaCaractere[it->first] << '\n';
        }

    }
    //fwrite(&elemente,sizeof(nod),1,fisierCompresat);
    for(int i = 0; i < textInitial.size(); i++)
    {
        int numar = conversieBaze(coduri[textInitial[i]]);
        fwrite(&numar,1,1,fisierCompresat);
    }
    fclose(fisierText);
    return 0;
}
