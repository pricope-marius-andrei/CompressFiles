#include <cstring>

void extDenumirefisier(char path[], char name[])
{
    char *n = strrchr(path,(char)92);
    strcpy(name,n + 1);
}

void determinareDestinatieFisier(char path[], char name[])
{
    strcat(path,name);
}

void golireVariabile()
{
    /// golire frecventa
    frecventaCaractere.clear();

    ///stergere coduri
    coduri.clear();

    /// golire testinitial
    textInitial.clear();
}
