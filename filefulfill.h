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
	
	const byte NumOpen = 0x90;	//Номер канала у открытых нот
	const byte NumClose = 0x80;	//Номер каналы у закрытых нот
	unsigned patch[16] = { 0, 0 ,0, 0, 0, 0, 0, 0 ,0 ,0, 0, 0, 0, 0, 0 ,0 };
	vector<unsigned> notes[16];
	vector<byte> bnotes;
	//Установление номера канала при открытии ноты
	byte setNumOpen(int input);
	//Установление номера канала при закрытии ноты
	byte setNumClose(int input);

	//Перевод чисел в char
	byte ToByte(int in);

	//Запись дельта-времини ноты в формате переменной длины
	byte* changableLength(int notetime);


	//Добавление ноты: notecode - код ноты, delay - время, прошедшее с прошлого события, bnotes - место, куда записываются все события
	void addNote(int notecode, int delay, unsigned patch, int channel);

	//Закрытие ноты
	void closeNote(int notecode, int delay, unsigned patch, int channel);

	void notesConvert(); //заполнение bnotes


public:

	vector<byte> file;
	
	void doTheMusic(int bpm);

	//Название файла со всеми проверками

	void settingFilename(char* newname);

	//Формирование файла

	errno_t formFile();

	void input(vector<unsigned> in, int ch, unsigned pa);
	
	void playing();

	void pausing();

	void stoping();
};
#endif 
