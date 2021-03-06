#include "stm32f10x.h"
#include "sd.h"
#include "usart.h"
#include "User_systick.h"


uint8_t buffer[512];

int main(void)
{
	uint32_t sd_size;
	uint8_t res;
	uint16_t i;
					  
	SystemInit();
	USART_Configuration();
	
//	printf("SD card experiment！\r\n");
//	printf("Please plug in 1 GB SD card！\r\n");
	while(SD_Init()!=0)//循环检测SD卡是否存在 (Cycle detection SD card was there)
	{
//		printf("No SD card detected！\r\n");
		delay_1ms(500);
//		printf("lease confirm whether inserted SD card\r\n");
		delay_1ms(500);
	}
//	printf("SD card is OK\r\n");
	sd_size=SD_GetCapacity();
	sd_size=(sd_size>>20);
//	printf("SD card size capacity:%d Mb\r\n",sd_size);

	/*------     给SD卡写入数据  SD card to write data   ------*/
	for(i=0;i<512;i++) // 给buf赋值(Buf to assign a value to)
	{
	 	buffer[i]='a';	   // 写入512个字母'a' (Written 512 letters' a ')
	}
	res = SD_WriteSingleBlock(10, buffer);// 把buf的数据写入到SD卡的第10个扇区(Buf data written to the SD card of 10 sector)
	if(res==0)	 // 如果写入成功   (If written to the success)
	{
//		printf("Written to the success！\r\n");
	}
	else		 // 如果写入失败 (If written to the failure)
	{
//		printf("Written to the failure！\r\n");
	}

	/*------     读SD卡的数据    Read the SD card data ------*/
	for(i=0;i<512;i++) // 给buf赋值	  Buf to assign a value to
	{
	 	buffer[i]='b';	   // 把buf的值重新赋值为‘b’ (The value of the buf to value of "b")
	}
	res = SD_ReadSingleBlock(10, buffer);// 读SD卡的第10个扇区，并把读出值存入buf(Read the SD card sector 10, and read the value buf deposit)
	if(res==0)	 // 如果读出数据成功 (If read data success)
	{
//		printf("Read success！\r\n");
	}
	else		 // 如果读出数据失败  (If read data failed)
	{
//		printf("Read data failed！\r\n");
	}

	if(res==0) // 如果读出数据成功(If read data success)
	{
	   	for(i=0;i<512;i++)
		{
		   	if(buffer[i]!='a') // 检测每一个读到的数据是否为a(Testing every read data whether for a)
			break;			   // 只要有一个数据不是a，就提前跳出for循环(As long as there is a data is not a, jumped out in advance for circulation)
		}
//		if(i==512) // 如果i=512,即所有数据全正确 (If i = 512, that all the right data)
//		printf("Testing is complete！All the data are correct！\r\n");
//		else	   // 如果i!=512,即读到的数据发生错误(If i! = 512, or read data error)
//	printf("Testing is complete！Read the wrong data！\r\n");
	}
		
	while(1);
}
