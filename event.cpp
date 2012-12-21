#include <stdio.h>
#include <unistd.h>
#include "event.hpp"

MessageQueue::MessageQueue()
    : msgqueue(), funcmap(), mLock(), tid(), condition()
{
    pthread_create(&tid, NULL, threadFunc, this);
}

void *MessageQueue::threadFunc(void *data)
{
    MessageQueue *m = static_cast<MessageQueue *>(data);
    m->mainLoop();

    return NULL;
}

bool MessageQueue::registerMsg(string &&name, Functor<MessageHandler> &cmd)
{
    AutoMutex _l(mLock);

    auto it = funcmap.find(name);
    if (it == funcmap.end()) {
        funcmap.insert(std::make_pair(name, cmd));
        return true;
    } else {
        printf("Can't register existed message: %s\n", name.c_str());
        return false;
    }
}

void MessageQueue::postMsg(string &&name)
{
    AutoMutex _l(mLock);

    msgqueue.push(name);
    condition.signal();
}

void MessageQueue::mainLoop()
{
    AutoMutex _l(mLock);

    while (true) {
        if (!msgqueue.empty()) {
            string msg = msgqueue.front();
            msgqueue.pop();
            auto it = funcmap.find(msg);
            if (it != funcmap.end()) {
                mLock.unlock();
                it->second();
                mLock.lock();
            }
        } else {
            //            printf("No message, wait...\n");
            condition.wait(mLock);
            //            printf("Get signal!\n");
        }
    }
}

void func1()
{
    printf("in %s\n", __func__);
}

void func2()
{
    printf("in %s\n", __func__);
}

class MyCallback {
public:
  void operator()() { printf("in %s\n", __func__); }
};

void registerx(MessageQueue &msg)
{
    MyCallback callback;
    Functor<MessageHandler> cmdx(callback);
    msg.registerMsg("cmdx", cmdx);
}

int main()
{
    MessageQueue msg;

    Functor<MessageHandler> cmd1(func1);
    Functor<MessageHandler> cmd2(func2);

    msg.registerMsg("cmd1", cmd1);
    msg.registerMsg("cmd2", cmd2);
    registerx(msg);

    //    while (1) {
    msg.postMsg("cmd1");
    msg.postMsg("cmd2");
    msg.postMsg("cmdx");
    //    usleep(100000);
    //    }

    pause();
    return 0;
}
