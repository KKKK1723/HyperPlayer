#include "videodecoder.h"

VideoDecoder::VideoDecoder() {

}

VideoDecoder::~VideoDecoder(){
    Close();
}

void VideoDecoder::Close(){
    if(rgbframe)
    {
        av_frame_free(&rgbframe);
    }

    if(buffer)
    {
        av_free(buffer);
        buffer=nullptr;
    }

    if(swsCtx)
    {
        sws_freeContext(swsCtx);
        swsCtx=nullptr;
    }

    if(codecCtx)
    {
        avcodec_free_context(&codecCtx);
    }
}


/*
1. 根据编码ID查找解码器
2. 分配解码器上下文
3. 复制编码参数到上下文
4. 打开解码器
*/
bool VideoDecoder::Init(AVCodecParameters* codecParams)
{
    const AVCodec* codec=avcodec_find_decoder(codecParams->codec_id);
    if(!codec)
    {
        qDebug()<<"avcodec_find_decoder is error";
        return false;
    }

    codecCtx=avcodec_alloc_context3(codec);
    if(!codecCtx)
    {
        qDebug()<<"avcodec_alloc_context3 is error";
        return false;
    }

    int result=avcodec_parameters_to_context(codecCtx,codecParams);
    if(result<0)
    {
        qDebug()<<"avcodec_parameters_to_context is error";
        Close();
        return false;
    }

    result=avcodec_open2(codecCtx,codec,nullptr);
    if(result<0)
    {
        qDebug()<<"avcodec_open2 is error";
        Close();
        return false;
    }

    return true;
}


int VideoDecoder::SendPacket(AVPacket* packet){
    if(!codecCtx){
        return -1;
    }

    int ret=avcodec_send_packet(codecCtx,packet);
    if(ret<0)
    {
        char errbuf[128];
        av_strerror(ret,errbuf,sizeof(errbuf));
        qDebug()<<"发送数据包packet失败:"<<errbuf;
    }
    return ret;//0 success
}



int VideoDecoder::ReceiveFrame(AVFrame* frame){
    if(!codecCtx){
        return -1;
    }

    int ret=avcodec_receive_frame(codecCtx,frame);
    if (ret < 0) {
        char errbuf[128];
        av_strerror(ret, errbuf, sizeof(errbuf));
        qDebug() << "接收解码帧失败:" << errbuf;
    }
    return ret;
}


QImage VideoDecoder::ConvertToQImage(AVFrame* frame){
    if(!frame)
    {
        return QImage();
    }

    int width=frame->width;
    int height=frame->height;


    if(!swsCtx)
    {
        swsCtx=sws_getContext(width,height,(AVPixelFormat)frame->format,
                            width,height,AV_PIX_FMT_RGB24,
                            SWS_BILINEAR,
                                nullptr,nullptr,nullptr);
        if(!swsCtx)
        {
            qDebug() << "创建SwsContext失败";
            return QImage();
        }
    }

    //  AVFrame* rgbframe=nullptr;
    //  uint8_t* buffer=nullptr;

    if(!rgbframe)
    {
        rgbframe=av_frame_alloc();

        int numBytes=av_image_get_buffer_size(AV_PIX_FMT_RGB24,width,height,1);

        buffer=(uint8_t*)av_malloc(numBytes);

        //将分配的RGB像素缓冲区（buffer）与rgbframe绑定,未写入缓冲区
        av_image_fill_arrays(rgbframe->data, rgbframe->linesize,
                             buffer, AV_PIX_FMT_RGB24,
                             width, height, 1);
    }

    //YUV--RGB
    sws_scale(swsCtx,frame->data,frame->linesize,0,height,rgbframe->data,rgbframe->linesize);

    //RGB--QImage
    QImage img(buffer,width,height,rgbframe->linesize[0],QImage::Format_RGB888);

    return img.copy();
}



int VideoDecoder::Width()const{
    return codecCtx?codecCtx->width:0;
}

int VideoDecoder::Height()const{
    return codecCtx?codecCtx->height:0;
}



















