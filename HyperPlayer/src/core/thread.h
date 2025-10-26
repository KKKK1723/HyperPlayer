#ifndef THREAD_H
#define THREAD_H

#include"const.h"
#include<atomic>
#include<QThread>

//所有线程的基类
class Thread:public QThread{
    Q_OBJECT
public:
    explicit Thread(QObject *parent = nullptr);
    ~Thread();

    int Start();//启动线程
    int Stop();//停止线程

    bool IsStop() const;

    virtual void run()=0;


protected:
    std::atomic<bool> abort_;//是否停止线程

};

#endif //THREAD_H
