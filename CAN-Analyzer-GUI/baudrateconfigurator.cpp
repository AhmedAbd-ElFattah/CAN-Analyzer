#include "baudrateconfigurator.h"

BaudRateConfigurator::BaudRateConfigurator()
{
    /*Configuration for 1000 kbs baudrate.*/
    PrescallerForTimeQuantum_Arr.at(CAN_Baudrate_1000_kbs) = 1;
    TimeQuantaBitSegment1_Arr.at(CAN_Baudrate_1000_kbs) = 13;
    TimeQuantaBitSegment2_Arr.at(CAN_Baudrate_1000_kbs) = 2;
    ReSynchronizationJumpWidth_Arr.at(CAN_Baudrate_1000_kbs) = 1;

    /*Configuration for 800  kbs baudrate.*/
    PrescallerForTimeQuantum_Arr.at(CAN_Baudrate_800_kbs) = 2;
    TimeQuantaBitSegment1_Arr.at(CAN_Baudrate_800_kbs) = 8;
    TimeQuantaBitSegment2_Arr.at(CAN_Baudrate_800_kbs) = 1;
    ReSynchronizationJumpWidth_Arr.at(CAN_Baudrate_800_kbs) = 1;

    /*Configuration for 500  kbs baudrate.*/
    PrescallerForTimeQuantum_Arr.at(CAN_Baudrate_500_kbs) = 2;
    TimeQuantaBitSegment1_Arr.at(CAN_Baudrate_500_kbs) = 13;
    TimeQuantaBitSegment2_Arr.at(CAN_Baudrate_500_kbs) = 2;
    ReSynchronizationJumpWidth_Arr.at(CAN_Baudrate_500_kbs) = 1;

    /*Configuration for 250  kbs baudrate.*/
    PrescallerForTimeQuantum_Arr.at(CAN_Baudrate_250_kbs) = 4;
    TimeQuantaBitSegment1_Arr.at(CAN_Baudrate_250_kbs) = 13;
    TimeQuantaBitSegment2_Arr.at(CAN_Baudrate_250_kbs) = 2;
    ReSynchronizationJumpWidth_Arr.at(CAN_Baudrate_250_kbs) = 1;

    /*Configuration for 125  kbs baudrate.*/
    PrescallerForTimeQuantum_Arr.at(CAN_Baudrate_125_kbs) = 8;
    TimeQuantaBitSegment1_Arr.at(CAN_Baudrate_125_kbs) = 13;
    TimeQuantaBitSegment2_Arr.at(CAN_Baudrate_125_kbs) = 2;
    ReSynchronizationJumpWidth_Arr.at(CAN_Baudrate_125_kbs) = 1;
}

short BaudRateConfigurator::GetPrescallerForTimeQuantumValue(CAN_Baudrates Arg_baudrate)
{
    return PrescallerForTimeQuantum_Arr.at(Arg_baudrate);
}

short BaudRateConfigurator::GetTimeQuantaBitSegment1Value(CAN_Baudrates Arg_baudrate)
{
    return TimeQuantaBitSegment1_Arr.at(Arg_baudrate);
}

short BaudRateConfigurator::GetTimeQuantaBitSegment2Value(CAN_Baudrates Arg_baudrate)
{
    return TimeQuantaBitSegment2_Arr.at(Arg_baudrate);
}

short BaudRateConfigurator::GetReSynchronizationJumpWidthValue(CAN_Baudrates Arg_baudrate)
{
    return ReSynchronizationJumpWidth_Arr.at(Arg_baudrate);
}
