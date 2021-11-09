/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// Section: Included Files
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include <string.h>
#include <stdio.h>
#include "PanelControl.h"
#include "BitMaps.h"
#include "UARTSlave.h"

// *****************************************************************************
// Section: MACROS
// *****************************************************************************

//#define MENU_DEBUG

#define DEVICE_MB_ADDRESS       0x08

#define PANEL_N_BYTES              512
#define BUFFER_SIZE_PANEL_CONFIG   10
#define BUFFER_SIZE_PTR_ADDR       6
#define BUFFER_SIZE_UART_RX        128
#define BUFFER_SIZE_BITMAP         2048 
#define EEPROM_TX_BUFFER_SZ        70

#define SET_BITMAP                 0
#define SET_BLINK_STATE            1
#define SET_COLOR                  2
#define BITMAP_COLOR_1             3
#define BITMAP_COLOR_2             4
#define BITMAP_COLOR_3             5
#define BITMAP_COLOR_4             6
#define SET_BLINK_TIME             7
#define SET_BRIGHTNESS             8

#define DEFAULT_BITMAP             4
#define DEFAULT_BLINK_TIME         1000
#define DEFAULT_COLOR              RED
#define DEFAULT_BTMP_COLOR1        RED
#define DEFAULT_BTMP_COLOR2        RED
#define DEFAULT_BTMP_COLOR3        RED
#define DEFAULT_BTMP_COLOR4        RED
#define DEFAULT_BLINK_STATE        0
#define DEFAULT_BRIGHTNESS         50
#define BLINK_ENABLE               1

#define RECEIVING_BITMAP_STATE     0
#define NO_RECEIVING_BITMAP        0
#define RECEIVING_BITMAP           1

#define DATA_TRANSFER_STATUS       1
#define DATA_TRANSFER_COMPLETE     0
#define DATA_TRANSFER_READY        1
     
#define BITMAP_1    0
#define BITMAP_2    1
#define BITMAP_3    2
#define BITMAP_4    3

#define BITMAP1_START_ADDR         0
#define BITMAP2_START_ADDR         512
#define BITMAP3_START_ADDR         1024
#define BITMAP4_START_ADDR         1536
#define BITMAP1_ADDR               0
#define BITMAP2_ADDR               1
#define BITMAP3_ADDR               2
#define BITMAP4_ADDR               3
#define BITMAP_DFLT_ADDR           4

#define EEPROM_ADDR                   0x0050
#define EEPROM_BITMAP_NREAD_BYTES     64
#define EEPROM_BITMAP_NWRITE_BYTES    64
#define EEPROM_CONFIG_NREAD_BYTES     18
#define EEPROM_BITMAP_READ_NCYCLES    32
#define EEPROM_CONFIG_BYTE_ADDRESS_H  0
#define EEPROM_CONFIG_BYTE_ADDRESS_L  1
#define EEPROM_CONFIG_START_ADDR      2
#define CONFIG_BYTE_ADDRESS_H         0
#define CONFIG_BYTE_ADDRESS_L         1
#define PANEL_CONFIG_BYTE             2

#define I2C_RXDATA_START_ADDRESS        0
#define BUFFER_SIZE_I2C_RX              64
#define RECEIVE_DUMMY_WRITE_LENGTH      2
#define PREVIOUS_CONFIGURATION_BYTE     0
#define CONFIGURATION_BYTE              0XBC
#define CONFIGURATION_BYTE_SIZE         1
#define N_CONFIG_BYTES                  9


#ifdef MENU_DEBUG
#define TO_HEX    0
#define TO_DEC    1
#define TO_BOOL   2
#define TO_ASCII  3
#define V_NULL    -1
#define F_NULL    -1  
#define T_DATA_LENGTH            130
#define R_DATA_LENGTH            128
#endif

// *****************************************************************************
// Section: GLOBAL VARIABLES
// *****************************************************************************

