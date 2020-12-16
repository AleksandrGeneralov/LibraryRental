#include "MessageDialog.h"

MessageDialog::MessageDialog(QPointer<QWidget> parent,
                             const QString &text)
    : QDialog(parent)
{
    this->setWindowTitle(QString("Внимание"));

    QPointer<QVBoxLayout> mainLay = new QVBoxLayout();
    QPointer<QHBoxLayout> messageLay = new QHBoxLayout();

    icon = new QSvgWidget(this);
    icon->setFixedSize(QSize(8, 8));
    icon->setMinimumSize(QSize(8, 8));

    QPointer<QLabel> textLabel = new QLabel(text, this);
    textLabel->setWordWrap(true);
    textLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    messageLay->addWidget(icon);
    messageLay->addWidget(textLabel);

    QPointer<QPushButton> buttonAccept = new QPushButton(QString("Ок"), this);
    connect(buttonAccept, SIGNAL(clicked()), this, SLOT(accept()));

    QPointer<QHBoxLayout> buttonLay = new QHBoxLayout();
    buttonLay->addStretch();
    buttonLay->addWidget(buttonAccept);

    mainLay->addLayout(messageLay);
    mainLay->addLayout(buttonLay);
    this->setLayout(mainLay);
}

int MessageDialog::information(QPointer<QWidget> parent,
                               const QString &text)
{
    MessageDialog dlg(parent, text);

    return dlg.exec();
}

int MessageDialog::warning(QPointer<QWidget> parent,
                           const QString &text)
{
    MessageDialog dlg(parent, text);

    return dlg.exec();
}

int MessageDialog::critical(QPointer<QWidget> parent,
                            const QString &text)
{
    MessageDialog dlg(parent, text);

    return dlg.exec();
}

void MessageDialog::setIcon(const QString &path)
{
    icon->load(path);
}
