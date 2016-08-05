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



        for string in tahta:
            yeni_s = ""

            renk_geldi = False
            renk_str = ""
            char_counter = 0
            char_geldi = False
            for s in string:
                if renk_geldi and renk_str in ['[97m', '[44m', '[46m', '[106m', '[30m']:
                    renk_geldi = False
                    if renk_str == '[97m':
                        yeni_s += '<span style="color:#ececec">'
                    elif renk_str == '[44m':
                        yeni_s += '<span style="background-color:#1c28bd">'
                    elif renk_str == '[46m':
                        yeni_s += '<span style="background-color:#37a7b8">'
                    elif renk_str == '[30m':
                        yeni_s += '<span style="color:#081115">'
                    elif renk_str == '[106m':
                        yeni_s += '<span style="background-color:#38e4e4">'
                    char_geldi = True
                    renk_str = ""
                    if s == "\x1b":
                        renk_geldi = True
                        char_geldi = False
                    else:
                        yeni_s += s
                    continue
                elif renk_geldi:
                    renk_str += s
                    continue
                if char_geldi and char_counter < 2:
                    yeni_s += s
                    char_counter += 1
                    if char_counter == 2:
                        yeni_s += '</span>'
                        char_counter = 0
                        char_geldi = False
                    continue
                if s == "\x1b":
                    renk_geldi = True
                else:
                    yeni_s += s

            string = yeni_s
            print(string)

        for t in tahta:
            t = t + "<br>"

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

        if "Hatalı Giriş !" not in tahta:
            for index in range(5):
                del tahta[10]
        else:
            for index in range(7):
                del tahta[10]

        tahta = [w.replace(w, w + "</span>") for w in tahta]

        tahta = [w.replace('[46m', '''<span style="background-color:#37a7b8">''') for w in tahta] # BG_COLOR1
        tahta = [w.replace('[106m', '''<span style="background-color:#38e4e4">''') for w in tahta] # BG_COLOR2
        tahta = [w.replace('[44m', '''<span style="background-color:#1c28bd">''') for w in tahta] # BG_CERCEVE
        tahta = [w.replace('[30m', '''<span style="color:#081115">''') for w in tahta] # FG_TASSIYAH
        tahta = [w.replace('[97m', '''<span style="color:#ececec">''') for w in tahta] # FG_TASBEYAZ
        tahta = [w.replace('[44m', '''<span style="background-color:#1c28bd">''') for w in tahta] # BG_BLUE

        return render(request, 'satranc.html', {'tahta': tahta} )
