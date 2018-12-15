/*
 复习进程间通信
 1.  管道
    1.1 有名管道 mkfifo
    1.2 无名管道 pipe(),父子进程间通信,半双工

 2.  消息队列
    #include <sys/msg.h>
    // 创建或打开消息队列：成功返回队列ID，失败返回-1
    int msgget(key_t key, int flag);

    // 添加消息：成功返回0，失败返回-1
    int msgsnd(int msqid, const void *ptr, size_t size, int flag);

    // 读取消息：成功返回消息数据的长度，失败返回-1
    int msgrcv(int msqid, void *ptr, size_t size, long type,int flag);
    // 控制消息队列：成功返回0，失败返回-1
    int msgctl(int msqid, int cmd, struct msqid_ds *buf);

  3.  信号量
*/

#include <iostream>
#include <functional>

#include <unistd.h>
#include <string.h>
using namespace std;

class ProcessCommunication {
public:

    inline void printProcId() { cout << "cur procId " << getpid() << endl;}

    void testPipe() {
        /* code */
        int fd[2];

        char buff[20];

        if (pipe(fd) < 0) {
            cout << "create Pipe error\n";
            exit(-1);
        }

        // 创建进程
        pid_t pid;
        if ((pid = fork()) < 0) {
            cout << "fork error\n";
            exit(-1);
        } else if (pid > 0) { // father
            close(fd[0]); // 关闭读端
            printProcId();
            auto sendData = "hello word\n";
            write(fd[1], sendData, strlen(sendData));
        } else {
            close(fd[1]); // 关闭写端
            char buf[20] {0};
            printProcId();
            read(fd[0], buf, 20);
            cout << buf;
        }
    }
};



int main(int argc, char const *argv[])
{
    ProcessCommunication t;
    t.testPipe();

    return 0;
}

