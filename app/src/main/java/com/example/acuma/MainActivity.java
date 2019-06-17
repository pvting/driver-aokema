package com.example.acuma;

import android.net.Uri;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.os.SystemClock;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.RadioGroup;
import android.widget.TextView;

import java.io.DataOutputStream;
import java.io.File;
import java.util.ArrayList;


public class MainActivity extends AppCompatActivity {


    int column;
    char cSetAddress;
    char cSetChannelAddress;
    char cPayType;
    char payMent;
    int nSetNumber;
    int nSetPrice;
    int nRefundPrice;
    EditText et;
    TextView tv;


    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("Aucma");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        et = (EditText) findViewById(R.id.editText);
        et.setOnFocusChangeListener(new View.OnFocusChangeListener() {

            @Override
            public void onFocusChange(View v, boolean hasFocus) {
                if (hasFocus) {
                    et.setText("");
                } else {
                    et.setText("请输入type类型");
                }
            }
        });
        tv = (TextView) findViewById(R.id.textview);
        tv.setText("澳柯玛售货机");
        tv.append("\n");

        Thread thread_protocol = new Thread(new Runnable() {
            @Override
            public void run() {
                Log.e("tag:","tag:");
                startProtocol();
            }
        });
        thread_protocol.start();




        final Handler mHandler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                super.handleMessage(msg);
                switch (msg.what) {
                    case 0xA1:
                        tv.append("系统故障:" + bytes2HexString(getSystemFailureInfo()));
                        tv.append("\n");
                        break;
                    case 0xA2:
                        tv.append("料到故障:" + bytes2HexString(getChannelFailureInfo()));
                        Log.e("tagg:",bytes2HexString(getChannelFailureInfo()));
                        tv.append("\n");
                        break;
                    case 0xA3:
                        tv.append("出货报告:" + bytes2HexString(getVenderOutReport()));
                        tv.append("\n");
                        break;
                    case 0xA4:
                        tv.append("状态信息:" + bytes2HexString(getVenderStatus()));
                        Log.e("tagg:",bytes2HexString(getVenderStatus()));
                        tv.append("\n");
                        break;
                    case 0xA5:
                        tv.append("VMC版本信息"+ bytes2HexString(getVersion()));
                        tv.append("\n");
                        break;
                    case 0xA6:
                        tv.append("料到配置信息:" + bytes2HexString(getChannelSetInfo()));
                        tv.append("\n");
                        break;
                    case 0xA9:
                        tv.append("有无货信息:" + bytes2HexString(getInventoryInfo()));
                        Log.e("tagg:",bytes2HexString(getInventoryInfo()));
                        tv.append("\n");
                        break;
                    case 0xB0:
                        tv.append("暂停营业");
                        tv.append("\n");
                        break;
                    case 0xB1:
                        tv.append("门开");
                        tv.append("\n");
                        break;

                    case 0xB4:
                        tv.append("设置价格成功" );
                        Log.e("taggg:","设置价格成功\n");
                        tv.append("\n");
                        break;
                    case 0xB6:
                        tv.append("门关");
                        tv.append("\n");
                        break;
                    case 0xB7:
                        tv.append("投币总金额:"+bytes2HexString(getTotalPrice()));
                        tv.append("\n");
                        break;
                    case 0xC1:
                        tv.append("Com状态:" + bytes2HexString(getCommStatusRpt()));
                        tv.append("\n");
                        break;
                    default:
                        break;
                }
            }
        };


        Thread thread_event = new Thread(new Runnable() {

            @Override
            public void run() {
                while (true) {
                    if (!(true)) break;
                    int i;
                    i = getEvent();
                    mHandler.sendEmptyMessage(i);
                }
            }
        });
        thread_event.start();

    }
    public static String bytes2HexString(byte[] b) {        //byte转16进制字符串函数
        String ret = "";
        for (int i = 0; i < b.length; i++) {
            String hex = Integer.toHexString(b[i] & 0xFF);
            if (hex.length() == 1) {
                hex = '0' + hex;
            }
            ret += hex.toUpperCase();
        }
        return ret;
    }



    public void VenderOutRequestClicked(View view){

        cSetAddress =0;
        cSetChannelAddress = 17;

        VenderOutRequest(cSetAddress,cSetChannelAddress);
        Log.e("tag:","出货查询");
    }





    public void VenderoutActionClicked(View view) {
        cSetAddress =1;
        cSetChannelAddress = 0x11;
        cPayType = 3;
        VenderOutAction(cPayType,cSetAddress,cSetChannelAddress);
        Log.e("tag:","出货");
    }


    public void setPriceButtonClicked(View view){

        cSetAddress =1;
        cSetChannelAddress = 0x11;
        nSetPrice = 100;
        SetPrice(cSetAddress,cSetChannelAddress,nSetPrice);
        Log.e("tag:","设置价格");
    }


    public void setAddProductsButtonClicked(View view){

        cSetAddress =1;
        cSetChannelAddress = 41;
        nSetNumber = 5;
        addproducts(cSetAddress,cSetChannelAddress,nSetNumber);
        Log.e("tag:","加货");
    }


    public void setIsOpenButtonClicked(View view){
        char cIsOpen =1;
        SetIsOpen(cIsOpen);
        Log.e("tag:","设置是否营业");
    }

    public void getReadStatusCommClicked(View view) {

        getCommStatus();
        tv.append("PC请求通讯类型");
        tv.append("\n");
    }

    public void RefundCoinClicked(View view) {

        nRefundPrice = 100;
        Refund(nRefundPrice);
        tv.append("PC请求退币");
        tv.append("\n");
    }


    public void GetChannelErrorClicked(View view) {

        cSetAddress =1;
        GetChannelError(cSetAddress);
        tv.append("PC请求获取料到状况");
        tv.append("\n");
    }


    public void GetInventoryClicked(View view) {

        cSetAddress =1;
        GetInventory(cSetAddress);
        tv.append("PC请求获库存状况");
        tv.append("\n");
    }

    public void GetMachineStatusClicked(View view) {


        GetMachineStatus();
        tv.append("PC请求MachineStatus状况");
        tv.append("\n");
    }

    public void GetMachineVersionClicked(View view) {


        GetMachineVersion();
        tv.append("PC请求Machine版本信息");
        tv.append("\n");
    }

    public void GetSystemFaultInfoClicked(View view) {


        GetSystemFaultInfo();
        tv.append("PC请求系统故障信息");
        tv.append("\n");
    }

    boolean isSet = false;
    public void setPriceClicked(View view) {
        final ArrayList<Integer> foodRoadid = new ArrayList<>();
        final ArrayList<Integer> drinkRoadid = new ArrayList<>();

        for (int i = 11; i <=16; i++) {
            foodRoadid.add(i);
        }
        for (int i = 21; i < 26; i++) {
            foodRoadid.add(i);
        }
        for (int i = 51; i < 58; i++) {
            foodRoadid.add(i);
        }
        foodRoadid.add(31);
        foodRoadid.add(33);
        foodRoadid.add(35);
        foodRoadid.add(41);
        foodRoadid.add(43);
        foodRoadid.add(45);

        for (int i = 13; i <= 24; i++) {
            drinkRoadid.add(i);
        }


        new Thread(){
            @Override
            public void run() {
                if(isSet){
                    return;
                }
                isSet = true;
                for (int j = 0; j < foodRoadid.size(); j++) {
                    int roadId = foodRoadid.get(j);
                    roadId = (roadId / 10) * 16 + roadId % 10;
                    Log.i("writeProduct", " boxId:" + 1 + "_roadId:" + roadId + "_price:" + 200);
                    SetPrice((char) 1, (char) roadId, 200);
                    Log.e("taggg:","设置饮料机价格");
                    SystemClock.sleep(3000);
                }
                SystemClock.sleep(10000);
                for (int j = 0; j < drinkRoadid.size(); j++) {
                    int roadid = drinkRoadid.get(j);
                    Log.i("writeProduct", " boxId:" + 1 + "_roadId:" + roadid + "_price:" + 300);
                    SetPrice((char) 0, (char)roadid, 300);
                    Log.e("taggg:","设置弹簧机价格");
                    SystemClock.sleep(3000);
                }
                isSet = false;

            }
        }.start();



    }


    public native int getEvent();

    public native int startProtocol();

    public native int VenderOutRequest(char cSetAddress,char cSetChannelAddress);

    public native int VenderOutAction(char cSetPaytype,char cSetAddress,char cSetChannelAddress);

    public native byte[] getVersion();

    public native byte[] getSystemFailureInfo();

    public native byte[] getChannelFailureInfo();

    public native byte[] getChannelSetInfo();

    public native byte[] getInventoryInfo();

    public native byte[] getVenderOutReport();

    public native byte[] getVenderStatus();

    public native int SetPrice(char cSetAddress,char cSetChannelAddress,int nSetPrice);

    public native int addproducts(char cSetAddress,char cSetChannelAddress,int nSetNumber);

    public native int SetIsOpen(char cSetIsOpen);

    public native void getCommStatus();

    public native byte[] getCommStatusRpt();

    public native int Refund(int nSetPrice);

    public native byte[] getTotalPrice();

    public native int GetChannelError(char cSetAddress);

    public native int GetInventory(char cSetAddress);

    public native int GetMachineStatus();

    public native int GetMachineVersion();

    public native int GetSystemFaultInfo();


  }
