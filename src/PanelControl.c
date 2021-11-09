/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
#include "PanelControl.h"
#include "definitions.h"

const int HORIZONTAL_PIXELS = 32;
const int VERTICAL_PIXELS = 32;
const int SCAN_RATE = 2;

void setColor1(int color,int p1,int p2);
void setColor2(int color,int p3,int p4);
void setColor3(int color,int p5,int p6);
void setColor4(int color,int p7,int p8);
void setAddress(int c,int row);

void panelOff(){
    OE_Set();
}

void panelOn1(uint8_t *addrBuffer,char color,int brightness){
    
    int upperPointer_1 = 0;
    int lowerPointer_1 = 64;
        
    for(int row = 0; row < 2; row++) {  
            
        setAddress(0,row);      
            
        for(int column = 0; column < 32; column++) {
               
            int pB1 = addrBuffer[upperPointer_1]; //upper half 8 pixels
            int pB2 = addrBuffer[lowerPointer_1]; //lower half 8 pixels
               
            for(int i = 7; i >= 0; i--) {
                    
                int p1 = (pB1 >> i) & 1;
                int p2 = (pB2 >> i) & 1;
                    
                setColor1(color,p1,p2);
                    
                CORETIMER_DelayUs(0.05);
                CLK_Set();
                CORETIMER_DelayUs(0.05);
                CLK_Clear();
            }
            upperPointer_1++;
            lowerPointer_1++;
        }
        CORETIMER_DelayUs(0.3);
        LATCH_Set();
        CORETIMER_DelayUs(0.3);
        LATCH_Clear();
        
        OE_Clear();
        CORETIMER_DelayUs(brightness);
        OE_Set();
    }
        for(int row = 0; row < 2; row++) {setAddress(1,row);}   
}

void panelOn2(uint8_t *addrBuffer,char color,int brightness){
       
    int upperPointer_1 = 0;
    int lowerPointer_1 = 64;
    int upperPointer_2 = 128;
    int lowerPointer_2 = 192;
    
    for(int row = 0; row < SCAN_RATE; row++) { 
            
        setAddress(0,row);
        
        for(int column = 0; column < HORIZONTAL_PIXELS; column++) { 
            
            int pB1 = addrBuffer[upperPointer_1]; 
            int pB2 = addrBuffer[lowerPointer_1]; 
            int pB3 = addrBuffer[upperPointer_2];
            int pB4 = addrBuffer[lowerPointer_2];
            
            for(int i = 7; i >= 0; i--) {
                    
                int p1 = (pB1 >> i) & 1;
                int p2 = (pB2 >> i) & 1;
                int p3 = (pB3 >> i) & 1;
                int p4 = (pB4 >> i) & 1; 
                
                setColor1(color,p1,p2);
                setColor2(color,p3,p4);
                
                CORETIMER_DelayUs(0.05);
                CLK_Set();
                CORETIMER_DelayUs(0.05);
                CLK_Clear(); 
            }
                upperPointer_1++;
                lowerPointer_1++;
                upperPointer_2++;
                lowerPointer_2++;
        }
        CORETIMER_DelayUs(0.3);
        LATCH_Set();
        CORETIMER_DelayUs(0.3);
        LATCH_Clear();
        
        OE_Clear();
        CORETIMER_DelayUs(brightness);
        OE_Set();
    }
    for(int row = 0; row < 2; row++) {setAddress(1,row);}         
}

void panelOn3(uint8_t *addrBuffer,char color,int brightness){

    int upperPointer_1 = 0;
    int lowerPointer_1 = 64;
    int upperPointer_2 = 128;
    int lowerPointer_2 = 192;
    int upperPointer_3 = 256;
    int lowerPointer_3 = 320;
    
    for(int row = 0; row < SCAN_RATE; row++) { 
            
        setAddress(0,row);
        
        for(int column = 0; column < HORIZONTAL_PIXELS; column++) { 
            
            int pB1 = addrBuffer[upperPointer_1]; 
            int pB2 = addrBuffer[lowerPointer_1]; 
            int pB3 = addrBuffer[upperPointer_2];
            int pB4 = addrBuffer[lowerPointer_2];
            int pB5 = addrBuffer[upperPointer_3];
            int pB6 = addrBuffer[lowerPointer_3];
            
            for(int i = 7; i >= 0; i--) {
                    
                int p1 = (pB1 >> i) & 1;
                int p2 = (pB2 >> i) & 1;
                int p3 = (pB3 >> i) & 1;
                int p4 = (pB4 >> i) & 1; 
                int p5 = (pB5 >> i) & 1;
                int p6 = (pB6 >> i) & 1;
                
                setColor1(color,p1,p2);
                setColor2(color,p3,p4);
                setColor3(color,p5,p6);
                
                CORETIMER_DelayUs(0.05);
                CLK_Set();
                CORETIMER_DelayUs(0.05);
                CLK_Clear();    
            }
            upperPointer_1++;
            lowerPointer_1++;
            upperPointer_2++;
            lowerPointer_2++;
            upperPointer_3++;
            lowerPointer_3++;
        }
        CORETIMER_DelayUs(0.3);
        LATCH_Set();
        CORETIMER_DelayUs(0.3);
        LATCH_Clear();
        
        OE_Clear();
        CORETIMER_DelayUs(brightness);
        OE_Set();
    }
    for(int row = 0; row < 2; row++) {setAddress(1,row);}
}

