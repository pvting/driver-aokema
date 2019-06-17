#include <termios.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include "pthread_resolveData.h"
#include "data.h"
#include "serialPort.h"

#include <android/log.h>

#define   LOG_TAG    "LOG_TEST"
#define   LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

int fd;
struct  timeval tv;

int serialInitialization(char const * portName,unsigned int baudRate);

int serialPortInitialize()
{
    char portName[20]={0};
    int fd;
    char c;
    char buf[20]={0};
    int baudRate = 0;
    int i;


    memcpy(portName, "/dev/", 5);
    if (-1 == (fd = open("/sdcard/AUCMA/config.ini", O_RDONLY))) {  // 读取配置文件，获取串口号，波特率
        LOGI("open config error\n");
        return -1;
    }
    read(fd, &c, 1);
    while (c != 10) {
        i = 0;
        while (c != '=') {
            buf[i++] = c;
            read(fd, &c, 1);
        }
        i = 0;
        if (!memcmp("commport", buf, 8)) {
            read(fd, &c, 1);
            while (c != 10) {
                portName[5 + i] = c;
                i++;
                read(fd, &c, 1);
            }
            portName[5 + i] = 0;  // 串口号
        } else if (!memcmp("baudrate", buf, 8)) {
            read(fd, &c, 1);
            while (c != 10) {
                baudRate = baudRate * 10 + c - 48;  // 波特率
                read(fd, &c, 1);
            }
        } else if (!memcmp("debug", buf, 5)) {
            read(fd, &c, 1);
            i = 0;
            while (c != 10) {
                buf[i++] = c;
                read(fd, &c, 1);
            }
            // if (!memcmp("true", buf, 4))
            //      debug = true;
            //  else
            //      debug = false;
        }
        read(fd, &c, 1);
    }
    if (-1 == close(fd)) {
        printf("close config error");
        return -2;
    }

    serialInitialization(portName, baudRate);
}

int serialInitialization(char const* portName,unsigned int baudRate)
{
    struct termios Opt;
    speed_t s;
    fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);	
    //fd = open("ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
printf("portName = %s\n", portName);
    if (fd >0) 
        printf("serial open successful\n");
    else 
    {
        printf("serial open error\n");
        return -1;
    }
    if (0 == fcntl(fd, F_SETFL, 0)) 
        printf("serial fcntl successful\n");
    else
    {
        printf("serial fcntl error\n");
        return -1;
    }
    if (0 == tcgetattr(fd, &Opt)) 
        printf("serial tcgetattr successful\n");
    else
    {
        printf("serial tcgetattr error\n");  
        return -1;     
    }
    switch (baudRate) {
    case 115200 :
        s = B115200;
        break;
    case 38400 :
        s = B38400;
        break;
    case 19200 :
        s = B19200;
        break;
    case 9600:
        s = B9600;
        break;
    default :
       printf("serial baudRate error\n");
    }
    cfsetispeed(&Opt, s); 					
    cfsetospeed(&Opt, s);


//Opt.c_cflag &= ~CSTOPB;  // one stop bit
//Opt.c_cflag |= (CLOCAL | CREAD);

//Opt.c_cflag &= ~PARENB;     //no
//Opt.c_cflag &= ~CSTOPB;    //one stop bit
//Opt.c_cflag &= ~CSIZE;
//Opt.c_cflag |= CS8;       //length

	// raw input/output
   cfmakeraw(&Opt);  // no parity, Mask the character size bits, 8 bit
  //  Opt.c_cflag |= PARENB;     
  //  Opt.c_cflag &= ~PARODD; 
  //  Opt.c_iflag |= (INPCK /*| ISTRIP*/);     
	//Opt.c_cc[VMIN] = 1;		
	//Opt.c_cc[VTIME] = 0;

    tcflush(fd, TCIOFLUSH);
    if (tcsetattr(fd, TCSANOW, &Opt) != 0)
       printf("serial tcsetattr error\n");  
    else
        printf("serial tcsetattr successful\n");

    return 0;
}

int  SendComStatus(int n)
{
    nReadStatus = n;
    return 0 ;
}

int getComStatus()
{
    return nReadStatus;
}

void getCommStatus()
{
    setEvent(VMC_COMMSTATUS);

}


int getCommStatusRpt(unsigned char *gComm)
{
    int len;
    char szCommStatus[2+1];
    memset(szCommStatus,0,sizeof(szCommStatus));


    //LOGI("nReadStatus = %d\n",nReadStatus);
    if (0 == nReadStatus)       //Read SUCC
    {
        memcpy(szCommStatus,"C0",2);
        memcpy(gComm, szCommStatus, sizeof(szCommStatus));
    }
    else if(1 == nReadStatus)
    {
        memcpy(szCommStatus,"C1",2);
        memcpy(gComm, szCommStatus, sizeof(szCommStatus));
    }

    printf("*****nReadStatus =  %d\n,szCommStatus = %s\n",nReadStatus,szCommStatus);
    return sizeof(szCommStatus);

}



void readData(unsigned char* buf,unsigned int bufSize)
{ 
    unsigned int len = 0;
    int len1;

    while (len < bufSize) {
        len1 = read(fd, (char*)(buf + len), bufSize - len);       
        if (-1 == len1) {
            printf("serial read error\n");
            nReadStatus = 1;
        }
        else 
            printf("serial read successful\n");
        len += len1;
    }
    nReadStatus = 0;
}

void writeData(unsigned char const* buf, unsigned int bufSize)
{
    unsigned int len = 0;
	int len1;

	while (len < bufSize) {
		len1 = write(fd, (char*)(buf + len), bufSize - len);
		if (-1 == len1) {
			printf("serial write error\n");
          //  nWriteStatus = 1;
		}
		len += len1;
	}
  //  nWriteStatus =0;
}

void CurrentTime()
{
    gettimeofday(&tv,NULL);
    strftime(timebuf,sizeof(timebuf)-1 ,"%Y-%m-%d %H:%M:%S",localtime(&tv.tv_sec));
}


void* threadDaemon(void *arg)
{
    while(1) {
        nReadStatus = 1;
        sleep(10);
        if(1 == nReadStatus)
            SendComStatus(1);


        CurrentTime();
        printf("%s",timebuf);
        printf("status  = %d\n", nReadStatus);
        LOGI("status  = %d\n", nReadStatus);

    }

}

