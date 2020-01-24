/********************************************************************************
** Form generated from reading UI file 'socketclient.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOCKETCLIENT_H
#define UI_SOCKETCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SocketClientClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SocketClientClass)
    {
        if (SocketClientClass->objectName().isEmpty())
            SocketClientClass->setObjectName(QStringLiteral("SocketClientClass"));
        SocketClientClass->resize(600, 400);
        menuBar = new QMenuBar(SocketClientClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        SocketClientClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SocketClientClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SocketClientClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SocketClientClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SocketClientClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SocketClientClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SocketClientClass->setStatusBar(statusBar);

        retranslateUi(SocketClientClass);

        QMetaObject::connectSlotsByName(SocketClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *SocketClientClass)
    {
        SocketClientClass->setWindowTitle(QApplication::translate("SocketClientClass", "SocketClient", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SocketClientClass: public Ui_SocketClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOCKETCLIENT_H