void panelOn4(uint8_t *addrBuffer,char color,int brightness){
  
    int upperPointer_1 = 0;
    int lowerPointer_1 = 64;
    int upperPointer_2 = 128;
    int lowerPointer_2 = 192;
    int upperPointer_3 = 256;
    int lowerPointer_3 = 320;
    int upperPointer_4 = 384;
    int lowerPointer_4 = 448;
    
    for(int row = 0; row < SCAN_RATE; row++) { 
            
        setAddress(0,row);
        
        for(int column = 0; column < HORIZONTAL_PIXELS; column++) { 
            
            int pB1 = addrBuffer[upperPointer_1]; 
            int pB2 = addrBuffer[lowerPointer_1]; 
            int pB3 = addrBuffer[upperPointer_2];
            int pB4 = addrBuffer[lowerPointer_2];
            int pB5 = addrBuffer[upperPointer_3];
            int pB6 = addrBuffer[lowerPointer_3];
            int pB7 = addrBuffer[upperPointer_4];
            int pB8 = addrBuffer[lowerPointer_4];
            
            for(int i = 7; i >= 0; i--) {
                    
                int p1 = (pB1 >> i) & 1;
                int p2 = (pB2 >> i) & 1;
                int p3 = (pB3 >> i) & 1;
                int p4 = (pB4 >> i) & 1; 
                int p5 = (pB5 >> i) & 1;
                int p6 = (pB6 >> i) & 1;
                int p7 = (pB7 >> i) & 1;
                int p8 = (pB8 >> i) & 1; 
                
                setColor1(color,p1,p2);
                setColor2(color,p3,p4);
                setColor3(color,p5,p6);
                setColor4(color,p7,p8);
                
                CORETIMER_DelayUs(0.05);
                CLK_Set();
                CORETIMER_DelayUs(0.05);
                CLK_Clear(); 
            }
            upperPointer_1++;
            lowerPointer_1++;
            upperPointer_2++;
            lowerPointer_2++;
            upperPointer_3++;
            lowerPointer_3++;
            upperPointer_4++;
            lowerPointer_4++;
        }
        CORETIMER_DelayUs(0.3);
        LATCH_Set();
        CORETIMER_DelayUs(0.3);
        LATCH_Clear();
        
        OE_Clear();
        CORETIMER_DelayUs(brightness);
        OE_Set();
    }
    for(int row = 0; row < 2; row++) {setAddress(1,row);}   
}

/***********************************************
 *               INNER FUNCTIONS
 ************************************************/

void setColor1(int color,int p1,int p2){
    switch (color){
        case RED:
            if (p1){R1_Set();G1_Clear();B1_Clear();}
            else{R1_Clear();G1_Clear();B1_Clear();}
            if (p2){R2_Set();G2_Clear();B2_Clear();}
            else{R2_Clear();G2_Clear();B2_Clear();}
            break;       
        case GREEN:
            if (p1){R1_Clear();G1_Set();B1_Clear();}
            else{R1_Clear();G1_Clear();B1_Clear();}
            if (p2){R2_Clear();G2_Set();B2_Clear();}
            else{R2_Clear();G2_Clear();B2_Clear();}
            break;
        case BLUE:
            if (p1){R1_Clear();G1_Clear();B1_Set();}
            else{R1_Clear();G1_Clear();B1_Clear();}
            if (p2){R2_Clear();G2_Clear();B2_Set();}
            else{R2_Clear();G2_Clear();B2_Clear();}
            break;
        case YELLOW:
            if (p1){R1_Set();G1_Set();B1_Clear();}
            else{R1_Clear();G1_Clear();B1_Clear();}
            if (p2){R2_Set();G2_Set();B2_Clear();}
            else{R2_Clear();G2_Clear();B2_Clear();}
            break;
        case PINK:
            if (p1){R1_Set();G1_Clear();B1_Set();}
            else{R1_Clear();G1_Clear();B1_Clear();}
            if (p2){R2_Set();G2_Clear();B2_Set();}
            else{R2_Clear();G2_Clear();B2_Clear();}
            break;
        case CYAN:
            if (p1){R1_Clear();B1_Set();G1_Set();}
            else{R1_Clear();G1_Clear();B1_Clear();}
            if (p2){R2_Clear();B2_Set();G2_Set();}
            else{R2_Clear();G2_Clear();B2_Clear();}
            break;
        case WHITE:
            if (p1){R1_Set();G1_Set();B1_Set();}
            else{R1_Clear();G1_Clear();B1_Clear();}
            if (p2){R2_Set();G2_Set();B2_Set();}
            else{R2_Clear();G2_Clear();B2_Clear();}
            break;
        case BLACK:
            if (p1){R1_Clear();G1_Clear();B1_Clear();}
            else{R1_Clear();G1_Clear();B1_Clear();}
            if (p2){R2_Clear();G2_Clear();B2_Clear();}
            else{R2_Clear();G2_Clear();B2_Clear();}
            break;
        default:
            if (p1){R1_Set();G1_Clear();B1_Clear();}
            else{R1_Clear();G1_Clear();B1_Clear();}
            if (p2){R2_Set();G2_Clear();B2_Clear();}
            else{R2_Clear();G2_Clear();B2_Clear();}
            break;
                    
    }
    
}

