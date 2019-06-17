#include <jni.h>
#include <string>
#include <android/log.h>

extern "C" {
#include "pthread_resolveData.h"
}

#define   LOG_TAG    "LOG_TEST"
#define   LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


extern "C"
JNIEXPORT jint JNICALL
Java_com_example_acuma_MainActivity_GetSystemFaultInfo(JNIEnv *env, jobject instance) {

    jint nRet;
    nRet = GetSystemFaultInfo();
    return nRet;

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_acuma_MainActivity_GetMachineVersion(JNIEnv *env, jobject instance) {

    jint nRet;
    nRet = GetMachineVersion();
    return nRet;

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_acuma_MainActivity_GetMachineStatus(JNIEnv *env, jobject instance) {

    jint nRet;
    nRet = GetMachineStatus();
    return nRet;

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_acuma_MainActivity_GetInventory(JNIEnv *env, jobject instance,
                                                           jchar cSetAddress) {

    jint nRet;
    nRet = GetInventory(cSetAddress);
    return nRet;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_acuma_MainActivity_GetChannelError(JNIEnv *env, jobject instance,
                                                    jchar cSetAddress) {
    jint nRet;
    nRet = GetChannelError(cSetAddress);
    return nRet;
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_acuma_MainActivity_getTotalPrice(JNIEnv *env, jobject instance) {

    jbyte gR[3+1];
    jint len = getTotalPrice((unsigned char*)gR);
    jbyteArray ret=(*env).NewByteArray(len);
    (*env).SetByteArrayRegion(ret,0,len,gR);
    return ret;

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_acuma_MainActivity_Refund(JNIEnv *env, jobject instance, jint nSetPrice) {

    jint nRet;
    nRet =Refund(nSetPrice);
    return nRet;

}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_acuma_MainActivity_getCommStatusRpt(JNIEnv *env, jobject instance) {

    jbyte gR[3];
    jint len = getCommStatusRpt((unsigned char*)gR);
    jbyteArray ret=(*env).NewByteArray(len);
    (*env).SetByteArrayRegion(ret,0,len,gR);
    return ret;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_acuma_MainActivity_getCommStatus(JNIEnv *env, jobject instance) {

    getCommStatus();

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_acuma_MainActivity_SetIsOpen(JNIEnv *env, jobject instance, jchar cSetIsOpen) {

    jint nRet;
    nRet = SetIsOpen(cSetIsOpen);
    return nRet;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_acuma_MainActivity_addproducts(JNIEnv *env, jobject instance, jchar cSetAddress,
                                                jchar cSetChannelAddress, jint nSetNumber) {

    jint nRet;
    nRet = addproducts(cSetAddress,cSetChannelAddress,nSetNumber);
    return nRet;

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_acuma_MainActivity_SetPrice(JNIEnv *env, jobject instance, jchar cSetAddress,
                                             jchar cSetChannelAddress, jint nSetPrice) {

    jint nRet;
    nRet = SetPrice(cSetAddress,cSetChannelAddress,nSetPrice);
    return nRet;

}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_acuma_MainActivity_getVenderStatus(JNIEnv *env, jobject instance) {

    jbyte gR[44+1];
    jint len = getVenderStatus((unsigned char*)gR);
    jbyteArray ret=(*env).NewByteArray(len);
    (*env).SetByteArrayRegion(ret,0,len,gR);
    return ret;
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_acuma_MainActivity_getVenderOutReport(JNIEnv *env, jobject instance) {

    jbyte gR[47+1];
    jint len = getVenderOutReport((unsigned char*)gR);
    jbyteArray ret=(*env).NewByteArray(len);
    (*env).SetByteArrayRegion(ret,0,len,gR);
    return ret;
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_acuma_MainActivity_getInventoryInfo(JNIEnv *env, jobject instance) {

    jbyte gR[13+1];
    jint len = getInventoryInfo((unsigned char*)gR);
    jbyteArray ret=(*env).NewByteArray(len);
    (*env).SetByteArrayRegion(ret,0,len,gR);
    return ret;

}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_acuma_MainActivity_getChannelSetInfo(JNIEnv *env, jobject instance) {

    jbyte gR[20];
    jint len = getChannelSetInfo((unsigned char*)gR);
    jbyteArray ret=(*env).NewByteArray(len);
    (*env).SetByteArrayRegion(ret,0,len,gR);
    return ret;

}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_acuma_MainActivity_getChannelFailureInfo(JNIEnv *env, jobject instance) {

    jbyte gR[11+1];
    jint len = getChannelFailureInfo((unsigned char*)gR);
    jbyteArray ret=(*env).NewByteArray(len);
    (*env).SetByteArrayRegion(ret,0,len,gR);
    return ret;


}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_acuma_MainActivity_getSystemFailureInfo(JNIEnv *env, jobject instance) {

    jbyte gR[9+1];
    jint len = getSystemFailureInfo((unsigned char*)gR);
    jbyteArray ret=(*env).NewByteArray(len);
    (*env).SetByteArrayRegion(ret,0,len,gR);
    return ret;

}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_acuma_MainActivity_getVersion(JNIEnv *env, jobject instance) {

    jbyte gR[18+1];
    jint len = getVersion((unsigned char*)gR);
    jbyteArray ret=(*env).NewByteArray(len);
    (*env).SetByteArrayRegion(ret,0,len,gR);
    return ret;

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_acuma_MainActivity_VenderOutAction(JNIEnv *env, jobject instance,
                                                    jchar cSetPaytype, jchar cSetAddress,
                                                    jchar cSetChannelAddress) {
    jint nRet;
    nRet = VenderOutAction(cSetPaytype,cSetAddress,cSetChannelAddress);
    return nRet;
}



extern "C"
JNIEXPORT jint JNICALL
Java_com_example_acuma_MainActivity_VenderOutRequest(JNIEnv *env, jobject instance,
                                                     jchar cSetAddress, jchar cSetChannelAddress,
                                                     jint columnID) {
    jint nRet;
    nRet = VenderOutRequest(cSetAddress,cSetChannelAddress);
    return nRet;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_acuma_MainActivity_startProtocol(JNIEnv *env, jobject instance) {

    jint nRet;
    nRet = startProtocol();
    return nRet;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_acuma_MainActivity_getEvent(JNIEnv *env, jobject instance) {

    LOGI("get Event\n");
    return getEvent();

}

