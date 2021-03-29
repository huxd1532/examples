## 一、编译
* ```gcc -Wall -g -o example-1 example-1.c -ludev```
* ```gcc -Wall -g -o example-2 example-2.c -ludev```
* ```gcc -Wall -g -o example-3 example-3.c -ludev```

## 二、API 介绍
## １、初始化
* udev_new函数：创建一个udev library context。udev library context采用引用记数机制，创建的context默认引用记数为1，使用udev_ref和udev_unref增加或减少引用记数，如果引用记数为0，则释放内部资源。

## ２、枚举设备
* udev_enumrate_new函数：创建一个枚举器，用于扫描系统已有设备。
* udev_enumrate_add_match/nomatch_xxx系列函数：增加枚举的过滤器，过滤关键字以字符表示，如"block"设备。
* udev_enumrate_scan_xxx系列函数:扫描/sys/目录下所有与过滤器匹配的设备,扫描完成后的数据结构是一个链表.
* udev_enumerate_get_list_entry函数：获取链表的首个节点，使用udev_list_entry_foreach遍历整个链表。

## ３、监控设备热拔插（基于netlink实现）
* udev_monitor_new_from_netlink函数: 创建一个新的monitor,函数的第二个参数是事件源的名称，可选"kernel"或"udev"。基于"kernel"的事件通知要早于"udev"，但相关的设备结点未必创建完成，所以一般应用的设计要基于"udev"进行监控。

* udev_monitor_filter_add_match_subsystem_devtype函数：增加一个基于设备类型的udev事件过滤器，例如: "block"设备。

* udev_monitor_enable_receiving函数：启动监控过程，监控可以使用udev_monitor_get_fd获取一个文件描述符，基于返回的fd可以执行poll操作，简化程序设计。

* udev_monitor_receive_device函数：获取产生事件的设备映射。
* udev_device_get_action函数：可以获得一个字符串："add"或者"remove"，以及"change", "online", "offline"等。

## ４、获取设备信息
＊　udev_list_entry_get_name：获取一个设备节点sys路径
＊　udev_device_new_from_syspath：根据sys路径创建udevs设备映射
＊　udev_device_get_properties_list_entry：获取设备属性信息，返回设备所有属性信息的链表
＊　udev_list_entry_foreach：遍历属性信息列表
＊　udev_list_entry_get_name：获取属性名称
＊　udev_list_entry_get_value：获取属性

## 三、参考资料
* http://presbrey.scripts.mit.edu/doc/libudev/libudev-udev-device.html