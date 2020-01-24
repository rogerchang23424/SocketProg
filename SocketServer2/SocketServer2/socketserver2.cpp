#include "socketserver2.h"
QMutex mutex;

SocketServer2::SocketServer2(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);
	widget = new QWidget();
	hc_layout = new QVBoxLayout;
	widget->setLayout(hc_layout);
	setCentralWidget(widget);
	resize(QSize(600, 500));

	header_frame = new QFrame();
	header_layout = new QHBoxLayout;
	header_frame->setLayout(header_layout);
	ip_label = new QLabel("IP位址:");
	ip_entry = new QLineEdit();
	ip_entry->setFixedWidth(160);
	QRegExp rx("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
	QValidator *validator = new QRegExpValidator(rx);
	ip_entry->setValidator(validator);
	port_label = new QLabel("連接埠:");
	port_entry = new QLineEdit();
	port_entry->setFixedWidth(60);
	QValidator *validator2 = new QIntValidator(0, 65535);
	port_entry->setValidator(validator2);
	username_label = new QLabel("使用者名稱:");
	username_entry = new QLineEdit();
	username_entry->setFixedWidth(80);
	username_entry->setMaxLength(50);
	connect_btn = new QPushButton("開始監聽");
	connect_btn->setFixedWidth(80);
	connect(connect_btn, SIGNAL(clicked()), this, SLOT(handleBind()));

	header_layout->addWidget(ip_label);
	header_layout->addWidget(ip_entry);
	header_layout->addWidget(port_label);
	header_layout->addWidget(port_entry);
	header_layout->addWidget(username_label);
	header_layout->addWidget(username_entry);
	header_layout->addWidget(connect_btn);
	header_layout->addStretch(0);
	header_layout->setMargin(5);
	header_layout->setSpacing(5);

	content_frame = new QFrame;
	hor_layout = new QHBoxLayout;
	content_frame->setLayout(hor_layout);
	left_top = new QFrame();
	left = new QFrame();
	right = new QFrame();
	left_bottom = new QFrame();
	right->setFixedWidth(150);

	font_family_box = new QComboBox();
	font_family_box->setFixedWidth(250);
	font_family_box->addItems(fontdb.families());
	font_size_box = new QComboBox();
	font_size_box->setFixedWidth(80);
	font_size_list = { "8", "9", "10", "11", "12", "14", "16", "18", "20", "22", "24", "26", "28", "36", "48", "72" };
	font_size_box->addItems(QStringList(font_size_list));
	font_size_box->setEditable(true);
	left_top_layout = new QHBoxLayout();
	left_top->setLayout(left_top_layout);
	doc = new QTextBrowser();
	left_layout = new QVBoxLayout;
	//doc->setStyleSheet("background-color:white;");
	doc->setFont(QFont("微軟正黑體", 12));
	QFont f = doc->property("font").value<QFont>();
	font_family_box->setCurrentText(f.family());
	font_size_box->setCurrentText(QString::number(f.pointSize()));
	left->setLayout(left_layout);

	left_btm_layout = new QGridLayout();

	msg_font_toolbox = new QFrame;
	font_toolbox_layout = new QHBoxLayout();
	msg_font_toolbox->setLayout(font_toolbox_layout);
	msg_font_family = new QComboBox();
	msg_font_family->setFixedWidth(250);
	msg_font_family->addItems(fontdb.families());
	msg_font_size = new QComboBox();
	msg_font_size->setFixedWidth(80);
	msg_font_size->addItems(QStringList({ "8", "9", "10", "11", "12" }));

	msg_entry = new QLineEdit();
	msg_entry->setFont(QFont("微軟正黑體", 10));
	msg_entry->setFixedHeight(25);
	f = msg_entry->property("font").value<QFont>();
	msg_font_family->setCurrentText(f.family());
	msg_font_size->setCurrentText(QString::number(f.pointSize()));

	font_toolbox_layout->addWidget(msg_font_family);
	font_toolbox_layout->addWidget(msg_font_size);
	font_toolbox_layout->addStretch(0);
	font_toolbox_layout->setMargin(0);
	font_toolbox_layout->setSpacing(5);

	msg_entry->setMaxLength(2000);
	send_out = new QPushButton("送出");
	left_bottom->setLayout(left_btm_layout);

	right_layout = new QGridLayout();
	right->setLayout(right_layout);
	online = new QLabel("");
	online->setAlignment(Qt::AlignCenter);
	online->setFont(QFont("Microsoft jhenghei", 9));
	online_people = new QListWidget();
	right_layout->addWidget(online, 0, 0);
	right_layout->addWidget(online_people, 1, 0);

	left_top_layout->addWidget(font_family_box);
	left_top_layout->addWidget(font_size_box);
	left_top_layout->addStretch(0);
	left_top_layout->setMargin(0);
	left_top_layout->setSpacing(5);

	connect(font_family_box, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(fontfamilychanged(const QString &)));
	connect(font_size_box, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(fontsizechanged(const QString &)));
	connect(msg_font_family, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(msgfontfamilychanged(const QString &)));
	connect(msg_font_size, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(msgfontsizechanged(const QString &)));

	left_btm_layout->addWidget(msg_font_toolbox, 0, 0);
	left_btm_layout->addWidget(msg_entry, 1, 0);
	left_btm_layout->addWidget(send_out, 1, 1);
	left_btm_layout->setMargin(0);
	left_btm_layout->setSpacing(5);
	left_layout->addWidget(left_top);
	left_layout->addWidget(doc);
	left_layout->addWidget(left_bottom);
	left_layout->setMargin(5);
	left_layout->setSpacing(5);
	hor_layout->addWidget(left);
	hor_layout->addWidget(right);
	hor_layout->setMargin(5);
	hor_layout->setSpacing(5);
	hc_layout->addWidget(header_frame);
	hc_layout->addWidget(content_frame);
	hc_layout->setMargin(0);
	hc_layout->setSpacing(0);

	connect(msg_entry, SIGNAL(returnPressed()), send_out, SIGNAL(clicked()));
	connect(send_out, SIGNAL(clicked()), this, SLOT(handleSend()));

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		QMessageBox::critical(this, "錯誤", "WSA 起始錯誤", QMessageBox::Ok);
		exit(1);
	}

	t_to_client = new QThread(this);
	recvtimer = new QTimer(NULL);
	recvtimer->setInterval(1);
	recvtimer->moveToThread(t_to_client);
	t_to_client->start();
	connect(recvtimer, SIGNAL(timeout()), this, SLOT(handleRecv()), Qt::DirectConnection);
	recvtimer->connect(t_to_client, SIGNAL(started()), SLOT(start()));

	apt_thread = new QThread(this);
	accepttimer = new QTimer(NULL);
	accepttimer->setInterval(1);
	accepttimer->moveToThread(apt_thread);
	connect(accepttimer, SIGNAL(timeout()), this, SLOT(handleAccept()), Qt::DirectConnection);
	accepttimer->connect(apt_thread, SIGNAL(started()), SLOT(start()));
	apt_thread->start();

	has_accepted = false;
	has_created = false;

	doc->setTextInteractionFlags(Qt::TextBrowserInteraction);
	doc->setOpenExternalLinks(true);
}

