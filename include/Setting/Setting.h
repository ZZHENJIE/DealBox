#pragma once

#include "cpr/cpr.h"
#include "ui_Setting.h"
#include <qsettings.h>
#include <qmessagebox.h>
#include <qthread.h>
#include <QProgressDialog>

class SettingRequest :public QThread {
	Q_OBJECT
public:
	void SetDownloadUrl(QString Url);
private:
	QString Url;
protected:
	virtual void run() override;
Q_SIGNALS:
	void DownloadProgress(double Progress,float downloadTotal, float downloadNow);
};

class Setting : public QMainWindow {
	Q_OBJECT
public:
	explicit Setting(QWidget* parent = nullptr);
	~Setting();
	void SetTheme(QVariant value);
private:
	Ui::SettingClass UI;
	QSettings * Options;
	SettingRequest* Request;
	QProgressDialog* DownloadDialog;
public Q_SLOTS:
	void Check_Update();
	void Select_Theme(int index);
	void DownloadProgress(double Progress, float downloadTotal, float downloadNow);
Q_SIGNALS:

};