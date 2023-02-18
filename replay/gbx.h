#pragma once

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <Psapi.h>
#include <vector>
#include <string>

using namespace std;

#ifndef file_reading_utils
#define file_reading_utils

/*
def readUInt16(file): return int.from_bytes(file.read(2), byteorder='little', signed=False)
def readUInt32(file): return int.from_bytes(file.read(4), byteorder='little', signed=False)

def readBytes(file,n): return file.read(n)
def readString(file,n): return file.read(n).decode()
*/

uint16_t readUInt16()
{

}

uint32_t readUInt32()
{

}

vector<char> readBytes(int n)
{

}

string readString(int n)
{

}

struct GbxHeader
{
    string magic;
    uint16_t version;

    string byteFormat;
    string refCompression;
    string bodyCompression;
    string unknown;

    uint32_t classID;

    uint32_t user_data_size;

    vector<char> user_data;

    uint32_t decompressed_size;
    uint32_t compressed_size;

    vector<char> compressed_data;
};

#endif