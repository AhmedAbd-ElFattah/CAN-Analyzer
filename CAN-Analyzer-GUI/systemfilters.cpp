#include "systemfilters.h"

SystemFilters::SystemFilters()
{
    for (unsigned long i = 0; i< Array_SystemFilters.size(); i++){
        Array_SystemFilters.at(i) = nullptr;
    }
}

void SystemFilters::AddFilter(Filter *Arg_Filter)
{
    Array_SystemFilters.at(Arg_Filter->GetFilterIndex()) = Arg_Filter;
}

void SystemFilters::DeleteFilter(short Arg_FilterId)
{
    if(nullptr == Array_SystemFilters.at(Arg_FilterId)){
        return ;
    }
    delete Array_SystemFilters.at(Arg_FilterId);
    Array_SystemFilters.at(Arg_FilterId) = nullptr;
}

Filter *SystemFilters::GetFilterAt(short Arg_FilterId)
{
    return Array_SystemFilters.at(Arg_FilterId);
}

bool SystemFilters::IsExist(short Arg_FilterId)
{
    return Array_SystemFilters.at(Arg_FilterId) != nullptr;
}


