#include<algorithm>
#include<string>
#include<array>
#include<algorithm>
#include"user.h"

using namespace std;

//kullanıcının yaptığı tahminin '(0123456789)' gibi rakamlardan oluşup olmadığını kontrol eden fonksiyon.
bool User::checkGuess(const string &guess) const
{
    string digits = "0123456789";
    bool error = false;

    if (guess.size() == 4)
    {
        if (GuessingGame::check(guess))
        {
            string::const_iterator itr;
            for (itr = guess.cbegin(); itr != guess.cend(); ++itr)
            {
                if (count(digits.cbegin(), digits.cend(), *itr) == 0)
                    error = true;
            }
            if (!error)
                return true;
        }
    }

    return false;
}

//kullanıcının, bilgisayarın tahminine verdiği cevabın doğru formatta olup olmadığını kontrol eden fonksiyon.
bool User::checkAnswer(const string &answer) const
{
    const array<string, 14> possibleAnswer{"00", "01", "02", "03", "04",
                                            "10", "11", "12", "13",
                                            "20", "21", "22", "30", "40"};

    if (answer[0] == '+' && answer[2] == ',' && answer[3] == '-')
    {
        string str = "";
        str.push_back(answer[1]);
        str.push_back(answer[4]);

        if (count(possibleAnswer.cbegin(), possibleAnswer.cend(), str) == 1)
            return true;
    }

    return false;
}
