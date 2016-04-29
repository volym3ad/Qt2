#include "newswidget.h"

NewsWidget::NewsWidget(News news, QWidget *parent) :
    QWidget(parent)
{
    //Мейновый лайаут
    QHBoxLayout* mainLayout = new QHBoxLayout;
    this->setLayout(mainLayout);

    //Левый лайаут
    QVBoxLayout* leftLayout = new QVBoxLayout;
    leftLayout->setAlignment(Qt::AlignTop);
    leftLayout->setSpacing(10);
    mainLayout->addLayout(leftLayout);

    //Лейбл с датой + именем автора
    QLabel* dataAuthorLabel = new QLabel(news.getDate() + "\n" + news.getAuthor());
    leftLayout->addWidget(dataAuthorLabel);

    //Правый лайаут
    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->setAlignment(Qt::AlignTop);
    rightLayout->setSpacing(10);
    mainLayout->addLayout(rightLayout);

    //Лейбл с заглавием
    QLabel* titleLabel = new QLabel(news.getTitle());
    //Перенос строки - он
    //если строка виходит за пределы заданного прямоугольника, она будет перенесена
    titleLabel->setWordWrap(true);
    //Меняем размер текста
    QFont font = titleLabel->font();
    font.setPointSize(14);
    font.setBold(true); // жирный шрифт
    titleLabel->setFont(font);
    rightLayout->addWidget(titleLabel);

    //Лейбл с текстом новости
    QLabel* textLabel = new QLabel(news.getText());
    //Перенос строки - он
    textLabel->setWordWrap(true);
    rightLayout->addWidget(textLabel);

    //Лейбл с катигорией
    QLabel* textCategory = new QLabel("Катигория: " + News::getCategoryString(news.getCategory()));
    rightLayout->addWidget(textCategory, 0, Qt::AlignRight);
}
