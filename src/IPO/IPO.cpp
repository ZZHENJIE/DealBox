#include "IPO/IPO.h"

IPO::IPO(QWidget* parent) :QMainWindow(parent) {
	UI.setupUi(this);

	Update = new QAction(QIcon(":/image/Reload.svg"), "刷新", this);

	this->addAction(Update);
	this->setContextMenuPolicy(Qt::ActionsContextMenu);
}

IPO::~IPO() {
	delete Update;
}