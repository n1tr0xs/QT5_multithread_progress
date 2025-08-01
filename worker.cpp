#include "worker.h"
#include <QThread>
#include <QTime>
#include <QtGlobal>
#include <QtMath>

Worker::Worker(int id, QObject *parent) : QObject(parent), m_id(id) {}

void Worker::process() {
    // Инициализация генератора случайных чисел с учетом ID потока
    srand(static_cast<uint>(QTime::currentTime().msec() + m_id * 123));

    const int steps = 100;
    for (int i = 1; i <= steps; ++i) {
        // "Ресурсоемкая" задача
        volatile double result = 0;
        for (int j = 0; j < 10000; ++j)
            result += qSin(j) * qCos(j);

        emit progress(m_id, i);

        // Случайная задержка от 20 до 120 мс
        int delay = 20 + rand() % 100;
        QThread::msleep(delay);
    }

    emit finished(m_id);
}
