#include "CameraThread.h"
#include <QDebug>
using namespace cv;

CameraThread::CameraThread(cv::VideoCapture capture, cv::Mat frame, QWidget *parent)
	: QThread(parent)
{
	m_capture = capture;
	m_frame = frame;
	m_timer.start(100);
}

CameraThread::~CameraThread()
{

}

void CameraThread::run()
{
	m_capture.open(0);
	//Ĭ�Ϸֱ���
	double frame_width = m_capture.get(cv::CAP_PROP_FRAME_WIDTH);
	double frame_height = m_capture.get(cv::CAP_PROP_FRAME_HEIGHT);
	double frame_rate = m_capture.get(cv::CAP_PROP_FPS);
	
	//�޸ķֱ���
	m_capture.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
	m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, 960);
	m_capture.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));

	connect(&m_timer, SIGNAL(timeout()), this, SLOT(showCameraSlot()));
}

void CameraThread::showCameraSlot()
{
	m_capture >> m_frame;
	if (!m_frame.empty())
	{
		//opencv�е�ͼƬ��BGR��ʽ���棬Qt����RGB������ת����ʽ�ٽ�MatתΪQImage
		cvtColor(m_frame, m_frame, CV_BGR2RGB);
		QImage  Qimg((uchar*)m_frame.data, m_frame.cols, m_frame.rows, m_frame.step, QImage::Format_RGB888);
		emit returnQImageSignal(Qimg);
	}
}

void CameraThread::stopCapture()
{
	if (m_capture.isOpened())
	{
		m_capture.release();
	}
}
