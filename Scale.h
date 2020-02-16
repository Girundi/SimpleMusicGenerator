#pragma once
#ifndef SCALE_H
#define SCALE_H

#include <vector>
//#include<iostream>
#include "note.h"

enum class ScaleType { MINOR, MAJOR, DJENTCLASSIC, N00LY, PHRYGIAN, DJENTPHRYG, DEMIURGE, PENTA };
class Scale
{
private:
	unsigned dominant;
	ScaleType st;
	std::vector<unsigned> scaleNotes;
	void scaleGenerate();


public:
	Scale(unsigned dominant = 13, ScaleType st = ScaleType::MINOR);
	std::vector<unsigned> const& getScale();
};

#endif // SCALE_H
