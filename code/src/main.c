#include "Application_Layer.h"

int main(void)
{
    Application_Init();
    while(1)
    {
        Application_Process();
    }
    return 0;
}
