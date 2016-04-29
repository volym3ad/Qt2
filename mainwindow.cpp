#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    newsFileName = "news.txt";

    _currentCategory = News::None;

    _newsContainer = NULL;

    //Мейновый лайаут
    QHBoxLayout* mainLayout = new QHBoxLayout();
    this->setLayout(mainLayout);

    //Если новости не грузятся
    if (!loadNews())
    {
        //Ошибка
        QLabel* lError = new QLabel("Ошибка при загрузке новости");
        lError->setAlignment(Qt::AlignCenter);
        //Меняем размер текста
        QFont font = lError->font();
        font.setPointSize(18);
        font.setBold(true);
        lError->setFont(font);
        mainLayout->addWidget(lError);

        return;
    }

    //Левый лайаут
    QVBoxLayout* leftLayout = new QVBoxLayout;
    leftLayout->setAlignment(Qt::AlignTop);
    leftLayout->setSpacing(10);
    mainLayout->addLayout(leftLayout);

    //Лайаут с кнопками менюшки
    QVBoxLayout* menuLayout = new QVBoxLayout;
    menuLayout->setAlignment(Qt::AlignTop);
    menuLayout->setSpacing(10);
    leftLayout->addLayout(menuLayout);

    //Менюшка
    //Кнопка добавления
    QPushButton* pbAddNews = new QPushButton("+\nДобавить\nновость");
    pbAddNews->setMaximumSize(70, 70);
    pbAddNews->setMinimumSize(70, 70);
    pbAddNews->setStyleSheet("background-color: lightgray");
    menuLayout->addWidget(pbAddNews);
    connect(pbAddNews, SIGNAL(pressed()), this, SLOT(btAddNewsPressed()));

    //Лайаут с катигориями
    QVBoxLayout* categoriesLayout = new QVBoxLayout;
    categoriesLayout->setAlignment(Qt::AlignTop);
    categoriesLayout->setSpacing(10);
    leftLayout->addLayout(categoriesLayout);

    //Надпись "Категории"
    QLabel* lCategories = new QLabel("Категории:");
    lCategories->setAlignment(Qt::AlignCenter);
    categoriesLayout->addWidget(lCategories);

    //Кнопка катигории "Все"
    QPushButton* pbCrAll = new QPushButton("Все");
    pbCrAll->setEnabled(false);
    pbCrAll->setStyleSheet("background-color: lightgray");
    categoriesLayout->addWidget(pbCrAll);
    connect(pbCrAll, SIGNAL(pressed()), this, SLOT(btCategoryPressed()));
    connect(this, SIGNAL(setAllCatButtonsEnabled(bool)), pbCrAll, SLOT(setEnabled(bool)));

    //Создаем кнопки для всех катигорий с 1(не 0), так как нулевая - это пустая катигория
    for (int i = 1; i < News::getAllCategories().length(); i++)
    {
        //Кнопка катигории
        QPushButton* pbCategory = new QPushButton(News::getAllCategories().at(i));
        pbCategory->setStyleSheet("background-color: lightgray");
        categoriesLayout->addWidget(pbCategory);
        connect(pbCategory, SIGNAL(pressed()), this, SLOT(btCategoryPressed()));

        connect(this, SIGNAL(setAllCatButtonsEnabled(bool)), pbCategory, SLOT(setEnabled(bool)));
    }

    //Правый лайаут
    QVBoxLayout* rightLayout = new QVBoxLayout();
    mainLayout->addLayout(rightLayout);

    //Скрол эриа
    _scrollArea = new QScrollArea;
    _scrollArea->setWidgetResizable(true);
    _scrollArea->setMinimumSize(600, 450);
    rightLayout->addWidget(_scrollArea);

    reloadNewsView();
}
void MainWindow::btAddNewsPressed()
{
    AddingNewsWindow* addingNewsWindow = new AddingNewsWindow;
    connect(addingNewsWindow, SIGNAL(commitNews(News)), this, SLOT(addNews(News))); //Соидиняем, что бы при нажатии кнопки в диалоге, новость добавлялась
    addingNewsWindow->setAttribute(Qt::WA_DeleteOnClose); //При закрытии будет удалятся полностью
    addingNewsWindow->exec(); //Открываем диалог
}

