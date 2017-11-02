# MM5451SEG
Arduino Library for 7-Segment Display / LED Drivers (MM5451)

##Main functions of **MM5451SEG** Class

>int **mySEG[35]** - Bits array for send to Chip (MM5451)

>int **seg_array[5][7]** - Array of SEGment & Number for pins

>void **clear** (bool print = true); // Clear mySEG & SEGments (optional)

>void **write** (); // Send mySEG Array via DATA-pin to MM5451

>byte **getBYTEfromSEG** (int); // Get BYTE from mySEG with some SEG-number

>void **setCHRtoSEG** (int, char, bool codepage = true, bool print = false); // Set CHAR (if use codepage)/BYTE to SEG with some NUMber & Show (optional)

>void **setINTtoSEG** (long, bool print = true); // Store 5-element INT to SEGs & Show (optional)

>void **setSTRtoSEG** (String, bool print = true); // Store 5-element CHAR to SEGs & Show (optional)
