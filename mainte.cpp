#include<iostream>
#include<vector>
#include<algorithm>
#include<stdio.h>
#include<map>
#include<stack>
#include<windows.h>

using namespace std;
//void Sleep(DWORD dwMilliseconds);
DWORD WINAPI Fun1Proc(LPVOID lpParameter);//thread data
DWORD WINAPI Fun2Proc(LPVOID lpParameter);//thread data


//int index=0;
int tickets = 100;
HANDLE hMutex;
int main()
{

	//cout<<"I love you Yudan MA!"<<endl;
	//cout<<"Ha Ha, I love you, too! Kai ZHANG! MUM!"<<endl;
	HANDLE hThread1;
	HANDLE hThread2;
	//创建互斥对象
	hMutex=CreateMutex(NULL,FALSE,"tickets");//参数3为互斥对象名，可根据需要随意指定 
	if(hMutex)
	{
		if(ERROR_ALREADY_EXISTS==GetLastError())
		{
			cout<<"only one instance can run!\n";
			return -1;
		}
	 } 
	//创建线程
	hThread1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);
	CloseHandle(hThread1);//关闭新线程的句柄    当不再需要线程句柄时，应将其关闭，让这个线程内核对象的引用计数减1
	CloseHandle(hThread2);
	//ReleaseMutex(hMutex);
	/*while(index++<10)
		cout<<"main thread is running"<<endl;;
	Sleep(10);*/
	Sleep(100);
	return 0;
}

/*线程1的入口函数*/
DWORD WINAPI Fun1Proc(LPVOID lpParameter)//thread data
{
	/*while(index++<10)
		cout<<"thread1 is running"<<endl;*/
	char buf[100] = { 0 };
	while (TRUE)
	{
		WaitForSingleObject(hMutex,INFINITE);
		if (tickets > 0)
		{
			sprintf(buf,"thread1 sell ticket:%d \n", tickets);
			cout << buf;
			tickets--;
		}
		else
			break;
		ReleaseMutex(hMutex);

	}
	return 0;
}

/*线程2的入口函数*/
DWORD WINAPI Fun2Proc(LPVOID lpParameter)//thread data
{
	/*while(index++<10)
		cout<<"thread1 is running"<<endl;*/
	char buf[100] = { 0 };
	while (TRUE)
	{
		WaitForSingleObject(hMutex,INFINITE);
		if (tickets > 0)
		{
			sprintf(buf,"thread2 sell ticket:%d \n", tickets);
			cout << buf;
			tickets--;
		}
		else
			break;
			
		ReleaseMutex(hMutex);

	}
	return 0;
}
