#include <Windows.h>
#include <iostream>
using namespace std;

#define SEARCH_LETTER "A"
#define FILENAME "..\\gibrish.bin"

int CountChar(PCHAR pBuf, int buff_size, LPCSTR letter);

int main()
{
	SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);
	int mem_buffer_size = sys_info.dwAllocationGranularity;

	HANDLE hFile;
	LPCSTR pFileName = FILENAME;
	hFile = CreateFileA(pFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		cout << "[ERROR] Error opening file!" << endl;
		exit(1);
	}

	DWORD file_size = GetFileSize(hFile, NULL);

	HANDLE hMapFile;
	hMapFile = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, "file");

	int buffer_number = 0, count;
	int file_location = buffer_number * mem_buffer_size;
	LPSTR pBuf;
	LPCSTR letter = SEARCH_LETTER;

	while (file_location <= (file_size - mem_buffer_size))
	{
		pBuf = (LPSTR)MapViewOfFile(hMapFile, FILE_MAP_READ, 0, file_location, mem_buffer_size);

		count = CountChar(pBuf, mem_buffer_size, letter);
		cout << "Counter of '" << SEARCH_LETTER << "': " << count << endl;
		buffer_number++;
		file_location = mem_buffer_size * buffer_number;
		UnmapViewOfFile(pBuf);
		Sleep(100);
	}
	int reminder = file_size - file_location;

	pBuf = (LPSTR)MapViewOfFile(hMapFile, FILE_MAP_READ, 0, file_location, reminder);
	count = CountChar(pBuf, reminder, letter);

	cout << "Counter of '" << SEARCH_LETTER << "': " << count << endl;

	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
	CloseHandle(hFile);
	return 0;
}

int CountChar(PCHAR pBuf, int buff_size, LPCSTR letter)
{
	static int count = 0;
	for (int i = 0; i < buff_size; i++)
	{
		if (pBuf[i] == *letter) count++;
	}
	return count;
}