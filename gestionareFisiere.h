#include <bits/stdc++.h>

string extDenumirefisier(char a[])
{
    string demunireFisier;
    for (int i=strlen(a)-1; i>=0; i--)
    {
        if (a[i]!=(char)92)
            demunireFisier.push_back(a[i]);
        else
        {
            reverse(demunireFisier.begin(),demunireFisier.end());
            return demunireFisier;
        }
    }
}
