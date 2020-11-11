#include "RegistrationDialog.h"
#include "MessageDialog.h"

RegistrationDialog::RegistrationDialog(QPointer<QWidget> parent)
    : QDialog(parent)
{
    init();
}

void RegistrationDialog::init()
{
    this->setFixedSize(300, 650);
    this->setWindowTitle("Регистрация");

    QPointer<QVBoxLayout> mainLay = new QVBoxLayout();

    QPointer<QHBoxLayout> loginLay = new QHBoxLayout();
    QPointer<QLabel> loginLabel = new QLabel(QString("Логин"), this);
    loginLay->addWidget(loginLabel);
    loginLay->addStretch();
    loginEdit = new QLineEdit(this);

    QPointer<QHBoxLayout> passwordLay = new QHBoxLayout();
    QPointer<QLabel> passwordLabel = new QLabel(QString("Пароль"), this);
    passwordLay->addWidget(passwordLabel);
    passwordLay->addStretch();
    passwordEdit = new QLineEdit(this);

    QPointer<QHBoxLayout> passwordRepeatLay = new QHBoxLayout();
    QPointer<QLabel> passwordRepeatLabel = new QLabel(QString("Повторите пароль"), this);
    passwordRepeatLay->addWidget(passwordRepeatLabel);
    passwordRepeatLay->addStretch();
    passwordRepeatEdit = new QLineEdit(this);

    QPointer<QHBoxLayout> lastNameLay = new QHBoxLayout();
    QPointer<QLabel> lastNameLabel = new QLabel(QString("Фамилия"), this);
    lastNameLay->addWidget(lastNameLabel);
    lastNameLay->addStretch();
    lastNameEdit = new QLineEdit(this);

    QPointer<QHBoxLayout> firstNameLay = new QHBoxLayout();
    QPointer<QLabel> firstNameLabel = new QLabel(QString("Имя"), this);
    firstNameLay->addWidget(firstNameLabel);
    firstNameLay->addStretch();
    firstNameEdit = new QLineEdit(this);

    QPointer<QHBoxLayout> middleNameLay = new QHBoxLayout();
    QPointer<QLabel> middleNameLabel = new QLabel(QString("Отчество"), this);
    middleNameLay->addWidget(middleNameLabel);
    middleNameLay->addStretch();
    middleNameEdit = new QLineEdit(this);

    QPointer<QHBoxLayout> seriesLay = new QHBoxLayout();
    QPointer<QLabel> seriesLabel = new QLabel(QString("Серия"), this);
    seriesLay->addWidget(seriesLabel);
    seriesLay->addStretch();
    seriesEdit = new QLineEdit(this);
    QPointer<QVBoxLayout> seriesVertLay = new QVBoxLayout();
    seriesVertLay->addLayout(seriesLay);
    seriesVertLay->addWidget(seriesEdit);

    QPointer<QHBoxLayout> numberLay = new QHBoxLayout();
    QPointer<QLabel> numberLabel = new QLabel(QString("Номер"), this);
    numberLay->addWidget(numberLabel);
    numberLay->addStretch();
    numberEdit = new QLineEdit(this);
    QPointer<QVBoxLayout> numberVertLay = new QVBoxLayout();
    numberVertLay->addLayout(numberLay);
    numberVertLay->addWidget(numberEdit);

    QPointer<QHBoxLayout> serNumLay = new QHBoxLayout();
    serNumLay->addLayout(seriesVertLay);
    serNumLay->addLayout(numberVertLay);

    QPointer<QHBoxLayout> organizeLay = new QHBoxLayout();
    QPointer<QLabel> organizeLabel = new QLabel(QString("Выдан"), this);
    organizeLay->addWidget(organizeLabel);
    organizeLay->addStretch();
    organizeEdit = new QTextEdit(this);

    QPointer<QHBoxLayout> registrationLay = new QHBoxLayout();
    QPointer<QLabel> registrationLabel = new QLabel(QString("Прописка"), this);
    registrationLay->addWidget(registrationLabel);
    registrationLay->addStretch();
    registrationEdit = new QTextEdit(this);

    QPointer<QPushButton> acceptButton = new QPushButton(QString("Принять"), this);
    acceptButton->setDefault(true);
    connect(acceptButton, SIGNAL(clicked()), SLOT(slotAccept()));

    QPointer<QPushButton> rejectButton = new QPushButton(QString("Отмена"), this);
    connect(rejectButton, SIGNAL(clicked()), SLOT(reject()));

    QPointer<QHBoxLayout> buttonLay = new QHBoxLayout();
    buttonLay->addWidget(acceptButton);
    buttonLay->addStretch();
    buttonLay->addWidget(rejectButton);

    mainLay->addLayout(loginLay);
    mainLay->addWidget(loginEdit);
    mainLay->addSpacing(5);
    mainLay->addLayout(passwordLay);
    mainLay->addWidget(passwordEdit);
    mainLay->addSpacing(5);
    mainLay->addLayout(passwordRepeatLay);
    mainLay->addWidget(passwordRepeatEdit);
    mainLay->addSpacing(5);
    mainLay->addLayout(lastNameLay);
    mainLay->addWidget(lastNameEdit);
    mainLay->addSpacing(5);
    mainLay->addLayout(firstNameLay);
    mainLay->addWidget(firstNameEdit);
    mainLay->addSpacing(5);
    mainLay->addLayout(middleNameLay);
    mainLay->addWidget(middleNameEdit);
    mainLay->addSpacing(5);
    mainLay->addLayout(serNumLay);
    mainLay->addSpacing(5);
    mainLay->addLayout(organizeLay);
    mainLay->addWidget(organizeEdit);
    mainLay->addSpacing(5);
    mainLay->addLayout(registrationLay);
    mainLay->addWidget(registrationEdit);
    mainLay->addSpacing(20);
    mainLay->addStretch();
    mainLay->addLayout(buttonLay);
    this->setLayout(mainLay);
}

bool RegistrationDialog::isEmptyFields()
{
    return loginEdit->text().isEmpty() || passwordEdit->text().isEmpty()
           || passwordRepeatEdit->text().isEmpty() || firstNameEdit->text().isEmpty()
           || middleNameEdit->text().isEmpty() || lastNameEdit->text().isEmpty()
           || seriesEdit->text().isEmpty() || numberEdit->text().isEmpty()
           || organizeEdit->toPlainText().isEmpty() || registrationEdit->toPlainText().isEmpty();
}

void RegistrationDialog::slotAccept()
{
    if (isEmptyFields())
    {
        MessageDialog::critical(this, QString("Пожалуйста, заполните все поля"));
        return;
    }

    this->accept();
}
