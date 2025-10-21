#include "demuxer.h"

Demuxer::Demuxer() {

}


Demuxer::~Demuxer(){
    Close();
}


bool Demuxer::Open(const std::string& filepath){

    formatCtx_=nullptr;

    int result=avformat_open_input(&formatCtx_,filepath.c_str(),nullptr,nullptr);

    if(result<0)
    {
        qDebug()<<"avformat_open_input is error";
        avformat_close_input(&formatCtx_);
        return false;
    }


    result=avformat_find_stream_info(formatCtx_,nullptr);
    if(result<0)
    {
        qDebug()<<"avformat_find_stream_info is error";
        avformat_close_input(&formatCtx_);
        return false;
    }

    for(unsigned int i=0;i<formatCtx_->nb_streams;i++)
    {
        //视频流
        if(formatCtx_->streams[i]->codecpar->codec_type==AVMEDIA_TYPE_VIDEO)
        {
            videoIndex_=i;
        }
        else if(formatCtx_->streams[i]->codecpar->codec_type==AVMEDIA_TYPE_AUDIO)//音频流
        {
            audioIndex_=i;
        }
        //TODO 字幕流/数据流
    }

    return true;
}


void Demuxer::Close(){
    if(formatCtx_)
    {
        formatCtx_=nullptr;
    }
}

int64_t Demuxer::Duration() const {
    if (!formatCtx_) return 0;
    return formatCtx_->duration;//微秒
}

int Demuxer::videoStreamIndex() const {
    return videoIndex_;
}

int Demuxer::audioStreamIndex() const{
    return audioIndex_;
}

//编解码参数
AVCodecParameters* Demuxer::GetVideoCodecParams() {
    if (videoIndex_ < 0) return nullptr;
    return formatCtx_->streams[videoIndex_]->codecpar;
}

AVCodecParameters* Demuxer::GetAudioCodecParams(){
    if (audioIndex_ < 0) return nullptr;
    return formatCtx_->streams[audioIndex_]->codecpar;
}

AVRational Demuxer::GetVideoTimeBase() {
    if (videoIndex_ < 0) return {0, 1};
    return formatCtx_->streams[videoIndex_]->time_base;
}
