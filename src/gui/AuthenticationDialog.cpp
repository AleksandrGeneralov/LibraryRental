#include "AuthenticationDialog.h"
#include "MessageDialog.h"
#include "RegistrationDialog.h"
#include "../data_base/SqlManager.h"

AuthenticationDialog::AuthenticationDialog(QPointer<QWidget> parent)
    : QDialog(parent)
{
    init();
}

std::unique_ptr<FullUserInfo> AuthenticationDialog::getUser()
{
    return std::move(user);
}

void AuthenticationDialog::init()
{
    this->setFixedSize(200, 180);
    this->setWindowTitle("Авторизация");

    QPointer<QVBoxLayout> mainLay = new QVBoxLayout();

    QPointer<QHBoxLayout> loginLay = new QHBoxLayout();
    QPointer<QLabel> loginLabel = new QLabel(QString("Логин"), this);
    loginLay->addWidget(loginLabel);
    loginLay->addStretch();

    QPointer<QHBoxLayout> passwordLay = new QHBoxLayout();
    QPointer<QLabel> passwordLabel = new QLabel(QString("Пароль"), this);
    passwordLay->addWidget(passwordLabel);
    passwordLay->addStretch();

    loginEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);

    QPointer<QPushButton> registerButton = new QPushButton(QString("Регистрация"), this);
    connect(registerButton, SIGNAL(clicked()), SLOT(slotRegister()));

    QPointer<QHBoxLayout> regButtonLay = new QHBoxLayout();
    regButtonLay->addStretch();
    regButtonLay->addWidget(registerButton);

    QPointer<QPushButton> acceptButton = new QPushButton(QString("Принять"), this);
    acceptButton->setDefault(true);
    connect(acceptButton, SIGNAL(clicked()), SLOT(slotAccept()));

    QPointer<QPushButton> rejectButton = new QPushButton(QString("Отмена"), this);
    connect(rejectButton, SIGNAL(clicked()), SLOT(reject()));

    QPointer<QHBoxLayout> buttonLay = new QHBoxLayout();
    buttonLay->addWidget(acceptButton);
    buttonLay->addWidget(rejectButton);

    mainLay->addLayout(regButtonLay);
    mainLay->addLayout(loginLay);
    mainLay->addWidget(loginEdit);
    mainLay->addLayout(passwordLay);
    mainLay->addWidget(passwordEdit);
    mainLay->addStretch();
    mainLay->addLayout(buttonLay);
    this->setLayout(mainLay);
}

void AuthenticationDialog::slotAccept()
{
    QString message = "";

    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();
    if (!SqlUtils::getInstance()->sqlIsExist(db.get(), "users", QStringList() << "login" << "password",
                                            QStringList() << loginEdit->text().trimmed()
                                            << passwordEdit->text().trimmed()))
    {
        message = QString("Неправильный логин/пароль");
    }

    if (message.isEmpty())
    {
        QString query = QString("SELECT * FROM users LEFT JOIN users_info ON users.id=users_info.user_id"
                                " WHERE users.login='%1' AND users.password='%2'")
                                .arg(loginEdit->text().trimmed())
                                .arg(passwordEdit->text().trimmed());
        QList<QSqlRecord> records;
        if (SqlUtils::getInstance()->sqlTable(db.get(), query, records))
        {
            if (records.isEmpty())
            {
                return;
            }

            user.reset();
            user = std::make_unique<FullUserInfo>(records.first());
        }
        else
        {
            MessageDialog::critical(this, QString("Ошибка запроса к БД."));
            return;
        }
    }
    SqlManager::getInstance().closeDB();

    if (!message.isEmpty())
    {
        MessageDialog::critical(this, message);
    }
    else
    {
        this->accept();
    }
}

void AuthenticationDialog::slotRegister()
{
    RegistrationDialog regDlg(this);
    regDlg.exec();
}
