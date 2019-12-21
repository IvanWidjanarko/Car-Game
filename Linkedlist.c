#include "Linkedlist.h"

void EmptyList(gbpsLinkedList* List)
{
    ListItem* i;
    while(i=PopItem(List))
        FreeItem(i);
}

void FreeItem(ListItem* i)
{
    free(i);
    return;
}

void* PopItem(gbpsLinkedList* List)
{
    void* Data;
    if(List->NoItems==0)
    {
        return NULL;
    }

    else if(List->NoItems==1)
    {
        Data=List->Head->Data;
        FreeItem(List->Head);
        List->NoItems=0;
        return Data;
    }

    Data=List->Head->Data;
    List->Head=List->Head->Next;
    FreeItem(List->Head->Prev);
    List->NoItems--;

    return Data;
}

int AddItem(gbpsLinkedList* List, void* Data)
{
    ListItem* NewItem=malloc(sizeof(ListItem));
    NewItem->Data=Data;

    if(List->NoItems==0)
    {
        List->Head=NewItem;
        List->Tail=NewItem;
    }

    else
    {
        NewItem->Prev=List->Tail;
        List->Tail->Next=NewItem;
        List->Tail=NewItem;
    }

    return ++List->NoItems;
}
