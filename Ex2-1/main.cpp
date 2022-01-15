#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>

using namespace std;

#define FILENAME L"C:\\Users\\magshimim\\Desktop\\Magshimim\\AssemblyYear2\\AfterAssembly\\Week12\\MagshimimAfterAssemblyEx12\\MagshimimAfterAssemblyEx12\\gibrish.bin"

TCHAR szName[] = TEXT("Local\\MoranMapping");
TCHAR szMsg[] = TEXT("");

int main()
{
    HANDLE hMapFile;
    LPCWSTR pBuf;

    HANDLE hFile;
    LPCWSTR pFileName = FILENAME;
    hFile = CreateFile(pFileName, GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        cout << "Error opening file!" << endl;
        exit(1);
    }

    hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, szName);

    if (hMapFile == NULL)
    {
        cout << "Could not create file mapping object " << GetLastError() << endl;
        CloseHandle(hFile);
        return 1;
    }

    int sizeofFile = GetFileSize(hFile, NULL);

    pBuf = (LPTSTR)MapViewOfFile(hMapFile, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, sizeofFile);

    if (pBuf == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFile);
        CloseHandle(hFile);
        return 1;
    }


    CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
    _getch();

    UnmapViewOfFile(pBuf);

    CloseHandle(hMapFile);
    CloseHandle(hFile);

    return 0;
}