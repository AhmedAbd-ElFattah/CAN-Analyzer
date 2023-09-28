#ifndef RECEIVEDATATABLE_H
#define RECEIVEDATATABLE_H

/*
 * File Name --> receivedatatable.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> Class SystemFilters responsible for system filter operations like
 * add filter, delete filter, or check the existance of filter.
 * */

#include <QTableWidget>
#include <QComboBox>
#include <QtGlobal>

#include "ApplicationConfigurations.h"
#include "common.h"
#include <QDebug>

class ReceiveDataTable
{
private:
    QTableWidget * const Table = nullptr;
    QComboBox const * const ID_Combobox;
    QComboBox const * const DataLength_Combobox;
    QComboBox const * const Data_Combobox;
    QComboBox const * const FilterId_Combobox;

    int MaxShownMessagesNumber = APP_CONFIG_DEFAULT_MESSAGES_NUM;
    QString ShowNumberWithBase(QComboBox const * const Arg_ComboBox, const quint8 Arg_value);
public:
    ReceiveDataTable(QTableWidget *Arg_TableWidget,
                     QComboBox *ID,
                     QComboBox *DataLength,
                     QComboBox *Data_Combobox,
                     QComboBox *Arg_FilterId_Combobox
                     );
    /*Add data to table*/
    void AddData(const CANData Arg_CANData);
    /*Change Maximum value of shown messages in the table*/
    void SetMaxShownMessagesNumber(const short int Arg_Val);
};

#endif // RECEIVEDATATABLE_H
