#ifndef VIDEODECODER_H
#define VIDEODECODER_H

#include"const.h"

//视频解码器
class VideoDecoder
{
public:
    VideoDecoder();
    ~VideoDecoder();

    void Close();

    //初始化解码器
    bool Init(AVCodecParameters* codecParams);

    //发送packet给解码器
    int SendPacket(AVPacket* packet);

    //从解码器中接收解码后的帧
    int ReceiveFrame(AVFrame* frame);

    //帧转QImage
    QImage ConvertToQImage(AVFrame* frame);

    int Width()const;

    int Height()const;

private:
    AVCodecContext* codecCtx=nullptr;
    SwsContext* swsCtx=nullptr;

    // RGB帧和缓冲区（用于转换）
    AVFrame* rgbframe=nullptr;
    uint8_t* buffer=nullptr;
};

#endif // VIDEODECODER_H
