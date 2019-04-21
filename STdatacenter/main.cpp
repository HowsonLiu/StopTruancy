#include <QtCore/QCoreApplication>
#include "datacenter.h"
#include "studentserializer.h"
#include "classserializer.h"
#include "sqlitehelper.h"
#include <opencv2/face.hpp>

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

	//SQLiteHelper h("D:\\tmp\\data\\class\\Math\\Math.db");
	//bool res;
	//if (h.isValid()) res = h.Init();
	//res = h.AddStudent("3115005489");
	//res = h.AddStudent("3115005490");
	//res = h.AddStudent("3115005491");
	//res = h.AddStudent("3115005492");
	//res = h.AddStudent("3115005493");
	//res = h.AddRecord("2019-1-1", { "3115005489", "3115005490" });
	//res = h.AddRecord("2019-1-2", { "3115005491", "3115005492" });
	//res = h.AddRecord("2019-1-3", { "3115005489", "3115005492" });
	//res = h.AddRecord("2019-1-4", { "3115005490" });
	//int allnum, num;
	//res = h.GetRecordNums(&allnum);
	//res = h.GetStudentAttendanceNums("3115005489", &num);

	StudentSerializer s1("5489");
	StudentSerializer s2("5490");
	StudentSerializer s3("5491");
	if (!s1.Exist()) s1.Init();
	if (!s2.Exist()) s2.Init();
	if (!s3.Exist()) s3.Init();

	ClassSerializer c1("Math");
	ClassSerializer c2("English");
	ClassSerializer c3("Physics");
	if (!c1.Exist()) c1.Init();
	if (!c2.Exist()) c2.Init();
	if (!c3.Exist()) c3.Init();
	int res;
	res = c1.AddStudents({ "5489", "5490", "5491"});
	
	//cv::Mat mat = cv::imread("D:\\PaPa Liu\\Pictures\\SankakuImage\\6550581_big.jpg", 1);
	//res = c1.AddLesson(mat, "2019-4-4", { "3115005489", "3115005491" });

	c1.Train();

	int sum, num;
	res = c1.GetLessonNum(&sum);
	res = c1.GetStudentAttendances("5489", &num);

	cv::Mat mat = cv::imread("D:\\tmp\\data\\student\\5489\\face_information\\1.jpg", 0);	// Ò»¶¨»Ò¶ÈÍ¼
	cv::imshow("1", mat);
	cv::waitKey(0);
	auto modelPCA = cv::face::EigenFaceRecognizer::create();
	// modelPCA->read("MyFacePCAModel.xml");
	modelPCA->read("D:\\tmp\\data\\class\\Math\\Math.xml");
	if (modelPCA.empty()) return 1;
	res = modelPCA->predict(mat);

	return a.exec();
}
