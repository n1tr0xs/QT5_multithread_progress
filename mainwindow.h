#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QTableWidget>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateProgress(int id, int value);
    void taskFinished(int id);

private:
    Ui::MainWindow *ui;
    QVector<QProgressBar *> progressBars;
    QVector<QThread *> threads;
};

#endif // MAINWINDOW_H
