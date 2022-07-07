#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SimpleIndexType{
    int position;
    int key;
}SimpleIndex;

SimpleIndex* createIndexTable(int values[], int size, int indexSize)
{
    SimpleIndex * pReturn = NULL;
    int i=0,ratio=0;

    ratio=size/indexSize;
    if(size% indexSize>0){
        ratio=ratio+1;
    }

    pReturn = (SimpleIndex*) malloc(sizeof(SimpleIndex)* indexSize);

    for(i=0;i<indexSize;i++){
        pReturn[i].position=i*ratio;
        pReturn[i].key=values[i*ratio];

    }

    return pReturn;
}

int sequentialIndexSearch(int values[],int size, SimpleIndex indexTable[],int indexSize,int key)
{
    int ret =1;
    int i =0;
    int start =0,end =0;

    if(key>=values[0]&&key<=values[size-1]){
        for(i=0;i<indexSize;i++){
            if(indexTable[i].key>key) {
                break;
            }
        }
        if(i<indexSize){
            start = indexTable[i-1].position;
            end = indexTable[i].position-1;

        }
        else{
            start = indexTable[i-1].position;
            end =size -1;

        }
        ret = sequentialIndexSearch(values, start ,end ,key);
    }

    return ret;
}

int sequentialRangeSearch(int values[],int start, int end , int key){

    int ret =-1;
    int i=0;
    for(i=start;i<=end&&values[i]<key;i++){

    }
    if(i<=end&&values[i]==key){
        ret = i;

    }

    return ret;
}

//색인 테이블 내용을 출력
void showIndexTable(SimpleIndex* pIndexTable, int indexSize){
    int i =0;

    printf("인덱스 테이블\n");
    printf("위치,키\n");
    printf("--------------\n");
    for(i=0;i<indexSize;i++){
        printf("%d,%d\n",pIndexTable[i].position,pIndexTable[i].key);
    }

}

void showArray(int values[],int size){
    int i =0;

    printf("위치, 키 값\n");
    printf("-----------\n");
    for(i=0;i<size;i++){
        printf("%d,%d\n",i,values[i]);
    }
}

int main(int argc,char *argv[]){
    SimpleIndex * pIndexTable =NULL;

    int indexSize = 3;
    int index = 0;
    int key =0;
    int ascSortedValues[] = {10,20,50,60,70,80};
    int arraySize = 6;

    showArray(ascSortedValues,arraySize);
    pIndexTable = createIndexTable(ascSortedValues,arraySize,indexSize);
    if(pIndexTable!=NULL){
        showIndexTable(pIndexTable,indexSize);

        key =60;
        index= sequentialIndexSearch(ascSortedValues,arraySize,
                                     pIndexTable,indexSize,key);

        if(index>=0){
            printf("키-%d,위치-%d\n",key,index);
        }
        else{
            printf("키-%d,검색 실패\n",key);
        }


        key =65;
        index= sequentialIndexSearch(ascSortedValues,arraySize,
                                     pIndexTable,indexSize,key);

        if(index>=0){
            printf("키-%d,위치-%d\n",key,index);
        }
        else{
            printf("키-%d,검색 실패\n",key);
        }

        free(pIndexTable);

    }

    return 0;
}