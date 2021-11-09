/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _UART_SLAVE_H    /* Guard against multiple inclusion */
#define _UART_SLAVE_H

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
    extern volatile uint8_t UARTRxFrameBuffer[128];
    extern volatile uint32_t  millis;
    extern volatile uint8_t bytesInRxBuffer;
    
    int processMasterRequest(uint8_t deviceId);    
    void dataBufferRegister(uint16_t* buffer1, uint8_t* buffer2, uint8_t* buffer3);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif

/* *****************************************************************************
 End of File
 */
