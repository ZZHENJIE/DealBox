#include "TimeViewer/TimeViewer.h"

TimeViewer::TimeViewer(QWidget* parent) :QMainWindow(parent) {
	UI.setupUi(this);

	Calibration = new QAction(QIcon(":/image/Calibration.svg"), "校准", this);
	Setting = new QAction(QIcon(":/image/Setting.svg"), "设置", this);

	this->addAction(Calibration);
	this->addAction(Setting);
	this->setContextMenuPolicy(Qt::ActionsContextMenu);
}

TimeViewer::~TimeViewer() {
	delete Calibration;
	delete Setting;
}