from django.shortcuts import render
from django.views.generic import View
from django.http import HttpResponse
import socket

# Haberleşme IP Belirlenmesi :
haberlesme_ip = "127.0.0.1"
# Haberleşme Portunun Belirlenmesi :
haberlesme_port = 12000

# Haberleşme Protokollerinin Belirlenmesi :
socket_server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# AF_INET -> İnternet alanı için ayarlama
# SOCK_DGRAM -> Protokol tipi UDP


# Create your views here.
class SatrancView(View):
    def create_div(self, pair):
        if pair[0] == 'B':
            return '<div class="blackMan">' + pair[1] + '</div>'
        elif pair[0] == 'W':
            return '<div class="whiteMan">' + pair[1] + '</div>'
        else:
            return ''

    def get(self, request):
        socket_server.sendto(b'Arda Mavi', (haberlesme_ip, haberlesme_port))
        # Tahta Bilgisi :
        gelen_veri, adres = socket_server.recvfrom(10000)
        tahta = gelen_veri.decode()
        tahta = tahta.split("\n")
        for index in range(7):
            del tahta[0]

        for index in range(5):
            del tahta[10]

        array = []

        for input in tahta[1:-1]:
            i = 0

            arr = []

            while i < 8:
                arr.append(['',''])
                i += 1

            i = 0

            for index in range(13,len(input)-3):
                if input[index] == " " and input[index+2] == " ":
                    if input[index-2] == "0":
                        arr[i][0] = "B"
                    elif input[index-2] == "7":
                        arr[i][0] = "W"
                    else:
                        arr[i][0] = "E"

                    arr[i][1] = input[index+1]
                    i+=1

            array.append(arr)

        tahta = []
        letter = 'a'
        color = "black"
        number = 1

        while number != 9:
            if letter == 'a':
                div = '<div class="location">' + str(number) + '</div>'
                tahta.append(div)
            position = str(number) + letter
            div = '<div class="' + color + '" id="' + position + '">' + self.create_div(array[number - 1][ord(letter) - ord('a')]) + '</div>'
            tahta.append(div)
            if color == "black": color = "white"
            elif color == "white": color = "black"
            letter = chr(ord(letter) + 1)
            if letter == 'i':
                div = '<div class="location">' + str(number) + '</div>'
                tahta.append(div)
                if color == "black": color = "white"
                elif color == "white": color = "black"
                number += 1
                letter = 'a'

        return render(request, 'base.html', {'tahta': tahta})

    def post(self, request):

        tas_konum = request.POST['tasKonum']
        gidilecek_yer = request.POST['oynanacakYer']


        # Paketin Gönderilmesi :
        socket_server.sendto(tas_konum.encode('utf-8'), (haberlesme_ip, haberlesme_port))

        # Tahta Bilgisi :
        gelen_veri, adres = socket_server.recvfrom(10000)

        if tas_konum != "kısa rok" and tas_konum != "uzun rok":
            # Paketin Gönderilmesi :
            socket_server.sendto(gidilecek_yer.encode('utf-8'), (haberlesme_ip, haberlesme_port))

            # Tahta Bilgisi :
            gelen_veri, adres = socket_server.recvfrom(10000)

        tahta = gelen_veri.decode()

        print(tahta)

        tahta = tahta.split("\n")

        del tahta[0]

        if "Hatalı Giriş !" not in tahta:
            for index in range(5):
                del tahta[10]
        else:
            for index in range(7):
                del tahta[10]

        array = []

        for input in tahta[1:-1]:
            i = 0

            arr = []

            while i < 8:
                arr.append(['',''])
                i += 1

            i = 0

            for index in range(13,len(input)-3):
                if input[index] == " " and input[index+2] == " ":
                    if input[index-2] == "0":
                        arr[i][0] = "B"
                    elif input[index-2] == "7":
                        arr[i][0] = "W"
                    else:
                        arr[i][0] = "E"

                    arr[i][1] = input[index+1]
                    i+=1

            array.append(arr)

        tahta = []
        letter = 'a'
        color = "black"
        number = 1

        while number != 9:
            if letter == 'a':
                div = '<div class="location">' + str(number) + '</div>'
                tahta.append(div)
            position = str(number) + letter
            div = '<div class="' + color + '" id="' + position + '">' + self.create_div(array[number - 1][ord(letter) - ord('a')]) + '</div>'
            tahta.append(div)
            if color == "black": color = "white"
            elif color == "white": color = "black"
            letter = chr(ord(letter) + 1)
            if letter == 'i':
                div = '<div class="location">' + str(number) + '</div>'
                tahta.append(div)
                if color == "black": color = "white"
                elif color == "white": color = "black"
                number += 1
                letter = 'a'

        return render(request, 'board.html', {'tahta': tahta})
