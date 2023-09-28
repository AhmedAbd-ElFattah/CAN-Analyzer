#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>

#include "availableboards.h"
#include <QSerialPort>
#include "multibasenumber.h"
#include "QDebug"
#include "systemfilters.h"


#include "filter_1id32_1mask32.h"
#include "filter_2ids32_nomask.h"
#include "filter_2id16_2mask16.h"
#include "filter_4ids16_nomask.h"
#include "common.h"
#include "receivedatatable.h"
#include "baudrateconfigurator.h"
#include "communication.h"
#include <stdexcept>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_FilterType_Combobox_currentIndexChanged(int index);

    void on_QTable_Filter_1ID32_1Mask32_cellChanged(int row, int column);

    void on_AddFilter_pushButton_clicked();

    void on_RefreshAvailableBoards_pushButton_clicked();

    void on_connect_pushButton_clicked();

    void on_QTable_Filter_2IDs32_NoMask_cellChanged(int row, int column);

    void on_QTable_Filter_2ID16_2Mask16_cellChanged(int row, int column);

    void on_QTable_Filter_4IDs16_NoMask_cellChanged(int row, int column);

    void on_FilterId_spinBox_valueChanged(int arg1);

    void on_DeleteFilter_pushButton_clicked();

    void on_CANSendFrame_pushButton_clicked();

    void on_SendData1DataType_comboBox_currentIndexChanged(int index);

    void on_SendData2DataType_comboBox_currentIndexChanged(int index);

    void on_SendData3DataType_comboBox_currentIndexChanged(int index);

    void on_SendData4DataType_comboBox_currentIndexChanged(int index);

    void on_SendData5DataType_comboBox_currentIndexChanged(int index);

    void on_SendData6DataType_comboBox_currentIndexChanged(int index);

    void on_SendData7DataType_comboBox_currentIndexChanged(int index);

    void on_SendData8DataType_comboBox_currentIndexChanged(int index);

    void on_SendData1_lineEdit_textChanged(const QString &arg1);

    void on_SendDataLength_comboBox_currentIndexChanged(int index);

    void on_SendData2_lineEdit_textChanged(const QString &arg1);

    void on_SendData3_lineEdit_textChanged(const QString &arg1);

    void on_SendData4_lineEdit_textChanged(const QString &arg1);

    void on_SendData5_lineEdit_textChanged(const QString &arg1);

    void on_SendData6_lineEdit_textChanged(const QString &arg1);

    void on_SendData7_lineEdit_textChanged(const QString &arg1);

    void on_SendData8_lineEdit_textChanged(const QString &arg1);

    void on_SendDataFrameType_comboBox_currentIndexChanged(int index);

    void on_spinBox_valueChanged(int arg1);

    void on_SendIdOfData_lineEdit_textChanged(const QString &arg1);

    void on_SendDataIdBase_comboBox_currentIndexChanged(int index);

private:
    /*
    ==================================================
      Start Section --> Send CAN Frame (Data)
    ==================================================
    */

    CANData SendFrame_CANData;
    /*Stores data of CAN frame in multi base numbering system.*/
    MultiBaseNumber MultiBaseNumber_SendFrame;

    void sendDataInitParameters();
    /* Called by slot of SendDataxDataType_comboBox
     * Where x = 1, 2, ...
     * for e.g SendDataxDataType_comboBox
     * called by slot on_SendData1DataType_comboBox_currentIndexChanged
     *
    */
    void on_SendDataxDataType_comboBox_currentIndexChanged(short int Arg_Byte_Idx, int index);

    /* Called by slot of on_SendDatax_lineEdit_textChanged
     * Where x = 1, 2, ...
     * for e.g on_SendDatax_lineEdit_textChanged
     * called by slot on_SendData1_lineEdit_textChanged
     *
    */
    void on_SendDatax_lineEdit_textChanged(const QString &arg1, short int idx);

    /*Theese two arrays hold ui objects related to send CAN frame.*/
    std::array<QLineEdit *, MaxDataLength> SendDataQLineEdits;
    std::array<QComboBox *, MaxDataLength> SendDataQComboBoxes;
    /*
    ==================================================
      End Section --> Send CAN Frame (Data)
    ==================================================
    */

    /*
    ==================================================
      Start Section --> Communication
    ==================================================
    */

    /*Communication with board*/
    Communication BoardCommunication;
    /*CAN Baudrate configurations*/
    BaudRateConfigurator baudrate_configurator_obj;
    /*Searches and find available boards to connect*/
    AvailableBoards BoardSelector;
    /*
    ==================================================
      End Section --> Communication
    ==================================================
    */

    /*
    ==================================================
      Start Section --> Receive CAN Messages UI
    ==================================================
    */
    ReceiveDataTable *ReceiveCANMessages_DataTable = nullptr;
    MultiBaseNumber MultiBaseNumber_Filter_1ID32_1Mask32    [APP_CONFIG_1ID32_1Mask32_ROWS];
    MultiBaseNumber MultiBaseNumber_Filter_2ID32_NoMask     [APP_CONFIG_2IDs32_NoMask_ROWS];
    MultiBaseNumber MultiBaseNumber_Filter_2IDs16_2Masks16  [APP_CONFIG_2ID16_2Mask16_ROWS];
    MultiBaseNumber MultiBaseNumber_Filter_4IDs16_NoMask    [APP_CONFIG_4IDs16_NoMask_ROWS];

    /*Init table basic objects*/
    void InitTableOfAddingFilters();
    void FillTableRows(QTableWidget *TableWidget, qint8 MaxBitsForVal, QVector<QString> RowNames);
    void UpdateTableRow(QTableWidget *TableWidget, MultiBaseNumber *MultiBaseNumber_obj, int row, int column);


    /*
    ==================================================
      End Section --> Receive CAN Messages UI
    ==================================================
    */

    /*
    ==================================================
      Start Section --> Filter
    ==================================================
    */

    QString FilterTypesString[4] {
        "1ID32-1Mask32",
        "2IDs32-NoMask",
        "2ID16-2Mask16",
        "4IDs16-NoMask",
    };

    QString FilterFrameTypesString[2] {
        "Data Frame",
        "Remote Frame",
    };

    SystemFilters sysFilters;
    void AddRowInFiltersTable(QString Arg_Col_1, QString Arg_Col_2);
    /*
    ==================================================
      End Section --> Filter
    ==================================================
    */
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
