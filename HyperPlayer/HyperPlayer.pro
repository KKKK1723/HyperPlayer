QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/demux/demuxer.cpp \
    src/decode/videodecoder.cpp \
    src/core/thread.cpp\
    src/ui/mainwindow.cpp


HEADERS += \
    src/const.h \
    src/demux/demuxer.h \
    src/decode/videodecoder.h \
    src/core/thread.h\
    src/ui/mainwindow.h

FORMS += \
    src/ui/mainwindow.ui

# 添加头文件搜索路径
INCLUDEPATH += $$PWD/src \
               $$PWD/src/core \
               $$PWD/src/demux \
               $$PWD/src/decode \
               $$PWD/src/output \
               $$PWD/src/ui \
               $$PWD/src/controller


# ----------------- FFmpeg 配置 -----------------
INCLUDEPATH += D:/ffmpeg/ffmpeg-master-latest-win64-gpl-shared/include
LIBS += -LD:/ffmpeg/ffmpeg-master-latest-win64-gpl-shared/lib \
        -lavformat -lavcodec -lswresample -lswscale -lavutil
# ----------------------------------------------

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
