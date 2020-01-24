#include "socketserver2.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SocketServer2 w;
	w.show();
	return a.exec();
}
