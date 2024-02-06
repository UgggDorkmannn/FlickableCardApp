#include "FlippableCard.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QSequentialAnimationGroup>
#include <QtMath>
#include <stdlib.h>
static const QStringList cardColorList{"lightblue","lightgreen","lightpink","thistle"};
FlippableCard::FlippableCard(const QString & cardName,QWidget *parent) :
    QWidget(parent),mCardName(cardName),mFrontLayout(nullptr),mBackLayout(nullptr),mFlipAngle(0),mAnimRunning(false)
{
    setFixedSize(150,150);

    static int cardIndex = 0;
    mCardIndex = cardIndex++ % cardColorList.size();
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
        flip(mFront,mBack);
    });

    mFrontLayout = new QVBoxLayout();
    mFrontLayout->setContentsMargins(0,42,0,0);
    mFront->setLayout(mFrontLayout);

    //init back page
    mBack = new QWidget(this);
    mBack->setFixedSize(this->size());
    auto* retBtn = new NeatButton("<",mBack);
    retBtn->move(110,2);
    connect(retBtn,&NeatButton::clicked,this,[=](){
        flip(mBack,mFront);
    });
    mBackLayout = new QVBoxLayout();
    mBackLayout->setContentsMargins(4,40,4,4);
    mBack->setLayout(mBackLayout);

    mBack->hide();
}
void FlippableCard::setFrontContent(QWidget* w){
    if(w && mFrontLayout) {
        mFrontLayout->addWidget(w);
    }

}
void FlippableCard::setBackContent(QWidget* w){
    if(w && mBackLayout)
        mBackLayout->addWidget(w);
}
void FlippableCard::flip(QWidget* toHide,QWidget* toShow){

    if(!toShow || !toHide) return;

    auto* group = new QSequentialAnimationGroup(this);
    auto * anim1 = new QPropertyAnimation(this,"flipAngle");
    anim1->setDuration(500);
    anim1->setStartValue(0);
    anim1->setEndValue(90);
    group->addAnimation(anim1);

    auto* anim2 = new QPropertyAnimation(this,"flipAngle");
    anim2->setDuration(500);
    anim2->setStartValue(90);
    anim2->setEndValue(180);
    group->addAnimation(anim2);

    connect(group,&QSequentialAnimationGroup::finished,this,[=](){
        mAnimRunning = false;
        mFlipAngle = 0;
        toShow->show();
        mToShowPixmap = mToHidePixmap;
        update();
        delete group;
        qDebug() << "all anim over";
    });

    mToHidePixmap = grab(rect());
    toHide->hide();
    if(mToShowPixmap.isNull()){
        toShow->show();
        mToShowPixmap = grab(rect());
        toShow->hide();
    }

    group->start();
    mAnimRunning = true;
}
qreal FlippableCard::getFlipAngle()const{return mFlipAngle;}
void  FlippableCard::setFlipAngle(qreal a){
    mFlipAngle = a;
    update();
}
void FlippableCard::paintEvent(QPaintEvent* e){
    if(!e) return;

    QPainter painter(this);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(cardColorList[mCardIndex]));

    const auto cx = width()/2;
    const auto cy = height()/2;
    painter.translate(cx,cy);

    const qreal r = qAbs<qreal>(90 - mFlipAngle) / 90.0;
    painter.scale(r,1);
    painter.translate(-cx,-cy);
    painter.drawRoundedRect(rect(),8,8);

    if(mAnimRunning){
        if(mFlipAngle < 90)
            painter.drawPixmap( rect(),mToHidePixmap,this->rect());
        else
            painter.drawPixmap( rect(),mToShowPixmap,this->rect());
    }
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
    static const QFont font("Microsoft YaHei",12,2);
    painter.setFont(font);
    painter.drawText(e->rect(),Qt::AlignCenter,mText);

}
void NeatButton::mousePressEvent(QMouseEvent*){
    if(mIsHovering) emit clicked();
}
