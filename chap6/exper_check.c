#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "experlinkedstack.h"


int inStackPrecedence(Precedence oper);

int outStackPrecedence(Precedence oper);

void printToken(ExprToken element);

LinkedStack *createLinkedStack() {
    LinkedStack *pReturn = NULL;
    pReturn = (LinkedStack *) malloc(sizeof(LinkedStack));
    memset(pReturn, 0, sizeof(LinkedStack));
    return pReturn;
}

int pushLS(LinkedStack *pStack, ExprToken data) {
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
            printf("오류, 메모리할당,pushLS()\n");
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
        printf("현재 노드 개수: %d\n",
               pStack->currentCount);
        pNode = pStack->pTop;
        while (pNode != NULL) {
            printf("[%d]-[%f]\n",
                   pStack->currentCount - i,
                   pNode->data.value);
            i++;
            pNode = pNode->pLink;
        }
    }
}


//중위 표기수식을 후위 표기수식으로 변환하는 함수
void convertInfixToPostfix(ExprToken *pExprTokens, int tokenCount) {
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode = NULL;

    Precedence tokenType, inStackTokenType;
    int i = 0;
    pStack = createLinkedStack();
    if (pStack != NULL) {
        for (i = 0; i < tokenCount; i++) {
            tokenType = pExprTokens[i].type;
            switch (tokenType) {
                case operand:
                    printf("%4.1f\t", pExprTokens[i].value);
                    break;
                case rparen:
                    pNode = popLS(pStack);
                    while (pNode != NULL && pNode->data.type != lparen) {
                        printToken(pNode->data);
                        free(pNode);

                        pNode = popLS(pStack);
                    }
                    if (pNode != NULL)free(pNode);
                    break;
                default:

                    while (isLinkedStackEmpty(pStack) == 0) {
                        inStackTokenType = peekLS(pStack)->data.type;
                        if (outStackPrecedence(tokenType) <= inStackPrecedence(inStackTokenType)) {
                            pNode = popLS(pStack);
                            if (pNode != NULL) {
                                printToken(pNode->data);
                                free(pNode);

                            }
                        } else {
                            break;
                        }
                    }
                    pushLS(pStack, pExprTokens[i]);
                    break;
            }
        }
        while (isLinkedStackEmpty(pStack) == 0) {
            pNode = popLS(pStack);
            if (pNode != NULL) {
                printToken(pNode->data);
                free(pNode);
            }
        }
        deleteLinkedStack(pStack);

    }
}

//스택내부의 우선순위를 반환하는 함수
int inStackPrecedence(Precedence oper) {
    switch (oper) {
        case lparen:  // '('
            return 0;
        case rparen:  // ')'
            return 4;
        case multiply:  // '*','/'
        case divide:
            return 2;
        case plus:    // '+','-'
        case minus:
            return 1;
    }
    return -1;
}

//스택 외부의 우선순위를 반환하는 함수
int outStackPrecedence(Precedence oper) {
    switch (oper) {
        case lparen:     // '('    0순위 ->5순위
            return 5;
        case rparen:    //  ')'
            return 4;
        case multiply:    // '*','/'
        case divide:
            return 2;
        case plus:       // '+','-'
        case minus:
            return 1;
    }
    return -1;
}

//토큰의 내용을 출력하는 함수
void printToken(ExprToken element) {
    switch (element.type) {
        case lparen:
            printf("(\t");
            break;
        case rparen:
            printf(")\t");
            break;
        case plus:
            printf("+\t");
            break;
        case minus:
            printf("-\t");
            break;
        case multiply:
            printf("*\t");
            break;
        case divide:
            printf("/\t");
            break;
        case operand:
            printf("\t", element.value);
            break;
    }
}


//괄호 검사 코드
int checkBracketMatching(ExprToken *pExprTokens, int tokenCount) {
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode = NULL;

    Precedence tokenType;
    int i = 0;
    int close = 0, open = 0;
    int ret;
    pStack = createLinkedStack();
    if (pStack != NULL) {
        for (i = 0; i < tokenCount; i++) {
            tokenType = pExprTokens[i].type;
            switch (tokenType) {
                case rparen: //  ')'
                    close++;
                    if (open == 0) {
                        ret = 2;
                        return ret;
                    }
                    break;
                case lparen: //  '('
                    open++;
                    break;
            }
        }
        deleteLinkedStack(pStack);
    }
    if (open == close) {
        ret = 0;   //쌍을 이룸
    } else {
        ret = 1;   //쌍을 이루지 못함
    }
    return ret;
}

int main(int argc, const char *argv[]) {

    int result;
    // 2 - (3 + 4 ) * 5 )
    ExprToken *pExprTokens = (ExprToken *) malloc(sizeof(ExprToken) * 10);
    pExprTokens[0].type = operand;
    pExprTokens[0].value = 2;
    pExprTokens[1].type = minus;
    pExprTokens[1].value = 0;
    pExprTokens[2].type = lparen;
    pExprTokens[2].value = 0;
    pExprTokens[3].type = operand;
    pExprTokens[3].value = 3;
    pExprTokens[4].type = plus;
    pExprTokens[4].value = 0;
    pExprTokens[5].type = operand;
    pExprTokens[5].value = 4;
    pExprTokens[6].type = rparen;
    pExprTokens[6].value = 0;
    pExprTokens[7].type = multiply;
    pExprTokens[7].value = 0;
    pExprTokens[8].type = operand;
    pExprTokens[8].value = 5;
    //pExprTokens[9].type = rparen;   // 닫는 괄호 추가
    //pExprTokens[9].value = 0;

    printf("Infix Expression: 2.0 - (3.0 + 4.0) * 5.0 )\n");

    result = checkBracketMatching(pExprTokens, 10);
    if (result == 0) {
        printf("괄호가 쌍을 이룹니다.\n");
    } else if (result == 1) {
        printf("괄호가 쌍을 이루지 못합니다.\n");
        return 0;
    } else if (result == 2) {
        printf("닫는 괄호가 먼저 나왔습니다.\n");
        return 0;
    }

    printf("Postfix Expression: \n");
    convertInfixToPostfix(pExprTokens, 10);  //후위 표기법으로 변환된 수식 출력
    free(pExprTokens);  //메모리를 동적으로 할당하기때문에 해제

    return 0;
}

