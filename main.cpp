#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <bitset>
#include "huffmanAlghoritm.h"

using namespace std;

ofstream out("dateiesire.out");

unsigned int n; ///numarul de caractere
unsigned long long int lg; /// lungime dupa aplicarea algoritmului

string codificare;

int main(int argc, char *argv[])
{
    int compresie;
    cout << "Compress(1)/Decompress(2):";
    cin >> compresie;
    if(compresie == 1) {
        FILE * fisierText = fopen(argv[1], "r");
        FILE * fisierCompresat = fopen(argv[2], "wb");
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
        /*for(auto it=coduri.begin(); it != coduri.end();++it)
        {
            if(it->first == '\n')
            {
                cout << "}:" << it->second <<":"<<frecventaCaractere[it->first] << '\n';
            }
            else
            {
                cout << it->first << ":" << it->second <<":"<<frecventaCaractere[it->first] << '\n';
            }

        }*/
        fwrite(elemente,sizeof(struct nod),1,fisierCompresat);

        for(int i = 0; i < textInitial.size(); i++)
        {
            scrieBit(fisierCompresat,coduri[textInitial[i]]);
        }
        if(fisierCompresat)
            cout << "FISIERUL A FOST COMPRESAT CU SUCCES!";
        else
            cout << "FISIERUL NU A PUTUT FI GASIT!";
        fclose(fisierText);
        fclose(fisierCompresat);
    }
    else
    {
        FILE * fisierCompresat = fopen("D:\\Programming\\Facultate\\IP\\Proiect Compresie Fisiere\\CompressFiles\\fisierCompresat.txt", "rb");
        if(fisierCompresat){
            nod *elemente;
            fread(elemente,sizeof(struct nod),1,fisierCompresat);
            cout << elemente ->frec;
        }
        /*for(auto it=coduri.begin(); it != coduri.end();++it)
        {
            if(it->first == '\n')
            {
                cout << "}:" << it->second <<":"<<frecventaCaractere[it->first] << '\n';
            }
            else
            {
                cout << it->first << ":" << it->second <<":"<<frecventaCaractere[it->first] << '\n';
            }
        }*/

        fclose(fisierCompresat);
    }

    return 0;
}
