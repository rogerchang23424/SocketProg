#ifndef SOCKETSERVER2_H
#define SOCKETSERVER2_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/qtextbrowser.h>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QScrollBar>
#include <QFontDatabase>
#include <QMessageBox>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QTimer>
#include <QCloseEvent>
#include <winsock2.h>
#include <windows.h>
#include <Ws2tcpip.h>
#include <sstream>
#include "ui_socketserver2.h"

class SocketServer2 : public QMainWindow
{
	Q_OBJECT

public:
	SocketServer2(QWidget *parent = 0);
	~SocketServer2();
	void closeEvent(QCloseEvent *event);
	int parsepackage(char* msg, QString &username, QString &content, QString &adduser);
	void addContent(QString &username, QString &content);

private:
	//Ui::SocketServer2Class ui;

	QWidget *widget;
	QVBoxLayout *hc_layout;

	QFrame *header_frame;
	QLabel *ip_label;
	QLineEdit *ip_entry;
	QLabel *port_label;
	QLineEdit *port_entry;
	QLabel *username_label;
	QLineEdit *username_entry;
	QPushButton *connect_btn;
	QHBoxLayout *header_layout;

	QFrame *content_frame;
	QHBoxLayout *hor_layout; 
	QFrame *left_top;
	QFrame *left;
	QFrame *right;
	QFrame *left_bottom;

	QComboBox *font_family_box;
	QComboBox *font_size_box;
	QHBoxLayout *left_top_layout;
	QTextBrowser *doc;
	QVBoxLayout *left_layout;
	QLineEdit *msg_entry;
	QPushButton *send_out;
	QFrame *msg_font_toolbox;
	QComboBox *msg_font_family;
	QComboBox *msg_font_size;
	QHBoxLayout *font_toolbox_layout;
	QGridLayout *left_btm_layout;

	QLabel *online;
	QListWidget *online_people;
	QGridLayout *right_layout;

	QThread *t_to_client;
	QThread *apt_thread;
	QTimer *recvtimer;
	QTimer *accepttimer;
	SOCKET ssocket;
	SOCKET csocket;
	QFontDatabase fontdb;
	QList<QString> font_size_list;

	timeval timeTimeout;
	fd_set readfds;

	bool has_accepted = false;
	bool has_created = false;

private slots:
	void handleSend();
	void handleRecv();
	void handleBind();
	void handleAccept();
	void fontfamilychanged(const QString &);
	void fontsizechanged(const QString &);
	void msgfontfamilychanged(const QString &);
	void msgfontsizechanged(const QString &);
};

#endif // SOCKETSERVER2_H
