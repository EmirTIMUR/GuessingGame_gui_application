#ifndef GUESSINGGAME_H
#define GUESSINGGAME_H

#include<string>

class GuessingGame
{
public:
    virtual std::string getScore(const std::string &, const std::string &) const final;
    bool check(const std::string &) const;

    static const size_t LEN; // 4 basamaklı tahmin için bir sabit
};

#endif // GUESSINGGAME_H
