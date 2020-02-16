#ifndef MELODY_H
#define MELODY_H

#include <vector>
#include <stdlib.h>

class Melody
{
private:
    std::vector<unsigned> scaleNotes;
    unsigned numerator;
    unsigned tactsNumber;
    unsigned notesNumber;
    std::vector<unsigned> riff;
    unsigned noteChance;
    unsigned inbetweenChance;

    bool fortuna(unsigned chance);

public:
    Melody( std::vector<unsigned> scaleNotes, unsigned numerator = 4, unsigned tactsNumber = 4, unsigned noteChance = 80, unsigned inbetweenChance = 30);

    std::vector<unsigned> const& getMelody();

    void generateSolo();

    void generateRiff(unsigned tactsNumber = 2);

    std::vector<unsigned> generateInterval(unsigned interval = 7);
};

#endif // MELODY_H
