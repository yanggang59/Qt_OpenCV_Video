#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//open file
void MainWindow::on_BTN_oepnFile_clicked()
{
    if (capture.isOpened())
            capture.release();     //decide if capture is already opened; if so,close it
        QString filename =QFileDialog::getOpenFileName(this,tr("Open Video File"),".",tr("Video Files(*.avi *.mp4 *.flv *.mkv)"));
        capture.open(filename.toLocal8Bit().data());
        if (capture.isOpened())
        {
            rate= capture.get(CV_CAP_PROP_FPS);
            capture >> frame;
            if (!frame.empty())
            {
                image = Mat2QImage(frame);
                ui->label->setPixmap(QPixmap::fromImage(image));
                timer = new QTimer(this);
                timer->setInterval(1000/rate);   //set timer match with FPS
                connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
                timer->start();
            }
        }
}


//open camera
void MainWindow::on_BTN_openCamera_clicked()
{
    if (capture.isOpened())
           capture.release();     //decide if capture is already opened; if so,close it
       capture.open(0);           //open the default camera
       if (capture.isOpened())
       {
           rate= capture.get(CV_CAP_PROP_FPS);
           capture >> frame;
           if (!frame.empty())
           {

               image = Mat2QImage(frame);
               ui->label->setPixmap(QPixmap::fromImage(image));
               timer = new QTimer(this);
               //timer->setInterval(1000/rate);   //set timer match with FPS
               timer->setInterval(30);   //set timer match with FPS
               connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
               timer->start();
           }
       }
}


void MainWindow::nextFrame()
{
    capture >> frame;
       if (!frame.empty())
       {
           image = Mat2QImage(frame);
           ui->label->setPixmap(QPixmap::fromImage(image));
       }


}


QImage MainWindow::Mat2QImage(cv::Mat cvImg)
{
    QImage qImg;
       if(cvImg.channels()==3)                             //3 channels color image
       {

           cv::cvtColor(cvImg,cvImg,CV_BGR2RGB);
           qImg =QImage((const unsigned char*)(cvImg.data),
                       cvImg.cols, cvImg.rows,
                       cvImg.cols*cvImg.channels(),
                       QImage::Format_RGB888);
       }
       else if(cvImg.channels()==1)                    //grayscale image
       {
           qImg =QImage((const unsigned char*)(cvImg.data),
                       cvImg.cols,cvImg.rows,
                       cvImg.cols*cvImg.channels(),
                       QImage::Format_Indexed8);
       }
       else
       {
           qImg =QImage((const unsigned char*)(cvImg.data),
                       cvImg.cols,cvImg.rows,
                       cvImg.cols*cvImg.channels(),
                       QImage::Format_RGB888);
       }

       return qImg;

}
