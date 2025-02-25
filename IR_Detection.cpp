#include <xc.h>

// PIC16F1827の設定 (クロックやWDTの無効化など)
#pragma config FOSC = INTOSC    // 内部オシレータを使用
#pragma config WDTE = OFF       // ウォッチドッグタイマー無効
#pragma config PWRTE = OFF      // パワーオンリセット無効
#pragma config MCLRE = OFF      // MCLRピン無効
#pragma config CP = OFF         // コードプロテクト無効
#pragma config BOREN = OFF      // ブラウンアウトリセット無効
#pragma config CLKOUTEN = OFF   // CLKOUTピン無効
#pragma config IESO = OFF       // 外部・内部オシレータ切り替え無効
#pragma config FCMEN = OFF      // フェイルセーフクロック監視無効

#define _XTAL_FREQ 1000000

void main(void) {
    TRISA = 0b0000001;
    TRISB = 0b00000000;
    ANSELA = 0b00000000;
    ANSELB = 0b00000000;
    OSCCONbits.IRCF = 0b1011;
    
    while (1) {
        if (RA0 == 0) { // OSRB38C9AAは赤外線検出時に LOW になる
            RA1 = 1; // LED ON
            __delay_ms(500);    //500ms = 0.5s待つ
            RA1 = 0;
            __delay_ms(500);
        } else {
            RA1 = 0; // LED OFF
        }
    }

    return;
}