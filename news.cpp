#include "news.h"

News::News()
{
}
News::News(QString date, QString author, QString title, QString text, News::Categories category)
{
    _date = date;
    _author = author;
    _title = title;
    _text = text;
    _category = category;
}
QString News::getAuthor() const
{
    return _author;
}

QString News::getDate() const
{
    return _date;
}

QString News::getText() const
{
    return _text;
}

QString News::getTitle() const
{
    return _title;
}

News::Categories News::getCategory() const
{
    return _category;
}

QString News::getCategoryString(News::Categories category)
{
    if (category < getAllCategories().length())
        return getAllCategories().at(category);

    return getAllCategories().at(0);
}

News::Categories News::getCategoryByString(QString categoryString)
{
    for (int i = 0; i < getAllCategories().length(); i++)
        if (getAllCategories().at(i) == categoryString)
            return (News::Categories)i;

    return News::None;
}

QList<QString> News::getAllCategories()
{
    QList<QString> categoriesList;
    categoriesList << "Без_катигории" << "Мир" << "Украина" << "Спорт" << "Политика" << "Технологии" ;

    return categoriesList;
}
