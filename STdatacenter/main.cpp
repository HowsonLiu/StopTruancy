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
	//s.init();
	//std::vector<cv::Mat> vm;
	//vm.push_back(cv::imread("D:\\PaPa Liu\\Pictures\\SankakuImage\\6550581_big.jpg", 0));
	//s.writeImage(vm);
	//s.addClass("Math");

	//ClassSerializer c("Math");
	//c.init();
	//c.addStudent("3115005489");
	//c.addStudents({ "3115005489", "3115005490" });

	//SQLiteHelper h("D:\\tmp\\data\\class\\Math\\Math.db");
	//bool res;
	//if (h.isValid()) res = h.init();
	//res = h.addStudent("3115005489");
	//res = h.addStudent("3115005490");
	//res = h.addStudent("3115005491");
	//res = h.addStudent("3115005492");
	//res = h.addStudent("3115005493");
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
	if (!s1.exists()) s1.init();
	if (!s2.exists()) s2.init();
	if (!s3.exists()) s3.init();

	ClassSerializer c1("Math");
	ClassSerializer c2("English");
	ClassSerializer c3("Physics");
	if (!c1.exists()) c1.init();
	if (!c2.exists()) c2.init();
	if (!c3.exists()) c3.init();
	int res;
	
	//cv::Mat mat = cv::imread("D:\\PaPa Liu\\Pictures\\SankakuImage\\6550581_big.jpg", 1);
	//res = c1.addLesson(mat, "2019-4-4", { "3115005489", "3115005491" });

	c1.trains();

	int sum, num;
	res = c1.getLessonNum(&sum);
	res = c1.getStudentAttendances("5489", &num);

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
