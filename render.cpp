#include "render.h"
#include "ui_mainwindow.h"

/// @brief This class contains the table's important functions
/// @param table The table, to handle (usually ui->Table)
/// @param wt the QMainWindow to work with
Render::Render(QTableWidget *table, QMainWindow *wt, int& x, int& y, int8_t& theme): table(table), w(wt),  x(x), y(y), theme(theme) {
}//mainWindow: width, height

/// @brief This should only run once. It sets up the table, sets it's properties.
/// @param x count of columns
/// @param y count of rows
/// @param theme the theme to set up
void Render::initTable(int x, int y, int8_t theme){
    table->setContentsMargins(0, 0, 0, 0);

    setTable();

    table->horizontalHeader()->setMinimumSectionSize(1);
    table->verticalHeader()->setMinimumSectionSize(1);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    QFont font("monospace");
    font.setStyleHint(QFont::Monospace);
    font.setPixelSize(5);
    table->setFont(font);

    resizeTable();
}


void Render::resizeTable()
{
    if (x <= 0 || y <= 0 || !table || !w || !w->centralWidget()) return;

    const QSize available = table->size();
    const int cellSize = std::min(available.width()  / x,
                                  available.height() / y);

    if (cellSize <= 0) return;

    table->horizontalHeader()->setDefaultSectionSize(cellSize);
    table->verticalHeader()->setDefaultSectionSize(cellSize);
    for (int i = 0; i < x; i++) table->setColumnWidth(i, cellSize);
    for (int i = 0; i < y; i++) table->setRowHeight(i, cellSize);

    QFont font("monospace");
    font.setStyleHint(QFont::Monospace);
    font.setPixelSize(std::max(1, static_cast<int>(cellSize * 0.8)));
    table->setFont(font);
}

/// @brief Resizes the table, and recolors it
/// @param x count of columns
/// @param y count of rows
/// @param theme the theme to set up
void Render::setTable(){
    table->setColumnCount(x);
    table->setRowCount(y);

    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            if (!table->item(i, j)) table->setItem(i, j, new QTableWidgetItem());
            this->applyTheme(table->item(i, j), 0);
        }
    }

    table->setFixedSize(0.8 * w->width(), 0.8 * w->height());
}

/// @brief Renders the whole table/map
/// @param x count of columns
/// @param y count of rows
/// @param theme the theme to set up
/// @param matrix the matrix, on wich it is based
void Render::renderMap(const std::vector<std::vector<int8_t>>& matrix){
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (!table->item(i, j)) table->setItem(i, j, new QTableWidgetItem("0", 0));
            if (i < matrix.size() && matrix.size() >= 1 && matrix[0].size() > j) applyTheme(table->item(i, j), matrix[i][j]);
            else applyTheme(table->item(i, j), 0);
        }
    }
}

/// @brief Sets a cell's value, and color
/// @param item the table cell
/// @param val the value that shoul be written in the cell you probably want to set it to 0 or 1
/// @param theme a theme from 0-4
void Render::applyTheme(QTableWidgetItem *item, int8_t val){
    if (item == nullptr) return;
    item->setText(QString::number(val));
    switch(theme){
    case 0://normal
        if (val == 0){
            item->setBackground(QBrush(QColor("#71d1f1")));
            item->setForeground(QBrush(QColor("#71d1f1")));
        }else{
            item->setBackground(QBrush(QColor("#00d800")));
            item->setForeground(QBrush(QColor("#00d800")));
        }
        break;
    case 1://values
        if (val == 0){
            item->setBackground(QBrush(QColor("#000000")));
            item->setForeground(QBrush(QColor("#FFFFFF")));
        }else{
            item->setBackground(QBrush(QColor("#FFFFFF")));
            item->setForeground(QBrush(QColor("#000000")));
        }
        break;
    case 2://night
        if (val == 0){
            item->setBackground(QBrush(QColor("#00008b")));
            item->setForeground(QBrush(QColor("#00008b")));
        }else{
            item->setBackground(QBrush(QColor("#013220")));
            item->setForeground(QBrush(QColor("#013220")));
        }
        break;
    case 3://monochrome
        if (val == 0){
            item->setBackground(QBrush(QColor("#FFFFFF")));
            item->setForeground(QBrush(QColor("#FFFFFF")));
        }else{
            item->setBackground(QBrush(QColor("#000000")));
            item->setForeground(QBrush(QColor("#000000")));
        }
        break;
    case 4://debug
        item->setBackground(QBrush(QColor("#999999")));
        item->setForeground(QBrush(QColor("#FF0000")));
        break;
    default:
        throw new std::range_error("Unexpected theme: " + theme);
    }
}
