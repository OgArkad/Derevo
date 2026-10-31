#pragma once

#include <QTimer>
#include <QIcon>

#include <QPalette>
#include <QColor>

#include <QPixmap>
#include <QScreen>
#include <QGuiApplication>
#include <QDir>

#include <QGuiApplication>
#include <QSizePolicy>
#include <QSize>
#include <QStyleHints>
#include "ui_mainwindow.h"

#include "render.h"
#include "main.h"//piszkosul circular-dependency

class QTableWidgetItem;

using namespace std;

extern vector<vector<int8_t>> matrix;
extern LinkedList<Tree::TreeClass> trees;


QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int x = 128;
    int y = 64;
    int tick = 0;
    int8_t theme = 0;
    void appendDebug(std::string strg);
    void appendDebug(QString strg);

private slots:
    void on_tickCount_editingFinished();
    void on_start_clicked();
    void on_stop_clicked();
    void on_xSize_editingFinished();
    void on_ySize_editingFinished();
    void on_uiCombo_currentIndexChanged(int index);
    void on_HideButton_clicked();
    void resizeEvent(QResizeEvent* event);

    void on_reset_clicked();

    void on_simSpeed_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    Render * renderer = nullptr;
    bool playing = false;
    bool sidebar = true;
    QTimer *timer;
    void stepTick();
    void resizeVectorMatrix();
};
