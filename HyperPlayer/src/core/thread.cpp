#include"thread.h"

Thread::Thread(QObject *parent):abort_(false),QThread(parent)
{

}

Thread::~Thread()
{
    Stop();
}

//成功0,失败-1
int Thread::Start()
{
    //正在运行
    if(isRunning())
    {
        return -1;
    }

    abort_=false;

    //启动线程
    start();

    return 0;
}

int Thread::Stop()
{
    abort_=true;


    //请求中断
    requestInterruption();//需要在run方法中主动检测

    //分级超时
    if(wait(1000))
    {
        return 0;
    }
    qDebug()<<"thread timeout 1 秒";

    if(wait(2000))
    {
        return 0;
    }
    qDebug()<<"thread timeout 3 秒";

    if(wait(2000))
    {
        return 0;
    }
    qDebug()<<"thread timeout 5 秒";
    //强制杀死
    terminate();
    wait();

    return 0;
}

bool Thread::IsStop() const
{
    return abort_ || isInterruptionRequested();
}
