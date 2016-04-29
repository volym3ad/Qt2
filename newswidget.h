#ifndef NEWSWIDGET_H
#define NEWSWIDGET_H

#include <QWidget>
#include <QtWidgets>

#include "news.h"

class NewsWidget : public QWidget
{
    Q_OBJECT
public:
    NewsWidget(News news, QWidget *parent = 0);

};

#endif // NEWSWIDGET_H
