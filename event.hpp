#ifndef MESSAGEQUEUE_HPP
#define MESSAGEQUEUE_HPP

#include <string>
#include <queue>
#include <map>
#include <utils/threads.h>
#include <pthread.h>
#include "lib/functor.h"
#include "lib/tuple.h"

using std::queue;
using std::string;
using std::map;
using android::Mutex;
using android::AutoMutex;
using android::Condition;

typedef std::tuple_element<0, std::tuple<void (void)>>::type MessageHandler;

class MessageQueue {
public:
    MessageQueue();
    bool registerMsg(string &&name, Functor<MessageHandler> &cmd);
    void postMsg(string &&name);
private:
    void mainLoop();
    static void *threadFunc(void *);

    queue<string> msgqueue;
    map<string, Functor<MessageHandler>> funcmap;
    mutable Mutex mLock;
    pthread_t tid;
    Condition condition;
};

#endif
