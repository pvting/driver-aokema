#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include "data.h"
#include "serialPort.h"
#include "pthread_resolveData.h"
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>

#include <android/log.h>

#define   LOG_TAG    "LOG_TEST"
#define   LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


struct  timeval tv;


sem_t event_sem_id;

void setEvent(int Id) {
LOGI("setEvent");
    nEventID = Id;
    sem_post(&event_sem_id);
}

int getEvent() {
    sem_wait(&event_sem_id);  //等待事件发生
    return nEventID;
}


void clearData()
{	
    memset(FrameReceive,0, sizeof(FrameReceive));
	memset(FrameSend,0, sizeof(FrameSend));
	memset(DataSend,0, sizeof(DataSend));
	nDataSendLen = 0;
	PollFlag = 0;
}


void setPollFlag(int setValue)
{
	PollFlag = setValue;
printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%PollFlag =%d\n",PollFlag);	
}

#if 1
void PrintDebug(unsigned char *data, int len,int type)
{
    int i = 0;
    char temp[2048], buf[128],disp[10];

    memset(temp, 0, sizeof(temp));
	memset(disp,0,sizeof(disp));
	if(1 == type)
	    memcpy(disp,"[write]",sizeof("[write]"));
	else if(0 == type)
		memcpy(disp,"[read]",sizeof("[read]"));

    sprintf(temp, "\r\n%s:%d", disp, len);
    for(i = 0; i < len; i++)
    {
        if(i % 16 == 0)
        {
            strcat(temp, "\r\n");
            if(strlen(temp) >= 1024)
            {
                LOGI("%s", temp);
                memset(temp, 0, sizeof(temp));
            }
        }
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "%02X ", data[i]);
        strcat(temp, buf);
    }
    strcat(temp, "\r\n");
    LOGI("%s", temp);
}
#endif

#if 0
void PrintDebug(unsigned char *data, int len,int type)
{
    int i = 0;
    char temp[2048], buf[128],disp[10];
	
    memset(temp, 0, sizeof(temp));
	memset(disp,0,sizeof(disp));
	if(1 == type)
	    memcpy(disp,"[write]",sizeof("[write]"));
	else if(0 == type)
		memcpy(disp,"[read]",sizeof("[read]"));
	
    sprintf(temp, "\r\n%s:%d", disp, len);
    for(i = 0; i < len; i++)
    {
        if(i % 16 == 0)
        {
            strcat(temp, "\r\n");
            if(strlen(temp) >= 1024)
            {
                LOGI("%s", temp);
                memset(temp, 0, sizeof(temp));
            }
        }
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "%02X ", data[i]);
        strcat(temp, buf);
    }
    strcat(temp, "\r\n");
    LOGI("%s", temp);
}
#endif

void frameSendDataGenerate(unsigned char cmd, unsigned char*data,unsigned int datasize)
{	
	int i;
	nFcc= 0x00;
    int nSendLen ; 
    char szCheckValue[100+1]={0};
 nSendLen = datasize+2;
	//FrameSend[0] = START_VALUE;
	//memcpy(FrameSend,sz,3);
	FrameSend[0]= 0xEF;
	FrameSend[1]= 0x55;
	FrameSend[2] = 0xFE;
	 	
	FrameSend[3] = datasize+2;
	FrameSend[4] = cmd;
	//if(1 == datasize )
	//    FrameSend[5] = &data;
    //else
         memcpy(FrameSend+5,data,datasize);
	//memcpy(FrameSend + 4, data, datasize);
printf("Data Genenrate\n");
for(i=0;i<nSendLen+3;i++)
	printf("%02x ",FrameSend[i]);

printf("\n");



    memcpy(szCheckValue,FrameSend+3,nSendLen);
for(i=0;i<nSendLen;i++)
    printf("%02x \n",szCheckValue[i]);
    printf("~~~~~~~~~~\n");


    for(unsigned int i=0;i<nSendLen;i++)
        nFcc+=szCheckValue[i];
    // nFcc =0x7B;
    printf("nFcc = %02x \n",nFcc);

    FrameSend[nSendLen +3] = nFcc;
	nFrameSendLen = nSendLen+1+3;
}



