#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int gen_ladder(float*array, int size){
    for(int o = 0; o < size-1; o++){
        float sum=0;
        for(int i = size-1; i > o; i--){
            array[i]-=array[i-1];
            sum+=array[i];
        }
        if(sum==0){
            return o+1;
        }
    }
    return size;
}

int main(){
    float values[64] = {};
    int size=0;
    float buffer[64] = {};
    char input[64];
    printf("data file: "); scanf("%s", input);
    FILE *fp = fopen(input, "r");
    if(!fp){
        printf("Unable to locate file: %s\n", input);
        return 1;
    }
    char fv[32]; char ch;
    int fvsize=0;
    do{
        ch = fgetc(fp);
        if(ch == '\n'){
            fv[fvsize] = '\0';
            fvsize = 0;
            values[size] = atof(fv);
            size++;
            continue;
        }
        fv[fvsize] = ch;
        fvsize++;

    }
    while(ch > -1);
    fclose(fp);

    int nsize = gen_ladder(values, size);
    for(int i = nsize-1; i >= 0; i--){
        int o = 1;
        for(; o <= i; o++){
            buffer[o-1] = pow(o, i);
        }
        buffer[o-1] = pow(o, i);
        gen_ladder(buffer, o);
        float scalar = values[i]/buffer[i];
        for(; o >= 0; o--){
            values[o]-=buffer[o]*scalar;
        }
        buffer[i]=scalar;
        printf("%f*pow(x, %d)\n", scalar, i);
    }
}
