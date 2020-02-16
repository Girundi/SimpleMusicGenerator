#pragma once
#include "stdafx.h"
#include "scale.h"
#include <iostream>
#include <vector>


Scale::Scale(unsigned dominant, ScaleType st)
{
	this->dominant = dominant;
	this->st = st;
	this->scaleGenerate();
}


void Scale::scaleGenerate()
{
	switch (st)
	{
	case ScaleType::MINOR:
		scaleNotes.resize(8);
		scaleNotes[0] = dominant;
		scaleNotes[1] = dominant - 2;
		scaleNotes[2] = dominant - 3;
		scaleNotes[3] = dominant - 5;
		scaleNotes[4] = dominant - 7;
		scaleNotes[5] = dominant - 8;
		scaleNotes[6] = dominant - 10;
		scaleNotes[7] = dominant - 12;
		break;

	case ScaleType::MAJOR:
		scaleNotes.resize(8);
		scaleNotes[0] = dominant;
		scaleNotes[1] = dominant - 2;
		scaleNotes[2] = dominant - 4;
		scaleNotes[3] = dominant - 5;
		scaleNotes[4] = dominant - 7;
		scaleNotes[5] = dominant - 9;
		scaleNotes[6] = dominant - 11;
		scaleNotes[7] = dominant - 12;
		break;

	case ScaleType::PHRYGIAN:
		scaleNotes.resize(8);
		scaleNotes[0] = dominant;
		scaleNotes[1] = dominant - 1;
		scaleNotes[2] = dominant - 3;
		scaleNotes[3] = dominant - 5;
		scaleNotes[4] = dominant - 7;
		scaleNotes[5] = dominant - 8;
		scaleNotes[6] = dominant - 10;
		scaleNotes[7] = dominant - 12;
		break;

	case ScaleType::DJENTCLASSIC:
		scaleNotes.resize(2);
		scaleNotes[0] = dominant;
		scaleNotes[1] = dominant - 2;
		break;

	case ScaleType::DJENTPHRYG:
		scaleNotes.resize(2);
		scaleNotes[0] = dominant;
		scaleNotes[1] = dominant - 1;
		break;

	case ScaleType::N00LY:
		scaleNotes.resize(1);
		scaleNotes[0] = dominant;
		break;

	case ScaleType::DEMIURGE:
		scaleNotes.resize(2);
		scaleNotes[0] = dominant;
		scaleNotes[1] = dominant - 12;
		break;

	case ScaleType::PENTA:
		scaleNotes.resize(6);
		scaleNotes[0] = dominant;
		scaleNotes[1] = dominant - 3;
		scaleNotes[2] = dominant - 5;
		scaleNotes[3] = dominant - 8;
		scaleNotes[4] = dominant - 10;
		scaleNotes[5] = dominant - 12;
		break;

	}
}

std::vector<unsigned> const& Scale::getScale()
{
	return this->scaleNotes;
}

