#include "stm32f10x.h"
#include "ff.h"
#include "bsp_spi_flash.h"
#include "bsp_usart.h"
#include "bsp_led.h"
#include "dma.h"

FATFS fs;													/* FatFs文件系统对象 */
FIL fnew;													/* 文件对象 */
FRESULT res_flash;                /* 文件操作结果 */
UINT fnum;            					  /* 文件成功读写数量 */
BYTE ReadBuffer[1024]={0};        /* 读缓冲区 */
BYTE WriteBuffer[] =              /* 写缓冲区*/
"欢迎使用野火STM32开发板 今天是个好日子，1来来\r\n"; 
uint8_t by[256] = {0};
int a;
int main(void)
{
	/* 初始化LED */
	LED_GPIO_Config();	
	LED_BLUE;

        //数据发送DMA
    //MYDMA_Config(DMA1_Channel3,(u32)&SPI1->DR,0,0);
//    //数据接收DMA
    //MYDMA_Config2(DMA1_Channel2,(u32)&SPI1->DR,0,0);
    
//    DMA1_Channel3->CPAR = 256;//外设地址
//    DMA1_Channel3->CNDTR = 256;//传输数量
//    DMA1_Channel3->CMAR  = 256;//内存地址
    
	//MYDMA_Config(DMA1_Channel3,(SPI1->DR);
	/* 初始化调试串口，一般为串口1 */
	USART_Config();	
    SPI_FLASH_Init();
    SPI_Flash_WAKEUP();
    MYDMA_Config(DMA1_Channel3,(u32)&SPI1->DR,(u32)by,256);
    SPI_FLASH_SectorErase(0);
    for(a = 0;a < 256;a++)
    {
        by[a] = 0x0f;
    }
    SPI_FLASH_BufferWrite(by, 0, 256);
    for(a = 0;a < 256;a++)
    {
        by[a] = 0x0;
    }
    SPI_FLASH_BufferRead(by,0,256);
    for(a = 0;a < 256;a++)
    {
        printf("%d  ",by[a]);
        //by[a] = 0x0;
    }
//  printf("****** 这是一个SPI FLASH 文件系统实验 ******\r\n");
//  
//	//在外部SPI Flash挂载文件系统，文件系统挂载时会对SPI设备初始化
//	//初始化函数调用流程如下
//	//f_mount()->find_volume()->disk_initialize->SPI_FLASH_Init()
//	res_flash = f_mount(&fs,"1:",1);
//	
///*----------------------- 格式化测试 -----------------*/  
//	/* 如果没有文件系统就格式化创建创建文件系统 */
//	if(res_flash == FR_NO_FILESYSTEM)
//	{
//		printf("》FLASH还没有文件系统，即将进行格式化...\r\n");
//    /* 格式化 */
//		res_flash=f_mkfs("1:",0,0);							
//		
//		if(res_flash == FR_OK)
//		{
//			printf("》FLASH已成功格式化文件系统。\r\n");
//      /* 格式化后，先取消挂载 */
//			res_flash = f_mount(NULL,"1:",1);			
//      /* 重新挂载	*/			
//			res_flash = f_mount(&fs,"1:",1);
//		}
//		else
//		{
//			LED_RED;
//			printf("《《格式化失败。》》\r\n");
//			while(1);
//		}
//	}
//  else if(res_flash!=FR_OK)
//  {
//    printf("！！外部Flash挂载文件系统失败。(%d)\r\n",res_flash);
//    printf("！！可能原因：SPI Flash初始化不成功。\r\n");
//		while(1);
//  }
//  else
//  {
//    printf("》文件系统挂载成功，可以进行读写测试\r\n");
//  }
//  
///*----------------------- 文件系统测试：写测试 -------------------*/
//	/* 打开文件，每次都以新建的形式打开，属性为可写 */
//	printf("\r\n****** 即将进行文件写入测试... ******\r\n");	
//	res_flash = f_open(&fnew, "1:FatFs读写测试文件.txt",FA_CREATE_ALWAYS | FA_WRITE );
//	if ( res_flash == FR_OK )
//	{
//		printf("》打开/创建FatFs读写测试文件.txt文件成功，向文件写入数据。\r\n");
//    /* 将指定存储区内容写入到文件内 */
//		res_flash=f_write(&fnew,WriteBuffer,sizeof(WriteBuffer),&fnum);
//    if(res_flash==FR_OK)
//    {
//      printf("》文件写入成功，写入字节数据：%d\n",fnum);
//      printf("》向文件写入的数据为：\r\n%s\r\n",WriteBuffer);
//    }
//    else
//    {
//      printf("！！文件写入失败：(%d)\n",res_flash);
//    }    
//		/* 不再读写，关闭文件 */
//    f_close(&fnew);
//	}
//	else
//	{	
//		LED_RED;
//		printf("！！打开/创建文件失败。\r\n");
//	}
//	
///*------------------- 文件系统测试：读测试 --------------------------*/
//	printf("****** 即将进行文件读取测试... ******\r\n");
//	res_flash = f_open(&fnew, "1:FatFs读写测试文件.txt",FA_OPEN_EXISTING | FA_READ); 	 
//	if(res_flash == FR_OK)
//	{
//		LED_GREEN;
//		printf("》打开文件成功。\r\n");
//		res_flash = f_read(&fnew, ReadBuffer, sizeof(ReadBuffer), &fnum); 
//    if(res_flash==FR_OK)
//    {
//      printf("》文件读取成功,读到字节数据：%d\r\n",fnum);
//      printf("》读取得的文件数据为：\r\n%s \r\n", ReadBuffer);	
//    }
//    else
//    {
//      printf("！！文件读取失败：(%d)\n",res_flash);
//    }		
//	}
//	else
//	{
//		LED_RED;
//		printf("！！打开文件失败。\r\n");
//	}
//	/* 不再读写，关闭文件 */
//	f_close(&fnew);	
//  
//	/* 不再使用文件系统，取消挂载文件系统 */
//	f_mount(NULL,"1:",1);
  
  /* 操作完成，停机 */
	while(1)
	{
	}
}

/*********************************************END OF FILE**********************/
