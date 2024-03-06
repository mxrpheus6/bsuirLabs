#include <stdio.h>
#include <dos.h>

void init_COM1() {
    outp(0x3FB, 0x80);
    outp(0x3F8, 0x0C);
    outp(0x3F9, 0x00);
    outp(0x3FB, 0x03);
    outp(0x3FA, 0xC7);
}
void init_COM2() {
    outp(0x2FB, 0x80);
    outp(0x2F8, 0x0C);
    outp(0x2F9, 0x00);
    outp(0x2FB, 0x03);   
    outp(0x2FA, 0xC7);
}

void write_byte(char data) {
    while ((inp(0x3FD) & 0x20) == 0);
    outp(0x3F8, data);
}

char read_byte() {
    while ((inp(0x2FD) & 0x01) == 0);
    return inp(0x2F8);
}

int main() {
    init_COM1();
    init_COM2();
    write_byte('C');
    char chr = read_byte();
    printf("Byte recieved: %c", chr);

    return 0;
}
