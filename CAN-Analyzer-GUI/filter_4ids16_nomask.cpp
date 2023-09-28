#include "filter_4ids16_nomask.h"

Filter_4IDs16_NoMask::Filter_4IDs16_NoMask(QString Arg_FilterName_String, short int Arg_FilterIdx)
{
    IDsNumber = 4;
    MasksNumber = 0;

    FilterIndex = Arg_FilterIdx;
    FilterName = Arg_FilterName_String;
    FilterType = FilterType_4IDs16_NoMask;
}



void Filter_4IDs16_NoMask::SetFilterId(short idx, qint32 val)
{
    if (idx >= IDsNumber){
        throw std::out_of_range("Max index is " + std::to_string(IDsNumber-1) + " Entered index is " + std::to_string(idx));
    }
    ID[idx] = val;
}

void Filter_4IDs16_NoMask::SetFilterMask(short idx, qint32 val)
{
    if (idx >= MasksNumber){
        throw std::out_of_range("Max index is " + std::to_string(MasksNumber) + " Entered index is " + std::to_string(idx));
    }
}

quint32 Filter_4IDs16_NoMask::GetFilterId(short idx)
{
    if (idx >= IDsNumber){
        throw std::out_of_range("Max index is " + std::to_string(IDsNumber-1) + " Entered index is " + std::to_string(idx));
    }
    return ID[idx];
}

quint32 Filter_4IDs16_NoMask::GetFilterMask(short idx)
{
    if (idx >= MasksNumber){
        throw std::out_of_range("Max index is " + std::to_string(MasksNumber) + " Entered index is " + std::to_string(idx));
    }
    return -1;
}

qint32 Filter_4IDs16_NoMask::GetFilterBankR1_Value()
{
    FilterBankR1_Value = (ID[0]|ID[1]<<16);
    return FilterBankR1_Value;
}

qint32 Filter_4IDs16_NoMask::GetFilterBankR2_Value()
{
    FilterBankR2_Value = (ID[2]|ID[3]<<16);
    return FilterBankR2_Value;
}

Filter_4IDs16_NoMask::~Filter_4IDs16_NoMask()
{

}
