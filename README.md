# Smart-Sorting-Trash-Bin-Based-on-STM32F103ZET6
## 系统概述
本系统应用STM32F103单片机为控制处理器，将小区所有的垃圾桶通过ESP8266 WIFI模块与TLINK组建网络，每个垃圾桶上装有超声波传感器来检测垃圾桶剩余容量，还有烟雾传感器检测是否有物品自燃，垃圾分类通过固定在垃圾桶上的触摸屏幕进行垃圾选择分类。每个垃圾桶会将实时检测到的垃圾桶状态和分类信息发送给TLINK平台，可以在TLINK后台进行管理或通过组态界面实现远程查看。

## 运行环境
STEM32开发板：用于部署超声波传感器、烟雾传感器等，以及用ESP8266 WIFI模块接入网络，进行TCP透传，实现远程实时监控。
PC：WIN7以上，推荐WIN10，需要下载Keil uVision5进行代码修改，FlyMcu进行程序烧录，CH340驱动程序，XCOM串口调试助手。
路由器等能够提供WIFI热点的设备：需要给予开发板网络环境，与TLINK平台通过TCP透传实现远程。
TLINK物联网平台：实现远程监控及后台管理。

## 技术路线
使用Keil5编写基于STM32F103系列单片机的超声波测距程序，以及烟雾检测程序。超声波测距模块用来检测垃圾桶的满溢程度，这里使用的是HC-SR04超声波测距模块；烟雾检测模块主要用来检测垃圾桶是否有燃烧风险，使用MQ-2烟雾检测模块。同时设计多级用户模块，来实现垃圾分类以及垃圾桶状态显示。

## 系统用例图
<img width="6922" height="4934" alt="系统用例图" src="https://github.com/user-attachments/assets/c949b5ba-2ae4-491c-b72e-00aea2775fd2" />

## 用户手册
1、本系统出厂时已经下载进程序，可直接使用。
2、该系统需要通过ESP8266进行联网TCP透传，开机时会进行系统联网配置，TCP透传成功后会进入到主菜单界面，LED1绿灯显示运行状态。
3、通过手动触摸屏幕选择垃圾桶类别，在垃圾桶类别界面会实时显示该垃圾桶的剩余容量及是否自燃。
4、垃圾桶的剩余容量和烟雾浓度显示在LCD屏幕的同时，会将数据传输到TLINK平台，可通过该平台或组态界面进行远程监测数据。
5、若垃圾桶内剩余容量不足10%，则会通过LED0红灯亮报警，若垃圾桶烟雾浓度大于60%，即发生自燃，则会通过蜂鸣器发出响声进行报警，远程监控界面也会显示报警信息若设置了联系人，也会将报警信息发送到微信小程序里。

## 项目演示
### LCD界面
<img width="960" height="720" alt="主菜单界面" src="https://github.com/user-attachments/assets/954fe96f-0cdd-4127-82c5-02e62e1acb23" />
<img width="960" height="720" alt="可回收垃圾界面" src="https://github.com/user-attachments/assets/00320404-8463-4548-b84a-ccdc3ce3387a" />
<img width="960" height="720" alt="其他垃圾界面" src="https://github.com/user-attachments/assets/9c1e1a86-2dcf-4da6-9996-baf59aa640ec" />
### 云组态界面
<img width="1920" height="1080" alt="云组态界面" src="https://github.com/user-attachments/assets/1b2b62ae-0764-4786-97ca-bb5ce56e0839" />
<img width="1920" height="1080" alt="实时监控界面" src="https://github.com/user-attachments/assets/8214dad9-92f5-44a9-9d40-a496b940bab9" />
### TLINK监控中心
<img width="1920" height="1080" alt="TLINK监控中心界面" src="https://github.com/user-attachments/assets/e94df181-8cfd-487d-a71c-62d72877db31" />
<img width="1920" height="1080" alt="历史数据" src="https://github.com/user-attachments/assets/206ee369-444c-4cf4-bcfd-20d965e58ea1" />
### 设备管理
<img width="1920" height="1080" alt="设备管理界面" src="https://github.com/user-attachments/assets/2f29e5a1-c82f-43fd-ae7e-a895998e0346" />
### 触发器
<img width="1920" height="1080" alt="触发器界面" src="https://github.com/user-attachments/assets/667bf7d0-cf6b-4acf-b6bb-bd6f2ef307ae" />
### 报警记录
<img width="1920" height="1080" alt="报警记录" src="https://github.com/user-attachments/assets/877e491d-49aa-4f0d-8fc4-c52d94a8127a" />
