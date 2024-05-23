#pragma once

#include <QTimer>
#include <QTime>
#include <QAction>
#include "yyjson.h"
#include "ui_TimeViewer.h"

class TimeViewer : public QMainWindow {
	Q_OBJECT
public:
	explicit TimeViewer(QWidget* parent = nullptr);
	~TimeViewer();
private:
	QAction* Calibration;
	QAction* Setting;
	Ui::TimeViewerClass UI;
public Q_SLOTS:

Q_SIGNALS:

};