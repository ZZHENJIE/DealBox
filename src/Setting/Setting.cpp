#include "Setting/Setting.h"
#include <qapplication.h>
#include <QFile>
#include <QDir>

#define VERSION "Bata 0.0.1"

Setting::Setting(QWidget* parent) :QMainWindow(parent) {
	UI.setupUi(this);

	Options = new QSettings(QDir::homePath() + "/AppData/Local/DealBox/config/setting.ini", QSettings::Format::IniFormat);
	Request = new SettingRequest();
	DownloadDialog = nullptr;

	QFile Markdown(":/document/About.md");
	Markdown.open(QFile::ReadOnly);
	UI.About->setMarkdown(Markdown.readAll());
	Markdown.close();

	Markdown.setFileName(":/document/Update_Explain.md");
	Markdown.open(QFile::ReadOnly);
	UI.Update_Explain->setMarkdown(Markdown.readAll());
	Markdown.close();

	UI.Current_Version->setText("当前版本:" + QString(VERSION));

	UI.Select_Theme->addItem("黑暗", ":/qdarkstyle/dark/darkstyle.qss");
	UI.Select_Theme->addItem("明亮", ":/qdarkstyle/light/lightstyle.qss");
	UI.Select_Theme->addItem("默认");

	connect(UI.About_QT, &QPushButton::clicked, qApp, &QApplication::aboutQt);
	connect(UI.Check_Update, &QPushButton::clicked, this, &Setting::Check_Update);
	connect(UI.Select_Theme, &QComboBox::currentIndexChanged, this, &Setting::Select_Theme);
	connect(Request, &SettingRequest::DownloadProgress, this, &Setting::DownloadProgress);

	SetTheme(Options->value("Theme"));
}

void Setting::Select_Theme(int index) {
	Options->setValue("Theme", UI.Select_Theme->itemData(index));
	SetTheme(Options->value("Theme"));
}

void Setting::SetTheme(QVariant value) {
	if (!value.isNull()) {
		QFile Theme(value.toString());
		if (!Theme.exists()) {
			QMessageBox::warning(this, "提示", "无法打开:" + value.toString());
		}else {
			Theme.open(QFile::ReadOnly | QFile::Text);
			QTextStream ts(&Theme);
			qApp->setStyleSheet(ts.readAll());
		}
	}else {
		qApp->setStyleSheet("");
	}
}

bool ProgressCallback(cpr::cpr_off_t downloadTotal, cpr::cpr_off_t downloadNow, cpr::cpr_off_t uploadTotal, cpr::cpr_off_t uploadNow, intptr_t userdata) {

	if (downloadNow > 0) {
		SettingRequest* Dialog = reinterpret_cast<SettingRequest*>(userdata);
		double downloadProgress = static_cast<double>(downloadNow) / static_cast<double>(downloadTotal) * 100.0;
		emit Dialog->DownloadProgress(downloadProgress, downloadTotal / (1024.0 * 1024.0), downloadNow / (1024.0 * 1024.0));
	}

	return true;
}

void SettingRequest::run() {
	std::ofstream of((QDir::homePath() + "/AppData/Local/DealBox/cache/update.zip").toStdString(), std::ios::binary);
	cpr::Response Response = cpr::Download(of, cpr::Url{Url.toStdString()}, cpr::ProgressCallback{ProgressCallback,static_cast<int64_t>(reinterpret_cast<intptr_t>(this))});
}

void Setting::DownloadProgress(double Progress, float downloadTotal, float downloadNow) {
	DownloadDialog->setLabelText(QString::number(downloadNow,'f',2) + "MB/" + QString::number(downloadTotal,'f', 2) + "MB");
	DownloadDialog->setValue(int(Progress));
}

void Setting::Check_Update() {
	cpr::Response Response = cpr::Get(cpr::Url{ "https://api.github.com/repos/ZZHENJIE/DealBox/releases" });
	
	if (Request->isRunning()) {
		QMessageBox::information(this, "提示", "正在下载,请稍等...");
	}
	else {
		DownloadDialog = new QProgressDialog(this);
		DownloadDialog->setCancelButton(nullptr);
		DownloadDialog->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
		DownloadDialog->setWindowTitle("下载文件");
		DownloadDialog->setValue(0);
		DownloadDialog->show();
		Request->start();
	}
}

Setting::~Setting() {
	delete Options;
	delete Request;
	delete DownloadDialog;
}
