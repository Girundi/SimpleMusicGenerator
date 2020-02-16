#include "stdafx.h"
#include "melody.h"
#include "Scale.h"
#include "filefulfill.h"
#include "Patterns.h"
#include <ctime>
#include <cstdlib>

using namespace std;

typedef unsigned char byte;

void patterns::readbass(vector<unsigned> input)
{
	check[1] = true;
	for (int i = 0; i < input.size(); ++i)
		bass.push_back(input[i]);	
}
void patterns::readlead(vector<unsigned> input)
{
	check[0] = true;
	for (int i = 0; i < input.size(); ++i)
		lead.push_back(input[i]);
}
void patterns::readsolo(vector<unsigned> input)
{
	check[2] = true;
	for (int i = 0; i < input.size(); ++i)
		solo.push_back(input[i]);
}
void patterns::readdrum(vector<unsigned> input1, vector<unsigned> input2)
{
	check[3] = true;
	check[4] = true;
	for (int i = 0; i < input1.size(); ++i)
		sdrum.push_back(input1[i]);
	for (int i = 0; i < input2.size(); ++i)
		wdrum.push_back(input2[i]);
}
void patterns::emptyspace(vector<unsigned> input)
{
	vector<unsigned> empty;

	for (int i = 0; i < 32; ++i)
		empty.push_back(0);

	for (int i = 0; i < empty.size(); ++i)
		input.push_back(empty[i]);
}
void patterns::convert(unsigned pattern) 
{
	if (pattern == 1) // all in one
	{
		if (check[1]) //bass
			for (int i = 0; i < bass.size(); ++i)
				notes[1].push_back(bass[i]);
		if (check[0]) //lead
			for (int i = 0; i < bass.size(); ++i)
				notes[0].push_back(bass[i]);
		if (check[2]) //solo
			for (int i = 0; i < bass.size(); ++i)
				notes[2].push_back(bass[i]);
		if (check[3])
			for (int i = 0; i < sdrum.size(); ++i)
			{
				notes[3].push_back(sdrum[i]);
				notes[4].push_back(wdrum[i]);
			}
	}
	else if (pattern == 2) // one after another
	{
		if (check[1])
			for (int j = 0; j < 4; ++j)
				for (int i = 0; i < bass.size(); ++i)
					notes[1].push_back(bass[i]);
		if (check[0])
		{
			emptyspace(notes[0]);
			for (int j = 0; j < 3; ++j)
				for (int i = 0; i < lead.size(); ++i)
					notes[0].push_back(lead[i]);
		}
		if (check[2])
		{
			for (int j = 0; j < 3; ++j)
				emptyspace(notes[2]);
			for (int i = 0; i < solo.size(); ++i)
				notes[2].push_back(solo[i]);
		}
		if (check[3])
		{
			for (int i = 0; i < 2; ++i)
			{
				emptyspace(notes[3]);
				emptyspace(notes[4]);
			}
			for (int i = 0; i < 1; ++i)
				for (int j = 0; j < sdrum.size(); ++j)
				{
					notes[3].push_back(sdrum[j]);
					notes[4].push_back(wdrum[j]);
				}
		}
	}
	else if (pattern == 3)  // too random
	{
		srand(time(NULL));
		vector<unsigned> patternscheme[4];
		
		int amount = rand() % 8 + 3;
		for (int j = 0; j < 4; ++j)
		{
			patternscheme[j].resize(amount);
			for (int i = 0; i < amount; ++i)
				if (check[j] == true)
					patternscheme[j][i] = rand() % 3;
		}
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < amount; ++j)
				if (patternscheme[i][j] == 0)
					emptyspace(notes[i]);
				else if (patternscheme[i][j] != 0)
					if (i == 0)
						for (int k = 0; k < lead.size(); ++k)
							notes[0].push_back(lead[k]);
					else if (i == 1)
						for (int k = 0; k < bass.size(); ++k)
							notes[1].push_back(bass[k]);
					else if (i == 2)
						for (int k = 0; k < solo.size(); ++k)
							notes[2].push_back(solo[k]);
					else if (i == 3)
						for (int k = 0; k < sdrum.size(); ++k)
						{
							notes[3].push_back(sdrum[k]);
							notes[4].push_back(wdrum[k]);
						}
	}
}