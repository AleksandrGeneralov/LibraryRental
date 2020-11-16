#include "src/gui/mainwindow.h"
#include "src/gui/AuthenticationDialog.h"
#include "src/data_base/SqlDefine.h"
#include "src/data_base/SqlManager.h"
#include "src/data_base/SqlCreator.h"

#include <QApplication>
#include <QDir>
#include <memory>

void checkDataBase()
{
    QDir dir;
    if (!dir.exists(bases_path))
    {
        dir.mkpath(bases_path);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    checkDataBase();
    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();
    if (db)
    {
        SqlCreator::getInstance().create(db);
    }
    else
    {
        return 1;
    }

    AuthenticationDialog authDlg;

    if (authDlg.exec() == QDialog::Accepted)
    {
        MainWindow w;
        w.show();
    }
    return 0;
}
