#include "TimeViewer/TimeViewerSetting.h"

TimeViewerSetting::TimeViewerSetting(QSettings* Options,QWidget* parent) :QMainWindow(parent) {
	UI.setupUi(this);
	this->Options = Options;
}

TimeViewerSetting::~TimeViewerSetting() {

}