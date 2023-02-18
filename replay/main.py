#GBX header info from: https://wiki.xaseco.org/wiki/GBX#Engines.2C_classes.2C_chunks
#Big thanks to this github repo, was absolutely invaluable https://github.com/thaumictom/gbx.js/blob/master/src/gbx.js
#Additional thanks to this github repo https://github.com/railem/replayChart/blob/master/src/main/java/de/reilem/replaychart/gbx/GbxInputExtractor.java

import sys
import xmltodict
import struct
import lzo
import binascii
import pprint

from PyQt5.QtWidgets import *

def readUInt16(file): return int.from_bytes(file.read(2), byteorder='little', signed=False)
def readUInt32(file): return int.from_bytes(file.read(4), byteorder='little', signed=False)

def readBytes(file,n): return file.read(n)
def readString(file,n): return file.read(n).decode()

def parseHeader(filename):
    replay = open(filename, 'rb')

    magic = readString(replay,3)

    if magic != 'GBX':
        print(f'File is not GBX format! {magic}')

    __VERSION = readUInt16(replay)

    if __VERSION != 6: print(f'File version is not supported! This program only supports version 6, but this file is version {__VERSION}.')

    __BYTE_FORMAT = readString(replay,1)
    __REF_COMPRESSION = readString(replay,1)
    __BODY_COMPRESSION = readString(replay,1)
    __UNKNOWN = readString(replay,1)

    __CLASS_ID = readUInt32(replay)

    __USER_DATA_SIZE = readUInt32(replay)

    d = readBytes(replay,__USER_DATA_SIZE + 8)

    __UNCOMPRESSED_SIZE = readUInt32(replay)
    __COMPRESSED_SIZE = readUInt32(replay)

    print(f'{__UNCOMPRESSED_SIZE} Bytes uncompressed\n{__COMPRESSED_SIZE} Bytes compressed')

    compressed_data = readBytes(replay,__COMPRESSED_SIZE)
    uncompressed_data = lzo.decompress(compressed_data,False,__UNCOMPRESSED_SIZE)

    w = open('./replays/replay-body.bin', 'wb')
    w.write(uncompressed_data)
    w.close()

app = QApplication([])
window = QWidget()
window.setWindowTitle("TM-2020 TAS Tools")

def openFileDialog():
    options = QFileDialog.Options()
    fileName, _ = QFileDialog.getOpenFileName(window,"Open Trackmania 2020 .GBX Replay File", "","Trackmania Replay File (*.gbx)", options=options)

    parseHeader(fileName)
    return fileName

fileopenButton = QPushButton('Open GBX Replay File')
fileopenButton.clicked.connect(openFileDialog)

grid = QGridLayout()

keyboard_grid = QGridLayout()

button_w = QPushButton('W')
button_a = QPushButton('A')
button_s = QPushButton('S')
button_d = QPushButton('D')

keyboard_grid.addWidget(button_w,0,1)
keyboard_grid.addWidget(button_a,1,0)
keyboard_grid.addWidget(button_s,1,1)
keyboard_grid.addWidget(button_d,1,2)

grid.addLayout(keyboard_grid,0,1)
grid.addWidget(fileopenButton,0,0)

window.setLayout(grid)

window.show()
sys.exit(app.exec())