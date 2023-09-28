#ifndef SYSTEMFILTERS_H
#define SYSTEMFILTERS_H
/*
 * File Name --> systemfilters.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> Class SystemFilters responsible for system filter operations like
 * add filter, delete filter, or check the existance of filter.
 * */
#include "ApplicationConfigurations.h"
#include "filter_1id32_1mask32.h"
#include <array>


class SystemFilters
{
private:
    std::array<Filter *, (APP_CONFIG_MAX_FILTER_ID+1)>Array_SystemFilters;

public:
    SystemFilters();
    void AddFilter(Filter * Arg_Filter);
    void DeleteFilter(short int Arg_FilterId);
    Filter *GetFilterAt(short int Arg_FilterId);
    bool IsExist(short int Arg_FilterId);
};

#endif // SYSTEMFILTERS_H
