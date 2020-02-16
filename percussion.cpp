#include "percussion.h"

Percussion::Percussion(unsigned strongDominant, unsigned weakDominant, unsigned numerator, unsigned tactsNumber)
{
    this->numerator = numerator;
    this->strongDominant = strongDominant;
    this->weakDominant = weakDominant;
    notesNumber = numerator * tactsNumber * 2;
    strong = std::vector<unsigned>(notesNumber, 0);
    weak = std::vector<unsigned>(notesNumber, 0);
}

std::vector<unsigned> const& Percussion::getStrong()
{
    for (unsigned i = 0; i < notesNumber; i += 2)
    {
        strong[i] = strongDominant;
    }
    return strong;
}

std::vector<unsigned> const& Percussion::getWeak()
{
    for (unsigned i = 0; i < notesNumber; i += (numerator*2))
    {
        weak[i] = weakDominant;
    }
    return weak;
}

std::vector<unsigned> Percussion::getBlast()
{
    std::vector<unsigned> blast(notesNumber, 0);
    for (unsigned i = 0; i < notesNumber; i++)
    {
        blast[i] = strongDominant;
    }
    return blast;
}
