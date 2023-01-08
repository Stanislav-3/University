from Crypto.Cipher.DES import key_size
import des

key = 'key'
block_size = 8
key_size = 16

key = des.prepare_des3_key(key, key_size)
iv = des.prepare_iv(block_size)

with open('source.txt', 'r') as file:
    source_text = file.read()

encrypted_text = des.des3_encrypt(key, iv, source_text)
decrypted_text = des.des3_decrypt(key, iv, encrypted_text)

print('Source: ', source_text)
print('Encrypted: ', encrypted_text)
print('Decrypted: ', decrypted_text)