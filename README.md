# Web-Satranc
## Arda Mavi - [ardamavi.com](http://www.ardamavi.com/)

C++, Python 3 ve Django ile yaptığım web için bir satranç oyunudur.

#### Bilgisayarınızda Projeyi Çalıştırmak :
Projenin çalışması için SatrançProgramı dosyası içerisindeki C++ oyununun derlenmesi lazım bu nedenle projeye bir make file eklenmiştir.

C++ Satranç Programı : [github.com/ardamavi/Satranc](https://github.com/ardamavi/Satranc)

Django kullandığımız için bilgisayarınıza Django kurmayı unutmayınız.

C++ Satranç Programını Derleme Ve Çalıştırma: <br />
(Compiling And Running)<br />
##### Derleme :
(Compiling)<br />
1. `SatrancProgrami/Satranc` dizine giriniz. <br />
2. Kodları derlemek için `make` yazmanız yeterli.<br />
3. Derleme sonrasında SatrancProgrami dizininde `Satranc` diye uygulamamız oluştu.<br />

##### Uygulamayı çalıştırmak için :
Django kullandığımızdan manage.py dosyasını kullanarak Server'ı başlatmamız gerekli.
`python3 manage.py runserver` Komutu ile Server'i başlatabiliriz.

İnternet sayfası ile C++ programımızın iletişimini sağlamak amacıyla sProcess uygulamamızı başlatmamız gerekli.
Daha sonra sProcess.py 'u çalıştırıyoruz.
sProcess uygulaması başladığında Satranç oyunumuzuda başlatılacaktır.
`python3 sProcess.py` Komutu ile sProcess uygulamamızı çalıştırabiliriz.

### Hazırlanma Sürecinde :
Atom(Editor), Xcode (IDE), g++(derleyici), Python 3.5, C++ ve Mac Terminal (Sürüm 2.6.1 (361.1)) kullanılmıştır.
