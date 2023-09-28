#ifndef FILTER_1ID32_1MASK32_H
#define FILTER_1ID32_1MASK32_H
/*
 * File Name --> filter_1id32_1mask32.h
 * Author        --> Ahmed Mohamed Abd-Elfattah
 * Version       --> 1.0.0
 * Brief         --> Filter that has One 32-Bit ID & One Mask.
 * */
#include "filter.h"
class Filter_1ID32_1Mask32:public Filter
{
private:
    quint32 ID, Mask;
public:
    /*Attribute usually used for input data construction*/
    const QVector<QString> FilterAttributesInString = {"ID ", "Mask "};
    static const short int TableRows = APP_CONFIG_1ID32_1Mask32_ROWS;
    static const short int AttributeSizeInBits = APP_CONFIG_1ID32_1Mask32_BITS;

    Filter_1ID32_1Mask32(QString Arg_FilterName_String, short int Arg_FilterIdx);


    void SetFilterId(short int idx, qint32 val);
    void SetFilterMask(short int idx, qint32 val);
    quint32 GetFilterId(short int idx);
    quint32 GetFilterMask(short int idx);

    qint32 GetFilterBankR1_Value();
    qint32 GetFilterBankR2_Value();
    ~Filter_1ID32_1Mask32();
};

#endif // FILTER_1ID32_1MASK32_H