uint8_t  bitmapRegister[BUFFER_SIZE_BITMAP] = {};
uint8_t  bitmapRegisterDefault[BUFFER_SIZE_BITMAP] = {};
uint8_t* bitmapRegisterPtr = bitmapRegister;
uint8_t* bitmapRegisterDefaultPtr = bitmapRegisterDefault;
uint8_t* bitmapAddressBuffer[BUFFER_SIZE_PTR_ADDR] = {};

uint16_t panelConfigRegister[BUFFER_SIZE_PANEL_CONFIG] = {DEFAULT_BITMAP,
                                                          DEFAULT_BLINK_STATE,
                                                          DEFAULT_COLOR,
                                                          DEFAULT_BTMP_COLOR1,
                                                          DEFAULT_BTMP_COLOR2,
                                                          DEFAULT_BTMP_COLOR3,
                                                          DEFAULT_BTMP_COLOR4,
                                                          DEFAULT_BLINK_TIME,
                                                          DEFAULT_BRIGHTNESS};
uint16_t* panelConfigRegisterPtr = panelConfigRegister;

uint8_t systemConfigRegister[5] = {RECEIVING_BITMAP,DATA_TRANSFER_COMPLETE};
uint8_t* systemConfigRegisterPtr = systemConfigRegister;


static uint8_t EEPROMAddress[70] = {
    0X0A,0X00,0x0A,0X02,//Direccion de el byte de configuracion previa
    0x00,0x00, //Direccion de la parte 1 del bitmap1
    0x00,0x40, //Direccion de la parte 2 del bitmap1
    0x00,0x80, //Direccion de la parte 3 del bitmap1
    0x00,0xC0, //Direccion de la parte 4 del bitmap1
    0x01,0x00, //Direccion de la parte 5 del bitmap1
    0x01,0x40, //Direccion de la parte 6 del bitmap1
    0x01,0x80, //Direccion de la parte 7 del bitmap1
    0x01,0xC0, //Direccion de la parte 8 del bitmap1
    0x02,0x00, //Direccion de la parte 1 del bitmap2
    0x02,0x40, //Direccion de la parte 2 del bitmap2
    0x02,0x80, //Direccion de la parte 3 del bitmap2
    0x02,0xC0, //Direccion de la parte 4 del bitmap2
    0x03,0x00, //Direccion de la parte 5 del bitmap2
    0x03,0x40, //Direccion de la parte 6 del bitmap2
    0x03,0x80, //Direccion de la parte 7 del bitmap2
    0x03,0xC0, //Direccion de la parte 8 del bitmap2
    0x04,0x00, //Direccion de la parte 1 del bitmap3
    0x04,0x40, //Direccion de la parte 2 del bitmap3
    0x04,0x80, //Direccion de la parte 3 del bitmap3
    0x04,0xC0, //Direccion de la parte 4 del bitmap3
    0x05,0x00, //Direccion de la parte 5 del bitmap3
    0x05,0x40, //Direccion de la parte 6 del bitmap3
    0x05,0x80, //Direccion de la parte 7 del bitmap3
    0x05,0xC0, //Direccion de la parte 8 del bitmap3
    0x06,0x00, //Direccion de la parte 1 del bitmap4
    0x06,0x40, //Direccion de la parte 2 del bitmap4
    0x06,0x80, //Direccion de la parte 3 del bitmap4
    0x06,0xC0, //Direccion de la parte 4 del bitmap4
    0x07,0x00, //Direccion de la parte 5 del bitmap4
    0x07,0x40, //Direccion de la parte 6 del bitmap4
    0x07,0x80, //Direccion de la parte 7 del bitmap4
    0x07,0xC0, //Direccion de la parte 8 del bitmap4
};
static uint8_t I2CRxData[BUFFER_SIZE_I2C_RX]  = {};
bool     blinkFunctionState = true;

#ifdef  MENU_DEBUG
uint8_t nBytesToRead  = 0; 
uint8_t nBytesToWrite = 0;
uint8_t menuTxBuffer[128];
uint8_t menuRxBuffer[10] = {};
static uint8_t readSAddress[2]  =   {};
static uint8_t testTxData[T_DATA_LENGTH] = {};
static uint8_t testRxData[R_DATA_LENGTH]  = {};

bool inMenu = true;
uint16_t byteAddress;
#endif

