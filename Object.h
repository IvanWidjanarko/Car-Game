#ifndef GBPS_TREE_H
#define GBPS_TREE_H

#include "Common.h"

typedef struct
{
    float x,y;
    int type;

} GBPS_Tree;

void RenderTree(GBPS_Tree Tree);

#endif
