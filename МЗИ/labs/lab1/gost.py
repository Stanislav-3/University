def _crypt(part, key, sbox):
    temp = part ^ key
    output = 0

    for i in range(8):
        output |= ((sbox[i][(temp >> (4 * i)) & 0b1111]) << (4 * i))

    return ((output >> 11) | (output << (32 - 11))) & 0xFFFFFFFF


def encrypt(plain_msg, key, sbox):
    def encrypt_round(left_part, right_part, round_key):
        return right_part, left_part ^ _crypt(right_part, round_key, sbox)

    subkeys = [(key >> (32 * i)) & 0xFFFFFFFF for i in range(8)]
    left_part = plain_msg >> 32
    right_part = plain_msg & 0xFFFFFFFF

    for i in range(24):
        left_part, right_part = encrypt_round(left_part, right_part, subkeys[i % 8])

    for i in range(8):
        left_part, right_part = encrypt_round(left_part, right_part, subkeys[7 - i])

    return (left_part << 32) | right_part


def decrypt(crypted_msg, key, sbox):
    def decrypt_round(left_part, right_part, round_key):
        return right_part ^ _crypt(left_part, round_key, sbox), left_part

    subkeys = [(key >> (32 * i)) & 0xFFFFFFFF for i in range(8)] 
    left_part = crypted_msg >> 32
    right_part = crypted_msg & 0xFFFFFFFF

    for i in range(8):
        left_part, right_part = decrypt_round(left_part, right_part, subkeys[i])

    for i in range(24):
        left_part, right_part = decrypt_round(left_part, right_part, subkeys[(7 - i) % 8])

    return (left_part << 32) | right_part 
