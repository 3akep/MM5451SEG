/*
  MM5451SEG
*/
#ifndef mm5451seg_h

#define mm5451seg_h

#include "Arduino.h"

class MM5451SEG   
{
  private:
    int CLK = 8;      // to MM5451 pin 21
    int dataPin = 9;  // to MM5451 pin 22

    void CLKpulse (); // Clock Generator
    void zeroFill (); // Fill by Zeros
    byte CHRtoBIT (char); // Convert CHAR to Byte with 0-6 bits
                           
  public:
    MM5451SEG (int _clk = 8, int _data = 9); // Init & Define CLK & DATA pins
    void clear (bool print = true); // Clear mySEG & SEGments (optional)
    void write (); // Send mySEG Array via DATA-pin to MM5451
    byte getBYTEfromSEG (int); // Get BYTE from mySEG with some SEG-number
    void setCHRtoSEG (int, char, bool codepage = true, bool print = false); // Set CHAR (if use codepage)/BYTE to SEG with some NUMber & Show (optional)
    void setINTtoSEG (long, bool print = true); // Store 5-element INT to SEGs & Show (optional)
    void setSTRtoSEG (String, bool print = true); // Store 5-element CHAR to SEGs & Show (optional)

    // Array of SEGments (RTL) - 5SEGs
    int seg_array[5][7] = {{ 6,  7,  8,  9, 10, 11, 12}, //1SEG     5
                           { 3,  4,  5, 13, 14, 15, 16}, //2SEG   6    4            
                           { 0,  1,  2, 18, 17, 19, 20}, //3SEG     7
                           {32, 33, 34, 21, 22, 23, 24}, //4SEG   1    3
                           {29, 30, 31, 25, 26, 27, 28}};//5SEG     2   
    
    byte mySEG[35];
};
#endif