// *****************************************************************************
// Section: INTERRUPT FUNCTIONS
// *****************************************************************************

volatile uint8_t UARTRxFrameBuffer[BUFFER_SIZE_UART_RX];
volatile uint8_t bytesInRxBuffer = 0;
volatile uint32_t  millis = 0;

void timeEventHandler(uint32_t status, uintptr_t context)
{
    millis++;
}

void usartReadEventHandler(UART_EVENT event, uintptr_t context )
{
    uint32_t nBytesAvailableInRingBuffer = 0;
    
    if (event == UART_EVENT_READ_THRESHOLD_REACHED)
    {
        nBytesAvailableInRingBuffer = UART1_ReadCountGet();
        bytesInRxBuffer += UART1_Read((uint8_t*)&UARTRxFrameBuffer[bytesInRxBuffer], nBytesAvailableInRingBuffer);  
    }
}

// *****************************************************************************
// Section: FUNCTION PROTOYPES
// *****************************************************************************

#ifdef  MENU_DEBUG
bool menu();
void writeTerminal(const char* text, uint32_t variable, int format);
void waitBytes(uint16_t numberOfBytes);
#endif

void setBitmaps();
void EEPROMReadBitmap(uint8_t* bitmapPtr);
void EEPROMReadConfig(uint16_t* configPtr);
void EEPROMLoad();
void blinkFunction(uint8_t* bitmap, uint8_t color, uint16_t brightness, uint16_t blinkTime);
void checkPreviousConfig();
void setBitmapColor(uint16_t bitmap);

// *****************************************************************************
// Section: MAIN
// *****************************************************************************

int main ( void )
{    
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
     #ifdef MENU_DEBUG
    while(inMenu){
        inMenu = menu();
    }
    #endif

    CORETIMER_CallbackSet(&timeEventHandler,(uintptr_t)NULL);
    CORETIMER_Start();
    
    UART1_ReadCallbackRegister(usartReadEventHandler, (uintptr_t) NULL);
    UART1_ReadThresholdSet(1);
    UART1_ReadNotificationEnable(true, false);
    
    dataBufferRegister(panelConfigRegisterPtr,bitmapRegisterPtr,systemConfigRegisterPtr); 
    
    checkPreviousConfig();
    
    setBitmaps();
    
    while ( true )
    {
        processMasterRequest(DEVICE_MB_ADDRESS);
        
        if(systemConfigRegister[RECEIVING_BITMAP_STATE] == RECEIVING_BITMAP) // Demo Mode
        {
            blinkFunction(bitmapAddressBuffer[DEFAULT_BITMAP],
                          DEFAULT_COLOR,
                          DEFAULT_BRIGHTNESS,
                          DEFAULT_BLINK_TIME);
            
            if(systemConfigRegister[DATA_TRANSFER_STATUS] == DATA_TRANSFER_READY)
            {
                EEPROMLoad();
                systemConfigRegister[DATA_TRANSFER_STATUS] = DATA_TRANSFER_COMPLETE;
                systemConfigRegister[RECEIVING_BITMAP_STATE] = NO_RECEIVING_BITMAP;
            }
        }
        else //normal operation
        {
            setBitmapColor(panelConfigRegister[SET_BITMAP]);
            
            if(panelConfigRegister[SET_BLINK_STATE] == BLINK_ENABLE)
            {  
                blinkFunction(bitmapAddressBuffer[panelConfigRegister[SET_BITMAP]],
                              panelConfigRegister[SET_COLOR],
                              panelConfigRegister[SET_BRIGHTNESS],
                              panelConfigRegister[SET_BLINK_TIME]);
            }
            else
            { 
                panelOn4(bitmapAddressBuffer[panelConfigRegister[SET_BITMAP]],
                                             panelConfigRegister[SET_COLOR],
                                             panelConfigRegister[SET_BRIGHTNESS]);
                
                if(!blinkFunctionState){blinkFunctionState = true;}
            }
        }   
    }
    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}

// *****************************************************************************
// Section: INNER FUNCTIONS
// *****************************************************************************

