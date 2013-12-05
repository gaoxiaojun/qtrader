#include <QtCore>
#include "threadsafequeue.h"

class Thread : public QThread {
public:
    Thread(ThreadSafeQueue<int> &q, bool isProducer) : _queue(q), _prod(isProducer) {
        if(_prod)
            qDebug() << "I am a producer";
        else
            qDebug() << "I am a consumer";
    }

    void run() {
        if(_prod)
            while(1) produce();
        else
            while(1) consume();
    }
    void produce() {
        int v = qrand();
        _queue.enqueue(v);
        qDebug() << "WRITE:" << v;
        sleep(qrand()%5);
    }
    void consume() {
        int v = _queue.dequeue();
        qDebug() << "READ:" << v;
        sleep(qrand()%5);
    }

private:
    ThreadSafeQueue<int> &_queue;
    bool _prod;
};

int main() {
    ThreadSafeQueue<int> queue;
    for(int i=0;i<7;i++){
        Thread *thr = new Thread(queue, (qrand()%19) < 10);
        thr->start();
    }
    sleep(50);
}
