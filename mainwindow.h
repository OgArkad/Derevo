#pragma once

#include <QMainWindow>
#include<string>
#include <QTimer>

#include <iostream>
#include <vector>
#include <ctime>   // Добавлено для time(NULL)
#include <cstdint>

using namespace std;

extern vector<vector<int8_t>> matrix;//valamiért itt kell deklarálni

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
    int tick = 100;

private slots:
    void renderMap();
    void applyTheme(int);
    void initTable();
    void setTable();
    void stepTick();

    void on_tickCount_editingFinished();

    void on_start_clicked();

    void on_stop_clicked();

    void on_xSize_editingFinished();

    void on_ySize_editingFinished();

    void on_uiCombo_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    bool playing = false;
    QTimer *timer;
};
