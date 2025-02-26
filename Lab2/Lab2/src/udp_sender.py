import socket
import time


# Completati cu adresa IP a platformei ESP32
PEER_IP = "192.168.89.40"
PEER_PORT = 10002

MESSAGE = b"GPIO4="
i = 0

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
while 1:
    try:
        user_input = input("LED STATE: ")
        state = "1" if user_input != "0" else "0"

        TO_SEND = MESSAGE + state.encode()
        sock.sendto(TO_SEND, (PEER_IP, PEER_PORT))
        print("Am trimis mesajul: ", TO_SEND)
        i = i + 1
        # time.sleep(1)
    except KeyboardInterrupt:
        break