#include "Events/Events.h"

Events::Events(QWidget* parent) :QMainWindow(parent) {
	UI.setupUi(this);
	Update = new QAction(QIcon(":/image/Reload.svg"), "刷新", this);

	this->addAction(Update);
	this->setContextMenuPolicy(Qt::ActionsContextMenu);

	QStringList HeardList = { "国家","日期","事件"};
	
	//UI.Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//UI.Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//UI.Table->verticalHeader()->hide();
	UI.Table->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
	UI.Table->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
	UI.Table->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
	UI.Table->setColumnCount(HeardList.count());
	UI.Table->setHorizontalHeaderLabels(HeardList);

	
}

Events::~Events() {
	delete Update;
}