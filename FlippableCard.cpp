#include "FlippableCard.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QSequentialAnimationGroup>
static const QStringList cardColorList{"lightblue","lightgreen","lightpink","thistle"};
FlippableCard::FlippableCard(const QString & cardName,QWidget *parent) :
    QWidget(parent),mCardName(cardName),mFrontLayout(nullptr),mBackLayout(nullptr),mFlipAnim(nullptr),mFlipAngle(0)
{
    setFixedSize(150,150);

    static int cardIndex = 0;
    mCardIndex = cardIndex++ % cardColorList.size();
    setStyleSheet("border-radius:8px; background:" + cardColorList[mCardIndex] + ";");
    //init font page
    mFront = new QWidget(this);
    mFront->setFixedSize(this->size());
    QLabel* title = new QLabel(cardName,mFront);
    QFont font("Microsoft YaHei",12,2);
    title->setFont(font);
    title->move(8,4);

    NeatButton * settingButton = new NeatButton("🔧",mFront);
    settingButton->move(110,2);
    connect(settingButton,&NeatButton::clicked,this,[=](){
         flipToBackpage();
    });

    mFrontLayout = new QVBoxLayout(mFront);
    mFrontLayout->setContentsMargins(0,42,0,0);

    //init back page
    mBack = new QWidget(this);
    mBack->setFixedSize(this->size());
    auto* retBtn = new NeatButton("<",mBack);
    retBtn->move(110,2);
    connect(retBtn,&NeatButton::clicked,this,[=](){
        flipToFrontpage();
    });
    mBackLayout = new QVBoxLayout(mBack);
    mBackLayout->setContentsMargins(12,12,12,12);
    mBack->hide();

}
void FlippableCard::setFrontContent(QWidget* w){
    if(w && mFrontLayout) mFrontLayout->addWidget(w);
}
void FlippableCard::setBackContent(QWidget* w){
    if(w && mBackLayout) mBackLayout->addWidget(w);
}
void FlippableCard::flipToBackpage(){
    if(!mBack) return;
    //auto* group = new QSequentialAnimationGroup(this);
    //auto*
}
void FlippableCard::flipToFrontpage(){

}
//void FlippableCard::paintEvent(QPaintEvent* e){
//    if(!e) return;
//    QPainter painter(this);
//    QColor background(cardColorList[mCardIndex]);
//    painter.setPen(Qt::NoPen);
//    painter.setBrush(background);
//    painter.drawRoundedRect(rect(),8,8);
//    qDebug() << "in paintEvent,background:" << rect();
//    QWidget::paintEvent(e);
//}

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
    static const QFont font("Microsoft YaHei",12,2);
    painter.setFont(font);
    painter.drawText(e->rect(),Qt::AlignCenter,mText);

}
void NeatButton::mousePressEvent(QMouseEvent*){
    if(mIsHovering) emit clicked();
}
