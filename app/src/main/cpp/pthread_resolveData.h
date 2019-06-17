#ifndef  _RESOLVE_H_
#define  _RESOLVE_H_

extern void* pthread_resolveData(void *arg);
extern void* threadDaemon(void *arg);
//void resolveData();
extern void setEvent(int Id);

extern void setEvent(int Id);
extern int getEvent();
extern int startProtocol(void);
extern int VenderOutRequest(char cSetAddress,char cSetChannelAddress);
extern int VenderOutAction(char cSetPaytype,char cSetAddress,char cSetChannelAddress);
extern int getVersion(unsigned char *gR);
extern int getSystemFailureInfo(unsigned char *gR);
extern int getChannelFailureInfo(unsigned char *gR);
extern int getChannelSetInfo(unsigned char *gR);
extern int getInventoryInfo(unsigned char *gR);
extern int getVenderOutReport(unsigned char *gR);
extern int getVenderStatus(unsigned char *gR);
extern int SetPrice(char cSetAddress,char cSetChannelAddress,int szSetPrice);
void setPollFlag(int setValue);
extern int  addproducts(char setAddress,char setChannel,char setNumber);
extern int SetIsOpen(char cSetIsOpen);
extern void getCommStatus();
extern int getCommStatusRpt(unsigned char *gComm);
extern int Refund(int nRefundPrice);
extern int getTotalPrice(unsigned char *gR);
extern int GetChannelError(char cSetAddress);
extern int GetInventory(char cSetAddress);
extern int GetMachineStatus();
extern int GetMachineVersion();
extern int GetSystemFaultInfo();



#endif

