#pragma once

#include <QMainWindow>
#include <QAction>
#include <QDateTime>
#include <qthread>
#include "ui_Events.h"
#include "yyjson.h"
#include "cpr/cpr.h"

class EventsRequest : public QThread {
	Q_OBJECT
public:
	struct EventItem {
		QString Time;
		QString Country;
		QString Title;
		QString Actual;
		QString Forecast;
		QString Previous;
		int Importance;
	};
protected:
	virtual void run() override {
		cpr::Response Response = cpr::Get(cpr::Url{ "https://api-one-wscn.awtmt.com/apiv1/finance/macrodatas" });
		QVector<EventItem> Data;

		yyjson_doc* Doc = yyjson_read(Response.text.c_str(), Response.text.size(), YYJSON_READ_NOFLAG);
		yyjson_val* Message = yyjson_obj_get(Doc->root, "message");
		if (strcmp(yyjson_get_str(Message), "OK") == 0) {
			Data.clear();

			yyjson_val* Items = yyjson_obj_get(yyjson_obj_get(Doc->root, "data"), "items");
			yyjson_val* Value;
			yyjson_arr_iter Iter = yyjson_arr_iter_with(Items);
			while ((Value = yyjson_arr_iter_next(&Iter))) {
				yyjson_val* country = yyjson_obj_get(Value, "country");
				if (QString(yyjson_get_str(country)) == "美国") {
					yyjson_val* public_date = yyjson_obj_get(Value, "public_date");
					yyjson_val* title = yyjson_obj_get(Value, "title");
					yyjson_val* unit = yyjson_obj_get(Value, "unit");
					yyjson_val* importance = yyjson_obj_get(Value, "importance");
					yyjson_val* actual = yyjson_obj_get(Value, "actual");
					yyjson_val* forecast = yyjson_obj_get(Value, "forecast");
					yyjson_val* previous = yyjson_obj_get(Value, "previous");

					QString Actual;
					if (strcmp(yyjson_get_str(actual), "") == 0) {
						Actual = "--";
					}
					else {
						Actual = QString(yyjson_get_str(actual)) + QString(yyjson_get_str(unit));
					}

					QString Forecast;
					if (strcmp(yyjson_get_str(forecast), "") == 0) {
						Forecast = "--";
					}
					else {
						Forecast = QString(yyjson_get_str(forecast)) + QString(yyjson_get_str(unit));
					}

					QString Previous;
					if (strcmp(yyjson_get_str(previous), "") == 0) {
						Previous = "--";
					}
					else {
						Previous = QString(yyjson_get_str(previous)) + QString(yyjson_get_str(unit));
					}

					Data.push_back(EventItem{
						QDateTime::fromSecsSinceEpoch(yyjson_get_int(public_date)).time().toString(Qt::ISODate),
						yyjson_get_str(country),
						yyjson_get_str(title),
						Actual,
						Forecast,
						Previous,
						yyjson_get_int(importance)
					});
				}
			}
		}
		yyjson_doc_free(Doc);

		emit Finish(Data);
	}
Q_SIGNALS:
	void Finish(QVector<EventItem> Data);
};

class Events : public QMainWindow {
	Q_OBJECT
public:
	explicit Events(QWidget* parent = nullptr);
	~Events();
private:
	QAction * Update;
	EventsRequest* Request;
	QStringList HeardList;
	Ui::EventsClass UI;
public Q_SLOTS:
	void Refresh();
	void Finish(QVector<EventsRequest::EventItem> Data);
Q_SIGNALS:

};