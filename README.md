## esp32p4 project
### 1. 开发环境
####   win10 + virtualbox7.2.2 + ubuntu24.04 + esp-idf v5.5
### 2. 基于微雪ESP32-P4-WIFI6-Touch-LCD-3.4C开发板学习esp32项目开发
### 3. 开发板资料：https://www.waveshare.net/wiki/ESP32-P4-WIFI6-Touch-LCD-3.4C
### 4. 编译步骤：
   a. 设置开发板型号： idf.py set-target esp32p4  
   b. 执行编译： idf.py build  
   c. 执行烧录： idf.py -p /dev/ttyACM0 flash  
   d. 打印日志： idf.py -p /dev/ttyACM0 monitor
   e. 烧录和打印命令放在一起执行：idf.py -p /dev/ttyACM0 flash monitor
### dashboard的运行效果图
![image text](https://github.com/hgddingjun/esp32p4_3point4inch/blob/master/MarkDown/dashboard_cover.png)
