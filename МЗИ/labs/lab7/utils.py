from base64 import b64encode, b64decode
from binascii import hexlify, unhexlify
from random import SystemRandom

xrange = range
stringTypes = (str,)
intTypes = (int, float)

def toString(string):
    return string.decode("latin-1")

def toBytes(string):
    return string.encode("latin-1")

def safeBinaryFromHex(hexString):
    return unhexlify(hexString)

def safeHexFromBinary(byteString):
    return hexlify(byteString)

class Base64:
    @classmethod
    def decode(cls, string):
        return b64decode(string)

    @classmethod
    def encode(cls, string):
        return b64encode(string)

class BinaryAscii:
    @classmethod
    def hexFromBinary(cls, data):
        return safeHexFromBinary(data)

    @classmethod
    def binaryFromHex(cls, data):
        return safeBinaryFromHex(data)

    @classmethod
    def numberFromString(cls, string):
        return int(cls.hexFromBinary(string), 16)

    @classmethod
    def stringFromNumber(cls, number, length):
        fmtStr = "%0" + str(2 * length) + "x"
        return toString(cls.binaryFromHex((fmtStr % number).encode()))

class RandomInteger:
    @classmethod
    def between(cls, min, max):
        return SystemRandom().randrange(min, max + 1)

class Signature:

    def __init__(self, r, s, recoveryId=None):
        self.r = r
        self.s = s
        self.recoveryId = recoveryId

    def toDer(self, withRecoveryId=False):
        encodedSequence = encodeSequence(encodeInteger(self.r), encodeInteger(self.s))
        if not withRecoveryId:
            return encodedSequence
        return chr(27 + self.recoveryId) + encodedSequence

    def toBase64(self, withRecoveryId=False):
        return toString(Base64.encode(toBytes(self.toDer(withRecoveryId=withRecoveryId))))


hexAt = "\x00"
hexB = "\x02"
hexC = "\x03"
hexD = "\x04"
hexF = "\x06"
hex0 = "\x30"

hex31 = 0x1f
hex127 = 0x7f
hex129 = 0xa0
hex160 = 0x80
hex224 = 0xe0

bytesHex0 = toBytes(hex0)
bytesHexB = toBytes(hexB)
bytesHexC = toBytes(hexC)
bytesHexD = toBytes(hexD)
bytesHexF = toBytes(hexF)


def encodeSequence(*encodedPieces):
    totalLengthLen = sum([len(p) for p in encodedPieces])
    return hex0 + _encodeLength(totalLengthLen) + "".join(encodedPieces)

def encodeInteger(x):
    t = ("%x" % x).encode()

    if len(t) % 2:
        t = toBytes("0") + t

    x = BinaryAscii.binaryFromHex(t)
    num = x[0] if isinstance(x[0], intTypes) else ord(x[0])

    if num <= hex127:
        return hexB + chr(len(x)) + toString(x)
    return hexB + chr(len(x) + 1) + hexAt + toString(x)

def encodeOid(first, second, *pieces):
    encodedPieces = [chr(40 * first + second)] + [_encodeNumber(p) for p in pieces]
    body = "".join(encodedPieces)

    return hexF + _encodeLength(len(body)) + body

def encodeBitString(t):
    return hexC + _encodeLength(len(t)) + t

def encodeOctetString(t):
    return hexD + _encodeLength(len(t)) + t

def encodeConstructed(tag, value):
    return chr(hex129 + tag) + _encodeLength(len(value)) + value

def removeSequence(string):
    length, lengthLen = _readLength(string[1:])
    endSeq = 1 + lengthLen + length

    return string[1 + lengthLen: endSeq], string[endSeq:]

def removeInteger(string):
    length, lengthLen = _readLength(string[1:])
    numberBytes = string[1 + lengthLen:1 + lengthLen + length]
    rest = string[1 + lengthLen + length:]

    return int(BinaryAscii.hexFromBinary(numberBytes), 16), rest

def removeObject(string):
    length, lengthLen = _readLength(string[1:])
    body = string[1 + lengthLen:1 + lengthLen + length]
    rest = string[1 + lengthLen + length:]
    numbers = []

    while body:
        n, lengthLength = _readNumber(body)
        numbers.append(n)
        body = body[lengthLength:]

    n0 = numbers.pop(0)
    first = n0 // 40
    second = n0 - (40 * first)
    numbers.insert(0, first)
    numbers.insert(1, second)

    return tuple(numbers), rest

def removeBitString(string):
    length, lengthLen = _readLength(string[1:])
    body = string[1 + lengthLen:1 + lengthLen + length]
    rest = string[1 + lengthLen + length:]

    return body, rest

def removeOctetString(string):
    length, lengthLen = _readLength(string[1:])
    body = string[1 + lengthLen:1 + lengthLen + length]
    rest = string[1 + lengthLen + length:]

    return body, rest

def removeConstructed(string):
    s0 = _extractFirstInt(string)
    tag = s0 & hex31
    length, lengthLen = _readLength(string[1:])
    body = string[1 + lengthLen:1 + lengthLen + length]
    rest = string[1 + lengthLen + length:]

    return tag, body, rest

def _encodeLength(length):
    if length < hex160:
        return chr(length)

    s = ("%x" % length).encode()
    if len(s) % 2:
        s = "0" + s

    s = BinaryAscii.binaryFromHex(s)
    lengthLen = len(s)

    return chr(hex160 | lengthLen) + str(s)


def _encodeNumber(n):
    b128Digits = []
    while n:
        b128Digits.insert(0, (n & hex127) | hex160)
        n >>= 7

    if not b128Digits:
        b128Digits.append(0)

    b128Digits[-1] &= hex127

    return "".join([chr(d) for d in b128Digits])


def _readLength(string):
    num = _extractFirstInt(string)
    if not (num & hex160):
        return (num & hex127), 1

    lengthLen = num & hex127
    return int(BinaryAscii.hexFromBinary(string[1:1 + lengthLen]), 16), 1 + lengthLen


def _readNumber(string):
    number = 0
    lengthLen = 0
    while True:
        number <<= 7
        d = string[lengthLen]
        if not isinstance(d, intTypes):
            d = ord(d)

        number += (d & hex127)
        lengthLen += 1
        if not d & hex160:
            break

    return number, lengthLen



def _extractFirstInt(string):
    return string[0] if isinstance(string[0], intTypes) else ord(string[0])