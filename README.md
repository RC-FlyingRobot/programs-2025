# programs-2025

## 2/27現状
- PICは赤外線でLEDを光らせるだけ
- サーボはfcから動かす
- よって使うのはIR_Detection.cpp

## PIN の割り当て

- RA1 : LED
- RA0 : 赤外線センサ

## コードを書き込む際のピン
PICkit3 – PIC16F1827
- 1 – 4
- 2 – 14
- 3 – 5
- 4 – 13
- 5 – 12

![pic_pin_numbers](https://github.com/user-attachments/assets/5d57365b-f9f2-4b84-a49a-10cc6645f2ce)
