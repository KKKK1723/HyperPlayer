#include "avpacketqueue.h"



AVPacketQueue::AVPacketQueue(int MaxSize):queue_(MaxSize)
{

}


AVPacketQueue::~AVPacketQueue()
{
    Clear();
}

//0 成功，-1 超时，-2 队列已中止
int AVPacketQueue::Push(AVPacket *packet, int timeout)
{
    if(!packet)
    {
        return -1;//空包也算超时
    }

    AVPacket* newpacket=av_packet_alloc();
    if (!newpacket) {
        return -1;  // 内存分配失败
    }
    
    av_packet_move_ref(newpacket,packet);

    //放入队列
    int ret=queue_.Push(newpacket,timeout);
    if(ret!=0)
    {
        av_packet_free(&newpacket);
        return ret;
    }

    return 0;
}

int AVPacketQueue::Pop(AVPacket *&packet, int timeout)
{
    AVPacket* pkt = nullptr;
    int ret = queue_.Pop(pkt, timeout);

    if (ret == 0) {
        packet = pkt;
    }
    return ret;
}

int AVPacketQueue::Size()
{
    return queue_.Size();
}

void AVPacketQueue::Clear()
{
    // 释放所有缓存的 AVPacket
    AVPacket* packet = nullptr;
    while (queue_.Pop(packet, 0) == 0) {
        av_packet_free(&packet);
    }

    queue_.Clear();
}

void AVPacketQueue::Abort()
{
    queue_.Abort();
}
