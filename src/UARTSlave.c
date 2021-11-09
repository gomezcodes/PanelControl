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
/* ************************************************************************** */

//#define DEBUG_CODE

#include <stdint.h>
#include "definitions.h"
#include "UARTSlave.h"

#ifdef DEBUG_CODE
    #include <stdio.h>
#endif

// *****************************************************************************
// Section: DEFINE CONSTANTS
// *****************************************************************************

#define FRAME_HEADER_SIZE       3
#define INTER_FRAME_TIMEOUT     50UL
#define BROADCAST_ADR           0UL
#define FRAME_NET_ID            0
#define FRAME_DEVICE_ID         1
#define FRAME_NBYTES            2
#define FRAME_COMMAND           3
#define FRAME_DATA_ADR          4
#define FRAME_DATA_BLOCK        6
#define FRAME_CONTROL_SIZE      3

#define WRITE_PNL_CONFIG_REGISTER   0X80
#define WRITE_BTMAP_REGISTER        0X82
#define WRITE_SYS_CONFIG_REGISTER   0X84

#define BITMAP_SET          0
#define COLOR_SET           1
#define BRIGHTNESS_SET      2


#ifdef DEBUG_CODE
    #define TO_HEX              0
    #define TO_DEC              1
#endif


// *****************************************************************************
// Section: VARIABLES
// *****************************************************************************

uint16_t* panelConfigBuffer;
uint8_t* bitmapBuffer;
uint8_t* sysConfigBuffer;

uint8_t networkId           = 0x5A;
uint8_t txFrameBuffer[128];
bool    dataIsBeenReceived      = false;
// *****************************************************************************
// Section: FUNCTION PROTOYPES
// *****************************************************************************

uint8_t receiveFrame();
int validateFrame(uint8_t deviceId, uint8_t frameSz);
int processCommand();

#ifdef DEBUG_CODE
void writeVariable(uint32_t variable, int base_num);
#endif

// *****************************************************************************
// Section: FUNCTIONS
// *****************************************************************************

void dataBufferRegister(uint16_t* buffer1, uint8_t* buffer2, uint8_t* buffer3)
{
    panelConfigBuffer = buffer1;
    bitmapBuffer = buffer2;
    sysConfigBuffer = buffer3;
}

int processMasterRequest(uint8_t deviceId)
{
    uint8_t bytesInFrame = receiveFrame();

    if( !bytesInFrame )
    {
        return 0;
    }

    if( !validateFrame(deviceId, bytesInFrame) )
    {
        return 0;
    }

    return processCommand();
}

// *****************************************************************************
// Section: INNER FUNCTIONS
// *****************************************************************************

uint8_t receiveFrame()
{
    if( !bytesInRxBuffer ) 
    {
        return 0;
    }
    
    static uint32_t timeOutTimer = 0;
    
    if (!dataIsBeenReceived)
    {
        timeOutTimer = millis;
    }
    
    uint8_t bytesRead = bytesInRxBuffer;
    
    if ( (timeOutTimer + INTER_FRAME_TIMEOUT) < millis )
    {
        bytesInRxBuffer = 0;
        dataIsBeenReceived = false;
        return bytesRead;
    }
    else
    {
        if( bytesInRxBuffer > bytesRead )
        {
            bytesRead = bytesInRxBuffer;
            timeOutTimer = millis;
        }
        dataIsBeenReceived = true;
    }
    
    return 0;
}

