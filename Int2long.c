#include "include/gobiz.h"

unsigned long Int2Long(unsigned int hi,unsigned int low){
    unsigned long mres=0;
    mres=(hi*0x10000)+(low & 0xFFFF);
    return mres;
}
LONG_HiLow Long2Int(unsigned long mvalue){

    LONG_HiLow mret;
    unsigned long myval=mvalue;

    mret.int_Hi=myval / 0x10000;
    mret.int_Low=myval % 0x10000;
    return mret;	
}
unsigned int Byte2Int(unsigned char hi,unsigned char low){
    unsigned int mres;
    mres=(hi * 0x100) + low;
    return mres;
}
INT_HiLow Int2Byte(unsigned int mvalue){

    unsigned int myval=mvalue;
    INT_HiLow mret;
    mret.ch_Hi=myval / 0x100;
    mret.ch_Low=myval % 0x100;
    return mret;	
}

