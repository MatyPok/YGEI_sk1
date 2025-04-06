#ifndef DRAW_H
#define DRAW_H

#include <QWidget>

// U1
#include <QObject>
#include <QVector>
#include <QPolygonF>
#include <QFile>
#include <vector>

#include "ogrsf_frmts.h"

class Draw : public QWidget
{
    Q_OBJECT

private:
    QPolygonF building;
    QPolygonF ch;
    QVector<QPolygonF> maer;
    QVector<QPolygonF> erpca;
    QVector<QPolygonF> le;
    QVector<QPolygonF> we;

    //přidávám zatím všechno co máme navíc v U1 a může se hodit
    QPointF q;
    QPolygonF pol;

    QVector<QPolygonF> polygons;

    //bool add_point;
    bool isShapefileLoaded;

public:
    explicit Draw(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *event);
    //void switch_source();

    QPolygonF getBuilding()const {return building;}

    void setCH(QPolygonF &ch_){ch = ch_;}
    void setMAER(QVector<QPolygonF> &maer_){maer = maer_;}
    void setERPCA(QVector<QPolygonF> &erpca_){erpca= erpca_;}
    void setLE(QVector<QPolygonF> &le_){le= le_;}
    void setWE(QVector<QPolygonF> &we_){we= we_;}

    //přidávám zatím všechno co máme navíc v U1 a může se hodit
    QPointF getQ() const{return q;}
    QPolygonF getPol() const{return pol;}
    QVector<QPolygonF> getPolygons() const{return polygons;}

    void openFile();
    void openSHP();

    void clear();
    void clearResults();


signals:
};

#endif // DRAW_H


