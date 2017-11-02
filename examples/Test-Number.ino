#include <mm5451seg.h>
#define MM5451_CLK 8
#define MM5451_DATA 9

//MM5451SEG segs(MM5451_CLK, MM5451_DATA);
MM5451SEG segs; // SET CLK & DATA Pins

void setup() {

  // Show Welcome Message
  // -------------------------------
  segs.setSTRtoSEG ("TEST");
  delay(5000);
  // Data print to Serial
  Serial.begin(9600);
}

void loop() {

  segs.clear();
  Serial.println("Begin TEST...");
  
  // Test number of segment
  //----------------------------
  for (int i=0; i < 35; i++)
    {
    segs.mySEG[i] = 1;  
    segs.write();
    Serial.println(i);
    delay(1000);
    }
  
  Serial.println("...END!");
}
