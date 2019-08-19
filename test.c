#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char stringa1[100]="\"anna\"";
    char stringa2[100]="\"barbara\"";
    char stringa3[100]="\"carlo\"";

    if(strcmp(stringa3, stringa2)>0){
        printf("a>b\n");
    }else{
        printf("a<b\n");
    }
}