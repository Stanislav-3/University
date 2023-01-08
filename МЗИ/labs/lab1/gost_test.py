import binascii
from gost import encrypt, decrypt


sbox = (
        (4, 10, 9, 2, 13, 8, 0, 14, 6, 11, 1, 12, 7, 15, 5, 3),
        (14, 11, 4, 12, 6, 13, 15, 10, 2, 3, 8, 1, 0, 7, 5, 9),
        (5, 8, 1, 13, 10, 3, 4, 2, 14, 15, 12, 7, 6, 0, 9, 11),
        (7, 13, 10, 1, 0, 8, 9, 15, 14, 4, 6, 12, 11, 2, 5, 3),
        (6, 12, 7, 1, 5, 15, 13, 8, 4, 10, 9, 14, 0, 3, 11, 2),
        (4, 11, 10, 0, 7, 2, 1, 13, 3, 6, 8, 5, 9, 12, 15, 14),
        (13, 11, 4, 1, 3, 15, 5, 9, 0, 10, 14, 7, 6, 8, 2, 12),
        (1, 15, 13, 0, 5, 7, 10, 4, 9, 2, 3, 14, 6, 11, 8, 12),
    )
    
with open('source.txt', 'r') as file:
    source_text = file.read()
    
hex_text = int(binascii.hexlify(source_text.encode()).decode(), 16)
key = 54875546557

encrypted_hex_text = encrypt(hex_text, key, sbox)
decrypted_hex_text = decrypt(encrypted_hex_text, key, sbox)
assert hex_text == decrypted_hex_text
decrypted_hex_text = binascii.unhexlify(hex(decrypted_hex_text)[2:]).decode()
print('Source text: ', source_text)
print('Encrypted text: ', encrypted_hex_text)
print('Decrypted text: ', decrypted_hex_text)