#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

typedef struct DirectLinkedGraphType {
    int nodeCount;
    LinkedList **ppAdjEdge;
} DirectLinkedGraph;

DirectLinkedGraph *createDirectLinkedGraph(int nodeCount) {
    int i = 0;
    DirectLinkedGraph *pReturn = NULL;

    if (nodeCount > 0) {
        pReturn = (DirectLinkedGraph *) malloc(sizeof(DirectLinkedGraph));
        if (pReturn == NULL) return NULL;

        pReturn->nodeCount = nodeCount;
    } else {
        return NULL;
    }

    pReturn->ppAdjEdge = (LinkedList **) malloc(sizeof(LinkedList *) * nodeCount);
    if (pReturn->ppAdjEdge == NULL) {
        if (pReturn != NULL) free(pReturn);
        return NULL;
    }

    for (i = 0; i < nodeCount; i++) {
        pReturn->ppAdjEdge[i] = createLinkedList();
        if (pReturn->ppAdjEdge[i] == NULL) {
            if (pReturn->ppAdjEdge != NULL) free(pReturn->ppAdjEdge);
            if (pReturn != NULL) free(pReturn);
            return NULL;
        }
    }

    return pReturn;
}

int checkVertexValid(DirectLinkedGraph *pGraph, int node) {
    if (pGraph != NULL && node >= 0 && node < pGraph->nodeCount) return 1;
    else return 0;
}

int addEdgeDLG(DirectLinkedGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;

    if (pGraph != NULL && checkVertexValid(pGraph, fromNode)
        && checkVertexValid(pGraph, toNode)) {
        addLinkedListData(pGraph->ppAdjEdge[fromNode], 0, toNode);
    } else ret = -1;

    return ret;
}

int removeEdgeDLG(DirectLinkedGraph *pGraph, int fromNode, int toNode) {
    int ret = -1;
    LinkedList *pList = NULL;
    int i = 0, count = 0;

    if (pGraph != NULL
        && checkVertexValid(pGraph, fromNode)
        && checkVertexValid(pGraph, toNode)) {
        pList = pGraph->ppAdjEdge[fromNode];
        count = getLinkedListLength(pList);

        for (i = 0; i < count; i++) {
            if (getLinkedListData(pList, i) == toNode) {
                removeLinkedListData(pList, i);
                ret = 0;
                break;
            }
        }
    } else {
        ret = -1;
    }

    return ret;
}

int getEdgeDLG(DirectLinkedGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;
    LinkedList *pList = NULL;
    int i = 0, count = 0;

    if (pGraph != NULL && checkVertexValid(pGraph, fromNode) && checkVertexValid(pGraph, toNode)) {
        pList = pGraph->ppAdjEdge[fromNode];
        count = getLinkedListLength(pList);

        for (i = 0; i < count; i++) {
            if (getLinkedListData(pList, i) == toNode) {
                ret = 1;
                break;
            }
        }
    }

    return ret;
}

void displayGraphDLG(DirectLinkedGraph *pGraph) {
    int i = 0, j = 0, count = 0;

    if (pGraph != NULL) {
        count = pGraph->nodeCount;

        for (i = 0; i < count; i++) {
            if (getEdgeDLG(pGraph, i, j)) {
                printf("1 ");
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

void deleteGraphDLG(DirectLinkedGraph *pGraph) {
    int i = 0;

    if (pGraph != NULL) {
        for (i = 0; i < pGraph->nodeCount; i++) {
            deleteLinkedList(pGraph->ppAdjEdge[i]);
        }
        if (pGraph->ppAdjEdge != NULL) free(pGraph->ppAdjEdge);
        free(pGraph);
    }
}

int main(int argc, char *argv[]) {
    int nodeCount = 6;
    DirectLinkedGraph *pG2 = createDirectLinkedGraph(nodeCount);

    if (pG2 != NULL) {
        addEdgeDLG(pG2, 0, 1);
        addEdgeDLG(pG2, 1, 2);
        addEdgeDLG(pG2, 2, 0);
        addEdgeDLG(pG2, 2, 3);
        addEdgeDLG(pG2, 3, 2);
        addEdgeDLG(pG2, 3, 4);
        addEdgeDLG(pG2, 4, 5);
        addEdgeDLG(pG2, 5, 3);

        printf("G2 : 방향 그래프\n");
        displayGraphDLG(pG2);

        deleteGraphDLG(pG2);
    }

    return 0;
}