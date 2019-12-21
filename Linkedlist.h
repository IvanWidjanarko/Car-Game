#ifndef GBPS_LINKEDLIST_H
#define GBPS_LINKEDLIST_H

#include "Common.h"

struct _ListItem
{
    void* Data;
    struct _ListItem *Prev,*Next;
};

typedef struct _ListItem ListItem;

typedef struct
{
    ListItem* Head;
    ListItem* Tail;
    int NoItems;
} gbpsLinkedList;

int AddItem(gbpsLinkedList* List, void* Data);
void* PopItem(gbpsLinkedList* List);

#endif