void setColor2(int color, int p3,int p4){
     switch (color){
        case RED:
            if (p3){R3_Set();G3_Clear();B3_Clear();}
            else{R3_Clear();G3_Clear();B3_Clear();}
            if (p4){R4_Set();G4_Clear();B4_Clear();}
            else{R4_Clear();G4_Clear();B4_Clear();}
            break;       
        case GREEN:
            if (p3){R3_Clear();G3_Set();B3_Clear();}
            else{R3_Clear();G3_Clear();B3_Clear();}
            if (p4){R4_Clear();G4_Set();B4_Clear();}
            else{R4_Clear();G4_Clear();B4_Clear();}
            break;
        case BLUE:
            if (p3){R3_Clear();G3_Clear();B3_Set();}
            else{R3_Clear();G3_Clear();B3_Clear();}
            if (p4){R4_Clear();G4_Clear();B4_Set();}
            else{R4_Clear();G4_Clear();B4_Clear();}
            break;
        case YELLOW:
            if (p3){R3_Set();G3_Set();B3_Clear();}
            else{R3_Clear();G3_Clear();B3_Clear();}
            if (p4){R4_Set();G4_Set();B4_Clear();}
            else{R4_Clear();G4_Clear();B4_Clear();}
            break;
        case PINK:
            if (p3){R3_Set();G3_Clear();B3_Set();}
            else{R3_Clear();G3_Clear();B3_Clear();}
            if (p4){R4_Set();G4_Clear();B4_Set();}
            else{R4_Clear();G4_Clear();B4_Clear();}
            break;
        case CYAN:
            if (p3){R3_Clear();B3_Set();G3_Set();}
            else{R3_Clear();G3_Clear();B3_Clear();}
            if (p4){R4_Clear();B4_Set();G4_Set();}
            else{R4_Clear();G4_Clear();B4_Clear();}
            break;
        case WHITE:
            if (p3){R3_Set();G3_Set();B3_Set();}
            else{R3_Clear();G3_Clear();B3_Clear();}
            if (p4){R4_Set();G4_Set();B4_Set();}
            else{R4_Clear();G4_Clear();B4_Clear();}
            break;
        case BLACK:
            if (p3){R3_Clear();G3_Clear();B3_Clear();}
            else{R3_Clear();G3_Clear();B3_Clear();}
            if (p4){R4_Clear();G4_Clear();B4_Clear();}
            else{R4_Clear();G4_Clear();B4_Clear();}
            break;
        default:
            if (p3){R3_Set();G3_Clear();B3_Clear();}
            else{R3_Clear();G3_Clear();B3_Clear();}
            if (p4){R4_Set();G4_Clear();B4_Clear();}
            else{R4_Clear();G4_Clear();B4_Clear();}
            break;              
    }
}

