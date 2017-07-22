/*queue.h--队列接口*/
#pragma c9x on
#ifndef _MALL_H_
#define _MALL_H_
#include<stdbool.h>


typedef struct item{
    long arrival;
    int processtime;
}Item;

#define MAXQUEUE 10

typedef struct node{
    Item item;
    struct node * next;
} Node;

typedef struct queue{
    Node * front;    //指向队列首的指针
    Node * rear;     //指向队列尾的指针
    int items;      //统计队列中的项目数
} Queue;

/*操作：初始化队列                                                 */
/*操作前：pq指向一个队列                                           */
/*操作后：该队列被初始化为空队列                                    */
void InitializeTheQueue(Queue *pq);

/*操作：检查队列是否已满                                           */
/*操作前：pq指向一个已经被初始化的队列                              */
/*操作后：如果队列满，则返回false，否则返回true                     */
bool QueueIsFull(const Queue *pq);

/*操作：检查队列是否为空                                           */
/*操作前：pq指向已经被初始化的队列                                  */
/*操作后：如果队列空，则返回true，否则返回false                     */
bool QueueIsEmpty(const Queue *pq);

/*操作：确定队列中项目的个数                                       */
/*操作前：pq指向一个先前已经被初始化过的队列                        */
/*操作后：返回队列中项目的个数                                     */
int QueueItemCount(const Queue *pq);

/*操作：向队列尾端添加项目                                        */
/*操作前：pq指向已经被初始化的队列，item是要向尾部添加的项目         */
/*操作后：如果队列未满，则添加item到队列末尾，切返回true            */
bool Enqueue(Item item, Queue *pq);

/*操作：从队列首端删除项目                                        */
/*操作前：pq指向一个已经被初始化的队列                             */
/*操作后：若队列非空，队列首端的项目被复制到*pitem                  */
/*并且从队列中删除，函数返回ture；如果这个操作使队                  */
/*列为空，把队列重置为空队列。如果队列开始时为空，不改变队列，       */
/*函数返回false*/
bool DeQueue(Item *pitem,Queue *pq);

/*清空队列                                                      */
/*操作前：pq指向一个被初始化过的队列                              */
/*操作后：队列被置为空队列                                       */
void EmptyQueue(Queue *pq);

#endif