            AREA Assignment4, CODE, READONLY
            ENTRY                               ; r1 = sum, r2 = upc address, r3 = UPC 'digit', r4 = loop counter, r5 = even/odd register
	        
            ADR r2, UPC                         ; point for the UPC string
            MOV r4, #UPCLENGTH                     ; set counter for the length of the UPC string
            MOV r7, #THREE                      ; init multiplier for the odd digits
			                                    
sum         SUBS r4, #ONE                       ; decrease coutner so loop runs for length of string
            LDRB r3, [r2], #ONE                 ; load the next digit into r3
            AND r3, r3, #FIRSTDIGIT            ; convert the digit to from ascii to hex
            ANDS r5, r4, #FIRSTBIT             ; get the first bit, use r5 to check if even or odd
            ADDEQ r1, r3                        ; if r5 is 0, its even so add digit to sum variable
            MLANE r1, r3, r7, r1                ; if r5 is 1, its odd so x3 and add digit to sum variable 
            CMP r4, #ZERO                       ; check if counter is 0 which means loop is done
            BNE sum                             ; loop if counter is not 0, exit otherwise
												
divide      SUBS r1, #TEN                       ; r1-10, check if divisible
            CMP r1, #ONE                        ; compare the sum to 1 to use PL, check if sum <= 0
            BPL divide                          ; if >=0 go back to loop, otherwise we know sum < 0
			
            CMP r1, #ZERO                       ; compare r1 to 0 to check if the division was successful
            MOVEQ r0, #ONE                      ; if suuccessful, UPC code is correct
            MOVLT r0, #ZERO                     ; otherwise the UPC code is incorrect
Loop        B    Loop                           ; endless loop to finish

UPC         DCB "999999999999"                  ; a upc code
FIRSTBIT   EQU 2_1                             ; AND bits for first bit to determine if even/odd
FIRSTDIGIT EQU 0xF                             ; AND bits for first digit of an ASCII number
ZERO        EQU 0                               ; zero 
ONE         EQU 1                               ; one 
THREE       EQU 3                               ; three
TEN         EQU 10                              ; ten
UPCLENGTH      EQU 12                              ; length of upc code

	
            END