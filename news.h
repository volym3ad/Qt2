#ifndef NEWS_H
#define NEWS_H

#include <QtWidgets>
#include <QtGui>

//В этом классе будет свя инфа о новости
class News
{
public:
    //Катигории
    enum Categories
    {
        None,
        World,
        Ukraine,
        Sport,
        Politic,
        Tech
    };

    News();
    News(QString date, QString author, QString title, QString text, News::Categories category = News::None); //Если нет катигории, то - общая (None)

    //Вытаскивание инфы
    QString getDate() const;
    QString getAuthor() const;
    QString getTitle() const;
    QString getText() const;
    News::Categories getCategory() const;
    //Все катигории в стрингу
    static QList<QString> getAllCategories();

    //Категории в стринг и обратно
    static QString getCategoryString(News::Categories category);
    static News::Categories getCategoryByString(QString categoryString);

private:
    //Дата создания новости
    QString _date;
    //Имя того, кто запостил
    QString _author;
    //Заглавие новости
    QString _title;
    //Текст новости
    QString _text;
    //Категория новости
    News::Categories _category;
};

#endif // NEWS_H
