﻿#include "socketclient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SocketClient w;
	w.show();
	return a.exec();
}
