#include <QtCore/QCoreApplication>
#include "datacenter.h"
#include "studentserializer.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	StudentSerializer s("123");
	std::vector<cv::Mat> vm;
	//vm.push_back(cv::imread("D:\\PaPa Liu\\Pictures\\SankakuImage\\6550581_big.jpg", 0));
	s.ReadImages(&vm);
	s.AddClass("Math");
	DATA_CENTER_INSTANCE->addStudentName("123");
	return a.exec();
}
