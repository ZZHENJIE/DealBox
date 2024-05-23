#pragma once

#include <QMainWindow>
#include <QAction>
#include "ui_Events.h"

class Events : public QMainWindow {
	Q_OBJECT
public:
	explicit Events(QWidget* parent = nullptr);
	~Events();
private:
	QAction * Update;
	Ui::EventsClass UI;
public Q_SLOTS:

Q_SIGNALS:

};