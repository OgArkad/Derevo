#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->xSize->setMaximum(256);
    ui->xSize->setValue(128);
    ui->xSize->setMinimum(3);

    ui->ySize->setMaximum(128);
    ui->ySize->setValue(64);
    ui->ySize->setMinimum(3);
    initTable();
    timer = new QTimer(this);
    //ui->treeNumber->display(10);

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

    const int size = this->size().width()/200;

    ui->table->verticalHeader()->setMinimumSectionSize(1);//
    ui->table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->table->verticalHeader()->setDefaultSectionSize(size);

    ui->table->horizontalHeader()->setMinimumSectionSize(1);//
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->table->horizontalHeader()->setDefaultSectionSize(size);
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
    ui->tickCount->setText(QString::number(ui->tickCount->text().toInt() + 1));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_start_clicked()
{
    playing = true;
    timer->start(250);

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
    bool ok;
    int t = ui->tickCount->text().toInt(&ok);
    if (t <= 1 || !ok || t > 512){
        ui->tickCount->setText(0);
        qDebug() << "You must give a nuumber in this field, that is greater, or equals to 0. Your number: " + t << "\n";
    }
}


void MainWindow::on_xSize_editingFinished()
{
    x = ui->xSize->value();
    setTable();
}


void MainWindow::on_ySize_editingFinished()
{
    y = ui->ySize->value();
    setTable();
}


void MainWindow::on_uiCombo_currentIndexChanged(int index)
{
    applyTheme(index);
}

void MainWindow::applyTheme(int i){
    switch(i){
    case 0://normal
        ui->table->setStyleSheet(
            "QTableWidget {"
            "background-color: lightblue;"
            "}"
            );
        break;
    case 1://values
        ui->table->setStyleSheet(
            "QTableWidget {"
            "background-color: black;"
            "color: white;"
            "}"
            );
        break;
    case 2://monochrome
        ui->table->setStyleSheet(
            "QTableWidget {"
            "background-color: white;"
            "}"
            );
        break;
    case 3://debug
        ui->table->setStyleSheet(
            "QTableWidget {"
            "background-color: darkgrey;"
            "}"
            );
        break;
    default:
        break;
    }
}

