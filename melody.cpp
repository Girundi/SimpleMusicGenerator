#include "melody.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Melody::Melody(std::vector<unsigned> scaleNotes, unsigned numerator, unsigned tactsNumber, unsigned noteChance, unsigned inbetweenChance)
{
    this->scaleNotes = scaleNotes;
    this->numerator = numerator;
    this->tactsNumber = tactsNumber;
    this->notesNumber = numerator * tactsNumber * 2;
    this->riff = std::vector<unsigned>(this->notesNumber, 0);
    this->noteChance = noteChance;
    this->inbetweenChance = inbetweenChance;
}

std::vector<unsigned> const& Melody::getMelody()
{
    return this->riff;
}

void Melody::generateSolo()
{
    std::srand(time(NULL));

    for (size_t i = 0; i < this->notesNumber; i += 2)
    {
        if (std::rand()%100 < noteChance)
        {
            this->riff[i] = scaleNotes[std::rand()%this->scaleNotes.size()];
        }
    }

    for (size_t i = 1; i < this->notesNumber; i += 2)
    {
        if (std::rand()%100 < inbetweenChance && riff[i-1] != 0)
        {
            this->riff[i] = scaleNotes[std::rand()%this->scaleNotes.size()];
        }
    }
}

void Melody::generateRiff(unsigned tactsNumber)
{
    std::srand(time(NULL));
    size_t riffLength = tactsNumber*numerator*2;
    std::vector<unsigned> riff(riffLength, 0);

    for (size_t i = 0; i < riffLength; i += 2)
    {
        if (std::rand()%100 < noteChance)
        {
            riff[i] = scaleNotes[std::rand()%this->scaleNotes.size()];
        }
    }

    for (size_t i = 1; i < riffLength; i += 2)
    {
        if (std::rand()%100 < inbetweenChance && riff[i-1] != 0)
        {
            riff[i] = scaleNotes[std::rand()%this->scaleNotes.size()];
        }
    }

    for (size_t i = 0; i < notesNumber; i++)
    {
        this->riff[i] = riff[i % riffLength];
    }
}

std::vector<unsigned> Melody::generateInterval(unsigned interval)
{
    std::vector<unsigned> newTrack(notesNumber, 0);

    for (size_t i = 0; i < notesNumber; i++)
    {
        if(riff[i] - interval == 0 || riff[i] - interval > 127 )
        {
            newTrack[i] = riff[i];
        }
        else
        {
            newTrack[i] = riff[i] - interval;
        }
    }

    return newTrack;
}
