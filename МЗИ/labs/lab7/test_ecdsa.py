from ecdsa import *
from key import PrivateKey

private_key = PrivateKey()
public_key = private_key.publicKey()

with open('source.txt', 'r') as file:
    source_text = file.read()

signature = sign(source_text, private_key)
print('Source text: ', source_text)
print('Signature: ', signature.toBase64())

if verify(source_text, signature, public_key):
    print('verified')
else:
    print('not verified')