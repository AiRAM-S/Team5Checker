//.cpp
#include"mydialog.h"
#include"widget.h"
#include<QPushButton>

myDialog::myDialog(QWidget *parent, Qt::WindowFlags f)
    :QDialog(parent, f)
{
    setFixedSize(550, 550);
    /*pix = new QLabel;
    pix->setScaledContents(true);
    pix->setPixmap(QPixmap(":/image/map.png"));
    pix->setFixedSize(600, 600);*/
    an = new QPushButton(this);
    an->setMinimumSize(400, 500);
    an->setFlat(true);
    an->setIconSize(QSize(600, 600));
    an->setIcon(QIcon(":/image/background.png"));
    //setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    QPalette palette ;
    palette.setColor(QPalette::Window,QColor("#b0e0e6"));  //窗口背景
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    this->setWindowTitle("跳棋");

    joinSuccessed = false;

    checker = new QLabel("跳棋");

    ch_logo = new QLabel("START");

    checker->setAlignment(Qt::AlignCenter);
    ch_logo->setAlignment(Qt::AlignCenter);

    join = new QPushButton("START");
    quit = new QPushButton("EXIT");

    join->setStyleSheet("QPushButton {border: 0px solid #dadbde;border-radius: 5px;background-color: rgb(255,255,255);color:green;font:bold 25px;}");
    quit->setStyleSheet("QPushButton {border: 0px solid #dadbde;border-radius: 5px;background-color:  rgb(255,255,255);color:black;font:bold 25px;}");

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(an);
    vbox->addWidget(join);
    vbox->addWidget(quit);
    setLayout(vbox);

    connect(quit, SIGNAL(clicked(bool)), this, SLOT(close()));  //不加入游戏
    connect(join, &QPushButton::clicked, [&]()  //加入游戏并关闭开始窗口
    {
        if(setplayer->currentIndex()!=-1&&settype->currentIndex()!=-1&&PORTS->text()!="请输入..."){
                    port=PORTS->text();
            joinSuccessed = true;
            hide();
        }
    });

    /*setplayer = new QComboBox(this);
    setplayer->setPlaceholderText(QStringLiteral("请选择玩家人数"));
    setplayer->setCurrentIndex(-1);
    setplayer->addItem("2");
    setplayer->addItem("3");
    setplayer->addItem("6");
    setplayer->setGeometry(180,325,150,30);*/

    settype=new QComboBox(this);
    settype->setPlaceholderText(QStringLiteral("请选择..."));
    settype->setCurrentIndex(-1);
    settype->addItem("Client");
    settype->addItem("Server");
    settype->setGeometry(180,355,150,30);

    PORT=new QLabel(this);
    PORT->move(178,390);
    PORT->setText("Port");
    PORT->setStyleSheet("color:white;font:bold 12px;}");

    QRegularExpression rx3;
    rx3.setPattern("[0-9.]{9,13}");
    QValidator *validator3 = new QRegularExpressionValidator(rx3,this);
    //QValidator *validator=new QIntValidator(1024, 49151, this);
    PORTS=new QLineEdit(this);
    PORTS->move(205,385);
    PORTS->setPlaceholderText("请输入...");
    PORTS->setStyleSheet("QLineEdit{color:black;font:11px}");
    PORTS->setValidator(validator3);

}
