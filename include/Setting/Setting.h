#pragma once

#include "cpr/cpr.h"
#include "ui_Setting.h"

class Setting : public QMainWindow {
	Q_OBJECT
public:
	explicit Setting(QWidget* parent = nullptr);
	~Setting();
private:
	Ui::SettingClass UI;
	cpr::Response Response;
public Q_SLOTS:
	void Check_Update();
Q_SIGNALS:

};