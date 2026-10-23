#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon(":/appicon.ico"));//fél siker
    ui->setupUi(this);

    renderer = new Render(ui->table, this);

    ui->xSize->setMaximum(256);
    ui->xSize->setValue(128);
    ui->xSize->setMinimum(3);

    ui->ySize->setMaximum(128);
    ui->ySize->setValue(64);
    ui->ySize->setMinimum(3);
    renderer->initTable(x, y, theme);

    this->adjustSize();

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::stepTick);
}

/*                                                        ********************************                                    */
void MainWindow::stepTick(){
    ui->tickCount->setText(QString::number(tick));
    ui->treeNumber->display(trees);
    renderer->renderMap(x, y, theme, matrix);
    //TreeClass->tree1->grow();
}


MainWindow::~MainWindow() {
    delete ui;
}


#pragma region Event handlers

void MainWindow::resizeEvent(QResizeEvent* event)
{
    //if (!QGuiApplication::platformName().contains("wayland"))
    //   this->adjustSize();
}


void MainWindow::on_start_clicked()
{
    playing = true;
    timer->start(250);

    ui->start->setAutoFillBackground(true);//works on windows
    QPalette palette = ui->start->palette();
    palette.setColor(QPalette::Window, QColor(Qt::blue));
    ui->start->setPalette(palette);
    ui->start->show();
}


void MainWindow::on_stop_clicked()
{
    playing = false;
    timer->stop();

    ui->start->setAutoFillBackground(true);
    QPalette palette = ui->start->palette();
    palette.setColor(QPalette::Window, QColor(Qt::black));
    ui->start->setPalette(palette);
    ui->start->show();
}


void MainWindow::on_tickCount_editingFinished()
{
    bool ok;
    int t = ui->tickCount->text().toInt(&ok);
    if (t < 0 || !ok){
        ui->tickCount->setText(0);
        cout << "You must give a nuumber in this field, that is greater, or equals to 0. Your number: " + t << endl;
    }
    tick = t;
}

void MainWindow::resizeVectorMatrix(){
    vector<vector<int8_t>> vec(y, vector<int8_t>(x, 0));
    if (matrix.size() <= 2)
    {
        matrix = vec;
        ui->table->resize(x* (size().width()/x) * 0.9999, y* (size().width()/x) * 0.9999);
        return;
    }

    const int oy = static_cast<int>(matrix.size());
    const int ox = oy > 0 ? static_cast<int>(matrix[0].size()) : 0;

    int offy = 0;
    int offyt = 0;

    if (oy < y){
        offy = y - min(oy, y);
        offyt = ox - min(ox, x);
    }else{
        offyt = max(0, oy - y);
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


void MainWindow::on_xSize_editingFinished()
{
    x = ui->xSize->value();
    renderer->setTable(x, y, theme);
    if (matrix.size() != x)
        resizeVectorMatrix();
}


void MainWindow::on_ySize_editingFinished()
{
    y = ui->ySize->value();
    renderer->setTable(x, y, theme);
    if (matrix.size() > 0 && matrix[0].size() != y)
        resizeVectorMatrix();
}


void MainWindow::on_uiCombo_currentIndexChanged(int index)
{
    theme = index;
    renderer->renderMap(x, y, theme, matrix);
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

#pragma endregion
