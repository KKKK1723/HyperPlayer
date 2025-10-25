#ifndef DEMUXER_H
#define DEMUXER_H

#include <QDebug>
extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libswresample/swresample.h>
#include <libavutil/samplefmt.h>
#include <libavutil/channel_layout.h>
}

//解封装器
class Demuxer {
public:
    
    Demuxer();
    ~Demuxer();
    
    // 文件操作
    bool Open(const std::string& filepath);//打开并获取信息
    void Close();
    
    // 数据读取
    bool ReadPacket(AVPacket* packet);  
    bool Seek(int64_t timestamp);   
    
    // 信息查询
    int64_t Duration() const;//返回视频总时长,这里用const防止修改成员对象
    int videoStreamIndex() const; // 返回视频流索引
    int audioStreamIndex() const; // 返回音频流索引
    
    // 获取编解码参数
    AVCodecParameters* GetVideoCodecParams();
    AVCodecParameters* GetAudioCodecParams();
    
    // 获取时间基（后面计算时间戳需要）
    AVRational GetVideoTimeBase();
    AVRational GetAudioTimeBase();
    
//private:
    AVFormatContext* formatCtx_ = nullptr;
    int videoIndex_ = -1;
    int audioIndex_ = -1;
};

#endif // DEMUXER_H
