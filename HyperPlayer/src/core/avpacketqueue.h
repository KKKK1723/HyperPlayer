#ifndef AVPACKETQUEUE_H
#define AVPACKETQUEUE_H

#include"const.h"
#include"safequeue.h"

class AVPacketQueue
{
public:
    explicit AVPacketQueue(int MaxSize=100);
    ~AVPacketQueue();

    //0 成功，-1 超时，-2 队列已中止
    int Push(AVPacket* packet,int timeout=-1);
    int Pop(AVPacket* &packet,int timeout=-1);

    int Size();

    void Clear();

    void Abort();
private:
    Queue<AVPacket*>queue_;
};

#endif // AVPACKETQUEUE_H
