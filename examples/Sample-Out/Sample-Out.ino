#include <mm5451seg.h>
#define MM5451_CLK 8
#define MM5451_DATA 9

//MM5451SEG segs(MM5451_CLK, MM5451_DATA);
MM5451SEG segs; // SET CLK & DATA Pins

void setup() {

  // Show Welcome Message
  // -------------------------------
  segs.setSTRtoSEG ("=YPA=");
  //segs.setSTRtoSEG ("=YPA=", false); // if you don't want print, only store in SEGs-Array (mySEG)
  //segs.write(); // Print SEGs-Array
}

void loop() {
  
  delay(1000);
  
  // Print Digits
  // -------------------------------
  for (int i = 10; i >= -10; i--)
    {
    segs.setINTtoSEG(i); 
    //segs.setINTtoSEG (i, false); // if you don't want print, only store in SEGs-Array (mySEG)
    //segs.write(); // Print SEGs-Array
    delay(700);
    }
  
  delay(1000);

  // Clear SEGs-Array & SEGs
  // -------------------------------
  segs.clear(); // Use false as parameter for not print
  delay(1000);
  
  // Print Char
  // -------------------------------
  segs.setCHRtoSEG(5, 'C'); // 5-SEG (Right-To-Left) set "C"
  segs.write(); // Print SEGs-Array content
  delay(500);
  for (int i=4; i>=2; i--) {segs.setCHRtoSEG(i, 'O');} // From 4 to 2 SEGs set "O"
  segs.write(); // Print SEGs-Array content
  delay(500);
  segs.setCHRtoSEG(1, 'L', true, true); // Set 1st SEG use codepage (3rd parameter) and re-print result

  delay(2000);
  
  // Print Bytes without codepage
  // -------------------------------
  // Fill start data
  segs.setCHRtoSEG(1, 0b10101000, false);
  segs.setCHRtoSEG(2, 0b10000100, false);
  segs.setCHRtoSEG(3, 0b10100000, false);
  segs.setCHRtoSEG(4, 0b10000100, false);
  segs.setCHRtoSEG(5, 0b10100010, false, true); // Fill & print All SEGs
  
  delay(1000);  
  
}
