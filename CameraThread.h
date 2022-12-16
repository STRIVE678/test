#pragma once
#include <Windows.h>
#include <QWidget>
#include <QThread>
#include <QLabel>
#include <QTimer>
#include<opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include "opencv2/imgproc/types_c.h"

using namespace cv;
class CameraThread  : public QThread
{
	Q_OBJECT

public:
	CameraThread(cv::VideoCapture capture, cv::Mat frame, QWidget* parent = NULL);
	~CameraThread();

public:

	/*
	* @brief 获取当前帧
	* @return 每一帧
	*/
	cv::Mat getFrame() const {return m_frame;};

	/*
	* @brief 获取摄像头
	* @return 摄像头
	*/
	cv::VideoCapture  getCapture() const { return m_capture; };

	/*
	* @brief 关闭摄像头
	*/
	void stopCapture();

protected:

	/*
	* @brief 线程处理函数
	*/
	void run();

signals:

	void returnQImageSignal(QImage);

private slots:

	/*
	* @brief 定时发送转换后的图片
	*/
	void showCameraSlot();

private:
	cv::VideoCapture m_capture; 
    cv::Mat m_frame;              
	QTimer m_timer;                  
};
