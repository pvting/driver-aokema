#ifndef _DATA_H
#define _DATA_H

#define SERIAL_FAIL  -1
#define PTHREAD_FAIL -2


#define START_VALUE  "FE55EF"
#define SENDSTART_VALUE "EF55FE"

#define START_ADDRESS



enum MACHINETYPE {
    BEVERAGEMACHINE,
    SPRING48MACHINE,
    SPRING60MACHINE,
    BOXMACHINE,
};




static int nEventID = 0;



#define  DEVICE_REGISTER             0x78
#define  SYSTEM_ERROR          0x79
#define  CHANNEL_ERROR               0x7A
#define  BEVERAGECHANNEL_SETTING     0x73
#define  BEVERAGECHANNEL_GOODS       0x7B
#define  VENDEROUT_RPT               0x7C
#define  STATUS_RPT                  0x7D
#define  POLL                        0x76
#define  QUARRY_AMOUNT               0x77
#define  QUARRY_RECORD               0x74


#define PUSH_BUTTON_EVENT_ID   0x01




#define RECEIVE_BUF 512

static unsigned int nLen;
static unsigned int nFrame_len;
static unsigned int nCMD;
unsigned char nFcc;


static unsigned char cAddress;
static unsigned char cChannelAddress; 
static unsigned char Number;
static unsigned char szPrice[2+1]={0};
static unsigned int PollFlag;
static unsigned char cFaultReason;
static unsigned  char cIsOpen;
static unsigned char timebuf[64]={0};   //储存当地时间
static int nReadStatus = 0;
static unsigned  char szRefundPrice[2+1]={0};
static unsigned int setPriceFlag  = 0;
static unsigned char szTotalAmount[3+1] ={0};
static unsigned char szOldTotalAmount[3+1]={0};
static unsigned char cRunningStateBit;
static unsigned char cOldRunningStateBit = 0;




static unsigned char DataSend[RECEIVE_BUF] ={0};
static unsigned char FrameSend[RECEIVE_BUF] = {0};
static unsigned int  nDataSendLen;
static unsigned int  nFrameSendLen;
static unsigned char szSign[2+1]={0};
static unsigned char szBoxNum[2]= {0};
static unsigned char szChannelNum[2];
static unsigned char szChannelPrice[2];
static unsigned char cBoxAddress;
static unsigned char cChannelValue;
static unsigned char cProductPriceHigh;
static unsigned char cProductPriceLow;


static unsigned char szPayAmount[4+1] = {0};  //Ͷ�һ�ˢ�����
static unsigned char cPayType ;
static unsigned char szBeverageInventory[10+1]={0};
static unsigned char szSpringMachine48Inventory[10+1] ={0};
static unsigned char szSpringMachine60Inventory[16+1] ={0};
static unsigned char szBoxInventory[10+1]={0};

static unsigned char szSpring48ChannelsInfo[10+1];
static unsigned char szSpring60ChannelsInfo[20];
static unsigned char szBoxChannelsInfo[10+1];



static unsigned char FrameReceive[RECEIVE_BUF] = {0};
static unsigned char szMainVersion[2+1];                    //���ذ�汾��
static unsigned int nDriverVersion;                         //������汾��
static unsigned int szDispenserNo[2+1];                         //�ۻ������
static unsigned int nHostMachineType;                           //��������
static unsigned int nProtocolType;                          //Э�鷽ʽ
static unsigned int nSpringMachineVersion;
static unsigned int nBoxMachineVersion1;
static unsigned int nBoxMachineVersion2;
static unsigned int nBoxMachineVersion3;
static unsigned int nBoxMachineVersion4;
static unsigned int nBoxMachineVersion5;
static unsigned int nBoxMachineVersion6;
static unsigned int nBoxMachineVersion7;
static unsigned int nBoxMachineVersion8;

static unsigned char cSystemBreakdown;
static unsigned char cBillvalidatorBreakdown;
static unsigned char cCoinselectorBreakdown1;
static unsigned char cCoinselectorBreakdown2;
static unsigned char cCommBreakdown;
static unsigned char cSpringMachineBreakdown;
static unsigned char cReserved1;
static unsigned char cReserved2;
static unsigned char szSystemFault[8+1]={0};

 static unsigned char cAddress;
 static unsigned char szChannelFault[16+1]={0};




static unsigned char cMaxBeverageChannels;
static unsigned char cMachineInfo;
static unsigned char szMachineData[7+1]= {0};
static unsigned char cMachineType;
	



static unsigned char cBeveragechannel;
static unsigned char szSalseAmount[4+1];//�������
static unsigned char szReferenceNo[2+1];//�������к�
static unsigned char szCardNo[10+1];//����
static unsigned char cPaytype;//֧����ʽ
static unsigned char szProductsNo[4+1];//��Ʒ���
static unsigned char cFalseNo;//���ϴ���
static unsigned char szRemainAmount[4+1];//��ʣ����
static unsigned char szTransTime[7+1];//����ʱ��
static unsigned char szControlNo[2+1];//�������к�

	



static unsigned char szProductsPrice[4+1];
static unsigned char cRemain1;
static unsigned char cRemain5;
static unsigned char cRunningState;
static unsigned char cDeviceCode;
static unsigned char cKeyValue;
static unsigned char cSalseMode;
static unsigned char szEnergyTime[4+1];
static unsigned char szLampTime[4+1];

static unsigned char cBeverageMachineStatus ;
static unsigned char cLeftRoomCold ;
static unsigned char cLampOpen;
static unsigned char cLampAuto;
static unsigned char cLeftRoomHot;
static unsigned char cRightRoomHot;
static unsigned char cRightRoomCold;
static unsigned char cSpringMachineStatus;
static unsigned char cSpringMachineCold;
static unsigned char cSpringMachineLampOpen;
static unsigned char cSpringMachineLampAuto;
static unsigned char cSpringMachineHot;
static unsigned char cSpringMachineInfraredCheck;
static unsigned char cSpringMachineInfraredButton;
static unsigned char cBoxMachineLampStatus;
static unsigned char cBoxMachineLamp1;
static unsigned char cBoxMachineLamp2;
static unsigned char cBoxMachineLamp3;
static unsigned char cBoxMachineLamp4;
static unsigned char cBoxMachineLamp5;
static unsigned char cBoxMachineLamp6;












#define VMC_SYSTEMFAULT  0xA1
#define VMC_CHANNELFAULT 0xA2
#define VENDEROUT_REPORT   0xA3
#define VENDEROUT_STATUS 0xA4
#define VENDEROUT_REGISTER 0xA5
#define VENDER_CHANNELSETTING 0xA6
#define VENDER_SETTING   0xA7
#define VMC_SYSTEMFAULT  0xA8
#define CAHNNEL_STATUS   0xA9

#define SUSPENSION_BUSINESS 0xB0
#define DOOR_OPEN   0xB1

#define GOODSOUT_SUCCESS_EVENT_ID 0xB2
#define SETOUT_GOODS_FAILURE_EVENT_ID 0xB3
#define SETPRICESUCC  0xB4
#define SETPRICEFAIL  0xB5
#define DOOE_CLOSE  0xB6
#define GET_MONEY   0xB7


#define VMC_COMMSTATUS 0xC1


static unsigned  char vendoutStatusReceived[44+1]={0};
static unsigned  char vendoutRptReceived[47+1]={0};
static unsigned  char szChannelStatus[13+1]={0};
static unsigned  char vendoutChannelSetting[20]={0};
static unsigned  char szChannelError[11+1]={0};
static unsigned  char szSystemError[9+1]={0};
static unsigned  char vendoutRegisterReceived[18+1]={0};





#endif