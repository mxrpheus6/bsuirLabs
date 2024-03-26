#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <iostream.h>


int frequencies[] = { 349, 392, 440, 349, 440, 440, 392, 349, 392 };

int duration[] =    { 600, 300, 600, 300, 300, 300, 300, 300, 300 };

void sound(int frequency, int time) {
    //int cnt;

    // b6 = 10100110 - channel 2, operation 4, mode = 3
    outp(0x43, 0xB6);  //timer mode 2

    long signal = 1193180;
    long cnt = signal / frequency;
    //cnt = (int)(1193180L / frequency);
    //out two bits of port 42h
    outp(0x42, cnt % 256);
    cnt /= 256;
    outp(0x42, cnt);

    //enable system speaker, 3 = 00000011
    outp(0x61, inp(0x61) | 3);

    delay(time);

    //disable system speaker, fc = 11111100
    outp(0x61, inp(0x61) & 0xFC);
}

void state_channel() {
    unsigned char temp;
    char* string = new char[9];
    unsigned i;

    //state word 0
    //e2 = 11100010
    outp(0x43, 0xE2);

    temp = inp(0x40); // получение слова состояния канала
    itoa(temp, string, 2);
    cout << "Channel 0 state word: " << string << endl;

    //state word 1
    //e4 = 11100100
    outp(0x43, 0xE4);

    temp = inp(0x41);
    itoa(temp, string, 2);
    cout << "Channel 1 state word: " << string << endl;

    //state word 2
    //e8 = 11101000
    outp(0x43, 0xE8);

    temp = inp(0x42);
    itoa(temp, string, 2);
    cout << "Channel 2 state word: " << string << endl;

    free(string);
}

void print_counter(int channel) {
    unsigned char controlWord = 0xE2 | (channel << 1);
    outp(0x43, controlWord);

    unsigned short counter;
    outp(0x43, 0x00); // Чтение младшего байта
    counter = inp(0x40); // Младший байт
    counter |= (inp(0x40) << 8); // Старший байт

    cout << "Channel " << channel << " counter: " << hex << counter << endl;
}

int main() {
    for (int i = 0; i < 8; i++) {
        sound(frequencies[i], duration[i]);
    }
    state_channel();

    printf("\n");

    for (int j = 0; j < 3; j++) {
        print_counter(j);
    }

    return 0;
}
