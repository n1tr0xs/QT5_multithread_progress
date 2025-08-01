#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject {
    Q_OBJECT
public:
    explicit Worker(int id, QObject *parent = nullptr);

public slots:
    void process();

signals:
    void progress(int id, int percent);
    void finished(int id);

private:
    int m_id;
};

#endif // WORKER_H
