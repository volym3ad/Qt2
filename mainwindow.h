#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtWidgets>

#include "newswidget.h"
#include "addingnewswindow.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

    //Имя файла с новостями, или его путь + название от текущей папки
    QString newsFileName;

    //Загрузка новостей с файла "newsFileName"
    bool loadNews();

    //Сохранение новостей в файл "newsFileName"
    bool saveNews();

    void reloadNewsView(News::Categories categoryFilter = News::None);

private:
    //Лист с новостями
    QList<News> _news;

    //Контейнер с новостями
    QWidget* _newsContainer;

    //Скрол эриа, что-бы скролить новости
    QScrollArea* _scrollArea;

    //Текущая категория
    News::Categories _currentCategory;

public slots:
    //Вызывается при добавлении катигории в окне добавления
    void addNews(News news);

private slots:
    //Ф-я вызывается при нажатии кнопки добавить новость
    void btAddNewsPressed();
    //Ф-я вызывается при нажатии кнопки катигории
    void btCategoryPressed();

signals:
    //Отправляем кнопкам катигории что бы сделать неактивными
    void setAllCatButtonsEnabled(bool enabled);
};

#endif // MAINWINDOW_H
