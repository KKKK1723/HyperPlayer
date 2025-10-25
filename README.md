# 🎬 HyperPlayer

> 基于 Qt6 + FFmpeg 7.x 的现代化视频播放器

[![Qt](https://img.shields.io/badge/Qt-6.7.3-green.svg)](https://www.qt.io/)
[![FFmpeg](https://img.shields.io/badge/FFmpeg-7.x-orange.svg)](https://ffmpeg.org/)
[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![IDE](https://img.shields.io/badge/IDE-Qt%20Creator-41CD52.svg)](https://www.qt.io/product/development-tools)

[![Multi-Threading](https://img.shields.io/badge/Multi--Threading-4%20Threads-purple.svg)](#)
[![Network](https://img.shields.io/badge/Network-HTTP%20%7C%20HLS%20%7C%20RTMP-brightgreen.svg)](#)
[![A/V Sync](https://img.shields.io/badge/A%2FV%20Sync-Audio%20Master-red.svg)](#)
[![Cross-Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)](#)

一个功能完整、性能优异的跨平台视频播放器，采用现代化 C++ 设计，支持本地文件和网络流播放。


> ⚠️ **项目状态**: 正在积极开发中，部分功能尚未实现！！！

---

## ✨ 功能特性

### 🎬 核心播放
- 多格式视频播放（MP4/MKV/AVI/FLV/MOV/WMV/WebM等）
- 软件/硬件解码（H264/H265/AV1/VP9/MPEG2等）
- 音频播放和输出（AAC/MP3/AC3/DTS/FLAC等）
- 音视频精确同步（音频主时钟方案）
- 完整播放控制（播放/暂停/停止/快进/快退）
- 进度条拖拽和精确 Seek
- 音量控制和静音功能

### 🌐 网络流媒体
- HTTP/HTTPS 在线视频播放
- HLS (m3u8) 直播流支持
- RTMP 流媒体协议
- 网络断线自动重连
- 缓冲进度实时显示

### ⚡ 性能优化
- 4线程异步架构（解封装/音频解码/视频解码独立线程）
- 线程安全队列（零拷贝数据传递）
- 硬件加速解码（NVIDIA CUVID）
- 多核并行解码
- GPU 渲染加速

### 🎮 播放控制
- 播放速度调节（0.5x - 2.0x）
- 多种循环模式（单曲循环/列表循环/随机播放）
- 上一个/下一个切换

### 📋 播放列表
- 添加/删除/清空文件
- 拖拽排序
- 双击播放
- 保存/加载播放列表（.m3u 格式）
- 自动播放下一个

### 🎨 界面和主题
- 现代化 UI 设计
- 深色/浅色主题切换
- 全屏模式
- 无边框窗口模式
- 自适应布局

### 🎯 高级功能
- 字幕支持（.srt/.ass 格式）
- 字幕样式自定义
- 字幕时间轴调整
- 视频截图（PNG/JPG）
- 画面比例调节（16:9/4:3/自适应）
- 画面调节（亮度/对比度/饱和度/锐化）

### ⌨️ 交互功能
- 丰富的快捷键（Space/←→/↑↓/F/M 等）
- 鼠标手势
- 右键快捷菜单
- 拖拽打开文件

### 💾 智能记忆
- 播放位置自动记忆
- 音量大小记忆
- 窗口大小和位置记忆
- 播放历史记录
- 最近播放列表

---

## 🏗️ 技术架构

### 核心架构：4线程异步模型

<img width="1158" height="1061" alt="QQ_1761405219123" src="https://github.com/user-attachments/assets/71a8695e-871e-4918-a6cc-e14e39e36b2d" />


### 技术栈
- **开发语言**：C++17
- **GUI框架**：Qt 6.7.3
- **多媒体库**：FFmpeg 7.x (libavcodec 62.x)
- **开发工具**：Qt Creator（推荐）
- **编译器**：MSVC / MinGW / GCC / Clang（支持 C++17）
- **构建系统**：qmake

### 核心特性
- 🧵 **多线程架构**：解封装、音频解码、视频解码独立线程
- 🔒 **线程安全队列**：生产者-消费者模式，零拷贝传递
- ⏱️ **音视频同步**：音频主时钟，精确到毫秒级同步
- 🚀 **性能优化**：零拷贝技术、多核解码、硬件加速

---

## 📁 项目结构

```
HyperPlayer/
├── src/
│   ├── core/                       # 核心模块
│   │   ├── thread.h/cpp            # 线程基类
│   │   ├── safequeue.h             # 线程安全队列模板
│   │   ├── avpacketqueue.h/cpp     # FFmpeg包队列
│   │   ├── avframequeue.h/cpp      # FFmpeg帧队列
│   │   ├── avsync.h/cpp            # 音视频同步
│   │   └── config.h/cpp            # 配置管理
│   │
│   ├── demux/                      # 解封装
│   │   ├── demuxer.h/cpp           # 解封装器
│   │   └── demuxthread.h/cpp       # 解封装线程
│   │
│   ├── decode/                     # 解码
│   │   ├── videodecoder.h/cpp      # 视频解码器
│   │   ├── audiodecoder.h/cpp      # 音频解码器
│   │   ├── videodecodethread.h/cpp # 视频解码线程
│   │   └── audiodecodethread.h/cpp # 音频解码线程
│   │
│   ├── output/                     # 输出
│   │   ├── videowidget.h/cpp       # 视频渲染组件
│   │   └── audioplayer.h/cpp       # 音频播放器
│   │
│   ├── ui/                         # 界面
│   │   ├── mainwindow.h/cpp/ui     # 主窗口
│   │   ├── controlbar.h/cpp        # 控制栏
│   │   ├── playlistwidget.h/cpp    # 播放列表
│   │   ├── settingsdialog.h/cpp    # 设置对话框
│   │   ├── aboutdialog.h/cpp       # 关于对话框
│   │   └── videosettingsdialog.h/cpp # 视频设置
│   │
│   ├── playlist/                   # 播放列表
│   │   └── playlist.h/cpp          # 播放列表数据模型
│   │
│   ├── subtitle/                   # 字幕
│   │   └── subtitle.h/cpp          # 字幕解析和渲染
│   │
│   ├── theme/                      # 主题
│   │   └── theme.h/cpp             # 主题管理器
│   │
│   ├── controller/                 # 控制器
│   │   └── playercontroller.h/cpp  # 播放器总控制器
│   │
│   ├── const.h                     # FFmpeg头文件统一管理
│   └── main.cpp                    # 程序入口
│
├── resources/                      # 资源文件
│   ├── themes/                     # 主题样式
│   │   ├── dark.qss
│   │   └── light.qss
│   ├── icons/                      # 图标资源
│   └── images/                     # 图片资源
│
├── docs/                           # 文档
│   ├── BUILD.md                    # 编译说明
│   ├── CHANGELOG.md                # 更新日志
│   └── architecture.md             # 架构文档
│
├── HyperPlayer.pro                 # Qt项目文件
└── README.md                       # 本文件
```

---

## 🛠️ 编译说明

### 环境要求
- **Qt**: 6.7.3 或更高版本（推荐使用 Qt Creator）
- **FFmpeg**: 7.x 主分支或更高版本（libavcodec 62.x+）
- **C++ 编译器**: 支持 C++17 标准
  - Windows: MSVC 2019+ 或 MinGW-w64 (GCC 9+)
  - Linux: GCC 9+ / Clang 10+
  - macOS: Xcode 11+ (Clang)

> 💡 **Qt Creator 使用提示**：安装 Qt 时建议选择 MinGW 或 MSVC 编译器套件，Qt Creator 会自动配置。


---

## 🚀 使用方法

### 基本操作
- **打开文件**: `Ctrl+O` 或 `文件` → `打开`
- **播放/暂停**: `Space` 空格键
- **停止**: `S` 键
- **快进/快退**: `←` / `→` 方向键
- **音量控制**: `↑` / `↓` 方向键
- **全屏**: `F` 或 `F11` 键
- **截图**: `Ctrl+S`

### 支持的格式
- **视频编码**: H264, H265/HEVC, AV1, VP9, VP8, MPEG2, MPEG4
- **音频编码**: AAC, MP3, AC3, DTS, FLAC, PCM
- **容器格式**: MP4, MKV, AVI, FLV, MOV, WMV, WebM, TS

---



## 🌟 Star History

如果这个项目对你有帮助，欢迎 Star ⭐ 支持一下！

---

<div align="center">

**📝 项目开发中......**

Made with ❤️ using Qt & FFmpeg

</div>
