#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArrayListNodeType {
	int data;
} ArrayListNode;

typedef struct ArrayListType {
	int maxCount;   // 배열의 크기
	int currentCount;   //현재 자료의 개수
	ArrayListNode* pData;  // 자료저장을 위한 1차원 배열
} ArrayList;

ArrayList* createList(int count)
{
	ArrayList* pReturn = (ArrayList*)malloc(sizeof(ArrayList));
	pReturn->maxCount = count;
	pReturn->currentCount = 0;
	pReturn->pData = (ArrayListNode*)malloc(sizeof(ArrayListNode) * count);
	memset(pReturn->pData, 0, sizeof(ArrayListNode) * count);

	return pReturn;
}

int addListData(ArrayList* pList, int position, int data)
{
	int i = 0;
	for (i = pList->currentCount - 1; i >= position; i--) {
		pList->pData[i + 1] = pList->pData[i];
	}
	pList->pData[position].data = data; //실제 자료 추가
	pList->currentCount++;          // 현재 저장된 자료 개수를 1 증가
	return 0;
}


int removeListData(ArrayList* pList, int position)
{
	int i = 0;
	if (pList == NULL)
	{
		return 0;
	}
	else
	{
		if (position > pList->maxCount)
			return 0;
		else
		{
			for (i = position; i < pList->currentCount - 1; i++)
			{
				pList->pData[i] = pList->pData[i + 1];
				pList->currentCount--;
			}
		}
	}

	return 0;
}

int getListData(ArrayList* pList, int position)
{
	if (pList == NULL) 
	{
		return 0;
	}
	else 
	{
		if(position> pList->maxCount)
			return 0;
		else
			return pList->pData[position].data;
	}
}

void deleteList(ArrayList* pList)
{
	free(pList->pData);
	free(pList);
}

int main(int argc, char* argv[])
{
	ArrayList* pList = NULL;
	int value = 0;
	int value2 = 0;
	pList = createList(5);//크기가 5인 리스트 생성
	addListData(pList, 0, 10);//자료 10 위치0에 저장
	addListData(pList, 1, 20); //자료 20 위치 1에 저장
	addListData(pList, 2, 30);//자료 30 위치 0에 저장, 기존에 있던 자료들 오른쪽으로 한 칸씩 이동
	addListData(pList, 3, 40);
	addListData(pList, 4, 50);
	// 10 20 30 40 50
 	// 0  1  2   3  4
	// 1  2  3   4  5  
	value = getListData(pList, 2); //포인터 주소로 설정
	printf("위치: %d, 값: %d\n", 3, value); 

	value2= removeListData(pList, 4);//배열 리스트 첫 번째 위치의 자료제거, 오른쪽 자료들 왼쪽으로 한 칸씩 이동
	printf("위치: %d, 값: %d\n", 1, value2);
	deleteList(pList);//배열 리스트 삭제
	
	return 0;
}
int getListLength(ArrayList* pList) {
	return pList->currentCount;
}
/*int main(int argc, char* argv[]) {
	ArrayList* pList = NULL;
	int value = 0;

	pList = createList(5);
	addListData(pList, 0, 10);
	addListData(pList, 1, 20);
	addListData(pList, 1, 30);
	value = getListLength(pList);
	printf("자료의 개수 : %d\n", value);
	return 0;
}*/
