#include "Setting/Setting.h"
#include <qapplication.h>
#include <QFile>

#define VERSION "0.0.1"

Setting::Setting(QWidget* parent) :QMainWindow(parent) {
	UI.setupUi(this);
	QFile AboutMd(":/document/About.md");
	AboutMd.open(QFile::ReadOnly);
	UI.About->setMarkdown(AboutMd.readAll());
	AboutMd.close();
	UI.Current_Version->setText("当前版本:" + QString(VERSION));
	connect(UI.About_QT, &QPushButton::clicked, qApp, &QApplication::aboutQt);
	connect(UI.Check_Update, &QPushButton::clicked, this, &Setting::Check_Update);
}

void Setting::Check_Update() {
	//Response = cpr::Get(cpr::Url{ "https://api.github.com/repos/neovim/neovim/releases" });
}

Setting::~Setting() {

}

//bool ProgressCallback(cpr::cpr_off_t downloadTotal, cpr::cpr_off_t downloadNow, cpr::cpr_off_t uploadTotal, cpr::cpr_off_t uploadNow, intptr_t userdata) {
//
//
//
//    return true;
//}
//
//int main() {
//
//
//    //std::ofstream of("D:\\Downloads\\nvim-win64.zip", ios::binary);
//
//    //cpr::Response r = cpr::Download(of, cpr::Url{ "https://github.com/neovim/neovim/releases/download/v0.10.0/nvim-win64.zip" }, cpr::ProgressCallback{ ProgressCallback});
//
//    return 0;
//}
