#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MASTER_BASE_VECTOR 0xA8
#define SLAVE_BASE_VECTOR 0x08


struct VIDEO {
	unsigned char symbol;
	unsigned char attribute;
};

//IRQ0-IRQ7
void interrupt(*oldInt08) (...); //прерывание интеравального таймера (18.2)
void interrupt(*oldInt09) (...); //прерывание от клавиатуры
void interrupt(*oldInt0A) (...); //каскадное подключение второго контроллера
void interrupt(*oldInt0B) (...); //прерывание COM2
void interrupt(*oldInt0C) (...); //прерывание COM1
void interrupt(*oldInt0D) (...); //прерывание параллельного порта LPT2
void interrupt(*oldInt0E) (...); //прерывание контроллера флоппи-дисководов
void interrupt(*oldInt0F) (...); //прерывание параллельного порта LPT1

//IRQ8-IRQ15
void interrupt(*oldIntA8) (...); //прерывание часов реального времени
void interrupt(*oldIntA9) (...); //прерывание контроллера EGA
void interrupt(*oldIntAA) (...); //прерывание контроллера видеоадаптера
void interrupt(*oldIntAB) (...); //свободен
void interrupt(*oldIntAC) (...); //прерывание мыши PS/2
void interrupt(*oldIntAD) (...); //прерывание математического сопроцессора
void interrupt(*oldIntAE) (...); //прерывание первого контроллера жесткого диска
void interrupt(*oldIntAF) (...); //прерывание второго контроллера жесткого диска

void print() {
	char temp;
	int i, val;
	VIDEO far* screen = (VIDEO far*)MK_FP(0xB800, 0);

	screen += 9;
	val = inp(0x21);
	for (i = 0; i < 8; i++)
	{
		temp = val % 2;
		val = val >> 1;
		screen->symbol = temp + '0';
		screen++;
	}
	screen++;

	val = inp(0xA1);
	for (i = 0; i < 8; i++)
	{
		temp = val % 2;
		val = val >> 1;
		screen->symbol = temp + '0';
		screen++;
	}
	screen += 54;
	outp(0x20, 0x0A);

	screen += 9;
	val = inp(0x20);
	for (i = 0; i < 8; i++)
	{
		temp = val % 2;
		val = val >> 1;
		screen->symbol = temp + '0';
		screen++;
	}
	screen++;

	outp(0xA0, 0x0A);
	val = inp(0xA0);
	for (i = 0; i < 8; i++)
	{
		temp = val % 2;
		val = val >> 1;
		screen->symbol = temp + '0';
		screen++;
	}
	screen += 54;

	screen += 9;
	outp(0x20, 0x0B);
	val = inp(0x20);
	for (i = 0; i < 8; i++)
	{
		temp = val % 2;
		val = val >> 1;
		screen->symbol = temp + '0';
		screen++;
	}
	screen++;

	outp(0xA0, 0x0B);
	val = inp(0xA0);
	for (i = 0; i < 8; i++)
	{
		temp = val % 2;
		val = val >> 1;
		screen->symbol = temp + '0';
		screen++;
	}

}

void interrupt newInt08(...) { print(); oldInt08(); }
void interrupt newInt09(...) { print(); oldInt09(); }
void interrupt newInt0A(...) { print(); oldInt0A(); }
void interrupt newInt0B(...) { print(); oldInt0B(); }
void interrupt newInt0C(...) { print(); oldInt0C(); }
void interrupt newInt0D(...) { print(); oldInt0D(); }
void interrupt newInt0E(...) { print(); oldInt0E(); }
void interrupt newInt0F(...) { print(); oldInt0F(); }

void interrupt newIntA8(...) { print(); oldIntA8(); }
void interrupt newIntA9(...) { print(); oldIntA9(); }
void interrupt newIntAA(...) { print(); oldIntAA(); }
void interrupt newIntAB(...) { print(); oldIntAB(); }
void interrupt newIntAC(...) { print(); oldIntAC(); }
void interrupt newIntAD(...) { print(); oldIntAD(); }
void interrupt newIntAE(...) { print(); oldIntAE(); }
void interrupt newIntAF(...) { print(); oldIntAE(); }


void init() {
	oldInt08 = getvect(0x08);
	oldInt09 = getvect(0x09);
	oldInt0A = getvect(0x0A);
	oldInt0B = getvect(0x0B);
	oldInt0C = getvect(0x0C);
	oldInt0D = getvect(0x0D);
	oldInt0E = getvect(0x0E);
	oldInt0F = getvect(0x0F);

	oldIntA8 = getvect(0x70);
	oldIntA9 = getvect(0x71);
	oldIntAA = getvect(0x72);
	oldIntAB = getvect(0x73);
	oldIntAC = getvect(0x74);
	oldIntAD = getvect(0x75);
	oldIntAE = getvect(0x76);
	oldIntAF = getvect(0x77);

	setvect(MASTER_BASE_VECTOR, newInt08);
	setvect(MASTER_BASE_VECTOR + 1, newInt09);
	setvect(MASTER_BASE_VECTOR + 2, newInt0A);
	setvect(MASTER_BASE_VECTOR + 3, newInt0B);
	setvect(MASTER_BASE_VECTOR + 4, newInt0C);
	setvect(MASTER_BASE_VECTOR + 5, newInt0D);
	setvect(MASTER_BASE_VECTOR + 6, newInt0E);
	setvect(MASTER_BASE_VECTOR + 7, newInt0F);

	setvect(SLAVE_BASE_VECTOR, newIntA8);
	setvect(SLAVE_BASE_VECTOR + 1, newIntA9);
	setvect(SLAVE_BASE_VECTOR + 2, newIntAA);
	setvect(SLAVE_BASE_VECTOR + 3, newIntAB);
	setvect(SLAVE_BASE_VECTOR + 4, newIntAC);
	setvect(SLAVE_BASE_VECTOR + 5, newIntAD);
	setvect(SLAVE_BASE_VECTOR + 6, newIntAE);
	setvect(SLAVE_BASE_VECTOR + 7, newIntAF);

	_disable();

	outp(0x20, 0x11);
	outp(0x21, MASTER_BASE_VECTOR);
	outp(0x21, 0x04);
	outp(0x21, 0x01);

	outp(0xA0, 0x11);
	outp(0xA1, SLAVE_BASE_VECTOR);
	outp(0xA1, 0x02);
	outp(0xA1, 0x01);

	_enable();
}


int main() {
	system("cls");

	unsigned far* fp;
	init();

	printf("Mask:\n");
	printf("Request:\n");
	printf("Service:\n");
	printf("         Master        Slave");

	FP_SEG(fp) = _psp;
	FP_OFF(fp) = 0x2c;
	_dos_freemem(*fp);

	_dos_keep(0, (_DS - _CS) + (_SP / 16) + 1);
	
	return 0;
}
