#ifndef FILTER_2IDS32_NOMASK_H
#define FILTER_2IDS32_NOMASK_H

#include "filter.h"


class Filter_2IDs32_NoMask:public Filter
{
private:
    quint32 ID[2];
public:
    /*Attribute usually used for input data construction*/
    const QVector<QString> FilterAttributesInString = {"ID 1 ", "ID 2 "};
    static const short int TableRows = APP_CONFIG_1ID32_1Mask32_ROWS;
    static const short int AttributeSizeInBits = APP_CONFIG_1ID32_1Mask32_BITS;

    Filter_2IDs32_NoMask(QString Arg_FilterName_String, short int Arg_FilterIdx);

    void SetFilterId(short int idx, qint32 val);
    void SetFilterMask(short int idx, qint32 val);
    quint32 GetFilterId(short int idx);
    quint32 GetFilterMask(short int idx);

    qint32 GetFilterBankR1_Value();
    qint32 GetFilterBankR2_Value();
    ~Filter_2IDs32_NoMask();
};


#endif // FILTER_2IDS32_NOMASK_H
