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
	
//	printf("SD card experiment��\r\n");
//	printf("Please plug in 1 GB SD card��\r\n");
	while(SD_Init()!=0)//ѭ�����SD���Ƿ���� (Cycle detection SD card was there)
	{
//		printf("No SD card detected��\r\n");
		delay_1ms(500);
//		printf("lease confirm whether inserted SD card\r\n");
		delay_1ms(500);
	}
//	printf("SD card is OK\r\n");
	sd_size=SD_GetCapacity();
	sd_size=(sd_size>>20);
//	printf("SD card size capacity:%d Mb\r\n",sd_size);

	/*------     ��SD��д������  SD card to write data   ------*/
	for(i=0;i<512;i++) // ��buf��ֵ(Buf to assign a value to)
	{
	 	buffer[i]='a';	   // д��512����ĸ'a' (Written 512 letters' a ')
	}
	res = SD_WriteSingleBlock(10, buffer);// ��buf������д�뵽SD���ĵ�10������(Buf data written to the SD card of 10 sector)
	if(res==0)	 // ���д��ɹ�   (If written to the success)
	{
//		printf("Written to the success��\r\n");
	}
	else		 // ���д��ʧ�� (If written to the failure)
	{
//		printf("Written to the failure��\r\n");
	}

	/*------     ��SD��������    Read the SD card data ------*/
	for(i=0;i<512;i++) // ��buf��ֵ	  Buf to assign a value to
	{
	 	buffer[i]='b';	   // ��buf��ֵ���¸�ֵΪ��b�� (The value of the buf to value of "b")
	}
	res = SD_ReadSingleBlock(10, buffer);// ��SD���ĵ�10�����������Ѷ���ֵ����buf(Read the SD card sector 10, and read the value buf deposit)
	if(res==0)	 // ����������ݳɹ� (If read data success)
	{
//		printf("Read success��\r\n");
	}
	else		 // �����������ʧ��  (If read data failed)
	{
//		printf("Read data failed��\r\n");
	}

	if(res==0) // ����������ݳɹ�(If read data success)
	{
	   	for(i=0;i<512;i++)
		{
		   	if(buffer[i]!='a') // ���ÿһ�������������Ƿ�Ϊa(Testing every read data whether for a)
			break;			   // ֻҪ��һ�����ݲ���a������ǰ����forѭ��(As long as there is a data is not a, jumped out in advance for circulation)
		}
//		if(i==512) // ���i=512,����������ȫ��ȷ (If i = 512, that all the right data)
//		printf("Testing is complete��All the data are correct��\r\n");
//		else	   // ���i!=512,�����������ݷ�������(If i! = 512, or read data error)
//	printf("Testing is complete��Read the wrong data��\r\n");
	}
		
	while(1);
}