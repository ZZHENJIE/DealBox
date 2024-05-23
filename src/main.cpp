#include "DealBox.h"
#include <QtWidgets/QApplication>
#include <QDir>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    QDir Config("./config/");
    if (!Config.exists()) {
        Config.mkdir(Config.absolutePath());
    }

    DealBox w;
    w.show();
    return a.exec();
}
