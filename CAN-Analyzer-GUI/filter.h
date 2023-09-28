#ifndef FILTER_H
#define FILTER_H
#include "ApplicationConfigurations.h"
#include <QtGlobal>
#include <QString>
#include <QVector>
#include "common.h"
#include <stdexcept>
/*
 * File Name --> filter.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> Filter class contains generic filter properties
 * */

enum FilterTypes{
    FilterType_1ID32_1Mask32,
    FilterType_2IDs32_NoMask,
    FilterType_2ID16_2Mask16,
    FilterType_4IDs16_NoMask
};


class Filter
{
private:
    FrameTypes FilterFrameType;

protected:
    short int IDsNumber;
    short int MasksNumber;
    short int FilterIndex;

    FilterTypes FilterType;

    QString FilterName;

    qint32 FilterBankR1_Value;
    qint32 FilterBankR2_Value;

public:
    Filter();

    short int GetIDsNumber();
    short int GetMasksNumber();

    void SetFilterFrameType(FrameTypes Arg_FrameType);
    FrameTypes GetFilterFrameType();
    short int GetFilterIndex();
    /*
     * Get filter parameter in the same form that
     * will be sent to microcontroller*/
    qint32 GetFilterParameters();

    FilterTypes GetFilterType();
    /*
     * If filter has 2 Ids
     * For example assume idx = 0 it sets the first Ids's value.
    */
    virtual void SetFilterId(short int idx, qint32 val) = 0;
    /*
     * If filter has 2 masks
     * For example assume idx = 0 it sets the first mask's value.
    */
    virtual void SetFilterMask(short int idx, qint32 val) = 0;
    /*
     * If filter has 2 Ids
     * For example assume idx = 0 it gets the first Id's value.
    */
    virtual quint32 GetFilterId(short int idx) = 0;
    /*
     * If filter has 2 masks
     * For example assume idx = 0 it gets the first mask's value.
    */
    virtual quint32 GetFilterMask(short int idx) = 0;
    /*CAN_FxR1 register value*/
    virtual qint32 GetFilterBankR1_Value() = 0;
    /*CAN_FxR1 register value*/
    virtual qint32 GetFilterBankR2_Value() = 0;
    virtual ~Filter();
};

#endif // FILTER_H
