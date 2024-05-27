#include "TimeViewer/TimeViewer.h"

TimeViewer::TimeViewer(QWidget* parent) :QMainWindow(parent) {
	UI.setupUi(this);

	CalibrationAction = new QAction(QIcon(":/image/Calibration.svg"), "校准", this);
	SettingAction = new QAction(QIcon(":/image/Setting.svg"), "设置", this);\
	Options = new QSettings("./config/TimeViewer.ini", QSettings::Format::IniFormat);
	Setting = new TimeViewerSetting(Options,this);
	Timer = new QTimer();

	this->addAction(CalibrationAction);
	this->addAction(SettingAction);
	this->setContextMenuPolicy(Qt::ActionsContextMenu);

	connect(CalibrationAction, &QAction::triggered, this, &TimeViewer::Calibration);
	connect(SettingAction, &QAction::triggered, Setting, &TimeViewerSetting::show);
	connect(Timer, &QTimer::timeout, this, &TimeViewer::Increase);
}

void TimeViewer::Increase() {
	Time = Time.addSecs(1);
	UI.TopTime->setText(Time.toString());
}

void TimeViewer::Calibration() {
	Timer->stop();

	cpr::Response Response = cpr::Get(cpr::Url{ "https://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp" });
	
	yyjson_doc* Doc = yyjson_read(Response.text.c_str(), Response.text.size(), YYJSON_READ_NOFLAG);

	yyjson_val* Data = yyjson_obj_get(Doc->root, "data");

	yyjson_val* Timestamp = yyjson_obj_get(Data,"t");

	Time = QDateTime::fromMSecsSinceEpoch(QString(yyjson_get_str(Timestamp)).toULongLong());

	yyjson_doc_free(Doc);

	Timer->start(1000);
}

TimeViewer::~TimeViewer() {
	delete CalibrationAction;
	delete SettingAction;
	delete Timer;
	delete Options;
	delete Setting;
}