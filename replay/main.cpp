#include "gbx.h"

#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <Psapi.h>
#include <vector>

GbxHeader parseHeader(string &filename)
{
    GbxHeader header;

    header.magic = readString(3);

    if (header.magic != "GBX")
    {
        cout << "File is not GBX format! Unknown format " << header.magic << ".\n";
    }

    header.version = readUInt16();
    
    if (header.version != 6)
    {
        cout << "Only GBX file version 6 is supported. This file is version " << header.version << ".\n"; 
    }

    header.byteFormat = readString(1);
    header.refCompression = readString(1);
    header.bodyCompression = readString(1);
    header.unknown = readString(1);

    header.classID = readUInt32();

    header.user_data_size = readUInt32();

    header.user_data = readBytes(header.user_data_size + 8);

    header.decompressed_size = readUInt32();
    header.compressed_size = readUInt32();

    header.compressed_data = readBytes(header.compressed_size);

    return header;
}