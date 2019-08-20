/******************** (C) COPYRIGHT 2011 lightEngines-tech ********************
* File Name          		: type.h
* Author             		: FanLiang
* Version            		: V0.1
* Suitable CPU      		: ATtiny4313
*Compile the software	: AVR Studio 5
* Date               		: 09/29/2011
* Description        		: This file contains all the common data types used for the
********************************************************************************
* History:
* 09/29/2011: V0.1
********************************************************************************
*
*
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TYPE_H
#define __TYPE_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity       */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity       */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity       */
typedef signed   short INT16S;                   /* Signed   16 bit quantity       */
typedef unsigned long   INT32U;                   /* Unsigned 32 bit quantity       */
typedef signed   long   INT32S;                   /* Signed   32 bit quantity       */
typedef float          FP32;                     /* Single precision floating point*/
typedef double         FP64;                     /* Double precision floating point*/

#define	u8 unsigned char
#define	u16 unsigned int
#define	u32 unsigned long

#endif /* __TYPE_H */




/******************* http://www.lightengine-tech.com/ *******END OF FILE******************/