int validateFrame(uint8_t deviceId, uint8_t frameSz)
{
    if(UARTRxFrameBuffer[FRAME_NET_ID] != networkId)
    {
        return 0;
    }
    
    if( (UARTRxFrameBuffer[FRAME_DEVICE_ID] != deviceId) &&
        (UARTRxFrameBuffer[FRAME_DEVICE_ID] != BROADCAST_ADR))
    {
        return 0;
    }
    
    if( UARTRxFrameBuffer[FRAME_NBYTES] != (frameSz - FRAME_HEADER_SIZE))
    {
        return 0;
    }
    
    /*for debugging*/
    /*uint8_t framedebug[128] ={'\n','\r'};
    for(int i = 0; i<frameSz; i++)
    {
        framedebug[i+2] = UARTRxFrameBuffer[i];
    }
    UART1_Write((uint8_t*)framedebug,frameSz+2);*/
    
    UART1_Write((uint8_t*)UARTRxFrameBuffer,frameSz);
    while (UART1_WriteCountGet() != 0);

    return 1;
}

int processCommand()
{
    if(UARTRxFrameBuffer[FRAME_COMMAND] == WRITE_PNL_CONFIG_REGISTER)
    { 
        uint16_t dataAddress = ((uint16_t)UARTRxFrameBuffer[FRAME_DATA_ADR] << 8) +
                                UARTRxFrameBuffer[FRAME_DATA_ADR + 1];
        
        uint8_t bytesToWrite  = UARTRxFrameBuffer[FRAME_NBYTES] - FRAME_CONTROL_SIZE;
        
        for (size_t i = 0; i < bytesToWrite/2 ; i++)
        {
            panelConfigBuffer[dataAddress] = ((uint16_t)UARTRxFrameBuffer[FRAME_DATA_BLOCK + (i*2)] << 8) + 
                                               UARTRxFrameBuffer[FRAME_DATA_BLOCK + (i*2) + 1];
            
            dataAddress ++;
        } 
        
        return WRITE_PNL_CONFIG_REGISTER;
    }
    
    if(UARTRxFrameBuffer[FRAME_COMMAND] == WRITE_BTMAP_REGISTER)
    {
        uint16_t dataAddress = ((uint16_t)UARTRxFrameBuffer[FRAME_DATA_ADR] << 8) +
                                UARTRxFrameBuffer[FRAME_DATA_ADR + 1];
        
        uint8_t bytesToWrite  = UARTRxFrameBuffer[FRAME_NBYTES] - FRAME_CONTROL_SIZE;
        
        for (size_t i = 0; i < bytesToWrite; i++)
        {
            bitmapBuffer[dataAddress] = UARTRxFrameBuffer[FRAME_DATA_BLOCK + i];
            dataAddress ++;
        }    
        return WRITE_BTMAP_REGISTER;
    }
    
    if(UARTRxFrameBuffer[FRAME_COMMAND] == WRITE_SYS_CONFIG_REGISTER)
    {
        uint16_t dataAddress = ((uint16_t)UARTRxFrameBuffer[FRAME_DATA_ADR] << 8) +
                                UARTRxFrameBuffer[FRAME_DATA_ADR + 1];
        
        uint8_t bytesToWrite  = UARTRxFrameBuffer[FRAME_NBYTES] - FRAME_CONTROL_SIZE;
        
        for (size_t i = 0; i < bytesToWrite; i++)
        {
            sysConfigBuffer[dataAddress] = UARTRxFrameBuffer[FRAME_DATA_BLOCK + i];
            dataAddress ++;
        }    
        return WRITE_SYS_CONFIG_REGISTER;
    }
    
    return 0;
}


#ifdef DEBUG_CODE
void writeVariable(uint32_t variable, int base_num)
{
    uint8_t nBytes;
    
    switch(base_num)
    {
        case TO_HEX:
            nBytes = sprintf((char*)&txFrameBuffer,"<%X>\r\n", variable);
            UART1_Write((uint8_t*)txFrameBuffer,nBytes);
            while (UART1_WriteCountGet() != 0); 
        case TO_DEC:
            nBytes = sprintf((char*)&txFrameBuffer,"<%d>\r\n", variable);
            UART1_Write((uint8_t*)txFrameBuffer,nBytes);
            while (UART1_WriteCountGet() != 0); 
    
    }
}
#endif

/* *****************************************************************************
 End of File
 */
