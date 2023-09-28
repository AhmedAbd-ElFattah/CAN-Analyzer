#include "receivedatatable.h"

ReceiveDataTable::ReceiveDataTable(
        QTableWidget *Arg_TableWidget,
        QComboBox *ID = nullptr,
        QComboBox *DataLength = nullptr,
        QComboBox *Data_Combobox = nullptr,
        QComboBox *Arg_FilterId_Combobox = nullptr
        ):
    Table(Arg_TableWidget),
    ID_Combobox(ID),
    DataLength_Combobox(DataLength),
    Data_Combobox(Data_Combobox),
    FilterId_Combobox(Arg_FilterId_Combobox)
{

}

QString ReceiveDataTable::ShowNumberWithBase(const QComboBox * const Arg_ComboBox, const quint8 Arg_value)
{
    QString text;
    switch (Arg_ComboBox->currentIndex()) {
    case Val_Bin_idx:
        text = "0b" + QString::number(Arg_value, 2);
        break;
    case Val_Oct_idx:
        text = "0o"+ QString::number(Arg_value, 8);
        break;
    case Val_Dec_idx:
        text = QString::number(Arg_value, 10);
        break;
    case Val_Hex_idx:
        text = "0x"+ QString::number(Arg_value, 16);
        break;
    default:
        throw std::runtime_error ("Not available numbering system !");
    }
    return text;
}



void ReceiveDataTable::AddData(const CANData Arg_CANData)
{
    if (nullptr == Table){
        return ;
    }

    Table->insertRow(Table->rowCount());
    /*
     * If number of viewed messages at it's maximim value,
     * Delete first one which is last received messaged from the shown messages.
    */
    if (Table->rowCount() > (MaxShownMessagesNumber)){
        /*Delete First row.*/
        while (Table->rowCount() != (MaxShownMessagesNumber)) {
            Table->removeRow(0);
        }
    }

    QString CurrentTextCellVal = "";
    CurrentTextCellVal = ShowNumberWithBase(ID_Combobox, Arg_CANData.FrameId);
    /*Add frame index to first column which has index = 0*/
    Table->setItem(Table->rowCount()-1, 0, new QTableWidgetItem(CurrentTextCellVal));

    switch (Arg_CANData.Frametype) {
    case DataFrame:
        CurrentTextCellVal = "Data Frame";

        break;
    case RemoteFrame:
        CurrentTextCellVal = "Remote Frame";
        break;
    default:
        throw std::runtime_error ("Not available Frame type !");
    }

    /*Add frame type to second column which has index = 1*/
    Table->setItem(Table->rowCount()-1, 1, new QTableWidgetItem(CurrentTextCellVal));

    /*Add frame type to third column which has index = 2*/
    CurrentTextCellVal = ShowNumberWithBase(DataLength_Combobox, Arg_CANData.DataLength);
    Table->setItem(Table->rowCount()-1, 2, new QTableWidgetItem(CurrentTextCellVal));

    /*Add filter id to third column which has index = 3*/
    CurrentTextCellVal = ShowNumberWithBase(FilterId_Combobox, Arg_CANData.FilterId);
    Table->setItem(Table->rowCount()-1, 3, new QTableWidgetItem(CurrentTextCellVal));

    if (0 == Arg_CANData.DataLength){
        return ;
    }
    for (int i = 0; i<(Arg_CANData.DataLength); i++){

        CurrentTextCellVal = ShowNumberWithBase(Data_Combobox, Arg_CANData.Data.at(i));
        Table->setItem(Table->rowCount()-1, 4+i, new QTableWidgetItem(CurrentTextCellVal));
    }

    /*Scroll to last element*/
    // Assuming myTableWidget is your QTableWidget
    int lastRow = Table->rowCount() - 1; // Get the last row index

    if (lastRow >= 0) {
        QTableWidgetItem* lastItem = Table->item(lastRow, 0); // Assuming you want the first column
        Table->scrollToItem(lastItem);
    }


}


void ReceiveDataTable::SetMaxShownMessagesNumber(const short Arg_Val)
{
    MaxShownMessagesNumber = Arg_Val;
}

