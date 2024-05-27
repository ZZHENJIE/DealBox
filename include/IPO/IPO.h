#pragma once

#include <QAction>
#include "ui_IPO.h"
#include "gumbo/gumbo.h"
#include "cpr/cpr.h"
#include <qthread>

GumboNode* FindElement(const GumboVector Root, QStringList List);

class IPORequest : public QThread {
    Q_OBJECT
public:
    struct IPONode final {
        QString Company;
        QString Symbol;
        QString Managers;
        QString Shares;
        QString PriceHigh;
        QString PriceLow;
        QString Volume;
        QString ExpectedDate;
    };
protected:
    virtual void run() override {
        cpr::SslOptions sslOpts = cpr::Ssl(cpr::ssl::VerifyPeer{ false });
        cpr::Response Response = cpr::Get(cpr::Url{ "https://www.iposcoop.com/ipo-calendar" }, sslOpts);

        GumboOutput* OutPut = gumbo_parse_with_options(&kGumboDefaultOptions, Response.text.c_str(), Response.text.size());

        GumboNode* List = FindElement(OutPut->root->v.element.children, QString("body>div>div.site-main light>div.row container>div>div>table>tbody").split('>'));

        QVector<IPONode> Data;

        if (List != NULL) {
            const GumboVector Vector = List->v.element.children;
            for (int Index = 0; Index < Vector.length; Index++) {
                GumboNode* Node = (GumboNode*)Vector.data[Index];
                if (Node->type == GUMBO_NODE_ELEMENT) {
                    GumboNode* Company = (GumboNode*)((GumboNode*)Node->v.element.children.data[1])->v.element.children.data[0];
                    GumboNode* Symbol = (GumboNode*)((GumboNode*)Node->v.element.children.data[3])->v.element.children.data[0];
                    GumboNode* Managers = (GumboNode*)Node->v.element.children.data[5];
                    GumboNode* Shares = (GumboNode*)Node->v.element.children.data[7];
                    GumboNode* PriceLow = (GumboNode*)Node->v.element.children.data[9];
                    GumboNode* PriceHigh = (GumboNode*)Node->v.element.children.data[11];
                    GumboNode* Volume = (GumboNode*)Node->v.element.children.data[13];
                    GumboNode* ExpectedDate = (GumboNode*)Node->v.element.children.data[15];

                    IPONode Item;
                    Item.Company = ((GumboNode*)Company->v.element.children.data[0])->v.text.text;
                    Item.Symbol = ((GumboNode*)Symbol->v.element.children.data[0])->v.text.text;
                    Item.Managers = ((GumboNode*)Managers->v.element.children.data[0])->v.text.text;
                    Item.Shares = ((GumboNode*)Shares->v.element.children.data[0])->v.text.text;
                    Item.PriceLow = ((GumboNode*)PriceLow->v.element.children.data[0])->v.text.text;
                    Item.PriceHigh = ((GumboNode*)PriceHigh->v.element.children.data[0])->v.text.text;
                    Item.Volume = ((GumboNode*)Volume->v.element.children.data[0])->v.text.text;
                    Item.ExpectedDate = ((GumboNode*)ExpectedDate->v.element.children.data[0])->v.text.text;
                    Data.push_back(Item);
                }
            }
        }
        gumbo_destroy_output(&kGumboDefaultOptions, OutPut);

        emit Finish(Data);
    }
Q_SIGNALS:
    void Finish(QVector<IPONode> Data);
};
class IPO : public QMainWindow {
	Q_OBJECT
public:
	explicit IPO(QWidget* parent = nullptr);
	~IPO();
private:
	QAction* Update;
    IPORequest* Request;
    QStringList HeardList;
	Ui::IPOClass UI;
public Q_SLOTS:
	void Refresh();
    void Finish(QVector<IPORequest::IPONode> Data);
Q_SIGNALS:

};