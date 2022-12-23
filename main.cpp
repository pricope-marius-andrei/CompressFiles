#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include "huffmanAlghoritm.h"
#include "gestionareFisiere.h"

using namespace std;

string codificare;

int main(int argc, char *argv[])
{
    int compresie;
    cout << "Compress(1)/Decompress(2):";
    cin >> compresie;
    if(compresie == 1)
    {
        FILE * fisierCompresat = fopen(argv[argc-1], "wb");

        for (int i=1; i<argc-1; i++)
        {
            FILE * fisierText = fopen(argv[i], "rb");
            ///lista in care vom retine nodurile frunza de la inceput
            nod* elemente = new nod;
            elemente = NULL;

            ///determinarea frecventei din fisier a caracterelor
            determinareFrecventa(fisierText);

            ///sortare dupa frecventa caracterelor
            vector<pair<char,int>> elementeSortate = sortareLista(frecventaCaractere);

            ///introducerea nodurilor frunza in lista de elemente
            creareListaDeCaractere(elemente,elementeSortate);

            ///cream legaturile intre noduri, pana ramanem cu un singur nod in lista, care reprezinta radacina arborelui
            creareArbore(elemente);

            ///determinam fiecare cod pentru caracterele din textul nostru
            codareCaractere(elemente,codificare);

            ///scriem numele fisierului
            fisier fisierCurent;
            extDenumirefisier(argv[i],fisierCurent.nume);
            fwrite(&fisierCurent,sizeof(fisierCurent),1,fisierCompresat);

            ///retinem nodurile arborelui in fisierul nostru comresat
            serializeTree(fisierCompresat,elemente);

            if(singurCaracter(frecventaCaractere))
            {
                ///daca avem un singur tip de caracter in text, retinem si frecventa acestuia pentru al putea decoda
                int frecventa = frecventaCaractere[textInitial[0]];
                fwrite(&frecventa,1,1,fisierCompresat);
                fwrite("\0",1,1,fisierCompresat);
            }
            else
            {

                ///scriem lungimea textului initial
                unsigned int sizeText = textInitial.size();
                fwrite(&sizeText,sizeof(unsigned int),1,fisierCompresat);

                ///luam fiecare caracter din textulInitial si le inlocuim cu codul creat pentru el
                for(unsigned int i = 0; i < textInitial.size(); i++)
                {
                    scrieByte(fisierCompresat,coduri[textInitial[i]]);
                }

                ///scriem ultimul caracter in fisier, in cazul in care nu a fost completat ultimul byte
                while (bitCurent)
                    scrieByte(fisierCompresat,"0");
                fwrite("\0",1,1,fisierCompresat);

            }

            if(fisierCompresat && fisierText)
                cout << "FISIERUL " << fisierCurent.nume <<" A FOST COMPRESAT CU SUCCES!" << '\n';
            else
                cout << "FISIERUL " << fisierCurent.nume <<" NU A FOST COMPRESAT CU SUCCES!" << '\n';

            ///dupa ce am terminat cu un fisier trebuie sa stergem urmele de la fisierul precedent
            golireVariabile();
            delete elemente;

            fclose(fisierText);
        }
        fclose(fisierCompresat);
    }
    else if(compresie == 2)
    {
        FILE * fisierCompresat = fopen(argv[1], "rb");

        for(int i = 0; i < 1; i++)
        {
            /// FILE * locatieDecompresare = fopen(argv[2], "wb");
            if(fisierCompresat)
            {
                cout << "FISIERUL A FOST DESCHIS" << '\n';
            }
            else
            {
                cout << "NU A FOST GASIT FISIERUL" << '\n';
                return 0;
            }

            ///citire date despre fisier
            fisier fisierCurent;
            fread(&fisierCurent,sizeof(fisierCurent),1,fisierCompresat);


            cout << "Nume fisier:";
            cout << fisierCurent.nume << endl;


            /// in arboreHuffman vom citii arborele pe care l-am scris la inceputul fisierului compresat
            nod *arboreHuffman;
            deserializeTree(fisierCompresat,arboreHuffman);

            unsigned int index = 0; ///index decodare

            ///verificam daca avem un singur tip de caractere, in cazul acesta avem nevoie doar de frecventa acestuia
            ///fara codificare
            if(arboreHuffman -> stg == NULL && arboreHuffman -> drt == NULL)
            {
                unsigned int frecCaracter;
                fread(&frecCaracter,1,1,fisierCompresat);
                while(index < frecCaracter)
                {
                    cout << arboreHuffman -> caracter;
                    index++;
                }
            }
            else
            {
                ///citesc lungimea textului
                int lungimeInitialText;
                fread(&lungimeInitialText,sizeof(unsigned int),1,fisierCompresat);

                cout << "Lungime text initial: ";
                cout<<lungimeInitialText<<endl;

                ///pentru cazul in care ultimul byte nu este complet, contorizam fiecare caracter citit
                ///pentru a evita scrierea unor caractere in plus
                int numarCurentCaractere = 0;

                string codare = citireCaractereFisierCompresat(fisierCompresat);
                while(index < codare.size())
                {
                    if(numarCurentCaractere == lungimeInitialText - 1)
                        break;
                    numarCurentCaractere++;
                    parcurgereArbore(arboreHuffman,index,codare);

                }
                cout << index;
                //cout << numarCurentCaractere << '\n';
            }
            cout << '\n';
            cout << '\n';
        }

        fclose(fisierCompresat);
    }

    return 0;
}
