#include <xc.h>

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config DEBUG = OFF      // In-Circuit Debugger Mode (In-Circuit Debugger disabled, ICSPCLK and ICSPDAT are general purpose I/O pins)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)


#define _XTAL_FREQ 1000000


void __interrupt() ISR(void) {
    if (INTF) {  // 外部割り込み（RA0がLOW）
        INTF = 0;  // 割り込みフラグクリア
        RA1 = 1;   // LED ON
        __delay_ms(500); // 0.5秒待機
        RA1 = 0;   // LED OFF
    }
}

void main(void) {
    TRISA = 0b00100001;
    TRISB = 0b00000001;
    ANSELA = 0b00000000;
    ANSELB = 0b00000000;
    WPUB = 0b00000001; // RB0をプルアップする
    OPTION_REGbits.nWPUEN = 0;//プルアップ機能を有効にする
    OSCCONbits.IRCF = 0b1011;   // 1MHz

    // 割り込み設定
    INTE = 1;    // 外部割り込み有効
    INTEDG = 0;  // 下降エッジ（LOWで割り込み）
    PEIE = 1;    // 周辺機能割り込み有効
    GIE = 1;     // グローバル割り込み有効


    while(1){
        if(RB0 == 1){ // 90°      
            RB3 = 1;
            __delay_us(1450);
            RB3 = 0;
            __delay_us(18550);
        }
        else { // 0°
            RB3 = 1;
            __delay_us(500);
            RB3 = 0;
            __delay_us(18550);
        }
    }
    
    return;
}