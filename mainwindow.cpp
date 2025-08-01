#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worker.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({"Задача", "Прогресс"});

    for (int i = 0; i < 10; ++i) {
        // Столбец названия
        ui->tableWidget->setItem(i, 0,
                                 new QTableWidgetItem(QString("Задача %1").arg(i)));

        // Прогрессбар
        QProgressBar *bar = new QProgressBar(this);
        bar->setRange(0, 100);
        ui->tableWidget->setCellWidget(i, 1, bar);
        progressBars.append(bar);

        // Поток и воркер
        QThread *thread = new QThread;
        Worker *worker = new Worker(i);
        worker->moveToThread(thread);

        connect(thread, &QThread::started, worker, &Worker::process);
        connect(worker, &Worker::progress, this, &MainWindow::updateProgress);
        connect(worker, &Worker::finished, this, &MainWindow::taskFinished);
        connect(worker, &Worker::finished, thread, &QThread::quit);
        connect(worker, &Worker::finished, worker, &Worker::deleteLater);
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);

        threads.append(thread);
        thread->start();
    }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::updateProgress(int id, int value) {
    if (id >= 0 && id < progressBars.size()) {
        progressBars[id]->setValue(value);
    }
}

void MainWindow::taskFinished(int id) {
    if (id >= 0 && id < progressBars.size()) {
        progressBars[id]->setFormat("Завершено");
    }
}
