replay = open('./replays/replay-body.bin', 'rb')

def readUInt16(): return int.from_bytes(replay.read(2), byteorder='little', signed=False)
def readUInt32(): return int.from_bytes(replay.read(4), byteorder='little', signed=False)

def readBytes(n): return replay.read(n)
def readString(n): return replay.read(n).decode()

def parseBody ():
    __BODY_CLASS_ID = readUInt32()
    __BODY_FILESIZE = readUInt32()

    print(__BODY_CLASS_ID, __BODY_FILESIZE)