// JosephusCircle.cpp : Defines the entry point for the console application.
//

//*******************************************************************************
//*题目：
//*已知n个人（以编号1，2，3，...，n分别表示）围坐在一张圆桌周围，从编号为k的人开始报数，数到m的那个人出列，一次重复下去，直到圆桌的人全部出列。
//*
//*解析：
//*本题就是约瑟夫环问题的实际场景，要通过输入n/m/k三个正整数，求出列的序列。这个问题采用的是典型的循环链表的数据结构，就是将一个链表的尾元素指针指向队首元素：
//*p->link = head;
//*
//*解决问题的核心步骤如下：
//* 1. 建立一个具有n个链节点、无头节点的循环链表;
//* 2. 确定第一个报数人的位置;
//* 3. 不断地从链表中删除链节点，直到链表为空。
//*******************************************************************************


#include "stdafx.h"
#include <iostream>
//#include<stdio.h>
//#include<stdlib.h>


using namespace std;


typedef struct Node
{
	int data;
	struct Node *link;
}LNode,*LinkList;	//LNode为struct Node的别名，LinkList是指向struct Node指针类型的别名

//n为总人数，k为第一个开始报数的人，m为出列者喊到的数
void JosephusCircle(int n, int m, int k)
{
	//p为头节点，r为辅助节点，指向p的前驱节点，curr为当前节点
	LinkList p,r,curr;//或者LNode *p,*r,*curr;

	//建立循环链表
	p = (LinkList)malloc(sizeof(Node));
	p->data = 1;
	p->link = p;//头节点的link指向自身
	curr = p;//curr先指向头节点
	for(int i = 2; i <= n; i++)
	{
		LinkList t = (LinkList)malloc(sizeof(Node));
		t->data = i;
		t->link = curr->link;//创建的新节点的link指向上当前节点的link。由于curr->link从头节点而来而且指向头节点，因此新建节点的link总是指向头节点，这样做到首尾相连
		curr->link = t;//当前节点的link指向新建节点，这样当前节点和新建节点建立了顺序链接，就将新建的节点加到链表中来了
		curr = t;//当前节点赋值为新建节点，这样curr就始终是最末尾或者最新的那个节点
	}

	
	//把当前指针移动到第一个报数的人，相当于对链表进行重新标号并找出头节点
	r = curr;//指向最后一个节点
	while (k--)
	{
		r = p;//r指向p，而下面p将移位
		p = p->link;//p指向下一个节点，即p向下移一位
	}
	while(n--)
	{
		for(int s = m-1; s--; r=p,p=p->link);//每间隔m个节点打印对应节点的结果并移除该节点
		r->link = p->link;//保存下一个节点的link
		cout<<p->data<<"->";
		//printf("d%->",p->data);
		free(p);//从链表中释放p节点
		p = r->link;//当前节点就到了下一个节点了
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout<<"Input the length of Johephus circle:";
	int n = 0;
	cin>>n;
	cout<<"Input the start point of Johephus circle:";
	int k = 0;
	cin>>k;
	cout<<"Input the stop point of Johephus circle:";
	int m = 0;
	cin>>m;

	JosephusCircle(n,m,k);

	return 0;
}