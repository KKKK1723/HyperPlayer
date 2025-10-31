#ifndef AVFRAMEQUEUE_H
#define AVFRAMEQUEUE_H

#include"const.h"
#include"safequeue.h"


//音视频帧队列
class AVFrameQueue
{
public:
    explicit AVFrameQueue(int maxSize = 10);
    ~AVFrameQueue();

    //0 成功，-1 超时，-2 队列已中止
    int Push(AVFrame* frame, int timeoutMs = -1);
    int Pop(AVFrame*& frame, int timeoutMs = -1);

    //0 成功，-1 队列为空
    int Front(AVFrame*& frame);//查看首帧

    int Size();
    void Clear();
    void Abort();
private:
    Queue<AVFrame*> queue_;
};

#endif // AVFRAMEQUEUE_H
