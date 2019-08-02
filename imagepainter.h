#ifndef IMAGEPAINTER_H
#define IMAGEPAINTER_H

#include <QQuickPaintedItem>
#include <QPixmap>
#include <QMutex>

class ImagePainter : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(bool mirrored READ mirrored WRITE setMirrored NOTIFY mirroredChanged)
public:
    explicit ImagePainter(QQuickItem *parent = nullptr);

    void paint(QPainter *painter);

    QImage image() const;
    bool mirrored() const;
private:
    QMutex m_mutex;
    QImage m_image;
    bool m_mirrored = false;

signals:
    void imageChanged(QImage image);
    void mirroredChanged(bool mirrored);

public slots:
    void setImage(QImage image);
    void setMirrored(bool mirrored);
};

#endif // IMAGEPAINTER_H
