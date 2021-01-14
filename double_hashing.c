#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "open_addressing.h"

double get_realtime(void){
    struct timespec t;
    clock_gettime(CLOCK_REALTIME,&t);
    return t.tv_sec +(double)t.tv_nsec*1e-9;
}

DictOpenAddr *create_dict(int len){
    DictOpenAddr  *new_dict=(DictOpenAddr*)malloc(sizeof(DictOpenAddr));
    if(new_dict!=NULL){
        new_dict->H=(DictData*)malloc(sizeof(DictData));
        if(new_dict->H==NULL){
            free(new_dict);
            return NULL;
        }
    }
    int x;
    new_dict->B=len;
    for(x=0;x<len;x++){
        new_dict->H[x].state=EMPTY;
    }
    printf("Dictionary created!\n");
    return new_dict;
}

int hash_func1(DictOpenAddr *dict, int d){
    return d % dict->B;
}

int hash_func2(DictOpenAddr *dict, int d){
    int x=1+(d%(dict->B-1));
    if(x%2==0){
        x++;
    }
    return x;
}

int hash_func(DictOpenAddr *dict, int d, int count){
    return ((hash_func1(dict,d)+count*hash_func2(dict,d))%dict->B);
}

void insert_hash(DictOpenAddr *dict, int d){
    if(search_hash(dict,d)!=-1)return;
    int count = 0;
    int b=hash_func(dict,d,count);
    int init_b =b;
    do{
        if(dict->H[b].state==EMPTY||dict->H[b].state==DELETED){
            dict->H[b].name=d;
            dict->H[b].state=OCCUPIED;
            return;
        }
        count++;
        b=hash_func(dict,d,count);
    }while(b!=init_b);
    printf("No Capacity!\n");
    return;
}

int search_hash(DictOpenAddr *dict, int d){
    int count = 0;
    int b=hash_func(dict,d,count);
    int init_b=b;
    do{
        if(dict->H[b].state==OCCUPIED){
            if(dict->H[b].name==d)return b;
        }
        else if(dict->H[b].state==EMPTY){
            return -1;
        }
        count++;
        b=hash_func(dict,d,count);
    }while(b!=init_b);
        return -1;
}


void delete_hash(DictOpenAddr *dict, int d){
    int b = search_hash(dict, d);
    if (b == -1) return;
    dict->H[b].state = DELETED;
    return;
}

void display(DictOpenAddr *dict){
    int b = 0;
    while (b < dict->B) {
        if (dict->H[b].state == EMPTY) {
            printf("e ");
        }
        else if (dict->H[b].state == DELETED) {
            printf("d ");
        }
        else {
            printf("%d ", dict->H[b].name);
        }
        b++;
    }
    printf("\n");
}

void delete_dict(DictOpenAddr *dict){
    free(dict);
    printf("Dictionary deleted!\n");
}