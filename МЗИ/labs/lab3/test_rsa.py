from rsa import *

with open('source.txt', 'r') as file:
    source_text = file.read()

private_key, public_key = generate_keys()

encrypted_text = encrypt(source_text, public_key)
decrypted_text = decrypt(encrypted_text, private_key)

print('Source text: ', source_text)
print('Encrypted text: ', encrypted_text)
print('Decrypted text: ', decrypted_text)