void ReturnAddproducts()
{
    DataSend[0] = 0x01;  //加货
    DataSend[1]= cAddress ;
	DataSend[2] = cChannelAddress;
	DataSend[3]= Number;
	nDataSendLen = 4;
	frameSendDataGenerate(POLL,DataSend, nDataSendLen);
	writeData(FrameSend, nFrameSendLen);

    PrintDebug(FrameSend, nFrameSendLen, 1);
    clearData();


}

#if 0
void ReturnProductsCode()
{
    DataSend[0] = 02;  //�ӻ�
    DataSend[1] =  Address ;
	DataSend[2] = channelNum ;
	DataSend[3] = productsCode1;
	DataSend[4] = productsCode2 ;
	DataSend[5] = productsCode3 ;
	DataSend[6] = productsCode4 ;
	DataSend[7] = productsCode5 ;
	nDataSendLen = 10;
	frameSendDataGenerate(POLL,DataSend, nDataSendLen);
	writeData(FrameSend, nFrameSendLen);
	
}
#endif

void ReturnSetIsOpen()
{
    DataSend[0] = 0x03;  //是否营业
    DataSend[1] =cIsOpen;
	nDataSendLen = 2;
	frameSendDataGenerate(POLL,DataSend, nDataSendLen);
	writeData(FrameSend, nFrameSendLen);
	
}

void ReturnMachineTime()
{
    DataSend[0] = 0x04; //售货机时间设定
    // DataSend[1] =szTime[];
	nDataSendLen = 9;
	frameSendDataGenerate(POLL,DataSend, nDataSendLen);
	writeData(FrameSend, nFrameSendLen);
}


void ReturnOutProductsAction()
{

	int nRand;
	char szTemp[2+1]={0};

	DataSend[0] = 0x05;

    srand((unsigned )time(NULL));
    nRand = rand()%100;
printf("@@@@@%d\n", nRand);
    sprintf(szTemp,"%d",nRand);

	memcpy(DataSend+1,szTemp,2);
	DataSend[3]=cAddress;
	DataSend[4]=cChannelAddress;
	DataSend[5]=0x01;
    LOGI("！！！！！cAddress = %d\n",DataSend[3]);
    LOGI("！！！！！cChannelAddress = %d\n",DataSend[4]);
    LOGI("！！！！！cPaytype = %d\n",DataSend[5]);
	memcpy(DataSend+6,"\x00\x00\x00\x00\x00\x00",6);    //支付金额
    if(1 == cPaytype)
	    DataSend[12]=0x00;   //扣款出货方式
    else
        DataSend[12]=0x01;   //扣款出货方式
    DataSend[13]=0;
    DataSend[14]=0x01; //金额变价0元按原价计入 1-现金
    memcpy(DataSend+15,"\x00\x00\x00\x00\x00\x00\x00\x00",6);

    nDataSendLen = 21;
	frameSendDataGenerate(POLL,DataSend, nDataSendLen);
	writeData(FrameSend, nFrameSendLen);
    PrintDebug(FrameSend, nFrameSendLen, 1);	
	clearData();

}

void ReturnVenderOutRequest()
{
   DataSend[0]= 0x77;
   DataSend[1]=cAddress;
   DataSend[2]=cChannelAddress;
   DataSend[3]=0x0;
   nDataSendLen = 4;
printf("~~~~~~~cAddress = %d\n",cAddress);
printf("~~~~~~~cChannelAddress = %d\n",cChannelAddress);
   
   frameSendDataGenerate(POLL,DataSend, nDataSendLen);
   writeData(FrameSend, nFrameSendLen);
   PrintDebug(FrameSend, nFrameSendLen, 1);	
	clearData();
}

void ReturnChannelTest()
{
	DataSend[0]= 0x07;
    memcpy(DataSend+1,"\x00\x00",2);
	DataSend[3]=cAddress;
	DataSend[4]=cChannelAddress;
	memcpy(DataSend+5,"\x00\x00",2);
	nDataSendLen = 7;

	frameSendDataGenerate(POLL,DataSend, nDataSendLen);
	writeData(FrameSend, nFrameSendLen);
	PrintDebug(FrameSend, nFrameSendLen, 1);
	clearData();
}

