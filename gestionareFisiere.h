#include <cstring>
#include <windows.h>

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

void modificareDataCreareFisier(char path[], time_t time)
{
    SYSTEMTIME thesystemtime;

    struct tm *local_time = localtime(&time);

    thesystemtime.wDay = local_time -> tm_mday;
    thesystemtime.wMonth = 1 + local_time -> tm_mon;
    thesystemtime.wYear = 1900 + local_time -> tm_year;
    thesystemtime.wHour = local_time -> tm_hour - 2;
    thesystemtime.wMinute = local_time -> tm_min;
    thesystemtime.wSecond = local_time -> tm_sec;

    // Create a FILETIME struct and convert our new SYSTEMTIME
    // over to the FILETIME struct for use in SetFileTime below
    FILETIME thefiletime;
    SystemTimeToFileTime(&thesystemtime,&thefiletime);

    // Get a handle to our file and with file_write_attributes access
    HANDLE filename = CreateFile(path, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    // Set the file time on the file
    //SetFileTime(filename,(LPFILETIME) NULL,(LPFILETIME) NULL,&thefiletime);
    SetFileTime(filename, &thefiletime, (LPFILETIME) NULL,(LPFILETIME) NULL);

    // Close our handle.
    CloseHandle(filename);
}
