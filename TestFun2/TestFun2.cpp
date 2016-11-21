// TestFun2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

const int maxLen = 1024;
const int chLen = 50;

int string2Array(const char * src, char des[][chLen], const char separator)
{
	char tmpString[maxLen];
	memset(tmpString,0,sizeof(tmpString));
	strcpy_s(tmpString,src);	//strcpy不安全，strcpy_s会做安全越界检查
	int srcLen = strlen(src);	//不包含结束符
	cout<<"src length: "<<srcLen<<endl;
	//判断最后一个字符是不是分隔符，如果不是就加一个，为了后面运算方便提取特征
	if (tmpString[srcLen-1] != separator)
	{
		//strcat_s(tmpString, separator);
		tmpString[srcLen] = separator;
		tmpString[srcLen+1] = '\0';
	}
	
	char * ptr = NULL;
	char * beginPos = NULL;
	char * endPos = NULL;
	char extractString[chLen];

	beginPos = tmpString;	//起始地址
	endPos = strchr(tmpString, separator);	//第一个逗号位置
	int desIndex = 0;
	int arrayLen = 0;
	do{
		arrayLen = endPos - beginPos;	//逗号之间有效字符串的长度
		memset(extractString,0,sizeof(extractString));	//先清空要保存截取字符串的数组
		strncpy_s(extractString, tmpString, arrayLen);	//将tmpString前面arrayLen个字符串copy到extractString中，这就是要提取的字符串
		strcpy_s(des[desIndex] , extractString);	//截取的字符串保存到二维字符数组里面
		desIndex++;	//索引值递增
		ptr = endPos + 1;	//指针指向当前逗号的下一个位置，这样ptr为提取字符串之后剩下字符串的首地址
		strcpy_s(tmpString, ptr);	//截取后的字符串copy
		beginPos = tmpString;	//beginPos再次指向要提取字符串的首地址
		endPos = strchr(tmpString,separator);	//endPos再次指向字符串的第一个逗号位置		
	}while (endPos != NULL);
	
	ptr = NULL;
	beginPos = NULL;
	return desIndex;
}

signed int stringCompare(char * str1, char * str2)
{
	int result=0;
	int len = strlen(str1)>=strlen(str2)?strlen(str2):strlen(str1);
	for(int i=0; i<len; i++)
	{
		if (str1[i] == str2[i])
		{
			//到最后一位，判断谁是子串或是否相等
			if(len-1 == i && strlen(str1)>strlen(str2))
			{
				cout<<str2<<" is a sub string of "<<str1<<endl;
				result = -1;
			}
			else if(len-1 == i && strlen(str1)<strlen(str2))
			{
				cout<<str1<<" is a sub string of "<<str2<<endl;
				result = 1;
			}
			else if(len-1 == i && strlen(str1)==strlen(str2))
			{
				cout<<str1<<" is equal to "<<str2<<endl;
				result = 0;
			}
			result = 0;
			continue;
		}
		else if(str1[i] > str2[i])
		{
			cout<<str1<<" > "<<str2<<endl;
			result = 1;
			break;
		}
		else if(str1[i] < str2[i])
		{
			cout<<str1<<" < "<<str2<<endl;
			result = -1;
			break;
		}
	}

	return result;
}

void stringSort(char str[][chLen])
{

}

void intSort(int data[], int len)
{
	int i, j, k;
	for(i=0; i<len; i++)
	{
		for (j=i; j<len; j++)
			if(data[j]>data[i])
			{
				k = data[i];
				data[i] = data[j];
				data[j] = k;
			}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	char input[maxLen];
	memset(input,0,sizeof(input));

	cout<<"Please input data with ',' separator:"<<endl;
	cin>>input;
	char afterConvert[maxLen][chLen];
	for(int i=0; i<maxLen; i++)
		memset(afterConvert[i],0,sizeof(afterConvert[i]));
	int arrayLen = string2Array(input, afterConvert, ',');
	int data[maxLen];
	for(int i = 0; i < arrayLen; i++)
	{
		cout<<i<<":"<<afterConvert[i]<<endl;
		data[i] = atoi(afterConvert[i]);
	}

	intSort(data,arrayLen);
	for(int i = 0; i < arrayLen; i++)
		cout<<data[i]<<endl;
	
	//找出所有连续数的起止点和数量
	int start[maxLen] = {0}, end[maxLen] = {0}, count = 1;
	bool finished = false;
	int len = arrayLen;
	int startIndex, endIndex;
	do
	{
		if(1 == count)//如果是第一次循环则从0开始
		{
			startIndex = end[count-1];//or 0
		}
		else//如果不是第一次循环，则起始点是上一次查找的end点
		{
			startIndex = end[count-2];
		}

		int i = 0;
		for(i = startIndex+1; i < arrayLen; i++)
		{
			if((data[i] == data[i-1]-1) && (data[i]-1 == data[i+1]))//两个连续的不算，因为最大最小就是这两个
			{
				start[count-1] = i-1;
				break;
			}
		}

		//如果第一个连续数的起点是第一个点如何处理？
		//不管是否存在连续总是这样设置，不需要判断start[count-1]的结果，因为如果是第一个点是没法区分开的
		//只要最后判断 end[count-1] 是否为0即可知道是否存在连续数
		endIndex = start[count-1];//从尾部截止查找到当前的start点
		for(i = arrayLen-1; i > endIndex; i--)
		{
			//0     1   2  3  4  5  6  7 8 9 10  11  12
			//2364,234,17,16,15,14,13,10,7,6,5,  2,  1
			//1,2,5,6,7,10,13,14,15,16,17,234,2364
			//如果当前值=起始点的值-连续值的长度（当前值的索引-起始点的索引值），则说明是连续的且找到了end点
			if(data[i] == data[endIndex]-(i-endIndex))
			{
				end[count-1] = i;
				break;
			}
		}	


		if(0 == end[count-1])//说明没有连续的数
		{
			finished = true;//终止do...while循环
			count--;//因为count初始值为1，如果没有的话要回退一个计数
		}
		else//否则继续查找
		{
			count++;
			//continue;
		}
		
	}while(!finished);

	if(0 == count)
	{
		cout<<"Can't find continuous number within the data."<<endl;
	}
	else
	{
		start[count] = arrayLen-1;//多一个start点为最后一个值的索引，为了后面处理方便
		for(int i=0;i<=count;i++) //=count是为了打印最后的点
		{	
			int j=0;
			if(0 == i)
			{
				for(j=0;j<=start[i];j++)//第一个点到第一个start点
					cout<<data[j]<<" ";
			}
			else
			{
				//前一个end点到后一个start点
				//如果后一个start点的确存在当然没有问题，如果后一个start点是结尾就刚好打印到结尾，也能够打印所有数
				for(int j=end[i-1];j<=start[i];j++)
					cout<<data[j]<<" ";
			}
		}
		cout<<endl;
	}
	

	/*
	char str1[maxLen];
	char str2[maxLen];
	cout<<"input string1 :";
	cin>>str1;
	cout<<"input string2 :";
	cin>>str2;
	int result = stringCompare(str1,str2);
	*/

	return 0;
}
