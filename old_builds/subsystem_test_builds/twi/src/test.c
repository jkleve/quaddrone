#include <stdio.h>
#include <stdint.h>

int main() {

    int8_t n = (1<<2);
    
    printf("%x becomes %x\n", n, ~n);

    return 0;
}
