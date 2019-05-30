#include<string>
#include<deque>
#include<cstdlib> // for rand() and srand()

#include"software.h"

using namespace std;

string Software::hiddenNumber = "";

Software::Software()
{
    createHiddenNumber(); // yazılım bir sayı saklıyor.
    fillSet(); // kullanıcının aklında tuttuğu muhtemel sayılar için bir havuz oluşturuluyor.
}

//yazılım bir sayı saklıyor.
void Software::createHiddenNumber(void)
{
    string temp = "";
    string digits = "0123456789";

    for (size_t i = 0; i < GuessingGame::LEN; ++i)
    {
        int x = rand() % digits.length();
        temp = temp + digits[x];
        digits.erase(x, 1);
    }

    hiddenNumber = temp;
}

//havuz dolduruluyor, '0' ile başlayan muhtemel sayılar da dahil.
void Software::fillSet(void)
{
    string number;

    for (size_t i = 123; i <= 9876; ++i)
    {
        if (i < 1000)
            number = "0" + to_string(i);
        else
            number = to_string(i);

        if (GuessingGame::check(number)) // rakam tekrarı olup olmadığı kontrol ediliyor.
            this->set.push_front(number);
    }
}

//yazılım, havuzdan rastgele bir sayı seçip tahminde bulunuyor.
string Software::makeGuess(void)
{
    return this->set[rand() % set.size()];
}

//bilgisayarın tahminine karşı kullanıcın verdiği cevaba göre 'havuz' budanıyor.
void Software::editSet(const std::string &guess, const std::string &answer)
{
    if (!set.empty())
        pruneTheSet(guess, answer);
}

/*
    havuzda bulunan sayılarla bilgisayarın tahmini karşılaştırılıyor.
    elde edilen 'cevap' ile kullanıcının verdiği cevap birbirine denk değilse
    havuzda bulunan o sayı, havuzdan siliniyor.
*/
void Software::pruneTheSet(const string &guess, const string &answer)
{
    deque<string>::iterator itr = this->set.begin();

    while (itr != set.end())
    {
        if (answer != GuessingGame::getScore(guess, *itr))
            itr = set.erase(itr);
        else
            ++itr;
    }
}

//kullanıcının tahminine karşı, yazılım cevap veriyor.
string Software::answerToGuess(const string &guess) const
{
    return GuessingGame::getScore(guess, getHiddenNumber());
}

//yazılımın sakladığı sayının elde edilmesini sağlayan fonksiyon.
string Software::getHiddenNumber(void)
{
    return hiddenNumber;
}

//hatalı puanlama sonucu, havuzun tamamen boşalıp boşalmadığını kontrol eden fonksiyon.
bool Software::isTheSetEmpty(void)
{
    if(set.empty())
        return true;
    else
        return false;
}
