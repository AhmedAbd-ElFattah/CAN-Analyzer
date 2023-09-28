#include "filter.h"

Filter::Filter()
{
    FilterBankR1_Value = 0;
    FilterBankR2_Value = 0;
}

short Filter::GetIDsNumber()
{
    return IDsNumber;
}

short Filter::GetMasksNumber()
{
    return MasksNumber;
}

void Filter::SetFilterFrameType(FrameTypes Arg_FrameType)
{
    FilterFrameType = Arg_FrameType;
}

FrameTypes Filter::GetFilterFrameType()
{
    return FilterFrameType;
}

short Filter::GetFilterIndex()
{
    return FilterIndex;
}

qint32 Filter::GetFilterParameters()
{
    qint32 L_FilterTypeAndId_qint32 = (qint32)GetFilterType();
    L_FilterTypeAndId_qint32 |= (GetFilterIndex() << 2);
    if (DataFrame == GetFilterFrameType()){
         L_FilterTypeAndId_qint32 &= ~(1<<31);
    }
    else if (RemoteFrame == GetFilterFrameType()) {
        L_FilterTypeAndId_qint32 |= (1<<31);
    }
    else{

    }
    return L_FilterTypeAndId_qint32;
}

FilterTypes Filter::GetFilterType()
{
    return FilterType;
}

Filter::~Filter()
{

}