void MainWindow::btCategoryPressed()
{
    //Вытягиваем ссылку на кнопку
    QPushButton* pressedButton = (QPushButton*)sender();

    //Делаем все кнопки активными
    emit setAllCatButtonsEnabled(true);

    //Делаем нажатую кнопку неактивной
    pressedButton->setEnabled(false);

    //Меняем катигорию
    _currentCategory = News::getCategoryByString(pressedButton->text());

    //Перегружаем новости с сортировкой
    reloadNewsView(_currentCategory);
}

void MainWindow::addNews(News news)
{
    //Добавляем новость
    _news.append(news);

    //Сохраняем новости
    saveNews();

    //Перегружаем новости с сортировкой
    reloadNewsView(_currentCategory);
}

void MainWindow::reloadNewsView(News::Categories categoryFilter)
{
    //Удаляем контейнер под новости, если он есть
    if (_newsContainer != NULL)
        delete _newsContainer;

    //Добавляем виджет с новостями
    _newsContainer = new QWidget;

    //Список с новостями
    QVBoxLayout* newsLayout = new QVBoxLayout;
    _newsContainer->setLayout(newsLayout);

    _scrollArea->setWidget(_newsContainer);

    for (int i = 0; i < _news.length(); i++)
    {
        //Если есть фильтр, то фильтруем
        if (categoryFilter != News::None)
            if (_news.at(i).getCategory() != categoryFilter)
                continue;

        NewsWidget* newsWidget = new NewsWidget(_news.at(i));
        newsWidget->setMaximumWidth(550);

        newsLayout->addWidget(newsWidget);
    }
}

//Возвращает булл, true - все ок, false - ошибка
bool MainWindow::loadNews()
{
    //Чистим массив новостей
    _news.clear();

    QFile file(newsFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

    QTextStream in(&file);
    QString line = in.readLine();

    //Каунтер строчек
    int lineCounter = 0;

    //Инфа о новости
    QString date = "Нет даты";
    QString posterName = "Ноунейм";
    News::Categories category = News::None;
    QString title = "Нет заглавия";
    QString text = "Нет текста";

    while (!line.isNull())
    {
        //В зависимости от каунтера, считываем нужную часть новости
        switch (lineCounter) {
        case 0:
            date = line;
            break;
        case 1:
            posterName = line;
            break;
        case 2:
            category = News::getCategoryByString(line);
            break;
        case 3:
            title = line;
            break;
        case 4:
            text = line;

            //Создаем новость
            News news(date, posterName, title, text, category);
            //Добавляем новость в лист
            _news.append(news);

            //Обнуляем
            date = "Нет даты";
            posterName = "Ноунейм";
            category = News::None;
            title = "Нет заглавия";
            text = "Нет текста";

            break;
        }

        //Переходим к некст строке
        line = in.readLine();

        if (lineCounter == 4)
        //{
        /*for (int i=0; i<text.length(); i++)
        {
            if (text[i] != '|')
                //t = in.readAll();
                continue;

            else
                lineCounter = 0;
            }
        }*/
         lineCounter = 0;

         else
            lineCounter++;
        }

    return true;
}

//Возвращает булл, true - все ок, false - ошибка
bool MainWindow::saveNews()
{
    QFile file(newsFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);

    for (int i = 0; i < _news.length(); i++)
    {
        out << _news.at(i).getDate() << "\n"
            << _news.at(i).getAuthor() << "\n"
            << News::getCategoryString(_news.at(i).getCategory()) << "\n"
            << _news.at(i).getTitle() << "\n"
            << _news.at(i).getText() << "\n" ;
    }

    return true;
}
