//#include <bits/stdc++.h>
#include <cstring>

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

void determinareDestinatieFisier(char a[], string s)
{
    int lung = strlen(a);
    for (int i=0; i<s.size(); i++)
    {
        a[lung] = s[i];
        lung++;
    }
    a[lung] = '\0';
}
