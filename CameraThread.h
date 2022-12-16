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
	* @brief ��ȡ��ǰ֡
	* @return ÿһ֡
	*/
	cv::Mat getFrame() const {return m_frame;};

	/*
	* @brief ��ȡ����ͷ
	* @return ����ͷ
	*/
	cv::VideoCapture  getCapture() const { return m_capture; };

	/*
	* @brief �ر�����ͷ
	*/
	void stopCapture();

protected:

	/*
	* @brief �̴߳�����
	*/
	void run();

signals:

	void returnQImageSignal(QImage);

private slots:

	/*
	* @brief ��ʱ����ת�����ͼƬ
	*/
	void showCameraSlot();

private:
	cv::VideoCapture m_capture; 
    cv::Mat m_frame;              
	QTimer m_timer;                  
};
