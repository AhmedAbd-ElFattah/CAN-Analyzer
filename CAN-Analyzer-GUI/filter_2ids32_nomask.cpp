#include "filter_2ids32_nomask.h"


Filter_2IDs32_NoMask::Filter_2IDs32_NoMask(QString Arg_FilterName_String, short int Arg_FilterIdx)
{
    IDsNumber = 2;
    MasksNumber = 0;

    FilterIndex = Arg_FilterIdx;
    FilterName = Arg_FilterName_String;
    FilterType = FilterType_2IDs32_NoMask;
}



void Filter_2IDs32_NoMask::SetFilterId(short idx, qint32 val)
{
    if (idx >= IDsNumber){
        throw std::out_of_range("Max index is " + std::to_string(IDsNumber-1) + " Entered index is " + std::to_string(idx));
    }
    ID[idx] = val;
}

void Filter_2IDs32_NoMask::SetFilterMask(short idx, qint32 val)
{
    if (idx >= MasksNumber){
        throw std::out_of_range("Max index is " + std::to_string(MasksNumber) + " Entered index is " + std::to_string(idx));
    }
}

quint32 Filter_2IDs32_NoMask::GetFilterId(short idx)
{
    if (idx >= IDsNumber){
        throw std::out_of_range("Max index is " + std::to_string(IDsNumber) + " Entered index is " + std::to_string(idx));
    }
    return ID[idx];
}

quint32 Filter_2IDs32_NoMask::GetFilterMask(short idx)
{
    if (idx >= MasksNumber){
        throw std::out_of_range("Max index is " + std::to_string(MasksNumber) + " Entered index is " + std::to_string(idx));
    }
    return -1;
}

qint32 Filter_2IDs32_NoMask::GetFilterBankR1_Value()
{
    FilterBankR1_Value = ID[0];
    return FilterBankR1_Value;
}

qint32 Filter_2IDs32_NoMask::GetFilterBankR2_Value()
{
    FilterBankR2_Value = ID[1];
    return FilterBankR2_Value;
}

Filter_2IDs32_NoMask::~Filter_2IDs32_NoMask()
{

}
