#### 简介
本程序是对timerfd的一个简单使用，timerfd是一linux提供一个定时接口，该接口基于文件描述进行操作，通过该文件描述符的可读时间进行超时通知；可见，该timerfd是一个超时提醒的接口，我们预先设置时间，当发生超时时，可以通过select/poll/epoll来监听。
#### 流程
程序基本的思路是通过封装的线程库类，timerfd类，timer_thread类以及一个任务类Task，timer_thread类启动线程库类，这时的程序将由主线程和子线程构成，子线程然后通过线程处理函数启动timerfd的start方法，这时的定时开始启动，进行定时任务(同时将该timerfd加入了poll中进行监听)，定时任务中采用了回调函数的机制，回调函数由main.cpp中的Task类来完成，子线程启动timerfd的start方法也是通过回调函数的方式，这将在一定程度上减少耦合度，也可以采用引用的方式，也就是类之间的关联/依赖方式来完成。
#### UML图
