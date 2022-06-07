import socket
from threading import Thread


SERVER_HOST = "127.0.0.1"
SERVER_PORT = 5002
separator = "<--***-->"

sockets = set()

# TCP socket
s = socket.socket()

s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((SERVER_HOST, SERVER_PORT))
s.listen(5)

print(f"*** Started to listen on  {SERVER_HOST}:{SERVER_PORT} ...")


def listen_for_client(socket_):
    while True:
        try:
            msg = socket_.recv(1024).decode()
        except Exception as e:
            print(f"* error occurred: {e}")
            sockets.remove(socket_)
        else:
            msg = msg.replace(separator, ": ")

        for socket in sockets:
            socket.send(msg.encode())


while True:
    socket, address = s.accept()
    print(f"*** New client on {address} connected.")

    sockets.add(socket)
    t = Thread(target=listen_for_client, args=(socket,))
    t.daemon = True
    t.start()


# for cs in sockets:
#     cs.close()
#
# s.close()