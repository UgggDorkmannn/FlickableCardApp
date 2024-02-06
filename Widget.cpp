#include "Widget.h"
#include "ui_Widget.h"
#include "FlippableCard.h"
#include <QLabel>
#include <QCheckBox>
Widget::Widget(QWidget *parent) :QWidget(parent)
{
    QPalette pa;
    pa.setColor(QPalette::Background,QColor("darkgray"));
    setPalette(pa);

    setFixedSize(320,320);
    FlippableCard * card1 = new FlippableCard("最冷天气" , this);
    FlippableCard * card2 = new FlippableCard("西方财富" , this);
    FlippableCard * card3 = new FlippableCard("部落冲突" , this);
    FlippableCard * card4 = new FlippableCard("宜家家居" , this);

    card1->move(8,8);
    card2->move(8,162);
    card3->move(162,8);
    card4->move(162,162);

    {//card1
        auto* front = new QWidget;
        auto* temperature = new QLabel("当前气温: 零度");
        auto* wind = new QLabel("风力: 5级");
        auto* tip = new QLabel("出行建议: 打车");
        auto* layout = new QVBoxLayout(front);
        layout->addWidget(temperature);
        layout->addWidget(wind);
        layout->addWidget(tip);
        layout->addStretch();
        card1->setFrontContent(front);


        auto* back = new QWidget;
        auto* ad = new QCheckBox("关闭广告");
        const QString cbstyle("QCheckBox { background-color: transparent; }");
        ad->setStyleSheet(cbstyle);
        auto* coat = new QCheckBox("显示穿衣指数");
        coat->setStyleSheet(cbstyle);
        auto* privacy = new QCheckBox("上传个人信息");
        privacy->setStyleSheet(cbstyle);

        auto* layoutBack = new QVBoxLayout(back);
        layoutBack->addWidget(ad);
        layoutBack->addWidget(coat);
        layoutBack->addWidget(privacy);
        layoutBack->addStretch();
        card1->setBackContent(back);
    }
}

Widget::~Widget()
{
}
