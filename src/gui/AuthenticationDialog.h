#ifndef AUTHENTICATIONDIALOG_H
#define AUTHENTICATIONDIALOG_H

#include "DialogIncludes.h"
#include "MainIncludes.h"

class AuthenticationDialog : public QDialog
{
    Q_OBJECT

    QPointer<QLineEdit> loginEdit;
    QPointer<QLineEdit> passwordEdit;

public:
    explicit AuthenticationDialog(QPointer<QWidget> parent = nullptr);

private:
    void init();

private slots:
    void slotAccept();
    void slotRegister();

};

#endif // AUTHENTICATIONDIALOG_H
