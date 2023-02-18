#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <Psapi.h>

#include "vec_utils.h"

using namespace std;

//Takes in a base pointer and offsets to find the address we're looking for.
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, vector <unsigned int> offsets)
{
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
        addr += offsets[i];
    }
    return addr;
}

int main()
{
    cout << "Attempting to find Trackmania..." << endl;

    HWND hwnd = FindWindowA(NULL, "Trackmania");

    vec3 playerPosition = vec3(0, 0, 0);

    HMODULE hMods[1024];
    DWORD cbNeeded;
    DWORD procID;

    if (hwnd == NULL)
    {
        cout << "Trackmania window not found! Please ensure Trackmania 2020 is open and running." << endl;
        Sleep(5000);
        exit(-1);
    }

    cout << "Found Trackmania..." << endl;
    
    GetWindowThreadProcessId(hwnd, &procID);

    if (procID == NULL)
    {
        cout << "Cannot obtain process!";
        Sleep(5000);
        exit(-1);
    }

    HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, procID);

    EnumProcessModules(handle, hMods, sizeof(hMods), &cbNeeded);

    uintptr_t dynamicPtrBaseAddr = (uintptr_t)hMods[0] + 0x01E340F8;
    vector <unsigned int> offsets = { 0x2A8, 0x1C0, 0x30, 0x160, 0x198, 0xD20, 0x2C };

    uintptr_t pos_addr = FindDMAAddy(handle, dynamicPtrBaseAddr, offsets);

    ofstream outfile;
    outfile.open("./car-location.txt");

    for (;;)
    {
        ReadProcessMemory(handle, (PBYTE*)pos_addr, &playerPosition.x, sizeof(float), 0);
        ReadProcessMemory(handle, (PBYTE*)(pos_addr+4), &playerPosition.y, sizeof(float), 0);
        ReadProcessMemory(handle, (PBYTE*)(pos_addr+8), &playerPosition.z, sizeof(float), 0);

        system("cls");

        cout << "Position: " << endl;
        cout << "    x: " << playerPosition.x << endl;
        cout << "    y: " << playerPosition.y << endl;
        cout << "    z: " << playerPosition.z << "\r";

        outfile << playerPosition.x << "," << playerPosition.y << "," << playerPosition.z << endl;
    }

    outfile.close();

    return 0;
}
