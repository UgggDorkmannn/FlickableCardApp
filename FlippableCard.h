#ifndef FLIPPABLECARD_H
#define FLIPPABLECARD_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QPropertyAnimation>
class NeatButton:public QWidget{
    Q_OBJECT
public:
    explicit NeatButton(const QString & str, QWidget* parent = nullptr);

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
private:
    QString mText;
    bool mIsHovering;
signals:
    void clicked();
};

class FlippableCard : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal flipAngle READ getFlipAngle WRITE setFlipAngle)
public:
    explicit FlippableCard(const QString & cardName,QWidget *parent = nullptr);

    void setFrontContent(QWidget* w);
    void setBackContent(QWidget* w);

    qreal getFlipAngle()const{return mFlipAngle;}
    void setFlipAngle(qreal a){mFlipAngle = a;}
protected:
    //void paintEvent(QPaintEvent*);
private:
    void flipToBackpage();
    void flipToFrontpage();

private:
    QWidget* mFront;
    QWidget* mBack;
    QVBoxLayout * mFrontLayout;
    QVBoxLayout * mBackLayout;
    QString mCardName;
    QPropertyAnimation* mFlipAnim;
    qreal mFlipAngle;
    int mCardIndex;
};

#endif // FLIPPABLECARD_H
