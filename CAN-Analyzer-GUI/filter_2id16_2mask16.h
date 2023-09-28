#ifndef FILTER_2ID16_2MASK16_H
#define FILTER_2ID16_2MASK16_H
/*
 * File Name     --> filter_2id16_2mask16.h
 * Author        --> Ahmed Mohamed Abd-Elfattah
 * Version       --> 1.0.0
 * Brief         --> Filter that has Two 16-Bit IDs & Two Masks.
 * */

#include "filter.h"


class Filter_2ID16_2Mask16:public Filter
{
private:
    quint16 ID[2];
    quint16 Mask[2];
public:
    /*Attribute usually used for input data construction*/
    const QVector<QString> FilterAttributesInString = {"ID 1 ", "Mask 1", "ID 2 ", "Mask 2"};
    static const short int TableRows = APP_CONFIG_2ID16_2Mask16_ROWS;
    static const short int AttributeSizeInBits = APP_CONFIG_2ID16_2Mask16_BITS;

    Filter_2ID16_2Mask16(QString Arg_FilterName_String, short int Arg_FilterIdx);

    void SetFilterId(short int idx, qint32 val);
    void SetFilterMask(short int idx, qint32 val);
    quint32 GetFilterId(short int idx);
    quint32 GetFilterMask(short int idx);

    qint32 GetFilterBankR1_Value();
    qint32 GetFilterBankR2_Value();
    ~Filter_2ID16_2Mask16();
};

#endif // FILTER_2ID16_2MASK16_H
