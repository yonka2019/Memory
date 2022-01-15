#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>

#define BUF_SIZE 10
TCHAR szName[] = TEXT("Local\\MoranMapping");

int main()
{
    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = OpenFileMapping(
        FILE_MAP_WRITE | FILE_MAP_READ,   // read/write access
        FALSE,                 // do not inherit the name
        szName);               // name of mapping object

    if (hMapFile == NULL)
    {
        _tprintf(TEXT("Could not open file mapping object (%d).\n"),
            GetLastError());
        return 1;
    }

    PBYTE  mapping = (PBYTE)MapViewOfFile(hMapFile, // handle to map object
        FILE_MAP_WRITE | FILE_MAP_READ,  // read/write permission
        0,
        0,
        BUF_SIZE);
    PBYTE filePtr = mapping;

    if (mapping == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFile);

        return 1;
    }
    filePtr[1] = 'C';
    filePtr[2] = 'K';
    filePtr[3] = 'D';
    filePtr[0] = 'Z';
    memcpy(filePtr, "Z", 1);

    UnmapViewOfFile(mapping);

    CloseHandle(hMapFile);

    return 0;
}