#include "multibasenumber.h"

MultiBaseNumber::MultiBaseNumber()
{
    number = 0;
    numberInBin = "0b";
    numberInDec = "0";
    numberInHex = "0x00";
    numberInOct = "0o0";
}

void MultiBaseNumber::Set_Bit(int bit_pos)
{
    number |= (1<<bit_pos);
    numberInDec = QString::number(number, 10);
    numberInHex = "0x0" + QString::number(number, 16);
    numberInOct = "0o0"+ QString::number(number, 8);
    numberInBin = "0b" + QString::number(number, 2);
}

void MultiBaseNumber::Clear_Bit(int bit_pos)
{
    number &= ~(1<<bit_pos);
    numberInDec = QString::number(number, 10);
    numberInHex = "0x0" + QString::number(number, 16);
    numberInOct = "0o0"+ QString::number(number, 8);
    numberInBin = "0b" + QString::number(number, 2);
}

bool MultiBaseNumber::Get_Bit(int bit_pos)
{
    if (1== ((number>>bit_pos)&0x1)){
        return true;
    }
    else{
        return false;
    }
}

void MultiBaseNumber::Set_Number(int num)
{
    number = num;
}

int MultiBaseNumber::Get_Number()
{
    return number;
}

bool MultiBaseNumber::Set_NumberInDecFormat(QString num_dec)
{
    unsigned int temp_num;
    bool valid_format;
    temp_num = num_dec.toInt(&valid_format, 10);

    if (valid_format){
        number = temp_num;
        numberInDec = QString::number(number, 10);
        numberInHex = "0x0" + QString::number(number, 16);
        numberInOct = "0o0"+ QString::number(number, 8);
    }

    return valid_format;
}

bool MultiBaseNumber::Set_NumberInOctFormat(QString num_dec)
{
    unsigned int temp_num;
    bool valid_format;
    temp_num = num_dec.toInt(&valid_format, 8);

    if (valid_format){
        number = temp_num;
        numberInDec = QString::number(number, 10);
        numberInOct = "0o0"+ QString::number(number, 8);
        numberInHex = "0x0" + QString::number(number, 16);

    }

    return valid_format;
}

bool MultiBaseNumber::Set_NumberInHexFormat(QString num_dec)
{
    unsigned int temp_num;
    bool valid_format;
    temp_num = num_dec.toInt(&valid_format, 16);

    if (valid_format){
        number = temp_num;
        numberInDec = QString::number(number, 10);
        numberInHex = "0x" + QString::number(number, 16);
        numberInOct = "0o"+ QString::number(number, 8);
    }

    return valid_format;
}

bool MultiBaseNumber::Set_NumberInBinFormat(QString num_dec)
{
    unsigned int temp_num;
    bool valid_format;
    temp_num = num_dec.toInt(&valid_format, 16);

    if (valid_format){
        number = temp_num;
        numberInDec = QString::number(number, 10);
        numberInBin = "0b" + QString::number(number, 2);
        numberInHex = "0x" + QString::number(number, 16);
        numberInOct = "0o"+ QString::number(number, 8);
    }

    return valid_format;
}

QString MultiBaseNumber::Get_NumberInDecFormat()
{
    return numberInDec;
}

QString MultiBaseNumber::Get_NumberInHexFormat()
{
    return numberInHex;
}

QString MultiBaseNumber::Get_NumberInOctFormat()
{
    return numberInOct;
}

QString MultiBaseNumber::Get_NumberInBinFormat()
{
    return numberInBin;
}



