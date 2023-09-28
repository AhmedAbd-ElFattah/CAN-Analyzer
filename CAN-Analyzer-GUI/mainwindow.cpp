#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ReceiveCANMessages_DataTable = new ReceiveDataTable(
                ui->Receive_tableWidget,
                ui->IDValBase_comboBox,
                ui->DataLenValBase_comboBox,
                ui->DataValBase_comboBox,
                ui->FilterId_comboBox
                );
    BoardSelector.AssignComboBox(ui->AvailableBoards_comboBox);
    InitTableOfAddingFilters();
    BoardCommunication.setReceiveDataTable(ReceiveCANMessages_DataTable);
    sendDataInitParameters();


}

MainWindow::~MainWindow()
{
    BoardCommunication.SendData((qint32)UI_Send_CMD_Stop, 0xABCD1234, 0x56780A0B, 0x01062160);
    delete ui;
}


void MainWindow::on_FilterType_Combobox_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void MainWindow::InitTableOfAddingFilters()
{
    /*Switch to default page of stacked widget based on filter type combo box.*/
    ui->stackedWidget->setCurrentIndex(ui->FilterType_Combobox->currentIndex());

    /*Create dummy filters of (one for each type) to get filter properities
     * and adjust ui elements based of theese properities.
     */
    Filter_1ID32_1Mask32 temp_Filter_1ID32_1Mask32("",0);
    Filter_2IDs32_NoMask temp_Filter_2IDs32_NoMask("",0);
    Filter_2ID16_2Mask16 temp_Filter_2ID16_2Mask16("",0);
    Filter_4IDs16_NoMask temp_filter_4ids16_nomask("",0);

    FillTableRows(ui->QTable_Filter_1ID32_1Mask32, // Table of filter that has One ID 32-Bit & One Mask 32-Bit
                  temp_Filter_1ID32_1Mask32.AttributeSizeInBits, // Number of bits which is in this filter is 32
                  temp_Filter_1ID32_1Mask32.FilterAttributesInString); // Filter types In string which is in out case "ID" and "Mask"

    FillTableRows(ui->QTable_Filter_2IDs32_NoMask, temp_Filter_2IDs32_NoMask.AttributeSizeInBits, temp_Filter_2IDs32_NoMask.FilterAttributesInString);

    FillTableRows(ui->QTable_Filter_2ID16_2Mask16, temp_Filter_2ID16_2Mask16.AttributeSizeInBits, temp_Filter_2ID16_2Mask16.FilterAttributesInString);

    FillTableRows(ui->QTable_Filter_4IDs16_NoMask, temp_filter_4ids16_nomask.AttributeSizeInBits, temp_filter_4ids16_nomask.FilterAttributesInString);

    /*For each filter type, Update default table row of values.
     * In this case exactly at initialization We init it with default values.
*/
    for (short int i = 0;i < APP_CONFIG_1ID32_1Mask32_ROWS; i++){
        UpdateTableRow(ui->QTable_Filter_1ID32_1Mask32, MultiBaseNumber_Filter_1ID32_1Mask32, i, 0);
    }

    for (short int i = 0;i < APP_CONFIG_2IDs32_NoMask_ROWS; i++){
        UpdateTableRow(ui->QTable_Filter_2IDs32_NoMask, MultiBaseNumber_Filter_2ID32_NoMask, i, 0);
    }


    for (short int i = 0;i < APP_CONFIG_2ID16_2Mask16_ROWS; i++){
        UpdateTableRow(ui->QTable_Filter_2ID16_2Mask16, MultiBaseNumber_Filter_2IDs16_2Masks16, i, 0);
    }


    for (short int i = 0;i < APP_CONFIG_4IDs16_NoMask_ROWS; i++){
        UpdateTableRow(ui->QTable_Filter_4IDs16_NoMask, MultiBaseNumber_Filter_4IDs16_NoMask, i, 0);
    }
}

