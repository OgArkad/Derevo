#ifndef RENDER_H
#define RENDER_H

#include <QMainWindow>
#include <QWidget>
#include <QFont>
#include <QTableWidget>
#include <iostream>
//#include <vector>

using namespace std;

class Render
{
public:
    explicit Render(QTableWidget *table, QMainWindow *w);
    void initTable(int x, int y, int8_t theme);
    void renderMap(int x, int y, int8_t theme, const vector<vector<int8_t>>& matrix);
    void setTable(int x, int y, int8_t theme);
    void applyTheme(QTableWidgetItem *item, int8_t val,  int8_t theme);

private:
    QTableWidget *table = nullptr;
    QMainWindow *w = nullptr;
};

#endif // RENDER_H
