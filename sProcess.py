from subprocess import Popen, PIPE
import socket

# Haberleşme IP Belirlenmesi :
haberlesme_ip = "localhost"
# Haberleşme Portunun Belirlenmesi :
haberlesme_port = 12000

# Haberleşme Protokollerinin Belirlenmesi :
socket_server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# AF_INET -> İnternet alanı için ayarlama
# SOCK_DGRAM -> Protokol tipi UDP

process = Popen(['SatrancProgrami/./Satranc'], stdin=PIPE, stdout=PIPE)

byte_input = b''

socket_server.bind(('', haberlesme_port))

inp_string, adres = socket_server.recvfrom(1024)

while 1:

    byte_input = b''
    byte_char = process.stdout.read(1)
    while 1:
        byte_input += byte_char
        if b'Son' in byte_input:
            break
        if b'giriniz:' in byte_input:
            break
        byte_char = process.stdout.read(1)

    # Paketin Gönderilmesi :
    socket_server.sendto(byte_input, adres)

    if b'Son' in byte_input:
        break

    # Gelen verileri alma :
    # Gelen Veriyi Kaydetmek :
    inp_string, adres = socket_server.recvfrom(1024)
    # Buradaki 1024 gelen verinin en büyük boyutunu belirtir.

    process.stdin.write(inp_string + b'\n')
    process.stdin.flush()
