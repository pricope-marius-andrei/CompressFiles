#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;

struct nod{
    char caracter;
    int frec;
    nod *urm;
    nod *stg,*drt;
};

///un hashmap pentru a retine codurile fiecarui caracter
unordered_map <char,string> coduri;
unordered_map <char,int> frecventaCaractere;
string textInitial;

///varibile folosite pentru scrierea, bit cu bit, in fisier
int bitCurent = 0;
unsigned char byteToWrite;

void scrieBit(FILE *file,string cod)
{
    for(int i = cod.size() - 1  ; i >= 0; i--) {
        unsigned char bit = cod[i];
        if(bit != '0')
            byteToWrite |= (1<<bitCurent);

        ++bitCurent;
        if(bitCurent == 8)
        {
            cout << byteToWrite << ' ';
            fwrite(&byteToWrite,1,1,file);
            bitCurent = 0;
            byteToWrite = 0;
        }
    }
}

int conversieBaze(string cod)
{
    int putere = 0;
    int numar = 0;
    for(int i = cod.size() - 1; i >= 0; i--)
    {
        if(cod[i] != '0')
            numar += pow(2,putere);
        putere++;
    }

    return numar;
}

void determinareFrecventa(FILE *fisier)
{
    if(fisier != NULL) {
        while(true)
        {
            // Citim caracter cu caracter din fisier
            char c = fgetc(fisier);
            //retinem textul initial
            textInitial.push_back(c);
            //printf("%c",c);
            // Verificicam daca am ajuns la finalul fisierului
            if (feof(fisier))
                break ;

            frecventaCaractere[c]++;
        }
    }
}

void creareListaDeCaractere(nod *&elemente, unordered_map <char,int> caractere)
{
    for(auto it = caractere.begin(); it != caractere.end(); ++it)
    {
        nod *nouNod = new nod;
        nouNod -> caracter = it->first;
        nouNod -> frec = it->second;
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

bool cmp(pair<char, int> &a, pair<char, int> &b)
{
    return a.second<b.second;
}

void sortareLista(unordered_map <char,int> caractere)
{
    vector<pair<char,int>> A;
    for (auto& it : caractere)
        A.push_back(it);
    sort(A.begin(), A.end(), cmp);
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
        ///retinem codurile intr-un hashmap
        coduri[rad->caracter] = cod;
        return;
    }
    else
    {
        parcurgere(rad->stg, cod + "0");
        parcurgere(rad->drt, cod + "1");
    }
}

int suma(nod *rad)
{
    if (rad -> stg == NULL && rad -> drt == NULL)
        return 0;
    else
        return rad -> frec + suma(rad->stg) + suma(rad->drt);
}
