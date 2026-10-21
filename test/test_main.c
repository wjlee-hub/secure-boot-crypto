#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint8_t a[4]  = {0x57, 0x00, 0x0f, 0xff};
    int i;

    for (i = 0; i<4; i++) {
        a[i] = a[i] ^ 0xff;
        printf("a[%d] = 0x%02x\n", i, a[i]);
        
    }
    return 0;
}
