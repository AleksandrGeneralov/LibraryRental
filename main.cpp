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

void finishWork()
{
    SqlManager::getInstance().closeDB();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    checkDataBase();
    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();
    if (db)
    {
        SqlCreator::getInstance().create(db);

        db.reset();
        SqlManager::getInstance().closeDB();
    }
    else
    {
        return 1;
    }

    AuthenticationDialog authDlg;

    if (authDlg.exec() == QDialog::Accepted)
    {
        w.show();
    }
    else
    {
        finishWork();

        return 1;
    }

    int result = a.exec();
    finishWork();

    return result;
}
