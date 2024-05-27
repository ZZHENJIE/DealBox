#include "IPO/IPO.h"
#include <qmessagebox.h>

GumboNode* FindElement(const GumboVector Root, QStringList List) {
    QString Element = List[0];
    List.pop_front();
    for (int Index = 0; Index < Root.length; Index++) {
        GumboNode* Child = (GumboNode*)Root.data[Index];
        if (Element.indexOf('.') == -1) {
            if (Child->type == GUMBO_NODE_ELEMENT && strcmp(gumbo_normalized_tagname(Child->v.element.tag), Element.toStdString().c_str()) == 0) {
                if (List.isEmpty()) {
                    return Child;
                }
                else {
                    if (*Child->v.element.children.data != NULL) {
                        return FindElement(Child->v.element.children, List);
                    }
                }
            }
        }
        else {
            QString Tag = Element.split('.').at(0);
            QString Class = Element.split('.').at(1);
            if (Child->type == GUMBO_NODE_ELEMENT && strcmp(gumbo_normalized_tagname(Child->v.element.tag), Tag.toStdString().c_str()) == 0) {
                GumboAttribute* Attribute = gumbo_get_attribute(&Child->v.element.attributes, "class");
                if (Attribute != NULL && strcmp(Attribute->value, Class.toStdString().c_str()) == 0) {
                    if (List.isEmpty()) {
                        return Child;
                    }
                    else {
                        if (*Child->v.element.children.data != NULL) {
                            return FindElement(Child->v.element.children, List);
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

IPO::IPO(QWidget* parent) :QMainWindow(parent) {
	UI.setupUi(this);

	Update = new QAction(QIcon(":/image/Reload.svg"), "刷新", this);
    Request = new IPORequest();

	this->addAction(Update);
	this->setContextMenuPolicy(Qt::ActionsContextMenu);

    HeardList = {"公司","代码","牵头经理","股份（百万）","最低价","最高价","预估 $ 成交量","预计交易时间"};
    UI.Table->setSelectionBehavior(QAbstractItemView::SelectItems);
    UI.Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    UI.Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    UI.Table->setSelectionMode(QAbstractItemView::SingleSelection);
    UI.Table->setColumnCount(HeardList.count());
    UI.Table->setHorizontalHeaderLabels(HeardList);

    connect(Update, &QAction::triggered, this, &IPO::Refresh);
    connect(Request, &IPORequest::Finish, this, &IPO::Finish);
}

void IPO::Finish(QVector<IPORequest::IPONode> Data) {
    UI.Table->clearContents();
    for (int Index = 0; Index < Data.size(); Index++) {
        UI.Table->insertRow(Index);
        UI.Table->setItem(Index, 0, new QTableWidgetItem(Data.at(Index).Company));
        UI.Table->setItem(Index, 1, new QTableWidgetItem(Data.at(Index).Symbol));
        UI.Table->setItem(Index, 2, new QTableWidgetItem(Data.at(Index).Managers));
        UI.Table->setItem(Index, 3, new QTableWidgetItem(Data.at(Index).Shares));
        UI.Table->setItem(Index, 4, new QTableWidgetItem(Data.at(Index).PriceLow));
        UI.Table->setItem(Index, 5, new QTableWidgetItem(Data.at(Index).PriceHigh));
        UI.Table->setItem(Index, 6, new QTableWidgetItem(Data.at(Index).Volume));
        UI.Table->setItem(Index, 7, new QTableWidgetItem(Data.at(Index).ExpectedDate));
    }
}

void IPO::Refresh() {
    if (Request->isRunning()) {
        QMessageBox::information(this, "提示", "正在请求,请稍等...");
    }else {
        Request->start();
    }
}

IPO::~IPO() {
	delete Update;
    delete Request;
}