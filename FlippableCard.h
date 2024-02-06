#ifndef FLIPPABLECARD_H
#define FLIPPABLECARD_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QVBoxLayout>
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
public:
    explicit FlippableCard(const QString & cardName,QWidget *parent = nullptr);

    void setFrontContent(QWidget* w);
    void setBackContent(QWidget* w);

signals:

public slots:

private:
    QWidget* mFront;
    QWidget* mBack;
    QVBoxLayout * mFrontLayout;
    QVBoxLayout * mBackLayout;
    QString mCardName;
};

#endif // FLIPPABLECARD_H