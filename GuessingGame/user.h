#ifndef USER_H
#define USER_H

#include<string>
#include"guessinggame.h"

class User : public GuessingGame
{
public:
    bool checkGuess(const std::string &) const;
    bool checkAnswer(const std::string &) const;
};

#endif // USER_H
