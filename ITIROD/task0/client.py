import socket
from threading import Thread
from datetime import datetime


SERVER_HOST = "127.0.0.1"
SERVER_PORT = 5002
separator = "<--***-->"

# TCP socket
s = socket.socket()
print(f"*** Connecting to {SERVER_HOST}:{SERVER_PORT}...")
s.connect((SERVER_HOST, SERVER_PORT))
print("*** Done! Connected!!!!!")

name = input("Enter your name: ")


def listen_for_messages():
    while True:
        message = s.recv(1024).decode()
        n = message.split('| ')[1].split(separator)[0]
        if not n.startswith(name):
            print("\n" + message)

t = Thread(target=listen_for_messages)
t.daemon = True
t.start()

while True:
    message = input()

    if message == '~':
        break

    time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    message = f"{time} | {name}{separator}{message}"

    s.send(message.encode())

s.close()