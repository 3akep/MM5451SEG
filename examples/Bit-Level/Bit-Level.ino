#include <mm5451seg.h>
#define MM5451_CLK 8
#define MM5451_DATA 9

//MM5451SEG segs(MM5451_CLK, MM5451_DATA);
MM5451SEG segs; // SET CLK & DATA Pins

void setup() {

  // Show Welcome Message
  // -------------------------------
  segs.setSTRtoSEG ("=YPA=");

}

void loop() {
  
  delay(1000);
  
  // Print Bytes without codepage
  // -------------------------------
  // Fill start data
  segs.setCHRtoSEG(1, 0b10101000, false);
  segs.setCHRtoSEG(2, 0b10000100, false);
  segs.setCHRtoSEG(3, 0b10100000, false);
  segs.setCHRtoSEG(4, 0b10000100, false);
  segs.setCHRtoSEG(5, 0b10100010, false, true); // Fill & print All SEGs
  
  delay(1000);

  // Low-Level work with SEG-Arrays
  // -------------------------------
  int cycle = 10;
  byte cur_bit;
  
  while (cycle >= 0)
  { // SEGs in Array start from 0
    // seg_array - Array with number bits for each SEG
    // mySEG - SEG-Array contain BITs
    for (int i = 0; i< 5; i++)
    {
      cur_bit = segs.seg_array[i][4];
      segs.mySEG[cur_bit] = abs(segs.mySEG[cur_bit]-1);
      cur_bit = segs.seg_array[i][1];
      segs.mySEG[cur_bit] = abs(segs.mySEG[cur_bit]-1);
      if (i == 0)
        {
          cur_bit = segs.seg_array[i][3];
          segs.mySEG[cur_bit] = abs(segs.mySEG[cur_bit]-1);
          cur_bit = segs.seg_array[i][2];
          segs.mySEG[cur_bit] = abs(segs.mySEG[cur_bit]-1);
        }
      if (i == 4)
        {
          cur_bit = segs.seg_array[i][5];
          segs.mySEG[cur_bit] = abs(segs.mySEG[cur_bit]-1);
          cur_bit = segs.seg_array[i][0];
          segs.mySEG[cur_bit] = abs(segs.mySEG[cur_bit]-1);
        }
    }
    cycle--;
    segs.write(); // Print SEGs-Array (mySEG)
    delay(700);
  }
  
  delay(1000);
  segs.clear();
  // Low-level Example #2
    for (int i = 5; i > 0; i--)
    {
      cur_bit = 0b10000010;
      segs.setCHRtoSEG(i, cur_bit, false, true);
      delay(300);
      bitWrite(cur_bit, 2, 1);
      segs.setCHRtoSEG(i, cur_bit, false, true);
      delay(300);
      bitWrite(cur_bit, 3, 1);
      segs.setCHRtoSEG(i, cur_bit, false, true);
      delay(300);
      bitWrite(cur_bit, 0, 1);
      segs.setCHRtoSEG(i, cur_bit, false, true);
      delay(300);
      bitWrite(cur_bit, 6, 1);
      segs.setCHRtoSEG(i, cur_bit, false, true);
      delay(300);
      bitWrite(cur_bit, 5, 1);
      segs.setCHRtoSEG(i, cur_bit, false, true);
      delay(300);
      bitWrite(cur_bit, 4, 1);
      segs.setCHRtoSEG(i, cur_bit, false, true);
      delay(300);
    }
  
  delay(1000);  
  
  // Low-level Example #3  
  segs.clear();  
  
  for(int i=1; i <= 5; i++ )   
  {    
    cur_bit = 0b10000000;
    for (int j=0; j<=6; j++)
    {        
      bitWrite(cur_bit, j, 1);
      segs.setCHRtoSEG(i, cur_bit, false, true);
      delay(200);
    }
  }
  
}
