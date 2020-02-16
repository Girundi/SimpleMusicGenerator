#pragma once
#ifndef PATTERNS
#define PATTERNS

class patterns
{
private:
	vector<unsigned>  solo;
	vector<unsigned> lead;
	vector<unsigned> bass;
	vector<unsigned> sdrum;
	vector<unsigned> wdrum;
	void emptyspace(vector<unsigned> input);

public:
	bool check[5] = { false, false, false, false, false }; // 0 - lead, 1 - bass, 2 - solo, 3 - drums
	void readlead(vector<unsigned> input);
	void readsolo(vector<unsigned> input);
	void readbass(vector<unsigned> input);
	void readdrum(vector<unsigned> input1, vector<unsigned> input2);
	vector<unsigned> notes[16];
	void convert(unsigned pattern);
};
#endif PATTERNS