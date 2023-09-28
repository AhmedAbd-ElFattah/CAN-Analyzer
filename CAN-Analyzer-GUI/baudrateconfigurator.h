#ifndef BAUDRATECONFIGURATOR_H
#define BAUDRATECONFIGURATOR_H
#include <array>
/*
 * File Name --> baudrateconfigurator.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> Provides configuration parameters for standard can baudrates
 */

enum CAN_Baudrates{
    CAN_Baudrate_1000_kbs,
    CAN_Baudrate_800_kbs,
    CAN_Baudrate_500_kbs,
    CAN_Baudrate_250_kbs,
    CAN_Baudrate_125_kbs,
};

#define CAN_NUMBER_AVAILABLE_BAUARATES 5

class BaudRateConfigurator
{
private:
    std::array<short int, CAN_NUMBER_AVAILABLE_BAUARATES> PrescallerForTimeQuantum_Arr;
    std::array<short int, CAN_NUMBER_AVAILABLE_BAUARATES> TimeQuantaBitSegment1_Arr;
    std::array<short int, CAN_NUMBER_AVAILABLE_BAUARATES> TimeQuantaBitSegment2_Arr;
    std::array<short int, CAN_NUMBER_AVAILABLE_BAUARATES> ReSynchronizationJumpWidth_Arr;

public:
    BaudRateConfigurator();
    short int GetPrescallerForTimeQuantumValue(CAN_Baudrates Arg_baudrate);
    short int GetTimeQuantaBitSegment1Value(CAN_Baudrates Arg_baudrate);
    short int GetTimeQuantaBitSegment2Value(CAN_Baudrates Arg_baudrate);
    short int GetReSynchronizationJumpWidthValue(CAN_Baudrates Arg_baudrate);
};
#undef CAN_NUMBER_AVAILABLE_BAUARATES

#endif // BAUDRATECONFIGURATOR_H
