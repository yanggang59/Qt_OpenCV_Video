#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <opencv2/opencv.hpp>
#include <QImage>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

     QImage Mat2QImage(cv::Mat cvImg);

private slots:
    void on_BTN_oepnFile_clicked();

    void on_BTN_openCamera_clicked();

    void nextFrame();


private:
    Ui::MainWindow *ui;


    cv::Mat frame;
    cv::VideoCapture capture;
    QImage  image;
    QTimer *timer;
    double rate; //FPS
    cv::VideoWriter writer;   //make a video record

};

#endif // MAINWINDOW_H
