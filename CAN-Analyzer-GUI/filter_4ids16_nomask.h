#ifndef FILTER_4IDS16_NOMASK_H
#define FILTER_4IDS16_NOMASK_H

#include "filter.h"

class Filter_4IDs16_NoMask:public Filter
{
private:
    quint16 ID[4];
public:
    /*Attribute usually used for input data construction*/
    const QVector<QString> FilterAttributesInString = {"ID 1 ", "ID 2 ", "ID 3 ", "ID 4 "};
    static const short int TableRows = APP_CONFIG_4IDs16_NoMask_ROWS;
    static const short int AttributeSizeInBits = APP_CONFIG_4IDs16_NoMask_BITS;
    /**/

    Filter_4IDs16_NoMask(QString Arg_FilterName_String, short int Arg_FilterIdx);


    void SetFilterId(short int idx, qint32 val);
    void SetFilterMask(short int idx, qint32 val);
    quint32 GetFilterId(short int idx);
    quint32 GetFilterMask(short int idx);

    qint32 GetFilterBankR1_Value();
    qint32 GetFilterBankR2_Value();
    ~Filter_4IDs16_NoMask();
};
#endif // FILTER_4IDS16_NOMASK_H
