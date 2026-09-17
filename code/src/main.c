#include "Flap Control Logic.h"
#include "System Startup/Initialization.h"

int main(void)
{
    (void)system_init();

    while (1)
    {
        Flap_Control_Logic_MainTask();
    }
}
