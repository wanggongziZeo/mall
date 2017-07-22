/*mall.c--使用Queue.c接口*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"queue.h"

#define MIN_PER_HR 60.0

bool newcustomer(double x); //有新顾客到来？
Item customertime(long when);   //设置顾客参数

int main()
{
    Queue line;
    Item temp;  //关于新顾客的数据
    int hours;   //模拟的小时数
    int perhour;    //每小时顾客的平均数
    long cycle,cyclelimit;  //循环计数器，计数器的上界
    long turnaways = 0;     //因队列已满而被拒绝的顾客数
    long customers = 0;     //被加入队列的顾客数
    long served = 0;        //在模拟期间得到服务的顾客数
    long sum_line = 0;      //累计的队列长度
    long wait_time = 0;     //从当前到被咨询人空闲所需的时间
                            //完成当前顾客咨询还需要的时间
    long min_per_cust;      //顾客到来的平均间隔时间
    long line_wait = 0;     //到目前为止队列累计等待时间

    InitializeTheQueue(&line);  //初始化队列
    srand(time(0));         //随机初始化rand()函数
    puts("Case Study: Sigmund Lander's Advice Booth");
    puts("Enter the number of simulation hours:");
    scanf("%d",&hours);
    cyclelimit = MIN_PER_HR*hours;  //计数器上界--分钟
    puts("Enter the average number of customers per hour:");
    scanf("%d",&perhour);
    min_per_cust = MIN_PER_HR/perhour;

    //以1分钟递增检查是否有顾客到来
    for(cycle = 0;cycle < cyclelimit;cycle++)
    {
        if(newcustomer(min_per_cust))   //顾客到来平均时间间隔进行检查
        {
            if(QueueIsFull(&line))
                turnaways++;
            else
            {
                customers++;
                temp = customertime(cycle);
                Enqueue(temp,&line);
            }
        }

        //前一位顾客咨询已经结束，并且队列非空（不是队列已满）
        //首先从队列删除当前顾客信息，
        if(wait_time <= 0 && !QueueIsEmpty(&line))
        {
            DeQueue(&temp,&line);
            wait_time = temp.processtime;
            line_wait += cycle - temp.arrival;
            served++;
        }
        
        if(wait_time > 0)
            wait_time--;
        sum_line += QueueItemCount(&line);
    }

    //输出队列信息
    if(customers > 0)
    {
        printf(" Customers accepted: %ld\n",customers);
        printf("   Customers served: %ld\n",served);
        printf("Customers turnaways: %ld\n",turnaways);
        printf(" Average queue size: %.2f\n",(double)sum_line/cyclelimit);
        printf("  Average wait time: %.2f\n",(double)line_wait/served);
    }

    else
        puts("No customers!");
    EmptyQueue(&line);
    puts(":::::::::::::Bye::::::::::::::");

    system("PAUSE");
    return 0;
}


//有新顾客到来？,x是顾客到来的平均时间间隔，以秒计
//如果这一分钟有顾客到来，则返回true
bool newcustomer(double x)  
{
    if(rand() * x /RAND_MAX < 1)    //rand()产生0~RAND_MAX之间的随机数
        return true;
    else 
        return false;
}


//when是顾客到来时间
//函数返回一个Item结构，该结构的顾客到来时间设置为when
//需要咨询的时间设置为一个范围在1-3之间的随机数
Item customertime(long when)   //设置顾客参数
{
    Item cust;

    cust.processtime = rand() % 3 + 1;
    cust.arrival = when;

    return cust;
}