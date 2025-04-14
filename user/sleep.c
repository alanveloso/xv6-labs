#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int num, char *num_2S[]){
    
    if (num <= 1){
        exit(1);
    }
    
    int ticks = atoi(num_2S[1]);
    sleep(ticks);
    exit(0);
    
}
