#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <vector>
#include <bitset>
#include "filefulfill.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
using namespace std;

typedef unsigned char byte;

	
	//Установление номера канала при открытии ноты
	byte FileFulfill::setNumOpen(int input)
	{
		byte result = NumOpen + input;
		return result;
	}
	//Установление номера канала при закрытии ноты
	byte FileFulfill::setNumClose(int input)
	{
		byte result = NumClose + input;
		return result;
	}

	//Перевод чисел в char
	byte FileFulfill::ToByte(int in)
	{
		byte y = static_cast<byte>(in);
		return y;
	};

	//Запись дельта-времини ноты в формате переменной длины
	byte* FileFulfill::changableLength(int notetime)
	{	//Всегда проверять входные данные на привышение 127. Числа меньше отправлять на decToHex или toByte


		if (notetime < 16384)
		{
			bitset<14> buf = notetime;
			bitset<7> buf1;
			bitset<7> buf2;
			bitset<8> op1;
			bitset<8> op2;
			op1[7] = 1;
			op2[7] = 0;
			byte newtime[2] = { 0, 0 };
			for (int i = 0; i < 7; ++i)
			{
				buf1[i] = buf[7 + i];
				buf2[i] = buf[i];
			}
			for (int i = 6; i >= 0; --i)
			{
				op1[i] = buf1[i];
				op2[i] = buf2[i];
			}
			newtime[0] = static_cast<byte>(op1.to_ulong());
			newtime[1] = static_cast<byte>(op2.to_ulong());
			return newtime;
		}
		else
		{
			bitset<21> buf = notetime;
			bitset<7> buf1;
			bitset<7> buf2;
			bitset<7> buf3;
			bitset<8> op1;
			bitset<8> op2;
			bitset<8> op3;
			op1[7] = 1;
			op2[7] = 1;
			op3[7] = 0;
			byte newtime[3] = { 0,0,0 };
			for (int i = 0; i < 7; ++i)
			{
				buf1[i] = buf[14 + i];
				buf2[i] = buf[7 + i];
				buf3[i] = buf[i];
			}
			for (int i = 6; i >= 0; --i)
			{
				op1[i] = buf1[i];
				op2[i] = buf2[i];
				op3[i] = buf3[i];
			}
			newtime[0] = static_cast<byte>(op1.to_ulong());
			newtime[1] = static_cast<byte>(op2.to_ulong());
			newtime[2] = static_cast<byte>(op3.to_ulong());
			return newtime;
		}

	};


	//Добавление ноты: notecode - код ноты, delay - время, прошедшее с прошлого события, bnotes - место, куда записываются все события
	void FileFulfill::addNote(int notecode, int delay, unsigned patch, int channel)
	{
		int vel;		//Выставление громкости
		if (patch < 7)
		{
			vel = 127;
		}
		else if (patch < 15)
		{
			vel = 90;
		}
		else if (patch < 31)
		{
			vel = 127;
		}
		else if (patch < 79)
		{
			vel = 90;
		}
		else if (patch < 103)
		{
			vel = 120;
		}
		else vel = 90;
		if (delay < 128)
		{
			byte byte4 = ToByte(vel);
			byte byte2 = setNumOpen(channel);
			byte byte3 = ToByte(notecode);
			byte byte1 = ToByte(delay);
			bnotes.push_back(byte1);
			bnotes.push_back(byte2);
			bnotes.push_back(byte3);
			bnotes.push_back(byte4);
		}
		else
		{
			byte* del = changableLength(delay);
			byte byte5 = ToByte(vel);
			byte byte3 = setNumOpen(channel);
			byte byte4 = ToByte(notecode);
			byte byte2 = del[1];
			byte byte1 = del[0];
			bnotes.push_back(byte1);
			bnotes.push_back(byte2);
			bnotes.push_back(byte3);
			bnotes.push_back(byte4);
			bnotes.push_back(byte5);
		}
	}

	//Закрытие ноты
	void FileFulfill::closeNote(int notecode, int delay, unsigned patch, int channel)
	{

		int vel;		//Выставление громкости
		if (patch < 7)
		{
			vel = 127;
		}
		else if (patch < 15)
		{
			vel = 90;
		}
		else if (patch < 31)
		{
			vel = 127;
		}
		else if (patch < 79)
		{
			vel = 90;
		}
		else if (patch < 103)
		{
			vel = 120;
		}
		else vel = 90;

		if (delay < 128)
		{
			byte byte4 = ToByte(vel);
			byte byte2 = setNumClose(channel);
			byte byte3 = ToByte(notecode);
			byte byte1 = ToByte(delay);
			bnotes.push_back(byte1);
			bnotes.push_back(byte2);
			bnotes.push_back(byte3);
			bnotes.push_back(byte4);
		}
		else
		{
			byte* del = changableLength(delay);
			byte byte5 = ToByte(vel);
			byte byte3 = setNumClose(channel);
			byte byte4 = ToByte(notecode);
			byte byte2 = del[1];
			byte byte1 = del[0];
			bnotes.push_back(byte1);
			bnotes.push_back(byte2);
			bnotes.push_back(byte3);
			bnotes.push_back(byte4);
			bnotes.push_back(byte5);
		}
	};

	void FileFulfill::notesConvert() //заполнение bnotes
	{
		int maxl = 0;
		bool check[16]; //проверка на конец вектора
		for (int i = 0; i < 16; ++i)
		{
			if (patch[i] != 0)
				check[i] = true;
			else check[i] = false;
			if (notes[i].size() > maxl)
				maxl = notes[i].size();
		}

		int extime = 0; //время с предыдущего события
		int step = 48; //шаг во времени

		for (int i = 0; i < maxl; ++i)
		{
			for (int j = 0; j < 16; ++j)
			{
				if (patch[j] != 0)
				{
					if ((i == 0)&&(notes[j][i] != 0))
					{
						addNote(notes[j][i], 0, patch[j], j);
						extime = 0;
					}
					else
					{
						if ((notes[j][i] != notes[j][i - 1]) && (notes[j][i] != 0) && (notes[j][i - 1] != 0))
						{
							closeNote(notes[j][i - 1], extime, patch[j], j);
							extime = 0;
							addNote(notes[j][i], extime, patch[j], j);
						}
						if ((notes[j][i - 1] == 0) && (notes[j][i] != 0))
						{
							addNote(notes[j][i], extime, patch[j], j);
							extime = 0;
						}
						if ((notes[j][i] == 0) && (notes[j][i - 1] != 0))
						{
							closeNote(notes[j][i - 1], extime, patch[j], j);
							extime = 0;
						}
						if ((i == notes[j].size() - 1) && (notes[j][i] != 0))
						{
							closeNote(notes[j][i], step, patch[j], j);
							extime = 0;
						}
					}
				}
			}
			extime += step;
		}

	};

	void FileFulfill::doTheMusic(int bpm)
	{
		notesConvert();
		file.resize(14);
		file = { 'M', 'T', 'h', 'd', 0x0, 0x0, 0x0, 0x6, 0x0, 0x1, 0x0, 0x1, 0x0, 0x60 };
		file.push_back('M'); file.push_back('T'); file.push_back('r'); file.push_back('k');
		if (bnotes.size() + 63 < 128)																				// LENGTH OF MTrk
		{
			file.push_back(0); file.push_back(0); file.push_back(0); file.push_back(ToByte(bnotes.size() + 63));
		}
		else if (bnotes.size() + 63 < 16384)
		{
			byte* length = changableLength(bnotes.size() + 63);
			file.push_back(0); file.push_back(0); file.push_back(length[0]); file.push_back(length[1]);
		}
		else
		{
			byte* length = changableLength(bnotes.size() + 63);
			file.push_back(0); file.push_back(length[0]); file.push_back(length[1]); file.push_back(length[2]);
		}

		int mlsec = 60 * 1000000 / bpm;
		byte tt[3];
		tt[0] = static_cast<byte>(mlsec / 0x10000);
		tt[1] = static_cast<byte>((mlsec % 0x10000) / 0x100);
		tt[2] = static_cast<byte>(mlsec % 0x100);

		file.push_back(0); file.push_back(0xFF); file.push_back(0x51); file.push_back(0x3); 
		file.push_back(tt[0]); file.push_back(tt[1]); file.push_back(tt[2]);

		const int ch = 0xC0;
		for (int i = 0; i < 16; ++i)
		{
			file.push_back(0); file.push_back(ch + i); file.push_back(patch[i]);
		}

		for (int i = 0; i < bnotes.size(); ++i) // Запись нот
			file.push_back(bnotes[i]);

		file.push_back(48);  file.push_back(0xFF); file.push_back(0x2F); file.push_back(0); // END OF TRACK
	}

	//Название файла со всеми проверками

	void FileFulfill::settingFilename(char* newname)
	{
		for (int i = 0; newname[i] != '\0', filename[i] != '\0'; ++i)
		{
			filename[i] = newname[i];
		}
	};

	//Формирование файла

	errno_t FileFulfill::formFile()
	{
		errno_t err2;
		err2 = fopen_s(&fp, "buffer.mid", "wb");
		fwrite(&file.at(0), 1, file.size(), fp);
		fclose(fp);
		return err2;
	};

	void FileFulfill::input(vector<unsigned> in, int ch, unsigned pa)
	{
		patch[ch] = pa;
		for (int i = 0; i < in.size(); ++i)
			notes[ch].push_back(in[i]);
	}

	void FileFulfill::playing()
	{
		wstring filic = L"play buffer.mid";
		DWORD result = mciSendStringW(filic.c_str(), NULL, 0, NULL);
	}
	void FileFulfill::pausing()
	{
		wstring filic = L"pause buffer.mid";
		DWORD result = mciSendStringW(filic.c_str(), NULL, 0, NULL);
	}
	void FileFulfill::stoping()
	{
		wstring filic = L"stop buffer.mid";
		DWORD result = mciSendStringW(filic.c_str(), NULL, 0, NULL);
	}