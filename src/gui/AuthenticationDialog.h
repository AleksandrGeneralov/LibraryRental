#ifndef AUTHENTICATIONDIALOG_H
#define AUTHENTICATIONDIALOG_H

#include "DialogIncludes.h"
#include "MainIncludes.h"
#include "DataStructures.h"

class AuthenticationDialog : public QDialog
{
    Q_OBJECT

    QPointer<QLineEdit> loginEdit;
    QPointer<QLineEdit> passwordEdit;

    std::unique_ptr<FullUserInfo> user;

public:
    explicit AuthenticationDialog(QPointer<QWidget> parent = nullptr);

    std::unique_ptr<FullUserInfo> getUser();

private:
    void init();

private slots:
    void slotAccept();
    void slotRegister();

};

#endif // AUTHENTICATIONDIALOG_H
