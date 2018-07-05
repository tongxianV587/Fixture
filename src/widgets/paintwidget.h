#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QGraphicsItem>
#include <QImageReader>
#include <QWheelEvent>
#include <QScrollBar>
#include <QObject>
#include <QFileInfo>
#include <QMimeData>
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>

#include <iostream>
#include <cmath>

#include "../items/drawing.h"
#include "../widgets/paintwidget.h"
#include "../model/canvas.h"
#include "../items/layer.h"

class PaintWidget : public QGraphicsView
{
    Q_OBJECT
public:
    PaintWidget(const QString &imagePath, QWidget *parent=0);
    PaintWidget(const Canvas *document, QWidget *parent=0);
    
    inline void setImagePath(QString path) { _imagePath = path; }
    inline QString getImagePath() const { return _imagePath; }
    inline QList<Layer> getItems() const { return _items; }
    // This has to be extended to accomodate new documents
    inline void updateLayers(QList<Layer> items){ d->updateImageCanvas(items); }
    static bool isFileValid(const QString& fileName);

public slots:
    void addNewLayer(const QString &imagePath);

protected:
    void wheelEvent(QWheelEvent *event);

private:
    Drawing *d;
    QString _imagePath;
    void addStyleSheet();
    QList<Layer> _items;
    QImage getImageFromPath(const QString &imagePath);
    void setupCanvas(QImage image);
    void pushLayer(QImage image, const QString &name);
    bool isRaw(const QString &imagePath);

    static bool isImageSupported(const QString& fileName);
};

#endif // PAINTWIDGET_H