void MainWindow::FillTableRows(QTableWidget *TableWidget, qint8 MaxBitsForVal, QVector<QString> RowNames)
{
    TableWidget->blockSignals(true);

    QString Label;
    qint8 NumberOfRows;

    /*For each filter type 's bits determine number of rows*/
    switch (MaxBitsForVal){
    case 16:
        NumberOfRows = 4;
        break;
    case 32:
        NumberOfRows = 2;
        break;
    }

    for (int i = 0; i<(MaxBitsForVal+3); i++){
        TableWidget->insertColumn(i);
        switch (i){
        case 0:
            /*Insert Decimal Column*/
            Label = "Decimal";
            TableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(Label));
            break;
        case 1:
            /*Insert Octal Column*/
            Label = "Oct";
            TableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(Label));
            break;
        case 2:
            /*Insert Hex Column*/
            Label = "Hex";
            TableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(Label));
            break;
        default:
            /* Insert checkboxes columns for each digit in binary.
             * Number of columns depends on filter
             * for e.h filters that hold 32-bit id has 32 columns for each digit in binary & the same for 16-bit id.
             */
            Label = "B"+QString::number(MaxBitsForVal-i+3-1);;
            TableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(Label));
        }
    }
    for (int i =0; i < NumberOfRows; i++){
        /*Insert New row*/
        TableWidget->insertRow(i);
    }

    /* Insert checkboxes for each digit in binary.
     * Number of checkboxes depends on filter
     * for e.h filters that hold 32-bit id has 32 checkbox & the same for 16-bit id.
     */
    for (int col = 3; col <(3+MaxBitsForVal); col++){
        for (int row =0; row < NumberOfRows; row++){
            QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
            checkBoxItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
            checkBoxItem->setCheckState(Qt::Unchecked);
            TableWidget->setItem(row, col, checkBoxItem);
        }
    }

    for (qint8 i = 0;i<RowNames.length();i++){
        TableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(RowNames[i]));

    }

    TableWidget->resizeColumnsToContents();
    TableWidget->blockSignals(false);
}

void MainWindow::UpdateTableRow(QTableWidget *TableWidget, MultiBaseNumber *MultiBaseNumber_obj, int row, int column)
{
    TableWidget->blockSignals(true);
    QTableWidgetItem* item;
    QString text;
    item = TableWidget->item(row, column);
    text = item ? item->text() : "";

    switch (column){
    /*Decimal Column*/
    case 0:
        MultiBaseNumber_obj[row].Set_NumberInDecFormat(text);
        break;
        /*Octal Column*/
    case 1:
        MultiBaseNumber_obj[row].Set_NumberInOctFormat(text);
        break;
        /*Hex Column*/
    case 2:
        MultiBaseNumber_obj[row].Set_NumberInHexFormat(text);
        break;
    default:
        /*Binary digits Columns*/
        int bit_pos = TableWidget->columnCount() - column - 1;
        item = TableWidget->item(row, 0);
        MultiBaseNumber_obj[row].Set_NumberInDecFormat(item->text());

        QTableWidgetItem* item_checkbox;
        Qt::CheckState state ;
        item_checkbox = TableWidget->item(row, column);
        state = item_checkbox->checkState();
        if (state == Qt::Checked ){
            MultiBaseNumber_obj[row].Set_Bit(bit_pos);
        }
        else{
            MultiBaseNumber_obj[row].Clear_Bit(bit_pos);
        }
    }


    QTableWidgetItem* TableWidgetItem;
    /*Dec*/
    TableWidgetItem = new QTableWidgetItem(MultiBaseNumber_obj[row].Get_NumberInDecFormat());
    TableWidget->setItem(row, 0,TableWidgetItem);

    /*Oct*/
    TableWidgetItem = new QTableWidgetItem(MultiBaseNumber_obj[row].Get_NumberInOctFormat());
    TableWidget->setItem(row, 1,TableWidgetItem);

    /*Oct*/
    TableWidgetItem = new QTableWidgetItem(MultiBaseNumber_obj[row].Get_NumberInHexFormat());
    TableWidget->setItem(row, 2,TableWidgetItem);

    for (int i = 0; i<(TableWidget->columnCount()-1-2); i++){
        item = TableWidget->item(row, TableWidget->columnCount()-1-i);
        if (MultiBaseNumber_obj[row].Get_Bit(i)){
            item->setCheckState(Qt::CheckState::Checked);
        }
        else{
            item->setCheckState(Qt::CheckState::Unchecked);
        }
    }
    TableWidget->blockSignals(false);
}

