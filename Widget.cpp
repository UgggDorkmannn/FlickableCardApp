#include "Widget.h"
#include "ui_Widget.h"
#include "FlippableCard.h"
#include <QLabel>
#include <QCheckBox>
Widget::Widget(QWidget *parent) :QWidget(parent)
{
    setObjectName("idCardContainer");
    setStyleSheet("#idCardContainer{background:darkgray}");

    setFixedSize(320,320);
    FlippableCard * card1 = new FlippableCard("最冷天气",this);
    FlippableCard * card2 = new FlippableCard("西方财富" , this);
    FlippableCard * card3 = new FlippableCard("合金浏览器" , this);
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
        auto* coat = new QCheckBox("显示穿衣指数");
        auto* privacy = new QCheckBox("上传个人信息");
        auto* layoutBack = new QVBoxLayout(back);
        layoutBack->addWidget(ad);
        layoutBack->addWidget(coat);
        layoutBack->addWidget(privacy);
        card1->setBackContent(back);


    }

}

Widget::~Widget()
{
}
