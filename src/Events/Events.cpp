#include "Events/Events.h"
#include <qmessagebox.h>

Events::Events(QWidget* parent) :QMainWindow(parent) {
	UI.setupUi(this);
	Update = new QAction(QIcon(":/image/Reload.svg"), "刷新", this);
	Request = new EventsRequest();

	this->addAction(Update);
	this->setContextMenuPolicy(Qt::ActionsContextMenu);

    HeardList = { "时间" , "国家" , "事件" , "重要程度" , "今值" , "预期" , "前值" };
    UI.Table->setSelectionBehavior(QAbstractItemView::SelectItems);
    UI.Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    UI.Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    UI.Table->setSelectionMode(QAbstractItemView::SingleSelection);
    UI.Table->setColumnCount(HeardList.count());
    UI.Table->setHorizontalHeaderLabels(HeardList);

	connect(Update, &QAction::triggered, this, &Events::Refresh);
	connect(Request, &EventsRequest::Finish, this, &Events::Finish);
}

void Events::Refresh() {
	if (Request->isRunning()) {
		QMessageBox::information(this, "提示", "正在请求,请稍等...");
	}
	else {
		Request->start();
	}
}

void Events::Finish(QVector<EventsRequest::EventItem> Data) {
	for (int Index = 0; Index < Data.size(); Index++) {
		UI.Table->insertRow(Index);
		UI.Table->setItem(Index, 0, new QTableWidgetItem(Data.at(Index).Time));
		UI.Table->setItem(Index, 1, new QTableWidgetItem(Data.at(Index).Country));
		UI.Table->setItem(Index, 2, new QTableWidgetItem(Data.at(Index).Title));
		switch (Data.at(Index).Importance) {
		case 1: {
			UI.Table->setItem(Index, 3, new QTableWidgetItem("⭐"));
			break;
		}
		case 2: {
			UI.Table->setItem(Index, 3, new QTableWidgetItem("⭐⭐"));
			break;
		}
		case 3: {
			UI.Table->setItem(Index, 3, new QTableWidgetItem("⭐⭐⭐"));
			break;
		}
		}
		UI.Table->setItem(Index, 4, new QTableWidgetItem(Data.at(Index).Actual));
		UI.Table->setItem(Index, 5, new QTableWidgetItem(Data.at(Index).Forecast));
		UI.Table->setItem(Index, 6, new QTableWidgetItem(Data.at(Index).Previous));
	}
}

Events::~Events() {
	delete Update;
	delete Request;
}