void MainWindow::AddRowInFiltersTable(QString Arg_Col_1, QString Arg_Col_2)
{
    ui->FilterExplorer_tableWidget->insertRow(ui->FilterExplorer_tableWidget->rowCount());
    ui->FilterExplorer_tableWidget->setItem(ui->FilterExplorer_tableWidget->rowCount()-1, 0, new QTableWidgetItem(Arg_Col_1));

    ui->FilterExplorer_tableWidget->setItem(ui->FilterExplorer_tableWidget->rowCount()-1, 1,
                                            new QTableWidgetItem(Arg_Col_2));
}



void MainWindow::on_AddFilter_pushButton_clicked()
{
    short int L_filter_index = ui->FilterId_spinBox->value();
    if (sysFilters.IsExist(L_filter_index)){
        QMessageBox::information(nullptr,
                                 "Filter index confliction",
                                 "This filter won't be added "
                                 "because there is another filter with the same index. "
                                 "Please either assign a non-existing filter index "
                                 "or remove the conflicting filter");
        return ;
    }

    Filter *AddedFilter = nullptr;
    switch (ui->FilterType_Combobox->currentIndex()) {
    case FilterType_1ID32_1Mask32:
        AddedFilter = new Filter_1ID32_1Mask32(ui->FilterName_lineEdit->text(), L_filter_index);
        AddedFilter->SetFilterId(0, MultiBaseNumber_Filter_1ID32_1Mask32[0].Get_Number());
        AddedFilter->SetFilterMask(0, MultiBaseNumber_Filter_1ID32_1Mask32[1].Get_Number());

        break;

    case FilterType_2IDs32_NoMask:
        AddedFilter = new Filter_2IDs32_NoMask(ui->FilterName_lineEdit->text(), L_filter_index);
        AddedFilter->SetFilterId(0, MultiBaseNumber_Filter_2ID32_NoMask[0].Get_Number());
        AddedFilter->SetFilterId(1, MultiBaseNumber_Filter_2ID32_NoMask[1].Get_Number());

        break;

    case FilterType_2ID16_2Mask16:
        AddedFilter = new Filter_2ID16_2Mask16(ui->FilterName_lineEdit->text(), L_filter_index);
        AddedFilter->SetFilterId(0, MultiBaseNumber_Filter_2IDs16_2Masks16[0].Get_Number());
        AddedFilter->SetFilterId(1, MultiBaseNumber_Filter_2IDs16_2Masks16[2].Get_Number());

        AddedFilter->SetFilterMask(0, MultiBaseNumber_Filter_2IDs16_2Masks16[1].Get_Number());
        AddedFilter->SetFilterMask(1, MultiBaseNumber_Filter_2IDs16_2Masks16[3].Get_Number());

        break;

    case FilterType_4IDs16_NoMask:
        AddedFilter = new Filter_4IDs16_NoMask(ui->FilterName_lineEdit->text(), L_filter_index);
        AddedFilter->SetFilterId(0, MultiBaseNumber_Filter_4IDs16_NoMask[0].Get_Number());
        AddedFilter->SetFilterId(1, MultiBaseNumber_Filter_4IDs16_NoMask[1].Get_Number());
        AddedFilter->SetFilterId(2, MultiBaseNumber_Filter_4IDs16_NoMask[2].Get_Number());
        AddedFilter->SetFilterId(3, MultiBaseNumber_Filter_4IDs16_NoMask[3].Get_Number());

        break;
    }


    if (nullptr == AddedFilter){
        return;
    }

    AddedFilter->SetFilterFrameType((FrameTypes)ui->FilterFrameTypecomboBox->currentIndex());


    sysFilters.AddFilter(AddedFilter);
    /*Send to microcontroller if it's connected*/
    if (BoardCommunication.IsConnected()){
        BoardCommunication.SendData((qint32)UI_Send_CMD_Add_Filter,
                                    AddedFilter->GetFilterParameters(),
                                    AddedFilter->GetFilterBankR1_Value(),
                                    AddedFilter->GetFilterBankR2_Value());
    }

    /*** Add filter data in filter data table***/
    /*Filter Name*/
    AddRowInFiltersTable("Filter Name", ui->FilterName_lineEdit->text());

    /*Filter index*/
    AddRowInFiltersTable("Filter Index", QString::number(AddedFilter->GetFilterIndex()));

    /*Filter Type*/
    AddRowInFiltersTable("Filter Type", FilterTypesString[AddedFilter->GetFilterType()]);

    /*Filter Frame Type*/
    AddRowInFiltersTable("Filter Frame Type", FilterFrameTypesString[AddedFilter->GetFilterFrameType()]);

    QString Property, Value;
    for (short int id_idx = 0; id_idx<AddedFilter->GetIDsNumber();id_idx++){
        Property = "ID " + QString::number(id_idx+1);
        Value = "0x"+QString::number(AddedFilter->GetFilterId(id_idx), 16);
        AddRowInFiltersTable(Property, Value);
    }

    for (short int mask_idx = 0; mask_idx<AddedFilter->GetMasksNumber();mask_idx++){
        Property = "Mask " + QString::number(mask_idx+1);
        Value = "0x"+QString::number(AddedFilter->GetFilterMask(mask_idx), 16);
        AddRowInFiltersTable(Property, Value);
    }

}


