#pragma once

#include "cpr/cpr.h"
#include "ui_TimeViewerSetting.h"
#include <qsettings.h>

class TimeViewerSetting : public QMainWindow {
	Q_OBJECT
public:
	explicit TimeViewerSetting(QSettings* Options,QWidget* parent = nullptr);
	~TimeViewerSetting();
private:
	Ui::TimeViewerSettingClass UI;
	QSettings* Options;
public Q_SLOTS:

Q_SIGNALS:

};