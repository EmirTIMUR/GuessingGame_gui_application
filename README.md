# GuessingGame
Geliştirilen yazılımda bilgisayar ile kullanıcı arasında oynanan bir oyun mevcuttur. Yazılım ve kullanıcı rakamları birbirinden farklı 4 basamaklı bir sayı tutacaklar(‘0’ ile başlayabilir). Yazılım, kullanıcının tahmin ettiği sayıyı bulmaya, kullanıcı da bilgisayarın tahmin ettiği sayıyı bulmaya çalışacak. Tahminler sonucunda tutulan sayı ile ilgili ipuçları verilecek. Eğer tahmin edilen sayı içinde tutulan sayının rakamlarından varsa ve basamak değeri doğruysa “+” değer olarak ipucu verilecek, basamak değeri yanlış ise “-” değer ipucu olarak verilecektir. Örneğin bilgisayar 5483 sayısını tutsun ve kullanıcı 3468 tahmini yaptığında 4 sayısının basamak değeri doğru olduğu için +1, 3 ve 8 sayısının basamak değeri yanlış olduğu için -2 değeri dönülecektir.

## Installation
Terminale aşağıdaki komutu girip, kaynak kodu elde edebilirsiniz. 
```bash
git clone https://github.com/EmirTIMUR/GuessingGame_gui_application.git
```
Terminale aşağıdaki komutları girip, programı çalıştırabilirsiniz.
```bash
cd GuessingGame_gui_application
./game
```
## Usage
```bash
./game
```
Komutu ile programı çalıştırdıktan sonra **BAŞLA** butonuna tıklayarak oyunu başlatabilirsiniz. Kullanıcının 4 haneli rakamları birbirinden farklı tahminler yapması gerekmektedir, aksi taktirde doğru formatta tahmin yapana kadar program yeni tahminler isteyecektir. Aynı zamanda kullanıcı, bilgisayarın yaptığı tahminlere cevap verirken cevabın **+x,-y** formatında olduğuna dikkat etmeli, aksi takdirde yeni cevap istenecektir. Doğru formatta fakat yanlış puanlanmış bir cevapda oyun yenilenecektir.
</br>
</br>
Yanlış puanlama gibi bir durum olmadıkça oyunun sonunda kimin kazandığı bildirilecektir.
