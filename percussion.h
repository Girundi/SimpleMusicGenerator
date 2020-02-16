#ifndef PERCUSSION_H
#define PERCUSSION_H

#include <vector>

class Percussion
{
private:
    unsigned notesNumber, weakDominant, strongDominant, numerator;
    std::vector<unsigned> strong;
    std::vector<unsigned> weak;

public:
    Percussion(unsigned strongDominant = 50, unsigned weakDominant = 51, unsigned numerator = 4, unsigned tactsNumber = 4);
    std::vector<unsigned> const& getStrong();
    std::vector<unsigned> const& getWeak();
    std::vector<unsigned> getBlast();
};

#endif // PERCUSSION_H
