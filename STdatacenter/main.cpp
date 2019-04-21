#include <QtCore/QCoreApplication>
#include "datacenter.h"
#include "studentserializer.h"
#include "classserializer.h"
#include "sqlitehelper.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	//DATA_CENTER_INSTANCE->addClassName("111");
	//DATA_CENTER_INSTANCE->addClassName("123");
	//DATA_CENTER_INSTANCE->addClassName("111");
	//DATA_CENTER_INSTANCE->addStudentName("3115005489");
	//DATA_CENTER_INSTANCE->addStudentName("3115005488");
	//DATA_CENTER_INSTANCE->addStudentName("3115005489");
	//DATA_CENTER_INSTANCE->delClassName("123");
	//DATA_CENTER_INSTANCE->delStudentName("3115005488");

	//StudentSerializer s("31150054891");
	//s.Init();
	//std::vector<cv::Mat> vm;
	//vm.push_back(cv::imread("D:\\PaPa Liu\\Pictures\\SankakuImage\\6550581_big.jpg", 0));
	//s.WriteImage(vm);
	//s.AddClass("Math");

	//ClassSerializer c("Math");
	//c.Init();
	//c.AddStudent("3115005489");
	//c.AddStudents({ "3115005489", "3115005490" });

	SQLiteHelper h("D:\\tmp\\data\\class\\Math\\Math.db");
	bool res;
	if (h.isValid()) res = h.Init();
	res = h.AddCols({ "3115005490", "3115005491"});
	return a.exec();
}
