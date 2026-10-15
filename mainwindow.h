#pragma once

#include <QTimer>
#include <string>

#include "render.h"
#include "main.h"

class QTableWidgetItem;

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
    int trees = 0;

private slots:
    void stepTick();
    void resizeVectorMatrix();

    void on_tickCount_editingFinished();
    void resizeEvent(QResizeEvent* event);

    void on_start_clicked();

    void on_stop_clicked();

    void on_xSize_editingFinished();

    void on_ySize_editingFinished();

    void on_uiCombo_currentIndexChanged(int index);

    void on_HideButton_clicked();

private:
    Ui::MainWindow *ui;
    Render * renderer = nullptr;
    bool playing = false;
    bool sidebar = true;
    int8_t theme = 0;
    QTimer *timer;
};