void MainWindow::on_RefreshAvailableBoards_pushButton_clicked()
{
    BoardSelector.Refresh();
}


void MainWindow::on_connect_pushButton_clicked()
{
    if (!BoardCommunication.IsConnected()){
        QString PortName = BoardSelector.GetPortName();
        if ("" == PortName){
            return;
        }
        /*Connect to board*/
        BoardCommunication.Connect(PortName);

        /*Send Connect signal.*/
        BoardCommunication.SendData((qint32)UI_Send_CMD_Connect, 0xABCD1234, 0x56780A0B, 0x01062160);


        CAN_ANALYZER_Baudrate_Configuration Baudrate_Cfg_union;

        CAN_Baudrates currentSelectedBaudrate = (CAN_Baudrates)ui->baudrateSelector_comboBox->currentIndex();

        short int prescaller = baudrate_configurator_obj.GetPrescallerForTimeQuantumValue(currentSelectedBaudrate);
        Baudrate_Cfg_union.TimeQuanta_1 = baudrate_configurator_obj.GetTimeQuantaBitSegment1Value(currentSelectedBaudrate);
        Baudrate_Cfg_union.TimeQuanta_2 = baudrate_configurator_obj.GetTimeQuantaBitSegment2Value(currentSelectedBaudrate);
        Baudrate_Cfg_union.ReSynchronizationJump = baudrate_configurator_obj.GetReSynchronizationJumpWidthValue(currentSelectedBaudrate);
        /*Send baudrate configurations*/
        BoardCommunication.SendData((qint32)UI_Send_Baudrate_Configurations, prescaller ,Baudrate_Cfg_union.value, 0);
        /*Send start command*/
        BoardCommunication.SendData((qint32)UI_Send_CMD_Start, 0xABCD1234, 0x56780A0B, 0x01062160);

        /*Add filters*/
        for (short int i = 0; i < APP_CONFIG_MAX_FILTER_ID; i++){
            Filter *current_filter = sysFilters.GetFilterAt(i);
            if (nullptr == current_filter){
                continue;
            }
            BoardCommunication.SendData((qint32)UI_Send_CMD_Add_Filter,
                                        current_filter->GetFilterParameters(),
                                        current_filter->GetFilterBankR1_Value(),
                                        current_filter->GetFilterBankR2_Value());
        }


        /*Change Connect pushbutton text*/
        ui->connect_pushButton->setText("Dis-Connect");

    }
    else{
        BoardCommunication.SendData((qint32)UI_Send_CMD_Stop, 0xABCD1234, 0x56780A0B, 0x01062160);
        BoardCommunication.DisConnect();
        /*Change Disconnect pushbutton text*/
        ui->connect_pushButton->setText("Connect");


    }

}

void MainWindow::on_QTable_Filter_1ID32_1Mask32_cellChanged(int row, int column)
{
    ui->QTable_Filter_1ID32_1Mask32->blockSignals(true);
    UpdateTableRow(ui->QTable_Filter_1ID32_1Mask32, MultiBaseNumber_Filter_1ID32_1Mask32, row, column);
    ui->QTable_Filter_1ID32_1Mask32->blockSignals(false);
}