void setColor3(int color, int p5,int p6){
    switch (color){
        case RED:
            if (p5){R5_Set();G5_Clear();B5_Clear();}
            else{R5_Clear();G5_Clear();B5_Clear();}
            if (p6){R6_Set();G6_Clear();B6_Clear();}
            else{R6_Clear();G6_Clear();B6_Clear();}
            break;
        case GREEN:
            if (p5){R5_Clear();G5_Set();B5_Clear();}
            else{R5_Clear();G5_Clear();B5_Clear();}
            if (p6){R6_Clear();G6_Set();B6_Clear();}
            else{R6_Clear();G6_Clear();B6_Clear();}
            break;
        case BLUE:
            if (p5){R5_Clear();G5_Clear();B5_Set();}
            else{R5_Clear();G5_Clear();B5_Clear();}
            if (p6){R6_Clear();G6_Clear();B6_Set();}
            else{R6_Clear();G6_Clear();B6_Clear();}
            break;
        case YELLOW:
            if (p5){R5_Set();G5_Set();B5_Clear();}
            else{R5_Clear();G5_Clear();B5_Clear();}
            if (p6){R6_Set();G6_Set();B6_Clear();}
            else{R6_Clear();G6_Clear();B6_Clear();}
            break;
        case PINK:
            if (p5){R5_Set();G5_Clear();B5_Set();}
            else{R5_Clear();G5_Clear();B5_Clear();}
            if (p6){R6_Set();G6_Clear();B6_Set();}
            else{R6_Clear();G6_Clear();B6_Clear();}
            break;
        case CYAN:
            if (p5){R5_Clear();B5_Set();G5_Set();}
            else{R5_Clear();G5_Clear();B5_Clear();}
            if (p6){R6_Clear();B6_Set();G6_Set();}
            else{R6_Clear();G6_Clear();B6_Clear();}
            break;
        case WHITE:
            if (p5){R5_Set();G5_Set();B5_Set();}
            else{R5_Clear();G5_Clear();B5_Clear();}
            if (p6){R6_Set();G6_Set();B6_Set();}
            else{R6_Clear();G6_Clear();B6_Clear();}
            break;
        case BLACK:
            if (p5){R5_Clear();G5_Clear();B5_Clear();}
            else{R5_Clear();G5_Clear();B5_Clear();}
            if (p6){R6_Clear();G6_Clear();B6_Clear();}
            else{R6_Clear();G6_Clear();B6_Clear();}
            break;
        default:
            if (p5){R5_Set();G5_Clear();B5_Clear();}
            else{R5_Clear();G5_Clear();B5_Clear();}
            if (p6){R6_Set();G6_Clear();B6_Clear();}
            else{R6_Clear();G6_Clear();B6_Clear();}
            break;
    }
    
} 

void setColor4(int color, int p7,int p8){
    switch (color){
        case RED:
            if (p7){R7_Set();G7_Clear();B7_Clear();}
            else{R7_Clear();G7_Clear();B7_Clear();}
            if (p8){R8_Set();G8_Clear();B8_Clear();}
            else{R8_Clear();G8_Clear();B8_Clear();}
            break;
        case GREEN:
            if (p7){R7_Clear();G7_Set();B7_Clear();}
            else{R7_Clear();G7_Clear();B7_Clear();}
            if (p8){R8_Clear();G8_Set();B8_Clear();}
            else{R8_Clear();G8_Clear();B8_Clear();}
            break;
        case BLUE:
            if (p7){R7_Clear();G7_Clear();B7_Set();}
            else{R7_Clear();G7_Clear();B7_Clear();}
            if (p8){R8_Clear();G8_Clear();B8_Set();}
            else{R8_Clear();G8_Clear();B8_Clear();}
            break;
        case YELLOW:
            if (p7){R7_Set();G7_Set();B7_Clear();}
            else{R7_Clear();G7_Clear();B7_Clear();}
            if (p8){R8_Set();G8_Set();B8_Clear();}
            else{R8_Clear();G8_Clear();B8_Clear();}
            break;
        case PINK:
            if (p7){R7_Set();G7_Clear();B7_Set();}
            else{R7_Clear();G7_Clear();B7_Clear();}
            if (p8){R8_Set();G8_Clear();B8_Set();}
            else{R8_Clear();G8_Clear();B8_Clear();}
            break;
        case CYAN:
            if (p7){R7_Clear();B7_Set();G7_Set();}
            else{R7_Clear();G7_Clear();B7_Clear();}
            if (p8){R8_Clear();B8_Set();G8_Set();}
            else{R8_Clear();G8_Clear();B8_Clear();}
            break;
        case WHITE:
            if (p7){R7_Set();G7_Set();B7_Set();}
            else{R7_Clear();G7_Clear();B7_Clear();}
            if (p8){R8_Set();G8_Set();B8_Set();}
            else{R8_Clear();G8_Clear();B8_Clear();}
            break;
        case BLACK:
            if (p7){R7_Clear();G7_Clear();B7_Clear();}
            else{R7_Clear();G7_Clear();B7_Clear();}
            if (p8){R8_Clear();G8_Clear();B8_Clear();}
            else{R8_Clear();G8_Clear();B8_Clear();}
            break;
        default:
            if (p7){R7_Set();G7_Clear();B7_Clear();}
            else{R7_Clear();G7_Clear();B7_Clear();}
            if (p8){R8_Set();G8_Clear();B8_Clear();}
            else{R8_Clear();G8_Clear();B8_Clear();}
            break;
    }
    
}

void setAddress(int c,int row){
    if(c){ADDR_C_Set();}
    else{ADDR_C_Clear();}
    
    if(row){ADDR_A_Set();}
    else{ADDR_A_Clear();}
}

/***********************************************
 *            END OF INNER FUNCTIONS
 ************************************************/

/* *****************************************************************************
 End of File
 */
