#pragma once
#ifndef FILEFULFILL
#define FILEFULFILL

#include <stdio.h>
#include <vector>
#include <bitset>

using namespace std;

typedef unsigned char byte;


class FileFulfill
{
private:
	char filename[500];
	FILE* fp;
	
	const byte NumOpen = 0x90;	//����� ������ � �������� ���
	const byte NumClose = 0x80;	//����� ������ � �������� ���
	unsigned patch[16] = { 0, 0 ,0, 0, 0, 0, 0, 0 ,0 ,0, 0, 0, 0, 0, 0 ,0 };
	vector<unsigned> notes[16];
	vector<byte> bnotes;
	//������������ ������ ������ ��� �������� ����
	byte setNumOpen(int input);
	//������������ ������ ������ ��� �������� ����
	byte setNumClose(int input);

	//������� ����� � char
	byte ToByte(int in);

	//������ ������-������� ���� � ������� ���������� �����
	byte* changableLength(int notetime);


	//���������� ����: notecode - ��� ����, delay - �����, ��������� � �������� �������, bnotes - �����, ���� ������������ ��� �������
	void addNote(int notecode, int delay, unsigned patch, int channel);

	//�������� ����
	void closeNote(int notecode, int delay, unsigned patch, int channel);

	void notesConvert(); //���������� bnotes


public:

	vector<byte> file;
	
	void doTheMusic(int bpm);

	//�������� ����� �� ����� ����������

	void settingFilename(char* newname);

	//������������ �����

	errno_t formFile();

	void input(vector<unsigned> in, int ch, unsigned pa);
	
	void playing();

	void pausing();

	void stoping();
};
#endif 
