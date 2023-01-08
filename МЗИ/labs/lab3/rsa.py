from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.PublicKey import RSA
import ast


def encrypt(message, public_key):
    encoded_message = str.encode(message)
    rsa_public_key = PKCS1_OAEP.new(RSA.importKey(public_key))

    return rsa_public_key.encrypt(encoded_message)


def decrypt(message, private_key):
    rsa_private_key = PKCS1_OAEP.new(RSA.importKey(private_key))

    return rsa_private_key.decrypt(ast.literal_eval(str(message))).decode()


def generate_keys():
    key = RSA.generate(2048)

    return key.export_key('PEM'), key.public_key().export_key('PEM')