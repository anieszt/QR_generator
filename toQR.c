
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "QRutils.h"

int main(int argc, char* argrv[]){

    //selecting the mode indicator:

    char mode[50]="", mode_indicator[5]="";
    char data[]="132463822345678998765";
    int num_check = 0, alnum_check = 0, byte_check = -2, jis_check = -2;
    int v = 11;

    for(int i= 0; i<= sizeof(data); i++){
        char c = data[i];
        if(isdigit(c)) num_check += 1;
        if(isdigit(c) || isupper(c)
          || c == '$' || c == ':'
          || c == '%' || c == '*'
          || c == '+' || c == '-'
          || c == '.' || c == '/'
          || c == '$' || c == ' ') alnum_check += 1;

        if((int)c <=255) byte_check += 1;
        if(isjis(data[i], data[i+1])) jis_check += 1;
    }

    if(num_check < alnum_check && alnum_check == byte_check){
        strcpy(mode, "alphanumeric");
        strcpy(mode_indicator, "0010");
    }else if (num_check == alnum_check  && num_check == byte_check){
        strcpy(mode, "numeric");
        strcpy(mode_indicator, "0001");
    }else if(byte_check > alnum_check && byte_check != alnum_check){
        strcpy(mode, "byte");
        strcpy(mode_indicator, "0100");
    }if(jis_check > 0){
        strcpy(mode, "JIS");
        strcpy(mode_indicator, "1000");
    }

    //selecting the version:
        //number of characters to binary for character count indicator:

    char *bin = tobin(strlen(data));
    char ch_count_indicator[33] ="";
    strcpy(ch_count_indicator, bin);
    free(bin);

        //padding of the character count indicator for normalization depending on the version range:
        
    char flag[38]="";
    strcpy(flag, strcat(strcat(mode_indicator, " "), pad_v(ch_count_indicator,v,mode_indicator)));
    //printf("%s\n", flag);

    
    numeric_enc(data);

    for(int i =0; i<sizeof(data)/3; i++){
        printf("%s\n", str_a[i]);
    }
    
    return 0;
}


