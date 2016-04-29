#ifndef ADDINGNEWSWINDOW_H
#define ADDINGNEWSWINDOW_H

#include <QDialog>
#include <QtWidgets>

#include "news.h"

class AddingNewsWindow : public QDialog
{
    Q_OBJECT
public:
    AddingNewsWindow();

private:
    //Нужные лайн эдиты
    QLineEdit* _lAuthor;
    QLineEdit* _lTitle;
    //Большой текст эдит
    QTextEdit* _tText;

    //Комбокс с катигориями
    QComboBox* _cbCategories;

private slots:
    //Вызывается при нажатии "Опубликовать новость"
    void btAddNewsPressed();

signals:
    //Отсылается при нажатии "Опубликовать новость"
    void commitNews(News news);
};

#endif // ADDINGNEWSWINDOW_H
