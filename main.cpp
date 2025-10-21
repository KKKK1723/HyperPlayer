#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "demuxer.h"

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

int main(int argc, char *argv[])
{

    // 测试Demuxer
    Demuxer demuxer;
    std::string videoPath = "D:/桌面/视频录制/搞笑生气猫_爱给网_aigei_com.mp4";

    if (demuxer.Open(videoPath)) {
        qDebug() << "✓ 打开文件成功！";

        // 打印视频信息
        qDebug() << "视频时长:" << demuxer.Duration() / 1000000 << "秒";
        qDebug() << "视频流索引:" << demuxer.videoStreamIndex();
        qDebug() << "音频流索引:" << demuxer.audioStreamIndex();

        // 获取视频流参数
        AVCodecParameters* videoParams = demuxer.GetVideoCodecParams();
        if (videoParams) {
            qDebug() << "视频分辨率:" << videoParams->width << "x" << videoParams->height;
            qDebug() << "视频编码:" << avcodec_get_name(videoParams->codec_id);
        }

        // 获取音频流参数
        AVCodecParameters* audioParams = demuxer.GetAudioCodecParams();
        if (audioParams) {
            qDebug() << "音频采样率:" << audioParams->sample_rate << "Hz";
            qDebug() << "音频编码:" << avcodec_get_name(audioParams->codec_id);
        }

        demuxer.Close();
        qDebug() << "✓ 关闭文件成功！";
    } else {
        qDebug() << "✗ 打开文件失败！";
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
