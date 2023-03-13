     AREA prog, CODE, READONLY
     ENTRY
     MOV  r0, #6
     MOV  r1, #8
     NEG  r0, r0
	 NEG r1, r1
for  ADD r0, r0, r1  
	 ADDS r1, r1, #2
	 BLE for
halt B halt
     END