#pragma once

#include <QAction>
#include "ui_IPO.h"

class IPO : public QMainWindow {
	Q_OBJECT
public:
	explicit IPO(QWidget* parent = nullptr);
	~IPO();
private:
	QAction* Update;
	Ui::IPOClass UI;
public Q_SLOTS:

Q_SIGNALS:

};