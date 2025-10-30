#ifndef CONST_H
#define CONST_H

#include <QApplication>
#include <QDebug>
#include<mutex>
#include<queue>
#include<condition_variable>
#include<chrono>


extern "C"{
#include<libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libswresample/swresample.h>
#include <libavutil/samplefmt.h>
#include <libavutil/channel_layout.h>
}

#endif // CONST_H
