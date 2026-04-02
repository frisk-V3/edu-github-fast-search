#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);

    searchField = new QLineEdit();
    searchField->setPlaceholderText("検索ワードを入力...");
    
    searchButton = new QPushButton("GitHubで高速検索");

    layout->addWidget(searchField);
    layout->addWidget(searchButton);

    setCentralWidget(centralWidget);
    setWindowTitle("GitHub Fast Searcher");

    connect(searchButton, &QPushButton::clicked, this, &MainWindow::executeSearch);
    connect(searchField, &QLineEdit::returnPressed, this, &MainWindow::executeSearch);
}

void MainWindow::executeSearch() {
    QString query = searchField->text();
    if (query.isEmpty()) return;

    // スペースなどをURLエンコード
    QString encodedQuery = QUrl::toPercentEncoding(query);
    QString urlTemplate = "https://github.com/search?q=%1";
    QString finalUrl = urlTemplate.arg(encodedQuery);

    QDesktopServices::openUrl(QUrl(finalUrl));
}
