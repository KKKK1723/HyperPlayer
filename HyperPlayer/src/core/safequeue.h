#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include"const.h"

template<typename T>
class Queue{
public:
    explicit Queue(int maxSize=100):MaxSize(maxSize),abort_(false)
    {

    }
    ~Queue()
    {
        Abort();
    }

    //返回-1表示超时，-2表示线程停止,0表示成功
    int Push(const T& val,int timeout=-1)//timeout表示最多等待时间 -1表示永久等待
    {
        std::unique_lock<std::mutex> lock(mutex_);

        if(abort_)
        {
            return -2;//线程已经停止
        }

        //等待队列有空间
        if(timeout<0)
        {
            //一直等
            cond_push_.wait(lock,[this](){
                int qs=queue_.size();
                return (qs<MaxSize)||abort_;
            });
        }
        //在规定时间内等待
        else
        {
            //如果超时了就返回-1
            auto t = std::chrono::milliseconds(timeout);
            if (!cond_push_.wait_for(lock, t, [this] {
                    int qs=queue_.size();
                    return qs < MaxSize|| abort_;
                })){
                return -1;  // 超时
            }
        }


        //再次判断是否终止
        if(abort_)
        {
            return -2;//线程已经停止
        }

        queue_.push(val);

        cond_pop_.notify_one();

        return 0;
    }

    //0成功,-1超时,-2线程停止
    int Pop(T& val,int timeout=-1)
    {
        std::unique_lock<std::mutex>lock (mutex_);

        if(abort_)
        {
            return -2;
        }

        //一直等
        if(timeout<0)
        {
            cond_pop_.wait(lock,[this](){
                int qs=queue_.size();
                return (qs>0)||abort_;
            });
        }
        //在规定时间内等待
        else
        {
            //如果超时了就返回-1
            auto t = std::chrono::milliseconds(timeout);
            if (!cond_pop_.wait_for(lock, t, [this] {
                    int qs=queue_.size();
                    return qs>0 || abort_;
                })){
                return -1;  // 超时
            }
        }

        if(abort_)
        {
            return -2;
        }

        val = queue_.front();
        queue_.pop();

        cond_push_.notify_one();

        return 0;
    }

    //0成功, -1失败
    int Front(T& val)
    {
        std::unique_lock<std::mutex>lock (mutex_);

        int qs=queue_.size();

        if(qs==0)
        {
            return -1;
        }

        val=queue_.front();

        return 0;
    }

    int Size()
    {
        std::unique_lock<std::mutex>lock (mutex_);

        return queue_.size();
    }

    void Clear()
    {
        std::unique_lock<std::mutex>lock (mutex_);

        while(!queue_.empty())
        {
            queue_.pop();
        }

        cond_push_.notify_all();
    }

    void Abort()
    {
        std::unique_lock<std::mutex>lock (mutex_);

        abort_=true;

        cond_pop_.notify_all();
        cond_push_.notify_all();
    }

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_push_;
    std::condition_variable cond_pop_;
    int MaxSize;
    std::atomic<bool> abort_;
};




#endif // SAFEQUEUE_H
