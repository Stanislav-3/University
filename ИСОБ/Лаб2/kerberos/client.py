import struct
import time

import des

from kdc.exceptions import AuthenticationError


class Client:
    def __init__(self, kdc):
        self._kdc = kdc
        self._id, self._key = kdc.register_client()
        self._tgs = None

    def connect(self, server):
        print(f'Client (C, id={self._id}): trying to connect to server (SS, id={server.id})')

        try:
            print('\t1:')
            print(f'\tC -> AS: sent client id ({self._id})')
            response = self._kdc.get_tgt((self._id,))
            print(f'\tC <- AS: received TGT and K_c_tgs: ({response})')
            response = des.decrypt(response, self._key)
            tgt = response[:-8]
            c_tgs, = struct.unpack("Q", response[-8:])

            now = int(time.time())
            aut = struct.pack("QQ", self._id, now)
            aut = des.encrypt(aut, c_tgs)

            print('\t3:')
            print('\tC -> TGS: sent TGT, Aut_1, and server id')
            response = self._kdc.get_tgs((tgt, aut, server.id))
            response = des.decrypt(response, c_tgs)
            tgs = response[:-8]
            k_c_ss, = struct.unpack("Q", response[-8:])
            print(f'\tC <- TGS: received:\n\t\tTGS={tgs}\n\t\tK_c_ss={k_c_ss}')

            now = int(time.time())
            aut = struct.pack("QQ", self._id, now)
            aut = des.encrypt(aut, k_c_ss)

            print('\t5:')
            print(f'\tC -> SS: sent TGS and Aut_2')
            response = server.start_session((tgs, aut))
            print(f'\tC <- SS: received incremented timestamp: {response}')
            response = des.decrypt(response, k_c_ss)
            inc_time, = struct.unpack("Q", response)

            if inc_time != now + 1:
                raise AuthenticationError('Server failed authentication')

            print(f'Client id={self._id}: Success connect to server with id={server.id}')

        except Exception as e:
            print(e)
