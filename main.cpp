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
        FILE * fisierText = fopen(argv[1], "rb");
        FILE * fisierCompresat = fopen(argv[2], "wb");
        ///lista in care vom retine nodurile frunza de la inceput
        nod* elemente = new nod;
        elemente = NULL;

        ///determinarea frecventei din fisier a caracterelor
        determinareFrecventa(fisierText);

        ///sortare dupa frecventa caracterelor
        vector<pair<char,int>> elementeSortate = sortareLista(frecventaCaractere);

        ///introducerea nodurilor frunza in lista de elemente
        creareListaDeCaractere(elemente,elementeSortate);

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
                cout << "}:" << it->second <<":"<<frecventaCaractere[it->first] << '\n';
            }
            else
            {
                cout << it->first << ":" << it->second <<":"<<frecventaCaractere[it->first] << '\n';
            }

        }
        cout << endl;
        serializeTree(fisierCompresat,elemente);

        ///luam fiecare caracter din textulInitial si le inlocuim cu codul creat pentru el
        for(unsigned int i = 0; i < textInitial.size(); i++)
        {
            scrieBit(fisierCompresat,coduri[textInitial[i]]);
        }

        ///scriem ultimul caracter in fisier, in cazul in care nu a fost completat ultimul byte
        /*if(byteToWrite != 0)
        {
            fwrite(&byteToWrite,sizeof(unsigned char),1,fisierCompresat);
        }*/

        if(fisierCompresat && fisierText)
            cout << "FISIERUL A FOST COMPRESAT CU SUCCES!";
        else
            cout << "FISIERUL NU A PUTUT FI GASIT!";

        fclose(fisierText);
        fclose(fisierCompresat);
    }
    else if(compresie == 2)
    {
        FILE * fisierCompresat = fopen(argv[3], "rb");
        if(fisierCompresat){
            cout << "FISIERUL A FOST DESCHIS" << '\n';
        }
        else
        {
            cout << "NU A FOST GASIT FISIERUL" << '\n';
            return 0;
        }
        nod *arboreHuffman;
        deserializeTree(fisierCompresat,arboreHuffman);

        ///retin codul textului initial
        string codare = citireCaractereFisierCompresat(fisierCompresat);
        cout << codare << endl;

        unsigned int index = 0;
        while(index < codare.size())
        {
            parcurgereArbore(arboreHuffman,index,codare);
        }

        /*cout << "Caractere din fisier" << '\n';
        parcurgereArbore(arboreHuffman);
*/
        fclose(fisierCompresat);
    }

    return 0;
}
