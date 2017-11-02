#include "mm5451seg.h"

// ----------------------------------
// Set pins & Start DATA
// ----------------------------------
MM5451SEG::MM5451SEG(int _clk, int _data) {
  
  CLK = _clk;      // Set CLK pin  (default: 8)
  dataPin = _data; // Set DATA pin (default: 9)  
  pinMode(CLK, OUTPUT);
  pinMode(dataPin, OUTPUT);
  // Init to Send DATA
  digitalWrite(CLK, HIGH);
  digitalWrite(dataPin, 1);
  zeroFill(); // Fill by zeros
  clear();
  
}
// ==================================

// ----------------------------------
// Clock Generator
// ----------------------------------
void MM5451SEG::CLKpulse() {

  digitalWrite (CLK, LOW);
  digitalWrite (CLK, HIGH);
    
}
// ==================================

// ----------------------------------
// Fill by Zeros
// ----------------------------------
void MM5451SEG::zeroFill() {

  digitalWrite (dataPin, LOW); // data bit LOW
  for(int x = 0; x < 35; x++) { CLKpulse (); }
  
}
// ==================================

// ----------------------------------
// Convert CHAR to Byte with 0-6 bits
// ----------------------------------
byte MM5451SEG::CHRtoBIT(char val) {

  byte myBit = 0b10000000;
  
  // Use codepage, if not in codepage return BYTE without modify
  switch (val){
    case 0: case '0': case 'O': myBit = 0b11111110; break;
    case 1: case '1': case '|': case 'I': myBit = 0b10011000; break;
    case 2: case '2': myBit = 0b11101101; break;
    case 3: case '3': myBit = 0b10111101; break;
    case 4: case '4': myBit = 0b10011011; break;
    ase 5: case '5': case 'S': case 's': myBit = 0b10110111; break;
    case 6: case '6': myBit = 0b11110111; break;
    case 7: case '7': myBit = 0b10011100; break;
    case 8: case '8': case 'B': myBit = 0b11111111; break;
    case 9: case '9': myBit = 0b10111111; break;
    case 'A': myBit = 0b11011111; break;
    case 'C': case '[': myBit = 0b11100110; break;
    case 'E': myBit = 0b11100111; break;
    case 'F': myBit = 0b11000111; break;
    case 'G': myBit = 0b11110110; break;
    case 'H': myBit = 0b11011011; break;
    case 'J': myBit = 0b11111000; break;
    case 'L': myBit = 0b11100010; break;
    case 'N': myBit = 0b11011110; break;
    case 'P': myBit = 0b11001111; break;
    case 'U': myBit = 0b11111010; break;
    case 'Y': myBit = 0b10111011; break;
    case '-': myBit = 0b10000001; break;
    case '=': myBit = 0b10100001; break;
    case 'o': myBit = 0b11110001; break;
    case 'b': myBit = 0b11110011; break;
    case 'c': myBit = 0b11100001; break;
    case 'd': case 'D': myBit = 0b11111001; break;
    case ']': myBit = 0b10111100; break;
    case ' ': myBit = 0b10000000; break;
    case 'h': myBit = 0b11010011; break;
    case 't': case 'T': myBit = 0b11100011; break;
    default:  myBit = val; break; // Return BYTE without modify
  }

  return myBit;
}
// ==================================

// ----------------------------------
// Send mySEG Array via DATA-pin to MM5451
// ----------------------------------
void MM5451SEG::write () {
  digitalWrite(dataPin, 1); //  Leading "1"
  CLKpulse(); // Clock Generator
  for(int x = 0; x < 35; x++)   {
    digitalWrite(dataPin, mySEG[x]);
    CLKpulse();
    }
  zeroFill();
}
// ==================================

// ----------------------------------
// Set CHAR/BYTE to SEG with some NUMber
// if CHAR not in CODEPAGE, use BYTE as BITs
// ----------------------------------
void MM5451SEG::setCHRtoSEG (int seg, char val, bool codepage, bool print) {

  int n_cur;

  //for 5 SEGments
  if ((seg <= 0) || (seg > 5)) seg = 1;
  for (int i=0; i<=6; i++)
    {
      n_cur = seg_array[seg-1][i];
      // Check Codepage usage
      if (codepage) { mySEG[n_cur] = bitRead(CHRtoBIT(val) , 6-i);}
        else { mySEG[n_cur] = bitRead(val , 6-i);} // Set BYTE without codepage
    }
  if (print) { write(); } // Print SEGs
}
// ==================================

// ----------------------------------
// Clear mySEG and Segments
// ----------------------------------
void MM5451SEG::clear(bool print) {

  for (int i = 1; i <= 5; i++) { setCHRtoSEG(i, ' '); } // Set Empty
  if (print) { write(); } //Clear SEGs
  
}
// ==================================

// ----------------------------------
// Store 5-element INT to SEGs
// ----------------------------------
void MM5451SEG::setINTtoSEG (long x , bool print) {

  bool n_status = false;
  byte int_mod = 0;
  byte n_seg = 1;
  
  // Check limit (temporary)
  if (x < 0) { n_status = true; x = abs(x); }
  if (x > 99999) { x = 99999; }
  if ((n_status) && (x > 9999)) { x = 9999; }
  
  while (x > 0) {
    int_mod = x % 10;
    setCHRtoSEG (n_seg, int_mod);
    n_seg++;
    x = x / 10;
  }
  
  // For Negative Int print minus sign
  if (n_status) { setCHRtoSEG (n_seg, '-'); n_seg++;}
  
  // Blank for emty SEGs
  while (n_seg <= 5) {
    setCHRtoSEG (n_seg, ' ');
    n_seg++;
  }
  
  if ((int_mod == 0)&&(x == 0)) { setCHRtoSEG (1, '0'); }
  
  if (print) { write(); } // Print SEGs
  
}
// ==================================

// ----------------------------------
// Store 5-element CHAR to SEGs
// ----------------------------------
void MM5451SEG::setSTRtoSEG (String x, bool print) {

  byte len = 0;
  char my_chr[6];
  // Get Length $ Store only Frist 5 Bytes
  len = x.length();
  x.toCharArray(my_chr, 6);
  if (len > 5) {len = 5;}
  
  // Store CHAR to SEGs-array
  for (int i = 0; i < len ; i++)
  {
    setCHRtoSEG (len-i, my_chr[i]);
  }

  // If String Length less than 5 SEGs - Blank Fill
  for (int i = 5; i > len; i--){
      setCHRtoSEG (i, ' ');
    }
  if (print) { write(); } // Print SEGs

}
// ==================================

// ----------------------------------
// Get BYTE from mySEG with some SEG-number
// ----------------------------------
byte MM5451SEG::getBYTEfromSEG (int seg) { 

  byte SEGbyte = 0b10000000;
  int n_cur;
  
  //for 5 SEGments
  if ((seg <= 0) || (seg > 5)) seg = 1;
  
  for (int i=0; i<=6; i++)
    {
      n_cur = seg_array[seg-1][i];
      bitWrite(SEGbyte, 6-i, mySEG[n_cur]);
    }
  return SEGbyte;
  
}
// ==================================
