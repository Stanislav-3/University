import des

key = 'key'
block_size = 8
key = des.prepare_des_key(key, block_size)

with open('source.txt', 'r') as file:
    source_text = file.read()

encrypted_text = des.des_encrypt(key, source_text, block_size)
decrypted_text = des.des_decrypt(key, encrypted_text, block_size)

print('Source text: ', source_text)
print('Encrypted text: ', encrypted_text)
print('Decrypted text: ', decrypted_text)