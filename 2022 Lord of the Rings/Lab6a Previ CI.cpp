#include <xc.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"
#include "GLCD.h"
#define __XTAL_FREQ 8000000

int dc = 60, a = 0, b = 0;
int altura = 7;

void pintaBarra() {
    clearGLCD(0,0,0,127);
    for(int i = 0; i < altura; i++) {
        for(int j = 0; j < dc; j++) {
            SetDot(i,j);
        }
    }
    writeNum(0, 20, dc);
}

void sumar() {
    for(int i = 0; i < altura; i++) {
        setDot(i, dc);
    }
    clearGLCD(0,0,100,110);
    writeNum(0, 20, dc);
}

void restar() {
    for(int i = 0; i < altura; i++) {
        clearDot(i, dc);
    }
    clearGLCD(0,0,100,110);
}

void calcularDC() {
    int x = 5 * dc;
    CCPR1L = x/4;
    CCP1CONbits.DC1B1 = (x % 4) >> 1;
    CCP1CONbits.DC1B0 = x % 2;
}
void writeTXT() {}


void main() {
    // ANSELA = 0x00;
    // ANSELB = 0x00;
    // ANSELC = 0x00;
    // ANSELD = 0x00;
    // ANSELE = 0x00;

    // TRISB = 0x00;
    // TRISD = 0x00;

    // PORTB = 0x00;
    // PORTD = 0x00;
    
    ANSELA = 0;
    TRISAbits.RA0 = 1;
    TRISAbits.RA1 = 1;
    
    ANSELC = 0;
    TRISCbits.RC2 = 0;

    T2CONbits.T2CKPS1 = 1;
    T2CONbits.T2CKPS0 = 0;
    PR2 = 124;

    CCPR1L = 50;
    CCP1CONbits.DC1B1 = 0;
    CCP1CONbits.DC1B0 = 0;
    

    
    CCPTMRS0bits.C1TSEL = 0b00;
    CCP1CONbits.CCP1M = 0b1100;

    T2CONbits.TMR2ON = 1;

    GLCDinit();
    clearGLCD(0,7,0,127);
    pintaBarra();

    while (1) {
        if(PORTAbits.RA0 == 1 && a == 0) {
            sumar();
            ++dc;
            calcularDC();
        }
        if(PORTAbits.RA1 == 1 && b == 0) {
            restar();
            --dc;
            calcularDC();

        }
        a = PORTAbits.RA0;
        b = PORTAbits.RA1;
    }
}
