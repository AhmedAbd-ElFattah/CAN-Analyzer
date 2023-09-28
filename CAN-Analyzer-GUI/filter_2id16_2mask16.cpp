#include "filter_2id16_2mask16.h"


Filter_2ID16_2Mask16::Filter_2ID16_2Mask16(QString Arg_FilterName_String, short int Arg_FilterIdx)
{
    IDsNumber = 2;
    MasksNumber = 2;

    FilterIndex = Arg_FilterIdx;
    FilterName = Arg_FilterName_String;
    FilterType = FilterType_2ID16_2Mask16;
}



void Filter_2ID16_2Mask16::SetFilterId(short idx, qint32 val)
{
    if (idx >= IDsNumber){
        throw std::out_of_range("Max index is " + std::to_string(IDsNumber-1) + " Entered index is " + std::to_string(idx));
    }
    ID[idx] = val;
}

void Filter_2ID16_2Mask16::SetFilterMask(short idx, qint32 val)
{
    if (idx >= MasksNumber){
        throw std::out_of_range("Max index is " + std::to_string(MasksNumber-1) + " Entered index is " + std::to_string(idx));
    }
    Mask[idx] = val;
}

quint32 Filter_2ID16_2Mask16::GetFilterId(short idx)
{
    if (idx >= IDsNumber){
        throw std::out_of_range("Max index is " + std::to_string(IDsNumber-1) + " Entered index is " + std::to_string(idx));
    }
    return ID[idx];
}

quint32 Filter_2ID16_2Mask16::GetFilterMask(short idx)
{
    if (idx >= MasksNumber){
        throw std::out_of_range("Max index is " + std::to_string(MasksNumber-1) + " Entered index is " + std::to_string(idx));
    }
    return Mask[idx];
}

qint32 Filter_2ID16_2Mask16::GetFilterBankR1_Value()
{
    FilterBankR1_Value = (ID[0]|(ID[1]<<16));
    return FilterBankR1_Value;
}

qint32 Filter_2ID16_2Mask16::GetFilterBankR2_Value()
{
    FilterBankR2_Value = (Mask[0]|(Mask[1]<<16));
    return FilterBankR2_Value;
}

Filter_2ID16_2Mask16::~Filter_2ID16_2Mask16()
{

}