void ReturnPriceSetting()
{
    LOGI("###########################  调用设置价格函数\n");
    setPriceFlag = 1;
	DataSend[0] = 0x08;
	DataSend[1]= cAddress;
	DataSend[2]= cChannelAddress;
	memcpy(DataSend+3,"\x00\x00",2);
	DataSend[5]=szPrice[1];
	DataSend[6]=szPrice[0];

	nDataSendLen = 7;
	frameSendDataGenerate(POLL,DataSend, nDataSendLen);
	writeData(FrameSend, nFrameSendLen);
    PrintDebug(FrameSend, nFrameSendLen, 1);
    clearData();


}

void ReturnRefund()
{

	DataSend[0]= 0x09;
	DataSend[1] = szRefundPrice[1];
	DataSend[2]= szRefundPrice[0];
	nDataSendLen = 3;
	frameSendDataGenerate(POLL,DataSend, nDataSendLen);
	writeData(FrameSend, nFrameSendLen);
    PrintDebug(FrameSend, nFrameSendLen, 1);
    clearData();

}

void  ReturnChannelError()
{
    DataSend[0] = 0x7A;
    DataSend[1] = cAddress;
    DataSend[2] = 0;
    DataSend[3] = 0;

    nDataSendLen = 4;
    frameSendDataGenerate(POLL,DataSend, nDataSendLen);
    writeData(FrameSend, nFrameSendLen);
    PrintDebug(FrameSend, nFrameSendLen, 1);
    clearData();

}

void ReturnInventoryInfo()
{
    DataSend[0] = 0x7B;
    DataSend[1] = cAddress;
    DataSend[2] = 0;
    DataSend[3] = 0;

    nDataSendLen = 4;
    frameSendDataGenerate(POLL,DataSend, nDataSendLen);
    writeData(FrameSend, nFrameSendLen);
    PrintDebug(FrameSend, nFrameSendLen, 1);
    clearData();

}


void ReturnMachineStatus()
{
    DataSend[0] = 0x7D;
    DataSend[1] = 0;
    DataSend[2] = 0;
    DataSend[3] = 0;

    nDataSendLen = 4;
    frameSendDataGenerate(POLL,DataSend, nDataSendLen);
    writeData(FrameSend, nFrameSendLen);
    PrintDebug(FrameSend, nFrameSendLen, 1);
    clearData();

}


void ReturnMachineVersion()
{
    DataSend[0] = 0x78;
    DataSend[1] = 0;
    DataSend[2] = 0;
    DataSend[3] = 0;

    nDataSendLen = 4;
    frameSendDataGenerate(POLL,DataSend, nDataSendLen);
    writeData(FrameSend, nFrameSendLen);
    PrintDebug(FrameSend, nFrameSendLen, 1);
    clearData();

}

void ReturnSystemFaultInfo()
{
    DataSend[0] = 0x79;
    DataSend[1] = 0;
    DataSend[2] = 0;
    DataSend[3] = 0;

    nDataSendLen = 4;
    frameSendDataGenerate(POLL,DataSend, nDataSendLen);
    writeData(FrameSend, nFrameSendLen);
    PrintDebug(FrameSend, nFrameSendLen, 1);
    clearData();

}




int VenderOutRequest(char cSetAddress,char cSetChannelAddress)
{
    cAddress =  cSetAddress;
    cChannelAddress = cSetChannelAddress;
printf("@@@@cAddress = %d\n",cAddress);
printf("@@@@cChannelAddress = %d\n",cChannelAddress);
    PollFlag = 3;
	return 0;
}

int VenderOutAction(char cSetPaytype,char cSetAddress,char cSetChannelAddress)
{
    cPaytype = cSetPaytype;
    cAddress = cSetAddress;
    cChannelAddress = cSetChannelAddress;
	PollFlag = 4;
 LOGI("\n\n cPaytype = %d\n",cPaytype);
    LOGI("\n\n cAddress = %d\n",cAddress);
    LOGI("\n\n cChannelAddress = %d\n",cChannelAddress);
	return 0;
}

int ChannelTest(char cTestAddress,char cTestChannelAddress)
{
	cAddress= cTestAddress;
	cChannelAddress = cTestChannelAddress;
	PollFlag = 5;
	return 0;


}

