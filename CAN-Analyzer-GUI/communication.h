#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/*
 * File Name --> communication.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> Communication with board.
 * */

#include <QObject>
#include <QSerialPort>
#include "ApplicationConfigurations.h"
#include "receivedatatable.h"
#include "common.h"

class Communication : public QObject
{
    Q_OBJECT
private:
    QSerialPort Board_Serial_Port;
    /*It holds pointer to table that shows received data.*/
    ReceiveDataTable *R_DataTable = nullptr;

private slots:
    /*
     * When serialport receives data, it will trigger this slot
     * then it reads data and shows it on receive data table.
     */
    void Read_Data();
public:
    Communication();
    /*Set pointer to QTable that shows received data.*/
    void setReceiveDataTable(ReceiveDataTable *Arg_DataTable);
    bool IsConnected(void);

    void Connect(QString Arg_PortName);
    void SendData(qint32 Arg_Command, qint32 Arg_Parameter_1, qint32 Arg_Parameter_2, qint32 Arg_Parameter_3);
    void SendData(const CANData &Arg_CANData);
    void DisConnect();
    ~Communication();
signals:


};

#endif // COMMUNICATION_H

