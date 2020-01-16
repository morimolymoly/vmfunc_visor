#include <stdio.h>

#define VMX_VMFUNC ".byte 0x0f,0x01,0xd4"
static void vmfunc(unsigned int nr, unsigned int ept)
{
    asm volatile(VMX_VMFUNC
                :
                : "a"(nr), "c"(ept)
                : "memory");
}

int main()
{
    vmfunc(0,1);
}