void setBitmaps()
{
    bitmapRegisterPtr = bitmapRegister;
    
    memcpy(bitmapRegisterDefault, allOnBitmap, PANEL_N_BYTES);
    
    bitmapAddressBuffer[BITMAP1_ADDR] = &bitmapRegister[BITMAP1_START_ADDR];
    bitmapAddressBuffer[BITMAP2_ADDR] = &bitmapRegister[BITMAP2_START_ADDR];
    bitmapAddressBuffer[BITMAP3_ADDR] = &bitmapRegister[BITMAP3_START_ADDR];
    bitmapAddressBuffer[BITMAP4_ADDR] = &bitmapRegister[BITMAP4_START_ADDR];
    bitmapAddressBuffer[BITMAP_DFLT_ADDR] = bitmapRegisterDefaultPtr;
    
}

void EEPROMReadBitmap(uint8_t* bitmapPtr)
{
    uint16_t readAddress = 4;

    for (int i = 0; i < EEPROM_BITMAP_READ_NCYCLES; i++)
    {
        I2C1_WriteRead(EEPROM_ADDR, &EEPROMAddress[readAddress], 
                       RECEIVE_DUMMY_WRITE_LENGTH,   
                       &I2CRxData[I2C_RXDATA_START_ADDRESS], 
                       EEPROM_BITMAP_NREAD_BYTES);
        
        while(I2C1_IsBusy());
        memcpy(bitmapPtr,I2CRxData,EEPROM_BITMAP_NREAD_BYTES);
        readAddress += 2;
        bitmapPtr += 64;
    }
}

void EEPROMReadConfig(uint16_t* configPtr)
{
    I2C1_WriteRead(EEPROM_ADDR, &EEPROMAddress[EEPROM_CONFIG_START_ADDR], 
                   RECEIVE_DUMMY_WRITE_LENGTH,  
                   &I2CRxData[I2C_RXDATA_START_ADDRESS], 
                   EEPROM_CONFIG_NREAD_BYTES);
    
    while(I2C1_IsBusy());
    
    uint16_t configFrame[BUFFER_SIZE_PANEL_CONFIG] = {};
    
    for(int i = 0; i < EEPROM_CONFIG_NREAD_BYTES/2 ; i++)
    {
        configFrame[i] = ((uint16_t)I2CRxData[i*2] << 8) + I2CRxData[(i*2)+1];    
    }
    memcpy(configPtr,configFrame,EEPROM_CONFIG_NREAD_BYTES);
}

void EEPROMLoad()
{
    uint8_t writeAddress = 4;
    uint8_t EEPROMtxBuffer[EEPROM_TX_BUFFER_SZ] = {};
    uint16_t increaseAddrBtmpRegister = 0;

    for (size_t j = 0; j < 32 ; j++)
    {
        EEPROMtxBuffer[0] = EEPROMAddress[writeAddress];
        EEPROMtxBuffer[1] = EEPROMAddress[writeAddress + 1];
        
        for(size_t i = 0; i < EEPROM_BITMAP_NWRITE_BYTES; i++)
        {
            EEPROMtxBuffer[i+2] = bitmapRegister[i + increaseAddrBtmpRegister];
        }

        I2C1_Write(EEPROM_ADDR, &EEPROMtxBuffer[0], EEPROM_BITMAP_NWRITE_BYTES + 2);
        while(I2C1_IsBusy());

        writeAddress += 2;
        increaseAddrBtmpRegister += 64;
        CORETIMER_DelayMs(20);
    } 
    
    EEPROMtxBuffer[EEPROM_CONFIG_BYTE_ADDRESS_H] = EEPROMAddress[CONFIG_BYTE_ADDRESS_H];
    EEPROMtxBuffer[EEPROM_CONFIG_BYTE_ADDRESS_L] = EEPROMAddress[CONFIG_BYTE_ADDRESS_L];
    EEPROMtxBuffer[PANEL_CONFIG_BYTE] = CONFIGURATION_BYTE;
    
    int configFrameStartAddress = 4;
    
    for(size_t i = 0; i< N_CONFIG_BYTES; i++)
    {
        EEPROMtxBuffer[configFrameStartAddress] = (uint8_t)(panelConfigRegister[i] >> 8);
        EEPROMtxBuffer[configFrameStartAddress+1] = (uint8_t)panelConfigRegister[i];
        configFrameStartAddress +=2;
    }
    
    I2C1_Write(EEPROM_ADDR, &EEPROMtxBuffer[0], 22);
    while(I2C1_IsBusy());
    
    #ifdef MENU_DEBUG    
    writeTerminal("[",V_NULL,F_NULL);
    for(int i = 0; i<20; i++)
    {
        writeTerminal("0x%X,",EEPROMtxBuffer[i],F_NULL);
    }
    writeTerminal("]",V_NULL,F_NULL);
    #endif
}

