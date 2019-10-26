// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <algorithm>
#include <string>
#include <iomanip>
#define BITS_IN_ON_MEM (sizeof(TELEM)*8)
TBitField::TBitField(int len)
{
	if (len <= 0)
		throw "Bad length of array";
	BitLen = len;
	MemLen = (len-1) / BITS_IN_ON_MEM + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	if(pMem!=NULL)
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n > BitLen))
		throw "Index is incorrect";
	else
	{
		int temp = n / BITS_IN_ON_MEM;
		return temp;
	}
  return 0;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n > BitLen))
		throw "Index is incorrect";
	else
	{
		int temp =  (n % BITS_IN_ON_MEM);
		TELEM mask = 1;
		mask = (mask << temp);
		return mask;
	}
	return 0;
  
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return (BitLen);
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n<0) || (n>BitLen))
		throw "Index is incorrect";
	else
	{
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n<0 || n>BitLen)
		throw "Index is incorrect";
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen))
		throw n;
	else
	{
		int m = GetMemIndex(n); // ищем ячейку
		TELEM mask = GetMemMask(n); // маска на эту ячейку
		int result = (mask & pMem[m]);
		if (result == 0)
			return(0);
		else
			return(1);
		
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen]; 
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	else
	{
		for (int i = 0; i < MemLen; i++)
			if (GetBit(i) != bf.GetBit(i))
				return 0;
		return 1;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 1;
	else
	{
		for (int i = 0; i < BitLen; i++)
			if (GetBit(i) != bf.GetBit(i))
				return 1;
		return 0;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	
	int len;

	(bf.BitLen <= BitLen) ? (len = BitLen) : (len = bf.BitLen);

	TBitField tmp(len);

	for (int i = 0; i < MemLen; i++)

		tmp.pMem[i] = pMem[i];

	for (int i = 0; i < bf.MemLen; i++)

		tmp.pMem[i] |= bf.pMem[i];

	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	
	int len;

	(bf.BitLen <= BitLen) ? (len = BitLen) : (len = bf.BitLen);

	TBitField tmp(len);

	for (int i = 0; i < MemLen; i++)

		tmp.pMem[i] = pMem[i];

	for (int i = 0; i < bf.MemLen; i++)

		tmp.pMem[i] &= bf.pMem[i];

	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = ~pMem[i];
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	while ((i >= 0) && (i < bf.BitLen))
	{
		bf.SetBit(i);
		istr >> i;
	}
	return istr;
}


ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << i <<" ";
	return ostr;
}
