/*queue.c--接口函数*/
#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

//局部函数
static void CopyToNode(Item item,Node *pq);
static void CopyToItem(Node *pq,Item *pitem);

//初始化
void InitializeTheQueue(Queue *pq)
{
    pq->front = NULL;
    pq->items = 0;
}

//检查队列是否已满
bool QueueIsFull(const Queue *pq)
{
    return (pq->items == MAXQUEUE);
}

//检查队列是否为空
bool QueueIsEmpty(const Queue *pq)
{
    return (pq->items == 0);
}

//返回队列中的项目数
int QueueItemCount(const Queue *pq)
{
    return pq->items;
}

//向队列尾端添加项目
//新建一个node，把item复制进node，然后
//把node添加进queue里面
bool Enqueue(Item item, Queue *pq)
{
    Node *pnew;
    if(QueueIsFull(pq))
        return false;
    pnew = (Node *)malloc(sizeof(Node));
    if(pnew == NULL)
    {
        fprintf(stderr,"Unable to allocate memory!\n");
        exit(1);
    }
    CopyToNode(item,pnew);
    pnew->next = NULL;
    
    if(QueueIsEmpty(pq))
        pq->front = pnew;   //项目位于队列首端
    else
        pq->rear->next = pnew;  //链接到队列尾端
    pq->rear = pnew;    //记录队列尾端的位置
    pq->items++;

    return true;
}

//从队列首端删除项目
bool DeQueue(Item *pitem,Queue *pq)
{
    Node *pt;
    if(QueueIsEmpty(pq))
        return false;
    CopyToItem(pq->front,pitem);
    pt = pq->front;
    pq->front = pq->front->next;
    free(pt);
    //为了删除首节点，得把首节点复制出来
    //然后进行释放
    pq->items--;

    if(pq->items == 0)
        pq->rear = NULL;
    
    return true;
}

//清空队列
//可以使用删除项目来清空队列
void EmptyQueue(Queue *pq)
{
    Item dummy;
    while(!QueueIsEmpty(pq))
        DeQueue(&dummy,pq);
}

//把项目复制到节点中
static void CopyToNode(Item item,Node *pn)
{
    pn->item = item;
}

//把列表的第一个节点复制到项目*pitem中
static void CopyToItem(Node *pn,Item *pi)
{
    *pi = pn->item;
}