[English](README.md) | 简体中文

# Video Photo Side By Side Player

一个媒体播放器，习惯大于配置，没有对话框，全部在配置文件处理，左边播放视频，右边看照片。适用于进行马列主义研修，譬如左边看清晰度欠佳的老师视频讲解，右边看高清的老师图像

## 主要功能
视频播放基于 [LAVFilters](https://github.com/Nevcairiel/LAVFilters)

* 支持 .avi, .mp4, .rm, .rmvb and .wmv 格式视频

* 支持 .jpg, .bmp and .png 格式图像

* 可以在配置文件设置目录，然后在播放器可以选择这些目录下的文件进行播放

* 右边支持热键，点击键盘1、2、3……9、0对应配置文件的1到10个目录

* 右边支持<kbd>PageUp</kbd>, <kbd>PageDown</kbd>, <kbd>Home</kbd>, <kbd>End</kbd>键进行图片浏览

## 如何使用
* 安装 Qt 5.x

* 在Qt Creator打开项目

* 构建！

* 把player.ini放在当前目录。并配置好

*注意：如果是开发环境，你要放到build-inst_player-Desktop_Qt_5_12_8_MinGW_64_bit-Debug/下*