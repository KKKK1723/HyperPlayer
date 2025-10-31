#include "avframequeue.h"


AVFrameQueue::AVFrameQueue(int maxSize) : queue_(maxSize)
{

}

AVFrameQueue::~AVFrameQueue()
{
    Clear();
}

int AVFrameQueue::Push(AVFrame* frame, int timeout)
{
    if (!frame) {
        return -1;
    }

    AVFrame* newFrame = av_frame_alloc();
    if (!newFrame) {
        return -1;
    }

    // 零拷贝
    av_frame_move_ref(newFrame, frame);

    int ret = queue_.Push(newFrame, timeout);
    if (ret != 0) {
        av_frame_free(&newFrame);
        return ret;
    }

    return 0;
}

int AVFrameQueue::Pop(AVFrame*& frame, int timeoutMs)
{
    AVFrame* frm = nullptr;
    int ret = queue_.Pop(frm, timeoutMs);

    if (ret == 0) {
        frame = frm;
    }

    return ret;
}

int AVFrameQueue::Front(AVFrame*& frame)
{
    AVFrame* frm = nullptr;
    int ret = queue_.Front(frm);

    if (ret == 0) {
        frame = frm;
    }

    return ret;
}

int AVFrameQueue::Size()
{
    return queue_.Size();
}

void AVFrameQueue::Clear()
{
    AVFrame* frame = nullptr;
    while (queue_.Pop(frame, 0) == 0) {
        av_frame_free(&frame);
    }

    queue_.Clear();
}

void AVFrameQueue::Abort()
{
    queue_.Abort();
}
