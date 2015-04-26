#ifndef DIALOGTEST_H
#define DIALOGTEST_H
#include <QtGui>
#include "sudoku.h"
#include "custom_delegate.h"
class TestDialog : public QDialog{
    Q_OBJECT
    public:
        TestDialog();
    private:
        QTableWidgetItem **squares;
        QTableWidget* table;
    private slots:
        void solve();
        void load();
 

};  

#endif
