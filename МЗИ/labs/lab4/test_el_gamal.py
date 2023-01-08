import random
from el_gamal import *

with open('source.txt', 'r') as file:
    source_text = file.read()

q = random.randint(pow(10, 20), pow(10, 50))
g = random.randint(2, q)
key = gen_key(q)  
h = power(g, key, q)

encrypted_text, p = encrypt(source_text, q, h, g)
decrypted_text = ''.join(decrypt(encrypted_text, p, key, q))

print('Source text: ', source_text)
print('Encrypted text: ', encrypted_text)
print('Decrypted text: ', decrypted_text)