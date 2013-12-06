#include "ulongsort.h"
#include "adc.h"

volatile unsigned long mas_copy[ADC_BUF_SIZE];
volatile unsigned char xdata mid_cycle_counter=0;
volatile unsigned long  temp;


//------------------------------------------------
//#pragma OT(0,Speed) 
 PT_THREAD(ulongsort_process(struct pt *pt))
 {
   static volatile  unsigned char counter=0,i=0,j=0;
   
   PT_BEGIN(pt);

  while(1) 
  {
	   PT_DELAY(pt,1);
	  //------------���� ����� ���������-----------------

		if(!adc_channels[USO_CHANNEL].new_measuring)
		{
//			counter=0;
//			while((!adc_channels[mid_cycle_counter].new_measuring) && (counter!=ADC_CHANNELS_NUM))
//			{
//				mid_cycle_counter= (mid_cycle_counter+1)&0x7;
//				counter++;
//				PT_YIELD(pt);//������ ������ ���������
//			}
//			
//			if(counter==ADC_CHANNELS_NUM)//���� ������ ��������� �� �������-������� ��������
//			{
			    PT_RESTART(pt);
//			}
		}
	
	  //-----------------�������� �� ��������� ������-----------------------------
	   	memcpy(mas_copy,adc_channels[USO_CHANNEL].ADC_BUF_UN,ADC_BUF_SIZE*sizeof(unsigned long)); 
		PT_YIELD(pt);//������ ������ ���������
	  //--------------���������� ���������--------------------------------
		  for (i=ADC_BUF_SIZE-1;i>0;i--)
		  {
		    for (j=0;j<i;j++)
		    {
		        if(mas_copy[j]>mas_copy[j+1])
		        {
		            temp=mas_copy[j];
		            mas_copy[j]=mas_copy[j+1];
		            mas_copy[j+1]=temp;
		        }
				PT_YIELD(pt);
		     }
		  }
	   //-----------������� �������--------------------
	  	channels[USO_CHANNEL].channel_data=(mas_copy[(ADC_BUF_SIZE>>1)-1]+mas_copy[ADC_BUF_SIZE>>1])>>1;

		if(channels[USO_CHANNEL].calibrate.cal.calibrate)
		{
 			channels[USO_CHANNEL].channel_data_calibrate=GetCalibrateVal(USO_CHANNEL,channels[USO_CHANNEL].channel_data);	//������������� ��������
  		}

		adc_channels[USO_CHANNEL].new_measuring=0;
		PT_RESTART(pt);
	  //----------------------------------------------	
   }
   PT_END(pt);
 }

