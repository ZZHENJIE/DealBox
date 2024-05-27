#include "DealBox.h"
#include <QDir>
#include <QFile>
#include <qmessagebox.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

DealBox::DealBox(QWidget *parent):QMainWindow(parent){
    this->setFixedSize(300, 30);
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint );
    ui.setupUi(this);

    TimeViewerWindow = new TimeViewer(nullptr);
    EventsWindow = new Events(nullptr);
    IPOWindow = new IPO(nullptr);
    SettingWindow = new Setting(nullptr);

    QFile Config(QDir::homePath() + "/AppData/Local/DealBox/config/window.json");
    if (Config.exists()) {
        Config.open(QFile::ReadOnly);
        QJsonDocument Doc = QJsonDocument::fromJson(Config.readAll());

        QJsonObject DealBox = Doc.object().value("DealBox").toObject();
        QJsonObject Events = Doc.object().value("Events").toObject();
        QJsonObject IPO = Doc.object().value("IPO").toObject();
        QJsonObject TimeViewer = Doc.object().value("TimeViewer").toObject();

        this->move(DealBox.value("WindowX").toInt(), DealBox.value("WindowY").toInt());

        EventsWindow->setGeometry(Events.value("WindowX").toInt(), Events.value("WindowY").toInt(), Events.value("WindowW").toInt(), Events.value("WindowH").toInt());
        EventsWindow->setVisible(Events.value("Visible").toBool());

        IPOWindow->setGeometry(IPO.value("WindowX").toInt(), IPO.value("WindowY").toInt(), IPO.value("WindowW").toInt(), IPO.value("WindowH").toInt());
        IPOWindow->setVisible(IPO.value("Visible").toBool());
        
        TimeViewerWindow->setGeometry(TimeViewer.value("WindowX").toInt(), TimeViewer.value("WindowY").toInt(), TimeViewer.value("WindowW").toInt(), TimeViewer.value("WindowH").toInt());
        TimeViewerWindow->setVisible(TimeViewer.value("Visible").toBool());

        Config.close();
    }

    connect(ui.TimeViewer, &QPushButton::clicked, TimeViewerWindow, &TimeViewer::show);
    connect(ui.Events, &QPushButton::clicked, EventsWindow, &Events::show);
    connect(ui.IPO, &QPushButton::clicked, IPOWindow, &IPO::show);
    connect(ui.Setting, &QPushButton::clicked, SettingWindow, &Setting::show);
    connect(ui.SaveLayout, &QPushButton::clicked, this, &DealBox::SaveLayout);
    connect(ui.Close, &QPushButton::clicked, this, &DealBox::Close);
}

void DealBox::Close() {
    QMessageBox::StandardButtons Reply = QMessageBox::warning(this, "保存布局", "是否保存布局?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    
    switch (Reply) {
        case QMessageBox::Yes: {
            SaveLayout();
            break;
        }
        case QMessageBox::Cancel: {
            return;
        }
    }

    delete TimeViewerWindow;
    delete EventsWindow;
    delete IPOWindow;
    delete SettingWindow;
    this->close();
}

void DealBox::SaveLayout() {
    QFile Config(QDir::homePath() + "/AppData/Local/DealBox/config/window.json");
    Config.open(QFile::WriteOnly);

    QJsonObject Root;
    QJsonObject DealBox;

    DealBox["WindowX"] = pos().x();
    DealBox["WindowY"] = pos().y();

    QJsonObject TimeViewer;

    TimeViewer["WindowX"] = TimeViewerWindow->pos().x();
    TimeViewer["WindowY"] = TimeViewerWindow->pos().y();
    TimeViewer["WindowW"] = TimeViewerWindow->size().width();
    TimeViewer["WindowH"] = TimeViewerWindow->size().height();
    TimeViewer["Visible"] = TimeViewerWindow->isVisible();

    QJsonObject Events;

    Events["WindowX"] = EventsWindow->pos().x();
    Events["WindowY"] = EventsWindow->pos().y();
    Events["WindowW"] = EventsWindow->size().width();
    Events["WindowH"] = EventsWindow->size().height();
    Events["Visible"] = EventsWindow->isVisible();

    QJsonObject IPO;

    IPO["WindowX"] = IPOWindow->pos().x();
    IPO["WindowY"] = IPOWindow->pos().y();
    IPO["WindowW"] = IPOWindow->size().width();
    IPO["WindowH"] = IPOWindow->size().height();
    IPO["Visible"] = IPOWindow->isVisible();

    Root["DealBox"] = DealBox;
    Root["TimeViewer"] = TimeViewer;
    Root["Events"] = Events;
    Root["IPO"] = IPO;

    QJsonDocument Doc = QJsonDocument(Root);

    Config.write(Doc.toJson());

    Config.close();
}

DealBox::~DealBox(){

}
