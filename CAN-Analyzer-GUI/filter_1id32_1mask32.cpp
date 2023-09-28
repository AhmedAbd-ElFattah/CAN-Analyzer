#include "filter_1id32_1mask32.h"

Filter_1ID32_1Mask32::Filter_1ID32_1Mask32(QString Arg_FilterName_String, short int Arg_FilterIdx)
{
    IDsNumber = 1;
    MasksNumber = 1;

    FilterIndex = Arg_FilterIdx;
    FilterName = Arg_FilterName_String;
    FilterType = FilterType_1ID32_1Mask32;
}



void Filter_1ID32_1Mask32::SetFilterId(short idx, qint32 val)
{
    if (idx >= IDsNumber){
        throw std::out_of_range("Max index is " + std::to_string(IDsNumber-1) + " Entered index is " + std::to_string(idx));
    }
    ID = val;
}

void Filter_1ID32_1Mask32::SetFilterMask(short idx, qint32 val)
{
    if (idx >= MasksNumber){
        throw std::out_of_range("Max index is " + std::to_string(MasksNumber-1) + " Entered index is " + std::to_string(idx));
    }
    Mask = val;
}

quint32 Filter_1ID32_1Mask32::GetFilterId(short idx)
{
    if (idx >= IDsNumber){
        throw std::out_of_range("Max index is " + std::to_string(IDsNumber-1) + " Entered index is " + std::to_string(idx));
    }
    return ID;
}

quint32 Filter_1ID32_1Mask32::GetFilterMask(short idx)
{
    if (idx >= MasksNumber){
        throw std::out_of_range("Max index is " + std::to_string(MasksNumber-1) + " Entered index is " + std::to_string(idx));
    }
    return Mask;
}

qint32 Filter_1ID32_1Mask32::GetFilterBankR1_Value()
{
    FilterBankR1_Value = ID;
    return FilterBankR1_Value;
}

qint32 Filter_1ID32_1Mask32::GetFilterBankR2_Value()
{
    FilterBankR2_Value = Mask;
    return FilterBankR2_Value;
}

Filter_1ID32_1Mask32::~Filter_1ID32_1Mask32()
{

}
