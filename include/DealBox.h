#pragma once

#include "TimeViewer/TimeViewer.h"
#include "Events/Events.h"
#include "IPO/IPO.h"
#include "Setting/Setting.h"
#include "ui_DealBox.h"

class DealBox : public QMainWindow{
    Q_OBJECT
public:
    explicit DealBox(QWidget *parent = nullptr);
    ~DealBox();
private:
    Ui::DealBoxClass ui;
    TimeViewer* TimeViewerWindow;
    Events* EventsWindow;
    IPO* IPOWindow;
    Setting* SettingWindow;
public Q_SLOTS:
    void SaveLayout();
    void Close();
Q_SIGNALS:

};