void blinkFunction(uint8_t* bitmap, uint8_t color, uint16_t brightness, uint16_t blinkTime)
{
    static uint32_t previousTime = 0;
   //static bool     blinkFunctionState = false;
    
    if (millis > (previousTime + blinkTime))
    {
        blinkFunctionState = !blinkFunctionState;
        previousTime = millis;
    }
    if(blinkFunctionState)
    {
        panelOn4(bitmap,color,brightness);
    }
    else
    {
        panelOff();
    }
}

void checkPreviousConfig()
{
    I2C1_WriteRead(EEPROM_ADDR, &EEPROMAddress[0], 
                   RECEIVE_DUMMY_WRITE_LENGTH,  
                   &I2CRxData[I2C_RXDATA_START_ADDRESS], 
                   CONFIGURATION_BYTE_SIZE);
    
    while(I2C1_IsBusy());
    
    if ( I2CRxData[PREVIOUS_CONFIGURATION_BYTE] == CONFIGURATION_BYTE )
    { 
        EEPROMReadBitmap(bitmapRegisterPtr);
        EEPROMReadConfig(panelConfigRegisterPtr);
        systemConfigRegister[RECEIVING_BITMAP_STATE] = NO_RECEIVING_BITMAP;
    }
}

void setBitmapColor(uint16_t bitmap)
{
    switch (bitmap)
    {
        case BITMAP_1:
            panelConfigRegister[SET_COLOR] = panelConfigRegister[BITMAP_COLOR_1];
            break;
        case BITMAP_2:
            panelConfigRegister[SET_COLOR] = panelConfigRegister[BITMAP_COLOR_2];
            break;
        case BITMAP_3:
            panelConfigRegister[SET_COLOR] = panelConfigRegister[BITMAP_COLOR_3];
            break;
        case BITMAP_4:
            panelConfigRegister[SET_COLOR] = panelConfigRegister[BITMAP_COLOR_4];            
            break;
        default:
            panelConfigRegister[SET_COLOR] = WHITE;            
            break;
    }
}

