#include "communication.h"

Communication::Communication()
{
    Board_Serial_Port.setBaudRate(QSerialPort::BaudRate::Baud115200);
    Board_Serial_Port.setParity(QSerialPort::Parity::NoParity);
    Board_Serial_Port.setDataBits(QSerialPort::DataBits::Data8);
    Board_Serial_Port.setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    Board_Serial_Port.setStopBits(QSerialPort::StopBits::OneStop);
}

void Communication::Connect(QString Arg_PortName)
{
    if (Board_Serial_Port.isOpen()){
        Board_Serial_Port.close();
    }
    connect(&Board_Serial_Port, SIGNAL(readyRead()), this, SLOT(Read_Data()));
    Board_Serial_Port.setPortName(Arg_PortName);
    Board_Serial_Port.open(QIODevice::ReadWrite);
}

void Communication::SendData(qint32 Arg_Command, qint32 Arg_Parameter_1, qint32 Arg_Parameter_2, qint32 Arg_Parameter_3)
{
    if (!IsConnected()){
        return;
    }
    Board_Serial_Port.write((char *)&Arg_Command, sizeof(Arg_Command));
    Board_Serial_Port.waitForBytesWritten();
    Board_Serial_Port.write((char *)&Arg_Parameter_1,    sizeof(Arg_Parameter_1));
    Board_Serial_Port.waitForBytesWritten();
    Board_Serial_Port.write((char *)&Arg_Parameter_2,    sizeof(Arg_Parameter_2));
    Board_Serial_Port.waitForBytesWritten();
    Board_Serial_Port.write((char *)&Arg_Parameter_3,    sizeof(Arg_Parameter_3));
    Board_Serial_Port.waitForBytesWritten();
}

void Communication::SendData(const CANData &Arg_CANData)
{
    if (!IsConnected()){
        return;
    }
    UI_Send_Commands L_ConnectCommand_qint32 = UI_Send_CMD_Send_Frame_DATA;
    qint32 L_Parameter_1_qint32;
    qint32 L_Parameter_2_qint32;
    qint32 L_Parameter_3_qint32;


    CAN_ANALYZER_SendData_Parameter1 L_Parameter_1_data_union;
    L_Parameter_1_data_union.ID = Arg_CANData.FrameId;
    L_Parameter_1_data_union.FrameType = Arg_CANData.Frametype;
    L_Parameter_1_data_union.DataLength = Arg_CANData.DataLength;
    L_Parameter_1_qint32 = (qint32)L_Parameter_1_data_union.Param_1_value;


    CAN_ANALYZER_SendData_Parameter2 L_Parameter_2_data_union;
    for (short int i = 0; i <4; i++){
        L_Parameter_2_data_union.data[i] = Arg_CANData.Data.at(i);
    }
    L_Parameter_2_qint32 = (qint32)L_Parameter_2_data_union.Param_2_value;

    CAN_ANALYZER_SendData_Parameter3 L_Parameter_3_data_union;
    for (short int i = 0; i <4; i++){
        L_Parameter_3_data_union.data[i] = Arg_CANData.Data.at(i+4);
    }
    L_Parameter_3_qint32 = (qint32)L_Parameter_3_data_union.Param_3_value;

    SendData(L_ConnectCommand_qint32,
             L_Parameter_1_qint32,
             L_Parameter_2_qint32,
             L_Parameter_3_qint32);
}

void Communication::DisConnect()
{
    if (Board_Serial_Port.isOpen()){
        Board_Serial_Port.close();
    }
}

void Communication::Read_Data()
{
    CANData L_CurrentData;
    int available_bytes;

    if (!IsConnected()){
        return;
    }
    if (Board_Serial_Port.isOpen()){
        available_bytes = Board_Serial_Port.bytesAvailable();
        if(available_bytes >= APP_CONFIG_BUFFER_SIZE){
            Board_Serial_Port.read((char *)L_CurrentData.Buffer.data(), APP_CONFIG_BUFFER_SIZE);
            if (nullptr != R_DataTable){
                /*Show data in table*/
                R_DataTable->AddData(L_CurrentData);
            }
        }
        else{

        }
    }
}


void Communication::setReceiveDataTable(ReceiveDataTable *Arg_DataTable)
{
    R_DataTable = Arg_DataTable;
}


bool Communication::IsConnected()
{
    return Board_Serial_Port.isOpen();
}

Communication::~Communication()
{
    if (Board_Serial_Port.isOpen()){
        Board_Serial_Port.close();
    }
    if (nullptr != R_DataTable){
        delete R_DataTable;
        R_DataTable = nullptr;
    }
}




