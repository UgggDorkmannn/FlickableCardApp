#include "FlippableCard.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QLabel>
FlippableCard::FlippableCard(const QString & cardName,QWidget *parent) :
    QWidget(parent),mCardName(cardName),mFrontLayout(nullptr),mBackLayout(nullptr)
{
    setFixedSize(150,150);

    static int cardIndex = 0;
    static const QStringList cardColorList{"lightblue","lightgreen","lightpink","thistle"};
    setStyleSheet("border-radius:8px;background:" +
                  cardColorList[cardIndex++ % cardColorList.size()] + ";");

    mFront = new QWidget(this);
    mFront->setFixedSize(150,150);
    QLabel* title = new QLabel(cardName,mFront);
    QFont font("Microsoft YaHei",12,2);
    title->setFont(font);


    NeatButton * settingButton = new NeatButton("🔧",mFront);
    title->move(8,4);
    settingButton->move(110,2);
    connect(settingButton,&NeatButton::clicked,this,[=](){
         qDebug() << "setting button clicked";
    });


    mFrontLayout = new QVBoxLayout(mFront);
    mFrontLayout->setContentsMargins(0,42,0,0);





}
void FlippableCard::setFrontContent(QWidget* w){
    if(w && mFrontLayout) mFrontLayout->addWidget(w);
}
void FlippableCard::setBackContent(QWidget* w){
    if(w && mBackLayout) mBackLayout->addWidget(w);
}

NeatButton::NeatButton(const QString & str, QWidget* parent):
    QWidget(parent),mText(str),mIsHovering(false)
{
    setMouseTracking(true);
    setFixedSize(32,32);
}

void NeatButton::enterEvent(QEvent*){
    mIsHovering = true;
    setCursor(Qt::PointingHandCursor);
    update();
}
void NeatButton::leaveEvent(QEvent*){
    mIsHovering = false;
    setCursor(Qt::ArrowCursor);
    update();
}

void NeatButton::paintEvent(QPaintEvent* e){
    if(!e) return;
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    if(mIsHovering){
        //draw background
        QColor background("black");
        background.setAlphaF(0.16);
        painter.setBrush(background);
        painter.drawRoundedRect(e->rect(),4,4);
    }
    else{
        painter.setBrush(Qt::NoBrush);
    }

    //draw text;

    painter.setPen(Qt::black);
    static const QFont font("Microsoft YaHei",15,2);
    painter.setFont(font);
    painter.drawText(e->rect(),Qt::AlignCenter,mText);

}
void NeatButton::mousePressEvent(QMouseEvent*){
    if(mIsHovering) emit clicked();
}