void SocketServer2::handleSend()
{
	std::ostringstream os;
	std::string a;
	int sent_byte;
	int need_len;
	const char *p;
	QString temp;
	os << "Username: " << username_entry->text().toStdString() << "\r\n";
	os << "Content: " << msg_entry->text().toStdString() << "\n\r\n";
	a = os.str();
	need_len = a.length();
	p = a.c_str();
	if (has_accepted) {
		sent_byte = send(csocket, p, need_len, 0);
	}
	if (msg_entry->text() != "") {
		temp = msg_entry->text();
		temp += "\n";
		mutex.lock();
		addContent(username_entry->text(), temp);
		doc->update();
		mutex.unlock();
		msg_entry->setText("");
	}
}

void SocketServer2::handleRecv()
{
	QString username;
	QString content;
	QString adduser;
	QListWidgetItem *lwi;
	SOCKADDR_IN client_in;
	int sock_len = sizeof(client_in);
	char ipv4[20];

	int nlength;
	char *msg = new char[10001];
	if (has_accepted) {
		nlength = recv(csocket, msg, 10000, 0);
		if (nlength <= 0) {
			has_accepted = false;
			online->setText("正在等候客戶端");
			delete online_people->item(0);
			closesocket(csocket);
			return;
		}
		msg[nlength] = 0;
		if (parsepackage(msg, username, content, adduser) < 0) {
			return;
		}

		if (adduser != "") {
			getpeername(csocket, (SOCKADDR *)&client_in, &sock_len);
			inet_ntop(AF_INET, &client_in.sin_addr, ipv4, sizeof(ipv4));
			
			adduser = adduser + "\nIP: " + ipv4;
			adduser = adduser + "\nPort: " + QString::number(ntohs(client_in.sin_port));
			lwi = new QListWidgetItem(adduser);
			lwi->setSizeHint(QSize(120, 45));
			online_people->addItem(lwi);
			lwi->setTextAlignment(Qt::AlignLeft);
		}
		else if(content != "\n"){
			mutex.lock();
			addContent(username, content);
			doc->update();
			mutex.unlock();
		}
	}
	delete[] msg;
}

