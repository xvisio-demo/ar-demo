#include "imagepainter.h"

#include <QQuickWindow>
#include <QPainter>
#include <QMutexLocker>

ImagePainter::ImagePainter(QQuickItem *parent) : QQuickPaintedItem(parent)
{
}

void ImagePainter::paint(QPainter *painter)
{
    QMutexLocker l(&m_mutex);
    if(m_image.isNull()){
        QPixmap tmp(640,400);
        tmp.fill(Qt::black);
        painter->drawPixmap(QPoint(0,0), tmp);
    }else{
#ifdef USE_COLOR
        QImage im = m_image.convertToFormat(QImage::Format::Format_RGB32);
#else
        QImage im = m_image;
#endif
        double ratio  = 1.0;

        int h = painter->window().height();
        int w = painter->window().width();
        if( w != im.width() || h != im.height() ){
            QSize s = im.size();

            QImage tmp = im.scaled( w , h, Qt::KeepAspectRatio );


            double ratio1 = static_cast<double>(tmp.width()) / static_cast<double>(s.width());
            double ratio2 = static_cast<double>(tmp.height()) / static_cast<double>(s.height());
            ratio = std::min(ratio1,ratio2);

            if( m_mirrored ){
                painter->drawImage(QPoint(0,0),tmp.mirrored(true,true));
            }else{
                painter->drawImage(QPoint(0,0),tmp);
            }
        }else{
            if( m_mirrored ){
                painter->drawImage(QPoint(0,0),im.mirrored(true,true));
            }else{
                painter->drawImage(QPoint(0,0),im);
            }
        }
    }
}

QImage ImagePainter::image() const
{
    return m_image;
}

bool ImagePainter::mirrored() const
{
    return m_mirrored;
}

void ImagePainter::setImage(QImage image)
{
    if (m_image == image)
        return;

    QMutexLocker l(&m_mutex);
    m_image = image;
    emit imageChanged(m_image);
    update();
}

void ImagePainter::setMirrored(bool mirrored)
{
    if (m_mirrored == mirrored)
        return;

    m_mirrored = mirrored;
    emit mirroredChanged(m_mirrored);
    update();
}
