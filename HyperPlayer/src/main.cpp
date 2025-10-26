#include "mainwindow.h"
#include "demuxer.h"
#include "const.h"
#include "videodecoder.h"
#include <QApplication>
#include <QLabel>
#include"thread.h"


int main(int argc, char *argv[])
{



    // qDebug() << "=== 测试VideoDecoder ===";

    // // 1. 打开文件
    // Demuxer demuxer;
    // std::string videoPath = "D:/桌面/视频录制/搞笑生气猫_爱给网_aigei_com.mp4";

    // if (!demuxer.Open(videoPath)) {
    //     qDebug() << "打开文件失败";
    //     return -1;
    // }

    // // 2. 初始化解码器
    // VideoDecoder decoder;
    // AVCodecParameters* videoParams = demuxer.GetVideoCodecParams();

    // if (!decoder.Init(videoParams)) {
    //     qDebug() << "初始化解码器失败";
    //     return -1;
    // }

    // // 3. 读取数据包并解码
    // AVPacket* packet = av_packet_alloc();
    // AVFrame* frame = av_frame_alloc();
    // bool gotFirstFrame = false;
    // QImage firstFrameImg;

    // // 循环读取数据包
    // while (!gotFirstFrame) {
    //     // 从Demuxer读取一个包（注意：这里需要实现ReadPacket）
    //     // 临时方案：直接用av_read_frame
    //     int ret = av_read_frame(demuxer.formatCtx_, packet);
    //     if (ret < 0) break;

    //     // 只处理视频包
    //     if (packet->stream_index != demuxer.videoStreamIndex()) {
    //         av_packet_unref(packet);
    //         continue;
    //     }

    //     // 发送到解码器
    //     decoder.SendPacket(packet);

    //     // 尝试接收帧
    //     while (decoder.ReceiveFrame(frame) == 0) {
    //         qDebug() << "解码到一帧！PTS:" << frame->pts;

    //         // 转换为QImage
    //         firstFrameImg = decoder.ConvertToQImage(frame);
    //         gotFirstFrame = true;
    //         break;
    //     }

    //     av_packet_unref(packet);
    // }

    // av_packet_free(&packet);
    // av_frame_free(&frame);
    // demuxer.Close();

    // // 4. 显示第一帧
    // QApplication a(argc, argv);

    // if (!firstFrameImg.isNull()) {
    //     qDebug() << "✓ 成功解码第一帧！";
    //     qDebug() << "图像尺寸:" << firstFrameImg.width()
    //              << "x" << firstFrameImg.height();

    //     // 显示图像
    //     QLabel* label = new QLabel();
    //     label->setPixmap(QPixmap::fromImage(firstFrameImg));
    //     label->setWindowTitle("HyperPlayer - 第一帧");
    //     label->show();

    //     return a.exec();
    // } else {
    //     qDebug() << "✗ 未能解码到帧";
    //     return -1;
    // }

    //TestThread* tt=new TestThread();
    //基本启动
    // int ret=tt.Start();
    // if(ret==-1)
    // {
    //     return 0;
    // }

    // tt.wait();


    //自动析构
   // delete tt;

    //TODO......


    return 0;
}
