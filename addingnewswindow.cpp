#include "addingnewswindow.h"

AddingNewsWindow::AddingNewsWindow()
{
    //Мейновый лайаут
    QVBoxLayout* mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    this->setStyleSheet("background-color: lightyellow");

    //Надпись "Тема"
    QLabel* Title = new QLabel("Тема:");
    mainLayout->addWidget(Title);

    //Эдит титла
    _lTitle = new QLineEdit;
    mainLayout->addWidget(_lTitle);

    //Надпись "Тект новости"
    QLabel* Text = new QLabel("Текст новости:");
    mainLayout->addWidget(Text);

    //Эдит титла
    _tText = new QTextEdit;
    _tText->setMinimumSize(600,350);
    mainLayout->addWidget(_tText);

    //Лайаут с катигорией и автором
    QHBoxLayout* catAndAutLayout = new QHBoxLayout;
    mainLayout->addLayout(catAndAutLayout);

    //Надпись "Категория"
    QLabel* Category = new QLabel("Категория:");
    catAndAutLayout->addWidget(Category);

    //Выплывающий список с катигориями
    _cbCategories = new QComboBox;
    catAndAutLayout->addWidget(_cbCategories);
    //Заполняем его катигориями
    for (int i = 0; i < News::getAllCategories().length(); i++)
        _cbCategories->addItem(News::getAllCategories().at(i));

    //Надпись "Автор"
    QLabel* Author = new QLabel("Автор:");
    catAndAutLayout->addWidget(Author);

    //Эдит автора
    _lAuthor = new QLineEdit("Неизвестный");
    catAndAutLayout->addWidget(_lAuthor);

    //Кнопка "Опубликовать новость"
    QPushButton* pbCommitNews = new QPushButton("Опубликовать новость");
    pbCommitNews->setStyleSheet("background-color: lightgray");
    mainLayout->addWidget(pbCommitNews);
    connect(pbCommitNews, SIGNAL(pressed()), this, SLOT(btAddNewsPressed()));
}

void AddingNewsWindow::btAddNewsPressed()
{
    //Создаем новость
    News news(QDate::currentDate().toString("dd.MM.yyyy") + " " + QTime::currentTime().toString("hh:mm"),
              _lAuthor->text(), _lTitle->text(), _tText->toPlainText(), News::getCategoryByString(_cbCategories->currentText()));

    //Отсылаем сигнал на добавление
    emit commitNews(news);

    //Закрываем окно
    close();
}
