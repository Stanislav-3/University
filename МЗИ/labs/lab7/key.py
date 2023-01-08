from utils import *
from math_utils import *

hexAt = "\x00"

class PublicKey:
    def __init__(self, point, curve):
        self.point = point
        self.curve = curve

class PrivateKey:
    def __init__(self, curve=secp256k1, secret=None):
        self.curve = curve
        self.secret = secret or RandomInteger.between(1, curve.N - 1)

    def publicKey(self):
        curve = self.curve
        publicPoint = Math.multiply(
            p=curve.G,
            n=self.secret,
            N=curve.N,
            A=curve.A,
            P=curve.P,
        )
        return PublicKey(point=publicPoint, curve=curve)
