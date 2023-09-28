#include "CANAnalyzer.h"

int main(void)
{
	CANAnalyzer_Init_v();
	while(1){
		CANAnalyzer_WaitPoolingForMessage();
	}
}