void MainWindow::on_QTable_Filter_2IDs32_NoMask_cellChanged(int row, int column)
{
    ui->QTable_Filter_2IDs32_NoMask->blockSignals(true);
    UpdateTableRow(ui->QTable_Filter_2IDs32_NoMask, MultiBaseNumber_Filter_2ID32_NoMask, row, column);
    ui->QTable_Filter_2IDs32_NoMask->blockSignals(false);
}


void MainWindow::on_QTable_Filter_2ID16_2Mask16_cellChanged(int row, int column)
{
    ui->QTable_Filter_2ID16_2Mask16->blockSignals(true);
    UpdateTableRow(ui->QTable_Filter_2ID16_2Mask16, MultiBaseNumber_Filter_2IDs16_2Masks16, row, column);
    ui->QTable_Filter_2ID16_2Mask16->blockSignals(false);
}


void MainWindow::on_QTable_Filter_4IDs16_NoMask_cellChanged(int row, int column)
{
    ui->QTable_Filter_4IDs16_NoMask->blockSignals(true);
    UpdateTableRow(ui->QTable_Filter_4IDs16_NoMask, MultiBaseNumber_Filter_4IDs16_NoMask, row, column);
    ui->QTable_Filter_4IDs16_NoMask->blockSignals(false);
}

void MainWindow::on_FilterId_spinBox_valueChanged(int arg1)
{
    QString PushButtonLabel = "Delete Filter with ID = " + QString::number(arg1);
    ui->DeleteFilter_pushButton->setText(PushButtonLabel);
}


void MainWindow::on_DeleteFilter_pushButton_clicked()
{
    short int target_index = ui->FilterId_spinBox->value();

    /*Delete from microcontroller*/
    if (BoardCommunication.IsConnected()){
        Filter *current_filter = sysFilters.GetFilterAt(target_index);

        if (nullptr != current_filter){
            BoardCommunication.SendData((qint32)UI_Send_CMD_Remove_Filter,
                                        current_filter->GetFilterParameters(),
                                        current_filter->GetFilterBankR1_Value(),
                                        current_filter->GetFilterBankR2_Value());
        }
    }


    /*Delete from system*/
    sysFilters.DeleteFilter(target_index);
    short int target_row = -1;

    for (short int i_row = 0; i_row < (ui->FilterExplorer_tableWidget->rowCount()-1); i_row++){

        if (
                ("Filter Index" == ui->FilterExplorer_tableWidget->item(i_row, 0)->text()) &&
                (ui->FilterExplorer_tableWidget->item(i_row, 1)->text().toInt() == target_index)

                ){
            target_row = i_row-1;
        }
    }

    if (-1 == target_row){
        return ;
    }

    ui->FilterExplorer_tableWidget->removeRow(target_row);

    while ((ui->FilterExplorer_tableWidget->rowCount() > 0) &&
           (target_row < ui->FilterExplorer_tableWidget->rowCount())
           ){

        if ("Filter Name" == ui->FilterExplorer_tableWidget->item(target_row, 0)->text()){
            break;
        }

        if (target_row == ui->FilterExplorer_tableWidget->rowCount()){
            break;
        }
        ui->FilterExplorer_tableWidget->removeRow(target_row);
    }
}


void MainWindow::on_CANSendFrame_pushButton_clicked()
{
    if (BoardCommunication.IsConnected()){
        BoardCommunication.SendData(SendFrame_CANData);
    }
}


void MainWindow::on_SendData1DataType_comboBox_currentIndexChanged(int index)
{
    on_SendDataxDataType_comboBox_currentIndexChanged(0, index);
}


void MainWindow::on_SendData2DataType_comboBox_currentIndexChanged(int index)
{
    on_SendDataxDataType_comboBox_currentIndexChanged(1, index);
}


void MainWindow::on_SendData3DataType_comboBox_currentIndexChanged(int index)
{
    on_SendDataxDataType_comboBox_currentIndexChanged(2, index);
}


void MainWindow::on_SendData4DataType_comboBox_currentIndexChanged(int index)
{
    on_SendDataxDataType_comboBox_currentIndexChanged(3, index);
}


