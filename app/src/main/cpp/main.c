#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include "data.h"
#include "pthread_resolveData.h"
#include "serialPort.h"
#include <android/log.h>

#define   LOG_TAG    "LOG_TEST"
#define   LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)



pthread_t id_thread,
          id_resolve_data;



void ReleaseResource(int signo)
{
	exit(0);
}

int startProtocol()
{
    int nRet;
    nRet =serialPortInitialize();
//    if(0 != nRet)
//    	return SERIAL_FAIL;



    nRet = pthread_create(&id_thread,0,threadDaemon,NULL);
LOGI("already start\n");
    nRet = pthread_create(&id_resolve_data,0,pthread_resolveData,NULL);
//resolveData();
    if(0 == nRet)
    	printf("pthread_create succ\n");
    else
    {
        printf("pthread_create error\n");
    	//return PTHREAD_FAIL;
    }
  //  pthread_join (id_get_event, NULL);
    printf ("g1\n");
    pthread_join (id_resolve_data, NULL); 
    printf ("g2\n");
    

   // signal(SIGINT,ReleaseResource);
    return 0;
}