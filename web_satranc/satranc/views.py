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

        return render(request, 'satranc.html', {'tahta': tahta})

    def post(self, request):

        tas_konum = request.POST['tasKonum']
        gidilecek_yer = request.POST['oynanacakYer']


        # Paketin Gönderilmesi :
        socket_server.sendto(tas_konum.encode('utf-8'), (haberlesme_ip, haberlesme_port))

        # Tahta Bilgisi :
        gelen_veri, adres = socket_server.recvfrom(10000)

        # Paketin Gönderilmesi :
        socket_server.sendto(gidilecek_yer.encode('utf-8'), (haberlesme_ip, haberlesme_port))

        # Tahta Bilgisi :
        gelen_veri, adres = socket_server.recvfrom(10000)

        tahta = gelen_veri.decode()

        tahta = tahta.split("\n")

        del tahta[0]

        for index in range(5):
            del tahta[10]

        print(tahta)

        #gelen_veri = ""

        return render(request, 'satranc.html', {'tahta': tahta} )