void SocketServer2::handleBind()
{
	if (ip_entry->text() == "" || port_entry->text() == "" || username_entry->text() == "") {
		QMessageBox::critical(this, "錯誤", "內容不能有空", QMessageBox::Ok);
		return;
	}

	QByteArray ba;
	char* p;
	ssocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN sockin;

	sockin.sin_port = htons(port_entry->text().toUShort());
	sockin.sin_family = AF_INET;
	ba = ip_entry->text().toLatin1();
	p = ba.data();
	inet_pton(AF_INET, p, &sockin.sin_addr);

	if (::bind(ssocket, (SOCKADDR *)&sockin, sizeof(sockin)) != 0) {
		QMessageBox::critical(this, "錯誤", "無法建立伺服器", QMessageBox::Ok);
		closesocket(ssocket);
		return;
	}

	if (listen(ssocket, 5) != 0)
		return;
	has_created = true;

	online->setText("正在等候客戶端");
	FD_ZERO(&readfds);
	FD_SET(ssocket, &readfds);

	timeTimeout.tv_sec = 5;
	timeTimeout.tv_usec = 0;
	username_entry->setReadOnly(true);
	connect_btn->setDisabled(true);
}

void SocketServer2::handleAccept()
{
	SOCKADDR_IN client_addr;
	int client_addr_len = sizeof(client_addr);
	int r;
	std::string username_stdstr;
	char *username_str = new char[200];

	if (has_created && !has_accepted) {
			csocket = accept(ssocket, (SOCKADDR *)&client_addr, &client_addr_len);
			if (csocket == INVALID_SOCKET) {
				//QMessageBox::critical(NULL, "錯誤", "無法接收", QMessageBox::Ok);
				qDebug("無法接受到客戶端\n");
				return;
			}
			online->setText("已成功建立連線");
			username_stdstr = username_entry->text().toStdString();
			sprintf(username_str, "AddUser: %s\r\n", &username_stdstr[0]);
			send(csocket, username_str, strlen(username_str), 0);
			has_accepted = true;
	}
	delete[] username_str;
}

void SocketServer2::fontfamilychanged(const QString &text)
{
	QFont f;
	f = doc->property("font").value<QFont>();
	f.setFamily(text);
	doc->setFont(f);
}

void SocketServer2::fontsizechanged(const QString &text)
{
	QFont f;
	f = doc->property("font").value<QFont>();
	f.setPointSize(text.toInt());
	doc->setFont(f);
}

void SocketServer2::msgfontfamilychanged(const QString &text)
{
	QFont f;
	f = msg_entry->property("font").value<QFont>();
	f.setFamily(text);
	msg_entry->setFont(f);
}

void SocketServer2::msgfontsizechanged(const QString &text)
{
	QFont f;
	f = msg_entry->property("font").value<QFont>();
	f.setPointSize(text.toInt());
	msg_entry->setFont(f);
}

void SocketServer2::closeEvent(QCloseEvent *aevent)
{	
	closesocket(csocket);
	has_created = false;
	closesocket(ssocket);
	t_to_client->quit();
	apt_thread->quit();
	aevent->accept();
}

int SocketServer2::parsepackage(char* msg, QString &username, QString &content, QString &adduser)
{
	char type[100];
	char *tmp = new char[1001];
	int a;
	bool is_define_type = true;
	int startptr = 0;
	for (int i = 0; msg[i] != 0; i++) {
		if (msg[i] == ':') {
			if (is_define_type) {
				is_define_type = false;
				strncpy(type, msg + startptr, i - startptr);
				type[i - startptr] = 0;
				startptr = i + 2;
				i++;
			}
		}
		else if (msg[i] == '\r') {
			if (is_define_type) {
				return -1;
			}
			is_define_type = true;
			strncpy(tmp, msg + startptr, i - startptr);
			tmp[i - startptr] = '\0';
			if (!strcmp(type, "Username")) {
				username = QString(tmp);
			}
			else if (!strcmp(type, "Content")) {
				content = QString(tmp);
			}
			else if (!strcmp(type, "AddUser")) {
				adduser = QString(tmp);
			}
			else
				return -1;

			if (msg[i] == '\r') {
				startptr = i + 2;
				i++;
			}
			else
				startptr = i + 1;
		}
	}
	delete[] tmp;
	return 1;
}

void SocketServer2::addContent(QString & username, QString & content)
{
	QScrollBar *sb;
	doc->moveCursor(QTextCursor::End);
	doc->insertPlainText(username + " 說:\n   ");
	doc->insertPlainText(content);
	//sb = doc->verticalScrollBar();
	//sb->setValue(sb->maximum());
	doc->moveCursor(QTextCursor::End);
}

SocketServer2::~SocketServer2()
{
}
