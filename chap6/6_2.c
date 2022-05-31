#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedstack.h"

LinkedStack *createLinkedStack() {
    LinkedStack *pReturn = NULL;
    pReturn = (LinkedStack *) malloc(sizeof(LinkedStack));
    if (pReturn != NULL) {
        memset(pReturn, 0, sizeof(LinkedStack));
    } else {
        printf("오류, 메모리할당,createLinkedStack()\n");
        return NULL;
    }

    return pReturn;
}

int pushLS(LinkedStack *pStack, char data) {
    int ret = 0;
    LinkedStackNode *pNode = NULL;

    if (pStack != NULL) {
        pNode = (LinkedStackNode *) malloc(sizeof(LinkedStackNode));
        if (pNode != NULL) {
            pNode->data = data;
            pNode->pLink = pStack->pTop;
            pStack->pTop = pNode;

            pStack->currentCount++;
            ret = 1;
        } else {
            printf("오류, 메모리 할당,pushLS()\n");
        }
    }

    return ret;
}

int isLinkedStackEmpty(LinkedStack *pStack) {
    int ret = 0;

    if (pStack != NULL) {
        if (pStack->currentCount == 0) {
            ret = 1;

        }
    }
    return ret;
}

LinkedStackNode *popLS(LinkedStack *pStack) {
    LinkedStackNode *pReturn = NULL;
    if (pStack != NULL) {
        if (isLinkedStackEmpty(pStack) == 0) {
            pReturn = pStack->pTop;
            pStack->pTop = pReturn->pLink;
            pReturn->pLink = NULL;

            pStack->currentCount--;

        }
    }

    return pReturn;
}

LinkedStackNode *peekLS(LinkedStack *pStack) {
    LinkedStackNode *pReturn = NULL;
    if (pStack != NULL) {
        if (isLinkedStackEmpty(pStack) == 0) {
            pReturn = pStack->pTop;

        }
    }

    return pReturn;

}

void deleteLinkedStack(LinkedStack *pStack) {
    LinkedStackNode *pNode = NULL;
    LinkedStackNode *pDelNode = NULL;

    if (pStack != NULL) {
        pNode = pStack->pTop;
        while (pNode != NULL) {
            pDelNode = pNode;
            pNode = pNode->pLink;
            free(pDelNode);

        }
        free(pStack);
    }
}

void displayLinkedStack(LinkedStack *pStack) {
    LinkedStackNode *pNode = NULL;
    int i = 1;
    if (pStack != NULL) {
        printf("현재 노드 개수: %d\n", pStack->currentCount);
        pNode = pStack->pTop;
        while (pNode != NULL) {
            printf("[%d]-[%c]\n", pStack->currentCount - i, pNode->data);

            i++;
            pNode = pNode->pLink;
        }
    }
}


int checkBracketMatching(char *pSource) {
    int ret = 0, i = 0;
    char symbol = '\0', checkSymbol = '\0';
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode = NULL;

    if (pSource == NULL) {   //pSource 유효성 검사
        return -1;
    }

    pStack = createLinkedStack();
    if (pStack != NULL) {
        while (0 != pSource[i] && 0 == ret) {
            symbol = pSource[i];
            switch (symbol) {
                case '(':
                case '[':
                case '{':
                    pushLS(pStack, symbol);
                    break;
                case ')':
                case ']':
                case '}':
                    pNode = popLS(pStack);
                    if (pNode == NULL) {
                        ret = 1;  //닫는 괄호가 부족한 경우
                    } else {
                        checkSymbol = pNode->data;
                        if ((symbol == ')' && checkSymbol == '(')
                            || (symbol == ']' && checkSymbol == '[')
                            || (symbol == '}' && checkSymbol == '{')) {

                        } else {
                            ret = 2;    //괄호의 쌍이 맞지 않은 경우

                        }
                        free(pNode);
                    }
                    break;
            }
            i++;
        } //while문 종료

        if (0 == ret && isLinkedStackEmpty(pStack) == 0) {
            ret = 3;          //닫는 괄호가 남은 경우
        }
        deleteLinkedStack(pStack);
    }

    return ret;
}


int main(int argc, const char * argv[]) {
    int checkResult = 0, i = 0;
    char szExpressionStr[][50] = {
            "( A + B ) * C",
            "{ ( A + B ) * C } * D",
            "( A + B ) * C )",
            "( ( A + B ) * C",
            "{ ( A + B } ) * C * D"
    };

    for (i = 0; i < sizeof(szExpressionStr) / sizeof(szExpressionStr[0]); i++) {
        checkResult = checkBracketMatching(szExpressionStr[i]);
        if (checkResult == 0) {
            printf("SUCCESS, %s\n", szExpressionStr[i]);
        }
        else {
            printf("FAIL-[%d], %s\n", checkResult, szExpressionStr[i]);
        }
    }

    return 0;
}