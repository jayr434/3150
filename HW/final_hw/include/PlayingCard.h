#pragma once
#include "Card.h"
#include <string>

class PlayingCard : public Card {
protected:
    std::string suit_;
    int rank_;
public:
    PlayingCard(const std::string& suit, int rank);
    static std::string rankToString(int rank);
    int value() const override;
    void print(std::ostream& os) const override;
};
