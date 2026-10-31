#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>//not used

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/appicon.ico"));//fél siker

    QPushButton* screensh = new QPushButton("Screenshot", this);
    ui->statusbar->addPermanentWidget(screensh);
    connect(screensh, &QPushButton::clicked, this, [this]() {
        QPixmap screenshot = ui->table->grab();
        bool s = screenshot.save("myForest.png", "PNG");
        if (s){
            appendDebug(QString::fromStdString("saved succesfully to: "));
            appendDebug(QDir::currentPath());
        }
        else
            appendDebug(QString::fromStdString("An unknown error occured"));
    });
    //addwidget: bal | addPermanentWidget: jobb
    /*QPushButton* save = new QPushButton("Save", this);
    ui->statusbar->addPermanentWidget(save); //this one wont be permanent, but at leat it's to the right
    connect(save, &QPushButton::clicked, this, [this]() {
        appendDebug(QString::fromStdString("saved to file...\n"));
    });*/



    renderer = new Render(ui->table, this, x, y, theme);

    renderer->initTable(x, y, MainWindow::theme);

    if (!QGuiApplication::platformName().contains("wayland") ||  windowFlags().testFlag(Qt::WindowStaysOnTopHint))
        this->adjustSize();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::stepTick);
    ui->statusbar->showMessage("Welcome!", 5000);
}

void MainWindow::appendDebug(QString strg){
    ui->debugElement->setTextColor(QColor::fromRgb(0, 255, 0));
    ui->debugElement->append(strg);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    renderer->resizeTable();
}

#pragma region stepTick

/*                                                        ********************************                                    */

void MainWindow::stepTick(){
    ui->tickCount->setText(QString::number(tick));
    ui->treeNumber->display(QString::number(trees.count));//így vagy az (int)... -el optimmálisabb vajon?
    Tree::step();
    renderer->renderMap(matrix);
    tick++;
}

#pragma endregion

/// @brief Resizes the main matrix, to the current x, y
void MainWindow::resizeVectorMatrix(){
    vector<vector<int8_t>> vec(y, vector<int8_t>(x, 0));
    if (matrix.size() <= 2)
    {
        matrix = vec;
        renderer->renderMap(matrix);
        ui->table->resize(x* (size().width()/x) * 0.9999, y* (size().width()/x) * 0.9999);
        return;
    }

    const int oy = static_cast<int>(matrix.size());
    const int ox = oy > 0 ? static_cast<int>(matrix[0].size()) : 0;

    int offy = 0;
    int offyt = 0;

    if (oy < y){
        offy = y - std::min(oy, y);
        offyt = ox - std::min(ox, x);
    }else{
        offyt = std::max(0, oy - y);
    }

    const int mx = matrix[0].size();
    const int my = matrix.size();
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if (j < mx && (i + offy) < y && (i + offyt) < mx)
                    vec[i + offy][j] = matrix[i + offyt][j];
            }
        }
    matrix = vec;
    ui->table->resize(x* (size().width()/x) * 0.9999, y* (size().width()/x) * 0.9999);
}

// Source - https://stackoverflow.com/a/78854851
// Posted by Nick Bolton
// Retrieved 2026-10-27, License - CC BY-SA 4.0
inline bool isDarkMode() {
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
  const Qt::ColorScheme scheme = QGuiApplication::styleHints()->colorScheme();
  return scheme == Qt::ColorScheme::Dark;
#else
  const QPalette defaultPalette;
  const QColor text = defaultPalette.color(QPalette::WindowText);
  const QColor window = defaultPalette.color(QPalette::Window);
  return text.lightness() > window.lightness();
#endif // QT_VERSION
}

#pragma region event handlers

void MainWindow::on_start_clicked()
{
    if (playing) return;
    playing = true;
    timer->start(ui->simSpeed->value());

    if (isDarkMode())
        ui->start->setStyleSheet("background-color: rgb(20, 20, 145);");
    else
        ui->start->setStyleSheet("background-color: rgb(110, 110, 255);");
}


void MainWindow::on_stop_clicked()
{
    if (!playing) return;
    playing = false;
    timer->stop();

    ui->start->setStyleSheet("");
}


void MainWindow::on_tickCount_editingFinished()
{
    bool ok;
    int t = ui->tickCount->text().toInt(&ok);
    if (t < 0 || !ok){
        ui->tickCount->setText(0);
        cout << "You must give a number in this field, that is greater, or equals to 0. Your number: " + t << endl;
    }
    tick = t;
    if (t = 0) Tree::reset();
}


void MainWindow::on_xSize_editingFinished()
{
    x = ui->xSize->value();
    renderer->setTable();
    if (matrix.size() != x)
        resizeVectorMatrix();
    if (!QGuiApplication::platformName().contains("wayland") ||  windowFlags().testFlag(Qt::WindowStaysOnTopHint))
        adjustSize();
}


void MainWindow::on_ySize_editingFinished()
{
    y = ui->ySize->value();
    renderer->setTable();
    if (matrix.size() > 0 && matrix[0].size() != y)
        resizeVectorMatrix();
    if (!QGuiApplication::platformName().contains("wayland") ||  windowFlags().testFlag(Qt::WindowStaysOnTopHint))
        adjustSize();
}


void MainWindow::on_uiCombo_currentIndexChanged(int index)
{
    theme = index;
    renderer->renderMap(matrix);
}


void MainWindow::on_HideButton_clicked()
{
    if (sidebar){
        ui->frame->hide();
        ui->HideButton->setText("<");
    }
    else{
        ui->frame->show();
        ui->HideButton->setText(">");
    }
    sidebar = !sidebar;
    if (!QGuiApplication::platformName().contains("wayland") ||  windowFlags().testFlag(Qt::WindowStaysOnTopHint))
        this->adjustSize();
}


void MainWindow::on_reset_clicked()
{
    Tree::reset();
    on_stop_clicked();
    renderer->renderMap(matrix);
    tick = 0;
    ui->tickCount->setText(QString::number(0));
    ui->treeNumber->display(QString::number(0));
}

void MainWindow::on_simSpeed_valueChanged(int value)
{
    timer->setInterval(value);
}

#pragma endregion
