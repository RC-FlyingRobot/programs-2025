#include <xc.h>

// CONFIG1
#pragma config FOSC = INTOSC    
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config MCLRE = ON       
#pragma config CP = OFF         
#pragma config CPD = OFF        
#pragma config BOREN = ON       
#pragma config CLKOUTEN = OFF   
#pragma config IESO = ON        
#pragma config FCMEN = ON       

// CONFIG2
#pragma config WRT = OFF        
#pragma config PLLEN = ON       
#pragma config STVREN = ON      
#pragma config BORV = LO        
#pragma config DEBUG = OFF      
#pragma config LVP = OFF        

#define _XTAL_FREQ 1000000

void __interrupt() ISR(void) {
    // 赤外線センサー（RB0）で割り込み
    if (INTF && RB0 == 0) {  
        __delay_ms(5);  // ノイズ対策
        if (RB0 == 0) {  // チャタリング防止
            INTF = 0;  // 割り込みフラグクリア
            RA1 = 1;   // LED ON
            __delay_ms(500); // 0.5秒待機
            RA1 = 0;   // LED OFF
        }
    }

    // サーボ入力（RB1）で割り込み
    if (RBIF && (RB1 == 0)) {  
        __delay_ms(5);  // ノイズ対策
        if (RB1 == 1) {  // 再確認
            RBIF = 0;  // 割り込みフラグクリア
            
            // サーボを開く（90°）
            for (int i = 0; i < 250; i++)
            {
                RB3 = 1;
                __delay_us(1450);

                RB3 = 0;
                __delay_us(18550);
            }

            __delay_ms(5000);  // 5秒待つ

            // サーボを閉じる（0°）
            for (int i = 0; i < 250; i++)
            {
                RB3 = 1;
                __delay_us(500);

                RB3 = 0;
                __delay_us(18550);
            }
        }
    }
}

void main(void) {
    // ピン設定
    TRISA = 0b00000000; // RA1（LED）を出力に設定
    TRISB = 0b00001011; // RB0（赤外線入力）、RB1（サーボ入力）を入力、RB3（サーボ出力）を出力に設定

    ANSELA = 0b00000000; // 全ピンをデジタルI/Oに設定
    ANSELB = 0b00000000; // 全ピンをデジタルI/Oに設定

    WPUBbits.WPUB0 = 1;  // RB0にプルアップを有効化（赤外線入力）
    WPUBbits.WPUB1 = 1;  // RB1にプルアップを有効化（サーボ入力）
    OPTION_REGbits.nWPUEN = 0; // プルアップ機能を有効にする

    OSCCONbits.IRCF = 0b1011;   // 1MHzクロック設定

    // 割り込み設定
    INTE = 1;    // 外部割り込み有効（RB0）
    INTEDG = 0;  // 下降エッジ（HIGH → LOW で割り込み）
    RBIE = 1;    // RBポートの割り込み有効（RB1用）
    PEIE = 1;    // 周辺機能割り込み有効
    GIE = 1;     // グローバル割り込み有効

    while(1){
        // メインループではサーボの自動制御を行わず、割り込みで処理
    }
}
