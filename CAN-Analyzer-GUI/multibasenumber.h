#ifndef MULTIBASENUMBER_H
#define MULTIBASENUMBER_H
/*
 * File Name --> multibasenumber.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> MultiBaseNumber provides conversion between different numbering systems.
 * It serves as a versatile bridge for converting numbers from one numerical base to another
 */
#include <QString>

#include "ApplicationConfigurations.h"

class MultiBaseNumber
{
private:
    unsigned int number;
    QString numberInHex;
    QString numberInOct;
    QString numberInDec;
    QString numberInBin;

public:
    MultiBaseNumber();
    void Set_Bit(int bit_pos);
    void Clear_Bit(int bit_pos);
    bool Get_Bit(int bit_pos);

    void Set_Number(int num);
    int Get_Number(void);
    QString Get_NumberInDecFormat(void);
    QString Get_NumberInHexFormat(void);
    QString Get_NumberInOctFormat(void);
    QString Get_NumberInBinFormat(void);
    /*
     * The following functions updates stored value provides that
     * they are in correct format for the selected numbering system.
     * They also return boolen value to determine whether
     * input value in correct format or not.
    */
    bool Set_NumberInBinFormat(QString num_dec);
    bool Set_NumberInDecFormat(QString num_dec);
    bool Set_NumberInOctFormat(QString num_dec);
    bool Set_NumberInHexFormat(QString num_dec);


} ;



#endif // MULTIBASENUMBER_H
