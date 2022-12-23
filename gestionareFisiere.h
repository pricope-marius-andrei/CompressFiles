#include <cstring>

void extDenumirefisier(char path[], char name[])
{
    char *n = strrchr(path,(char)92);
    strcpy(name,n + 1);
}

void determinareDestinatieFisier(char a[], string s)
{
    int lung = strlen(a);
    for (unsigned int i=0; i<s.size(); i++)
    {
        a[lung] = s[i];
        lung++;
    }
    a[lung] = '\0';
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
