#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include "DialogIncludes.h"
#include "MainIncludes.h"

class MessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MessageDialog(QPointer<QWidget> parent,
                           const QString &text);

    static int information(QPointer<QWidget> parent,
                           const QString &text);

    static int warning(QPointer<QWidget> parent,
                       const QString &text);

    static int critical(QPointer<QWidget> parent,
                       const QString &text);
};

#endif // MESSAGEDIALOG_H