int SetPrice(char cSetAddress,char cSetChannelAddress,int nSetPrice)
{
	memset(szPrice,0, sizeof(szPrice));
	cAddress=cSetAddress;
	cChannelAddress=cSetChannelAddress;

    char *p = (char*)&nSetPrice;

    szPrice[0]= *p;
    szPrice[1]= *(p+1);
    LOGI("szSetPrice = %d,szSetPrice = %02x ",nSetPrice,nSetPrice);
LOGI("szPrice[0] =%02x ",szPrice[0]);
	LOGI("szPrice[1] =%02x ",szPrice[1]);
	PollFlag = 6;


	return 0;

}




int SetMachineTime(char * szSetTime)
{
    //   memcpy(szTime,szSetTime,6);
    PollFlag = 7;
    return 0;
}

int Refund(int nRefundPrice)
{
    memset(szRefundPrice,0, sizeof(szRefundPrice));
    char *p = (char*)&nRefundPrice;
    szRefundPrice[0]= *p;
    szRefundPrice[1]= *(p+1);
LOGI("nRefundPrice = %d\n",nRefundPrice);
LOGI("退币价格 = %02x %02x\n",szRefundPrice[0],szRefundPrice[1]);
	PollFlag = 8;
	return 0;
}




int GetChannelError(char cSetAddress)
{
    cAddress = cSetAddress;
    PollFlag = 9;
    return 0;
}


int GetInventory(char cSetAddress)
{
    cAddress = cSetAddress;
    PollFlag = 10;
    return 0;

}

int GetMachineStatus()
{
    PollFlag = 11;
    return 0;
}


int GetMachineVersion()
{
    PollFlag = 12;
    return 0;

}

int GetSystemFaultInfo()
{
    PollFlag = 13;
    return 0;
}

int addproducts(char setAddress,char setChannel,char setNumber)
{
  cAddress = setAddress;
  cChannelAddress = setChannel;
  Number = setNumber;
  PollFlag = 1;
  return  0;
}



int SetIsOpen(char cSetIsOpen)
{
    cIsOpen = cSetIsOpen;
    PollFlag = 2;
    return 0;
}

void getCurrentTime()
{
    gettimeofday(&tv,NULL);
    strftime(timebuf,sizeof(timebuf)-1 ,"%Y-%m-%d %H:%M:%S",localtime(&tv.tv_sec));

}

void returnAck()
{
    memcpy(DataSend,"\x00\x00\x00\x00",4);
    nDataSendLen= 4;
    frameSendDataGenerate(POLL,DataSend,nDataSendLen);
    writeData(FrameSend, nFrameSendLen);
    PrintDebug(FrameSend, nFrameSendLen, 1);
    clearData();
}



