# Multi-Reactor Web Server

基于 C++ 实现的多 Reactor 多线程 Web 服务器，支持高并发 HTTP 静态资源服务

## 架构

MainReactor 主线程负责 accept 新连接并 Round-Robin 分发给 SubReactor

SubReactor 为 N 个工作线程，每个线程独立 EventLoop，独立处理 IO 事件

## 特性

- 多 Reactor 模式，MainReactor 负责连接管理，SubReactor 负责 IO 处理
- IO 多路复用，支持 epoll、poll、select 三种后端
- 线程池，固定数量工作线程，Round-Robin 负载均衡
- HTTP/1.1 请求解析，静态文件服务，目录浏览
- 自动扩容 Buffer，读写缓冲区按需扩展，支持 readv 分散读

## 编译

```bash
g++ -Wall -Wextra *.cpp -g -o webserver -lpthread

运行

bash
./webserver
./webserver

默认监听端口 10000，服务当前目录


bash
./webserver 8080 ./source/
./webserver 8080 ./source/

自定义端口和服务目录


项目结构

text
Buffer.h / Buffer.cpp               读写缓冲区
Channel.h / Channel.cpp             fd 事件封装
Dispatcher.h / Dispatcher.cpp       IO 多路复用抽象基类
EpollDispatcher.h / EpollDispatcher.cpp    epoll 后端
PollDispatcher.h / PollDispatcher.cpp      poll 后端
SelectDispatcher.h / SelectDispatcher.cpp  select 后端
EventLoop.h / EventLoop.cpp         事件循环核心
HttpRequest.h / HttpRequest.cpp     HTTP 请求解析
HttpResponse.h / HttpResponse.cpp   HTTP 响应构建
TcpConnection.h / TcpConnection.cpp TCP 连接管理
TcpServer.h / TcpServer.cpp         TCP 服务器
ThreadPool.h / ThreadPool.cpp       线程池
WorkerThread.h / WorkerThread.cpp   工作线程封装
Log.h                               日志宏
main.cpp                            程序入口
Buffer.h / Buffer.cpp               读写缓冲区
Channel.h / Channel.cpp             fd 事件封装
Dispatcher.h / Dispatcher.cpp       IO 多路复用抽象基类
EpollDispatcher.h / EpollDispatcher.cpp    epoll 后端
PollDispatcher.h / PollDispatcher.cpp      poll 后端
SelectDispatcher.h / SelectDispatcher.cpp  select 后端
EventLoop.h / EventLoop.cpp         事件循环核心
HttpRequest.h / HttpRequest.cpp     HTTP 请求解析
HttpResponse.h / HttpResponse.cpp   HTTP 响应构建
TcpConnection.h / TcpConnection.cpp TCP 连接管理
TcpServer.h / TcpServer.cpp         TCP 服务器
ThreadPool.h / ThreadPool.cpp       线程池
WorkerThread.h / WorkerThread.cpp   工作线程封装
Log.h                               日志宏
main.cpp                            程序入口

设计要点

1.每个线程一个 EventLoop，通过 socketpair 实现线程间唤醒
2.跨线程操作通过加锁任务队列和 wakeup 机制实现线程安全
3.读写分离缓冲区，支持内存合并与 readv 分散读
4.HTTP 请求逐行解析，请求行、请求头、请求体依次处理