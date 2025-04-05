#ifndef DRAW_H
#define DRAW_H

#include <QWidget>

class Draw : public QWidget
{
    Q_OBJECT

private:
    QPolygonF building;
    QPolygonF ch;
    QPolygonF maer;
    QPolygonF erpca;
    QPolygonF le;
    QPolygonF we;
public:
    explicit Draw(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *event);
    void switch_source();
    QPolygonF getBuilding()const {return building;}
    void setCH(QPolygonF &ch_){ch = ch_;}
    void setMAER(QPolygonF &maer_){maer = maer_;}
    void setERPCA(QPolygonF &erpca_){erpca= erpca_;}
    void setLE(QPolygonF &le_){le= le_;}
    void setWE(QPolygonF &we_){we= we_;}

signals:
};

#endif // DRAW_H
