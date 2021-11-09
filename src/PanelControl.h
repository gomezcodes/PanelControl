/* ************************************************************************** */
/** Panel Control Library Header

  @Company
    SISTRON
  @Author
    Gòmez Santos Joaquìn
  @File Name
    panel.h
  @Description
    Contains the constants and functions required by panel.c to control
    a 32x32 pixels panel 1:2 scan rate
 */
/* ************************************************************************** */

#ifndef _PANEL_CONTROL_H    /* Guard against multiple inclusion */
#define _PANEL_CONTROL_H

#include <stdint.h>

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
    
#define RED       0
#define GREEN     1
#define BLUE      2
#define YELLOW    3
#define PINK      4
#define CYAN      5
#define WHITE     6
#define BLACK     7
    
#define LEVEL0    10
#define LEVEL1    50
#define LEVEL2    250
#define LEVEL3    1000
#define LEVEL4    2000

void panelOff();
void panelOn1(uint8_t *addrBuffer,char color,int brightness);
void panelOn2(uint8_t *addrBuffer,char color,int brightness);
void panelOn3(uint8_t *addrBuffer,char color,int brightness);
void panelOn4(uint8_t *addrBuffer,char color,int brightness);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
