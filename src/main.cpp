#include "DealBox.h"
#include <QtWidgets/QApplication>
#include <QDir>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    QDir Config(QDir::homePath() + "/AppData/Local/DealBox/config");
    if (!Config.exists()) {
        Config.mkpath(Config.absolutePath());
    }
    Config.setPath(QDir::homePath() + "/AppData/Local/DealBox/cache");
    if (!Config.exists()) {
        Config.mkpath(Config.absolutePath());
    }

    DealBox w;
    w.show();
    return a.exec();
}
