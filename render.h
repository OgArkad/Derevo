#ifndef RENDER_H
#define RENDER_H

#include <QMainWindow>
#include <QWidget>
#include <QFont>
#include <QTableWidget>

#include <iostream>
//#include <vector>

class Render
{
public:
    explicit Render(QTableWidget *table, QMainWindow *wt, int& x, int& y, int8_t& theme);
    void initTable(int x, int y, int8_t theme);
    void renderMap(const std::vector<std::vector<int8_t>>& matrix);
    void setTable();
    void resizeTable();

private:
    QTableWidget *table = nullptr;
    QMainWindow *w = nullptr;
    void applyTheme(QTableWidgetItem *item, int8_t val);
    int& x;
    int& y;
    int8_t& theme;
};

#endif // RENDER_H