void MainWindow::on_SendData5DataType_comboBox_currentIndexChanged(int index)
{
    on_SendDataxDataType_comboBox_currentIndexChanged(4, index);
}


void MainWindow::on_SendData6DataType_comboBox_currentIndexChanged(int index)
{
    on_SendDataxDataType_comboBox_currentIndexChanged(5, index);
}


void MainWindow::on_SendData7DataType_comboBox_currentIndexChanged(int index)
{
    on_SendDataxDataType_comboBox_currentIndexChanged(6, index);
}


void MainWindow::on_SendData8DataType_comboBox_currentIndexChanged(int index)
{
    on_SendDataxDataType_comboBox_currentIndexChanged(7, index);
}



void MainWindow::on_SendDataLength_comboBox_currentIndexChanged(int index)
{
    SendFrame_CANData.DataLength = index;
    /*Enable objects from 0 to changed Data-Length.*/
    for (short int i = 0; i<index; i++){
        SendDataQLineEdits.at(i)->setEnabled(true);
        SendDataQComboBoxes.at(i)->setEnabled(true);
    }
    /*Disable objects from Data-Length to changed Maximum Data Length.*/
    for (short int i = index; i<MaxDataLength; i++){
        SendDataQLineEdits.at(i)->setEnabled(false);
        SendDataQComboBoxes.at(i)->setEnabled(false);
    }
}

void MainWindow::on_SendDatax_lineEdit_textChanged(const QString &arg1, short idx)
{

    bool validFormat;
    quint8 value; // Value of send data with index x where x = idx
    if ("" == arg1){
        SendFrame_CANData.Data.at(idx) = 0;
        return;
    }

    switch (SendDataQComboBoxes.at(idx)->currentIndex()) {
    case Val_Bin_idx:
        value = arg1.toInt(&validFormat, 2);
        break;

    case Val_Oct_idx:
        value = arg1.toInt(&validFormat, 8);
        break;

    case Val_Dec_idx:
        value = arg1.toInt(&validFormat, 10);
        break;

    case Val_Hex_idx:
        value = arg1.toInt(&validFormat, 16);
        break;
    default:
        throw std::runtime_error ("Not available numbering system !");
    }

    if (!validFormat){
        QMessageBox::critical(nullptr, "Numbering system conversion error.",
                              "Please enter number that match selected number system");
        SendDataQLineEdits.at(idx)->clear();
        return;
    }
    SendFrame_CANData.Data.at(idx) = value;
}

void MainWindow::on_SendData1_lineEdit_textChanged(const QString &arg1)
{
    on_SendDatax_lineEdit_textChanged(arg1, 0);
}


void MainWindow::on_SendData2_lineEdit_textChanged(const QString &arg1)
{
    on_SendDatax_lineEdit_textChanged(arg1, 1);
}


void MainWindow::on_SendData3_lineEdit_textChanged(const QString &arg1)
{
    on_SendDatax_lineEdit_textChanged(arg1, 2);
}


void MainWindow::on_SendData4_lineEdit_textChanged(const QString &arg1)
{
    on_SendDatax_lineEdit_textChanged(arg1, 3);
}


void MainWindow::on_SendData5_lineEdit_textChanged(const QString &arg1)
{
    on_SendDatax_lineEdit_textChanged(arg1, 4);
}


void MainWindow::on_SendData6_lineEdit_textChanged(const QString &arg1)
{
    on_SendDatax_lineEdit_textChanged(arg1, 5);
}


void MainWindow::on_SendData7_lineEdit_textChanged(const QString &arg1)
{
    on_SendDatax_lineEdit_textChanged(arg1, 6);
}


void MainWindow::on_SendData8_lineEdit_textChanged(const QString &arg1)
{
    on_SendDatax_lineEdit_textChanged(arg1, 7);
}

