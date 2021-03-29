## 1、数据及数据结构：

* Connector：代表显卡上的插口，有几个Connector表示会有几个输出。

* CRTC：crt controller，负责将帧缓存中的数据传送到Connector，数据在传送到Connector之前会经过Encoder。 帧缓存 --> CRTC --> Encoder --> Connector --> 显示器。

* FrameBuffer：在这里帧缓存并不是指的显存上的某一块区域，而是Linux DRM抽象出来的一个概念，用fb_id表示。 

* drm_mode_create_dumb：drmIoctl的参数，意思是请求内核创建缓存。 这个才是真正的内存块，可以使用mmap映射到程序虚拟内存中。Framebuffer的创建中必须指定一个缓存的id。

## 2、函数：

* drmModeSetCrtc：最核心的函数之一，它负责将建立从帧缓存到Connector的关联。只有调用它，显示器才能显示缓存中的数据。

* drmModePageFlip：直译就是翻页，笔者的理解是 drm_mode_create_dumb类型的缓存其实是双缓存，只有调用此函数之后，crtc才能将之前写入的数据传送给显示器。
