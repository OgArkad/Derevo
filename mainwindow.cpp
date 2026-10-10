#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tickCount->setText("0");
    initTable();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::stepTick);
}

void MainWindow::initTable(){
    ui->table->horizontalHeader()->hide();
    ui->table->verticalHeader()->hide();

    ui->table->setShowGrid(false);
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setFocusPolicy(Qt::NoFocus);
    //ui->table->setSelectionMode(QAbstractItemView::NoSelection);

    ui->table->setStyleSheet(
        "QTableWidget {"
        "background-color: lightblue;"
        "}"
    );//ui->tableWidget->item(1, 2)->setBackground(QColor("#ADD8E6"));

    ui->table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->table->verticalHeader()->setDefaultSectionSize(5);

    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->table->horizontalHeader()->setDefaultSectionSize(5);
    setTable();
}

void MainWindow::setTable(){
    ui->table->setColumnCount(x);
    ui->table->setRowCount(y);

    const int w = x * 5 + 2 * ui->table->frameWidth();
    const int h = y * 5 + 2 * ui->table->frameWidth();

    ui->table->setFixedSize(w, h);
}

void MainWindow::stepTick(){
    qDebug() << "updated";
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_start_clicked()
{
    playing = true;
    timer->start(1000);

    QPalette pal = ui->start->palette();
    pal.setColor(QPalette::Button, QColor(Qt::blue));
    ui->start->setAutoFillBackground(true);
    ui->start->setPalette(pal);
    ui->start->update();

}


void MainWindow::on_stop_clicked()
{
    playing = false;
    timer->stop();
    QPalette pal = ui->start->palette();//to be continued...
    pal.setColor(QPalette::Button, QColor(Qt::black));
    ui->start->setAutoFillBackground(true);
    ui->start->setPalette(pal);
    ui->start->update();
}


void MainWindow::on_tickCount_editingFinished()
{
    return;
}


void MainWindow::on_xSize_editingFinished()
{
    bool ok;
    int t = ui->xSize->text().toInt(&ok);
    if (t <= 1 || !ok || t > 512){
        ui->xSize->setText(QString::number(x));
        qDebug() << "You must give a nuumber in this field, that ius greater than 1. Your number: " + t << "\n";
        return;
    }else
        x = t;
    setTable();
}


void MainWindow::on_ySize_editingFinished()
{
    bool ok;
    int t = ui->ySize->text().toInt(&ok);
    if (t <= 1 || !ok || t > 512){
        ui->xSize->setText(QString::number(y));
        qDebug() << "You must give a nuumber in this field, that ius greater than 1. Your number: " + t << "\n";
        return;
    }else
        y = t;
    setTable();
}

