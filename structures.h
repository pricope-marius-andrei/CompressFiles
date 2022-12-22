#include <map>

using namespace std;

struct nod{
    char caracter;
    int frec;
    nod *urm;
    nod *stg,*drt;
};

struct fisier{
    char nume[10];
   /// string dataCreareFisier;
};

///un hashmap pentru a retine codurile fiecarui caracter
map <char,string> coduri;
map <char,int> frecventaCaractere;
string textInitial;

///varibile folosite pentru scrierea, bit cu bit, in fisier
int bitCurent = 0;
unsigned char byteToWrite;
