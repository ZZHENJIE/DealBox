#pragma once

#include <QTimer>
#include <QTime>
#include <QDate>
#include <QAction>
#include "cpr/cpr.h"
#include "yyjson.h"
#include "TimeViewerSetting.h"
#include "ui_TimeViewer.h"

class TimeViewer : public QMainWindow {
	Q_OBJECT
public:
	explicit TimeViewer(QWidget* parent = nullptr);
	~TimeViewer();
private:
	QAction* CalibrationAction;
	QAction* SettingAction;
	QSettings* Options;
	QTimer* Timer;
	TimeViewerSetting* Setting;
	Ui::TimeViewerClass UI;
	QDateTime Time;
public Q_SLOTS:
	void Increase();
	void Calibration();
Q_SIGNALS:

};