void* pthread_resolveData(void *arg)
{
    if(1)
    {
        char filename[60] = "/sdcard/AUCMA/log";
        //  char filename[60] = "log";
        int f_original_len = strlen(filename);
        getCurrentTime();
        memcpy(filename+f_original_len,timebuf,19);
        memcpy(filename+f_original_len+19,".txt",4);
        if(freopen(filename,"w",stdout) == NULL)
        {
            LOGI("log create error\n");
        }

    }

LOGI("\nthread start1\n");
    int i;
    int nType;
    char cGetValid; char cStatus;
    char ReceiveStart[3+1] = {0};
    memset(FrameReceive,0,sizeof(FrameReceive));
LOGI("\nthread start1\n");
    while(1)
    {
     SendComStatus(0);
        int comRet;
      //  comRet = getComStatus();
        LOGI("COMM  = %d\n",comRet);

     readData(FrameReceive,3);
     memcpy(ReceiveStart,FrameReceive,3);

//LOGI("FrameReceive start     ");
 for(i=0;i<3;i++)
 {
 	printf("%02x ", ReceiveStart[i]);
 }
 printf("\n");


 //    if(!memcmp(FrameReceive,START_VALUE,3))
     {
          
          readData(FrameReceive+3,1);
          nLen = FrameReceive[3];
printf("code len=%d\n",nLen);  
          readData(FrameReceive+4,nLen);
          nFrame_len = nLen+4;
          nCMD = FrameReceive[4];
printf("CMD = %02x\n",nCMD);    

PrintDebug(FrameReceive,nLen+3+1,0);
       
     }
          switch(nCMD)
          {
               case DEVICE_REGISTER:    //0x78
				   memset(vendoutRegisterReceived,0,sizeof(vendoutRegisterReceived));
 LOGI("nLen =%d\n",nLen);
                    memcpy(vendoutRegisterReceived,FrameReceive+4,nLen);
                    setEvent(VENDEROUT_REGISTER);
                    DataSend[0]=0;
                    nDataSendLen= 1;
                    frameSendDataGenerate(DEVICE_REGISTER,DataSend,nDataSendLen);
                    writeData(FrameSend, nFrameSendLen);
                    PrintDebug(FrameSend, nFrameSendLen, 1);
                    clearData();
                    break;
               case SYSTEM_ERROR:     //0x79
				   memset(szSystemError,0,sizeof(szSystemError));
                   memcpy(szSystemError,FrameReceive+4,nLen);
 LOGI("SYSTEM_ERROR nLen =%d\n",nLen);
                   setEvent(VMC_SYSTEMFAULT);
                   DataSend[0]=0;
                   nDataSendLen= 1;
                   frameSendDataGenerate(SYSTEM_ERROR,DataSend,nDataSendLen);
                   writeData(FrameSend, nFrameSendLen);
                   PrintDebug(FrameSend, nFrameSendLen, 1);
                   clearData();
                   break;
			    case CHANNEL_ERROR:    //0x7A
				    memset(szChannelError,0,sizeof(szChannelError));
                    memcpy(szChannelError,FrameReceive+4,nLen);
                    setEvent(VMC_CHANNELFAULT);
                    DataSend[0]=0;
                    nDataSendLen= 1;
                    frameSendDataGenerate(CHANNEL_ERROR,DataSend,nDataSendLen);
                    writeData(FrameSend, nFrameSendLen);
                    PrintDebug(FrameSend, nFrameSendLen, 1);
                    clearData();
                    break;



			   case BEVERAGECHANNEL_SETTING:   //0x73
			   	   nType = FrameReceive[5];
				   if(0 == nType)
				   	{
                        cMaxBeverageChannels = FrameReceive[6];
						cMachineInfo = FrameReceive[7];
						memcpy(szMachineData,FrameReceive+8,7);

						cGetValid = cMachineInfo & 0x80;
						if(1==cGetValid && 0 == szMachineData[0])
						{
                            cMachineType = SPRING48MACHINE;

						}
						else if (1 == cGetValid && 1== szMachineData[0])
						{
						    cMachineType = SPRING60MACHINE;
						}
						
						cGetValid = cMachineInfo &40;
						if (1 == cGetValid && 2== szMachineData[0])
						{
						    cMachineType = BOXMACHINE;
						}
							
				   }

                   else if (0 != nType) {
                       memset(vendoutChannelSetting, 0, sizeof(vendoutChannelSetting));
                       memcpy(vendoutChannelSetting, FrameReceive + 4, nLen);
                   }
                       setEvent(VENDER_CHANNELSETTING);
                       DataSend[0]=0;
                       nDataSendLen= 1;
                       frameSendDataGenerate(BEVERAGECHANNEL_SETTING,DataSend,nDataSendLen);
                       writeData(FrameSend, nFrameSendLen);
                       PrintDebug(FrameSend, nFrameSendLen, 1);
                       clearData();
                       break;

                  case BEVERAGECHANNEL_GOODS:      //0x7B
			    	  memset(szChannelStatus,0,sizeof(szChannelStatus));
				      memcpy(szChannelStatus,FrameReceive+4,nLen);
				      setEvent(CAHNNEL_STATUS);
				      DataSend[0]=0;
				      nDataSendLen= 1;
				      frameSendDataGenerate(BEVERAGECHANNEL_GOODS,DataSend,nDataSendLen);
				      writeData(FrameSend, nFrameSendLen);
				      PrintDebug(FrameSend, nFrameSendLen, 1);
				      clearData();
				      break;

					case VENDEROUT_RPT:     //0x7c
						memset(vendoutRptReceived,0,sizeof(vendoutRptReceived));
                       memcpy(vendoutRptReceived,FrameReceive+4,nLen);
                       setEvent(VENDEROUT_REPORT);
                       DataSend[0]=0;
                       nDataSendLen= 1;
                       frameSendDataGenerate(VENDEROUT_RPT,DataSend,nDataSendLen);
                       writeData(FrameSend, nFrameSendLen);
                       PrintDebug(FrameSend, nFrameSendLen, 1);
                       clearData();
				       break;
					case STATUS_RPT:         //0x7D
						memset(vendoutStatusReceived,0,sizeof(vendoutStatusReceived));
                        memcpy(vendoutStatusReceived,FrameReceive+4,nLen);
                        setEvent(VENDEROUT_STATUS);
                        DataSend[0]=0;
                        nDataSendLen= 1;
                        frameSendDataGenerate(STATUS_RPT,DataSend,nDataSendLen);
                        writeData(FrameSend, nFrameSendLen);
                        PrintDebug(FrameSend, nFrameSendLen, 1);
                        clearData();
                        break;
					case POLL:

						cStatus = FrameReceive[5];
                  LOGI("taggg::PollFlag=%d，setPriceFlag = %d ,cStatus = %02x\n",PollFlag,setPriceFlag,cStatus);
                        if(1 == setPriceFlag && 0 == cStatus)    //设置价格通知
                        {
                            setEvent(SETPRICESUCC);
                            LOGI("taggg::设置价格成功发送通知\n");
                            setPriceFlag = 0;

                            returnAck();
                            break;
                        }
                        else if(1 == setPriceFlag && 0!= cStatus)
                        {
                            setEvent(SETPRICEFAIL);
                            LOGI("设置价格失败发送通知\n");
                            setPriceFlag = 0;

                            returnAck();
                            break;
                        }

						if (7 == cStatus ||17 == nLen)
						{
                            cRunningState = FrameReceive[19];
							if(1 == cRunningState )
							{
								setEvent(SUSPENSION_BUSINESS);   //暂停营业
							}
/****changed by chen in 2017.05.22***/
                            cRunningStateBit = (cRunningState >> 2) & 0x01;
                            if(cRunningStateBit != cOldRunningStateBit &&1 == cRunningStateBit)
                            {
                                setEvent(DOOR_OPEN);   //门开
                            }
                            else if(cRunningStateBit != cOldRunningStateBit &&0 == cRunningStateBit)
                            {
                                setEvent(DOOE_CLOSE);   //门关
                            }
                            cOldRunningStateBit = cRunningStateBit;
/****changed by chen in 2017.05.22***/
#if 0
							else if(1==((cRunningState >> 2) & 0x01))
							{

								setEvent(DOOR_OPEN);   //门开
							}
                            else if(0==((cRunningState >> 2) & 0x01))
                            {
                                LOGI("###门关\n");
                                setEvent(DOOE_CLOSE);   //门关
                            }
#endif

                            memcpy(szTotalAmount,FrameReceive+12,3);

                            if(memcmp(szTotalAmount,szOldTotalAmount,3))
                            {
                                setEvent(GET_MONEY);
                            }
                            memcpy(szOldTotalAmount,szTotalAmount,3);

                        }
						else if(0x00 == cStatus||0x01 == cStatus||3 == nLen)
						{
                            setEvent(GOODSOUT_SUCCESS_EVENT_ID);
						}
				        else if(3 == nLen)
						{
							cFaultReason=cStatus;
							setEvent(SETOUT_GOODS_FAILURE_EVENT_ID);

						}
						if(1 == PollFlag)
						{
                            ReturnAddproducts();
                            clearData();
                            break;

						}
                        else if(2 == PollFlag)
                        {
                            ReturnSetIsOpen();
                            clearData();
                            break;
                        }
						else if(3 == PollFlag)
						{

							ReturnVenderOutRequest();
							clearData();
							break;

						}
						else if (4 == PollFlag) {
							ReturnOutProductsAction();
							clearData();
							break;
						}
                        else if(5 == PollFlag){
							ReturnChannelTest();
							clearData();
							break;
						}
				        else if(6 == PollFlag)
						{
							ReturnPriceSetting();
                            setPriceFlag = 1;
                            clearData();
                            break;
						}
                        else if(7 == PollFlag)
                        {
                            ReturnMachineTime();
                            clearData();
                            break;
                        }
                        else if(8 ==PollFlag)
                        {
                            ReturnRefund();
                            clearData();
                            break;
                        }
                        else if(9 ==PollFlag)
                        {
                            ReturnChannelError();
                            clearData();
                            break;
                        }
                        else if(10 ==PollFlag)
                        {
                            ReturnInventoryInfo();
                            clearData();
                            break;
                        }
                        else if(11 ==PollFlag)
                        {
                            ReturnMachineStatus();
                            clearData();
                            break;
                        }
                        else if(12 ==PollFlag)
                        {
                            ReturnMachineVersion();
                            clearData();
                            break;
                        }
                        else if(13 ==PollFlag)
                        {
                            ReturnSystemFaultInfo();
                            clearData();
                            break;
                        }

						//DataSend[0]=0;
                        memcpy(DataSend,"\x00\x00\x00\x00",4);
                        nDataSendLen= 4;
				        frameSendDataGenerate(POLL,DataSend,nDataSendLen);
				        writeData(FrameSend, nFrameSendLen);
				        PrintDebug(FrameSend, nFrameSendLen, 1);  
				        clearData();


						break;
					case QUARRY_AMOUNT:           //0x77
					
						if(0==cChannelValue)     //�ϵ�Ϊ0
						{
						    memcpy(szPayAmount,FrameReceive+6,4);
						    cPayType = FrameReceive[11];
						    cBoxAddress = FrameReceive[12];
						}
						else if(0 !=cChannelValue && 0 == cBoxAddress)  //���ϻ�
						{
                             memcpy(szPayAmount,FrameReceive+6,4);
							 cPayType = FrameReceive[11];
							 cBoxAddress = FrameReceive[12];
							 memcpy(szBeverageInventory,FrameReceive+12,10);
						}
						else if(0 !=cChannelValue && 1 ==cBoxAddress) //48���ɻ�
						{
						     memcpy(szPayAmount,FrameReceive+6,4);
							 cPayType = FrameReceive[11];
							 cBoxAddress = FrameReceive[12];
							 memcpy(szSpringMachine48Inventory,FrameReceive+12,10);
						}

					     else if (0 !=cChannelValue && 1== cBoxAddress)
						 {
                             memcpy(szPayAmount,FrameReceive+6,4);
							 cPayType = FrameReceive[11];
							 cBoxAddress = FrameReceive[12];     
							 memcpy(szSpringMachine60Inventory,FrameReceive+12,16);
					
						}
						else if (0 !=cChannelValue && (cBoxAddress >1 || cBoxAddress <8))
						{
						     memcpy(szPayAmount,FrameReceive+6,4);
							 cPayType = FrameReceive[11];
							 cBoxAddress = FrameReceive[12];     
							 memcpy(szBoxInventory,FrameReceive+12,16);
                            

						}	

printf("cPayType == %d\n", cPayType);
printf("szPayAmount =%s\n",szPayAmount);						
						DataSend[0]=0;
                        nDataSendLen= 1;
				        frameSendDataGenerate(QUARRY_AMOUNT,DataSend,nDataSendLen);
				        writeData(FrameSend, nFrameSendLen);
				        PrintDebug(FrameSend, nFrameSendLen, 1);   	
				        clearData();

						break;

						default:
						       break;
						
				   }
          }
     }