#ifdef MENU_DEBUG
bool menu(){
    /*Program menu*/
    writeTerminal("Read (R), Write (W), Exit(E), Erase(C)\r\n",V_NULL,F_NULL);
    waitBytes(1);
    //CORETIMER_DelayMs(1);

    /*if R is selected*/
    if (menuRxBuffer[0] == 82)
    {
        writeTerminal("\r\n---------------Read---------------\r\nStarting Address (2 Bytes):",V_NULL,F_NULL);
        waitBytes(2);

        readSAddress[0] = menuRxBuffer[0];
        readSAddress[1] = menuRxBuffer[1];

        byteAddress = ((uint16_t)readSAddress[0] << 8) + readSAddress[1];

        writeTerminal("\r\nNumber of Bytes to Read (MAX:%d) (1 Byte):",R_DATA_LENGTH,F_NULL);
        waitBytes(1);

        nBytesToRead = menuRxBuffer[0];

        writeTerminal("\r\nReading...\r\n",V_NULL,F_NULL);

        I2C1_WriteRead(EEPROM_ADDR, &readSAddress[0], RECEIVE_DUMMY_WRITE_LENGTH,  &testRxData[0], nBytesToRead);
        while(I2C1_IsBusy());

        for (int i = 0; i < nBytesToRead ; i++)
        {
            writeTerminal("0X%X_",byteAddress,F_NULL);
            writeTerminal(NULL,testRxData[i],TO_HEX); 
            byteAddress++;
        }
        writeTerminal("Reading complete...\r\n",V_NULL,F_NULL);
        return true;
    }

    /*if W is selected*/
    else if(menuRxBuffer[0] == 87)
    {
        writeTerminal("\r\n---------------Write---------------\r\nStarting Address (2 Bytes):",V_NULL,F_NULL);
        waitBytes(2);

        testTxData[0] = menuRxBuffer[0];
        testTxData[1] = menuRxBuffer[1];

        writeTerminal("\r\nNumber of Bytes to Write (MAX:%d) (1 Byte):",T_DATA_LENGTH - 2,F_NULL);
        waitBytes(1);

        nBytesToWrite = menuRxBuffer[0];

        writeTerminal("\r\nWrite Data (%d Bytes):",nBytesToWrite,F_NULL);
        waitBytes(nBytesToWrite);

        for(int i = 0; i < nBytesToWrite; i++)
        {
            testTxData[i+2] = menuRxBuffer[i];
        }

        I2C1_Write(EEPROM_ADDR, &testTxData[0], nBytesToWrite + 2);
        while(I2C1_IsBusy());

        writeTerminal("\r\nWriting Complete...\r\n",V_NULL,F_NULL);
        return true;
    }
    
    /*if C is selected*/
    else if(menuRxBuffer[0] == 67)
    {
        writeTerminal("\r\n---------------Erase---------------\r\n",V_NULL,F_NULL);
        uint8_t nBytesToErase = 64;
        uint8_t eraseAddress = 4;
        
        for(size_t i = 0; i < nBytesToErase; i++)
        {
            testTxData[i+2] = 0xFF;
        }

        for (size_t j = 0; j < 32 ; j++)
        {
            testTxData[0] = EEPROMAddress[eraseAddress];
            testTxData[1] = EEPROMAddress[eraseAddress + 1];

            I2C1_Write(EEPROM_ADDR, &testTxData[0], nBytesToErase + 2);
            while(I2C1_IsBusy());

            eraseAddress += 2;
            CORETIMER_DelayMs(20);
        }
        
        writeTerminal("\r\nErase Complete...\r\n",V_NULL,F_NULL);
        return true;
    }
    else if(menuRxBuffer[0] == 69)
    {
        return false;
    }
    /*if not selected (R) - (W)*/
    else 
    {
        writeTerminal("Invalid Command...\r\n",V_NULL,F_NULL);
        return true;
    }
}

void waitBytes(uint16_t numberOfBytes)
{
    while (UART1_ReadCountGet() < numberOfBytes);    
    UART1_Read((uint8_t*)menuRxBuffer, numberOfBytes);
}

void writeTerminal(const char* text, uint32_t variable, int format)
{
    uint8_t nBytes = 0;

    if( (variable == V_NULL) && (format == F_NULL) )    //Write a text on terminal
    {
        nBytes = sprintf((char*)menuTxBuffer,text);   
    }
    else                   //Write a text and variable on terminal
    {   
        if (text != NULL) 
        {
            nBytes = sprintf((char*)&menuTxBuffer,text, variable);
        }
        else
        {
            switch(format) 
            {
                case TO_HEX:
                    nBytes = sprintf((char*)&menuTxBuffer,"<0X%X>\r\n", variable);
                    break;
                case TO_DEC:
                    nBytes = sprintf((char*)&menuTxBuffer,"<%d>\r\n", variable);
                    break;
                case TO_BOOL:
                    nBytes = sprintf((char*)&menuTxBuffer,"<%s>\r\n",variable ? "true" : "false");
                    break;
                case TO_ASCII:
                    nBytes = sprintf((char*)&menuTxBuffer,"<%c>\r\n",variable);
                    break;
            }
        } 
    }
    UART1_Write((uint8_t*)menuTxBuffer, nBytes);  
    while (UART1_WriteCountGet() != 0); 
}
#endif


/*******************************************************************************
 End of File
*/
