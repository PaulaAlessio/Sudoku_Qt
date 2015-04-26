#include <QtGui>
#include "custom_delegate.h"
#include "SudokuDialog.h"


int main(int argc, char *argv[ ])
{
    QApplication app(argc, argv);
    TestDialog prueba;
    prueba.setAttribute(Qt::WA_QuitOnClose);
    prueba.show();
    return app.exec();
}