int getVersion(unsigned char *gR)
{
    int i;
	memcpy(gR,vendoutRegisterReceived, sizeof(vendoutRegisterReceived));
	return sizeof(vendoutRegisterReceived);
}

int getSystemFailureInfo(unsigned char *gR)
{
	memcpy(gR,szSystemError, sizeof(szSystemError));
	return sizeof(szSystemError);

}

int getChannelFailureInfo(unsigned char *gR)
{
    memcpy(gR,szChannelError, sizeof(szChannelError));
	return sizeof(szChannelError);
}

int getChannelSetInfo(unsigned char *gR)
{
	memcpy(gR,vendoutChannelSetting, sizeof(vendoutChannelSetting));
	return sizeof(vendoutChannelSetting);

}

int getInventoryInfo(unsigned char *gR)
{
	memcpy(gR,szChannelStatus, sizeof(szChannelStatus));
	return sizeof(szChannelStatus);
}

int getVenderOutReport(unsigned char *gR)
{
	memcpy(gR,vendoutRptReceived, sizeof(vendoutRptReceived));
	return sizeof(vendoutRptReceived);

}


extern int getVenderStatus(unsigned char *gR)
{
	memcpy(gR,vendoutStatusReceived, sizeof(vendoutStatusReceived));
	return sizeof(vendoutStatusReceived);
}

extern int getVenderOutError(unsigned char *gR)
{


}

extern int getTotalPrice(unsigned char *gR)
{
    memcpy(gR,szTotalAmount, sizeof(szTotalAmount));
    return sizeof(szTotalAmount);
}