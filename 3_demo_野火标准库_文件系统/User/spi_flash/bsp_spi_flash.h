#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#include "stm32f10x.h"


//#define  sFLASH_ID              0xEF3015   //W25X16
//#define  sFLASH_ID              0xEF4015	 //W25Q16
//#define  sFLASH_ID              0XEF4018   //W25Q128
#define  sFLASH_ID              0XEF4017    //W25Q64

#define SPI_FLASH_PageSize              256
#define SPI_FLASH_PerWritePageSize      256

/*命令定义-开头*******************************/
#define W25X_WriteEnable		      0x06 
#define W25X_WriteDisable		      0x04 
#define W25X_ReadStatusReg		    0x05 
#define W25X_WriteStatusReg		    0x01 
#define W25X_ReadData			        0x03 
#define W25X_FastReadData		      0x0B 
#define W25X_FastReadDual		      0x3B 
#define W25X_PageProgram		      0x02 
#define W25X_BlockErase			      0xD8 
#define W25X_SectorErase		      0x20 
#define W25X_ChipErase			      0xC7 
#define W25X_PowerDown			      0xB9 
#define W25X_ReleasePowerDown	    0xAB 
#define W25X_DeviceID			        0xAB 
#define W25X_ManufactDeviceID   	0x90 
#define W25X_JedecDeviceID		    0x9F

/* WIP(busy)标志，FLASH内部正在写入 */
#define WIP_Flag                  0x01
#define Dummy_Byte                0xFF
/*命令定义-结尾*******************************/


/*SPI接口定义-开头****************************/
#define      SPIx                        SPI1
#define      SPI_APBxClock_FUN           RCC_APB2PeriphClockCmd
#define      SPI_CLK                     RCC_APB2Periph_SPI1
//CS(NSS)引脚 片选选普通GPIO即可
#define      SPI_CS_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define      SPI_CS_CLK                  RCC_APB2Periph_GPIOA    
#define      SPI_CS_PORT                 GPIOA
#define      SPI_CS_PIN                  GPIO_Pin_4
//SCK引脚
#define      SPI_SCK_APBxClock_FUN       RCC_APB2PeriphClockCmd
#define      SPI_SCK_CLK                 RCC_APB2Periph_GPIOA   
#define      SPI_SCK_PORT                GPIOA   
#define      SPI_SCK_PIN                 GPIO_Pin_5
//MISO引脚
#define      SPI_MISO_APBxClock_FUN      RCC_APB2PeriphClockCmd
#define      SPI_MISO_CLK                RCC_APB2Periph_GPIOA    
#define      SPI_MISO_PORT               GPIOA 
#define      SPI_MISO_PIN                GPIO_Pin_6
//MOSI引脚
#define      SPI_MOSI_APBxClock_FUN      RCC_APB2PeriphClockCmd
#define      SPI_MOSI_CLK                RCC_APB2Periph_GPIOA    
#define      SPI_MOSI_PORT               GPIOA 
#define      SPI_MOSI_PIN                GPIO_Pin_7

#define  SPI_FLASH_CS_LOW()     GPIO_ResetBits( SPI_CS_PORT, SPI_CS_PIN )
#define  SPI_FLASH_CS_HIGH()    GPIO_SetBits( SPI_CS_PORT, SPI_CS_PIN )

/*SPI接口定义-结尾****************************/


/*信息输出*/
#define FLASH_DEBUG_ON         1

#define FLASH_INFO(fmt,arg...)           printf("<<-FLASH-INFO->> "fmt"\n",##arg)
#define FLASH_ERROR(fmt,arg...)          printf("<<-FLASH-ERROR->> "fmt"\n",##arg)
#define FLASH_DEBUG(fmt,arg...)          do{\
                                          if(FLASH_DEBUG_ON)\
                                          printf("<<-FLASH-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)

void SPI_FLASH_Init(void);
void SPI_FLASH_SectorErase(u32 SectorAddr);
void SPI_FLASH_BulkErase(void);
void SPI_FLASH_PageWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void SPI_FLASH_BufferWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);
u32 SPI_FLASH_ReadID(void);
u32 SPI_FLASH_ReadDeviceID(void);
void SPI_FLASH_StartReadSequence(u32 ReadAddr);
void SPI_Flash_PowerDown(void);
void SPI_Flash_WAKEUP(void);


u8 SPI_FLASH_ReadByte(void);
u8 SPI_FLASH_SendByte(u8 byte);
u16 SPI_FLASH_SendHalfWord(u16 HalfWord);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WaitForWriteEnd(void);


#endif /* __SPI_FLASH_H */

