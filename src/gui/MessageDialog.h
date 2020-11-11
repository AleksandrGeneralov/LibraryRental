#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include "DialogIncludes.h"
#include "MainIncludes.h"

#include <QtSvg/QSvgWidget>

class MessageDialog : public QDialog
{
    Q_OBJECT

    QPointer<QSvgWidget> icon;

public:
    explicit MessageDialog(QPointer<QWidget> parent,
                           const QString &text);

    static int information(QPointer<QWidget> parent,
                           const QString &text);

    static int warning(QPointer<QWidget> parent,
                       const QString &text);

    static int critical(QPointer<QWidget> parent,
                       const QString &text);

private:
    void setIcon(const QString &path);
};

#endif // MESSAGEDIALOG_H