void MainWindow::on_SendDataxDataType_comboBox_currentIndexChanged(short Arg_Byte_Idx, int index)
{
    QString NewTextVal;
    quint8 currentByteVal = SendFrame_CANData.Data.at(Arg_Byte_Idx);

    switch (index) {
    case Val_Bin_idx:
        NewTextVal = QString::number(currentByteVal, 2);
        break;

    case Val_Oct_idx:
        NewTextVal = QString::number(currentByteVal, 8);
        break;

    case Val_Dec_idx:
        NewTextVal = QString::number(currentByteVal, 10);
        break;

    case Val_Hex_idx:
        NewTextVal = QString::number(currentByteVal, 16);
        break;
    default:
        throw std::runtime_error ("Not available numbering system !");
    }

    SendDataQLineEdits.at(Arg_Byte_Idx)->blockSignals(true);
    SendDataQLineEdits.at(Arg_Byte_Idx)->setText(NewTextVal);
    SendDataQLineEdits.at(Arg_Byte_Idx)->blockSignals(false);

}



void MainWindow::on_SendDataFrameType_comboBox_currentIndexChanged(int index)
{
    SendFrame_CANData.Frametype = (FrameTypes) index;
}




void MainWindow::on_spinBox_valueChanged(int arg1)
{
    if (nullptr == ReceiveCANMessages_DataTable){
        return ;
    }
    ReceiveCANMessages_DataTable->SetMaxShownMessagesNumber(arg1);
}


void MainWindow::on_SendIdOfData_lineEdit_textChanged(const QString &arg1)
{
    bool conversionSuccess = true;
    switch (ui->SendDataIdBase_comboBox->currentIndex()) {
    case Val_Bin_idx:
        conversionSuccess = MultiBaseNumber_SendFrame.Set_NumberInBinFormat(arg1);
        break;

    case Val_Oct_idx:
        conversionSuccess = MultiBaseNumber_SendFrame.Set_NumberInOctFormat(arg1);
        break;

    case Val_Dec_idx:
        conversionSuccess = MultiBaseNumber_SendFrame.Set_NumberInDecFormat(arg1);
        break;

    case Val_Hex_idx:
        conversionSuccess = MultiBaseNumber_SendFrame.Set_NumberInHexFormat(arg1);
        break;
    default:
        throw std::runtime_error ("Not available numbering system !");
    }

    if (!conversionSuccess){
        QMessageBox::critical(nullptr, "Numbering system conversion error.",
                              "Please enter number that match selected number system");
        ui->SendIdOfData_lineEdit->clear();
        MultiBaseNumber_SendFrame.Set_Number(0);

    }
    SendFrame_CANData.FrameId = MultiBaseNumber_SendFrame.Get_Number();
}



void MainWindow::on_SendDataIdBase_comboBox_currentIndexChanged(int index)
{
    QString NewTextVal;
    quint32 ID_Val = MultiBaseNumber_SendFrame.Get_Number();
    switch (index) {
    case Val_Bin_idx:
        NewTextVal = QString::number(ID_Val, 2);
        break;

    case Val_Oct_idx:
        NewTextVal = QString::number(ID_Val, 8);
        break;

    case Val_Dec_idx:
        NewTextVal = QString::number(ID_Val, 10);
        break;

    case Val_Hex_idx:
        NewTextVal = QString::number(ID_Val, 16);
        break;
    default:
        throw std::runtime_error ("Not available numbering system !");
    }

    ui->SendIdOfData_lineEdit->blockSignals(true);
    ui->SendIdOfData_lineEdit->setText(NewTextVal);
    ui->SendIdOfData_lineEdit->blockSignals(false);
}

void MainWindow::sendDataInitParameters()
{
    SendDataQLineEdits ={
        ui->SendData1_lineEdit,
        ui->SendData2_lineEdit,
        ui->SendData3_lineEdit,
        ui->SendData4_lineEdit,
        ui->SendData5_lineEdit,
        ui->SendData6_lineEdit,
        ui->SendData7_lineEdit,
        ui->SendData8_lineEdit,

    };
    SendDataQComboBoxes = {
        ui->SendData1DataType_comboBox,
        ui->SendData2DataType_comboBox,
        ui->SendData3DataType_comboBox,
        ui->SendData4DataType_comboBox,
        ui->SendData5DataType_comboBox,
        ui->SendData6DataType_comboBox,
        ui->SendData7DataType_comboBox,
        ui->SendData8DataType_comboBox,
    };

    SendFrame_CANData.FrameId = 0;
    SendFrame_CANData.Frametype = DataFrame;
    SendFrame_CANData.DataLength = 0;
    SendFrame_CANData.Data.fill(0);
}
