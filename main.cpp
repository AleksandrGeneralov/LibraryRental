#include "mainwindow.h"
#include "AuthenticationDialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuthenticationDialog authDlg;

    if (authDlg.exec() == QDialog::Accepted)
    {
        MainWindow w;
        w.show();
    }
    return 0;
}
