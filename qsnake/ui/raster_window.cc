#include <QRect>
#include <iostream>

#include "log/log.h"
#include "raster_window.h"

RasterWindow::RasterWindow(QWindow *parent)
    : QWindow(parent), m_backingStore(new QBackingStore(this)) {
    setGeometry(200, 200, 800, 800);
    Log::d("RasterWindow is built");
}

//! [7]
bool RasterWindow::event(QEvent *event) {
    if (event->type() == QEvent::UpdateRequest) {
        renderNow();
        return true;
    }
    return QWindow::event(event);
}

void RasterWindow::renderLater() {
    Log::d("RasterWindow::renderLater() is called");
    requestUpdate();
}

void RasterWindow::resizeEvent(QResizeEvent *resizeEvent) {
    Log::d("RasterWindow::resizeEvent(QResizeEvent *resizeEvent) is called");
    m_backingStore->resize(resizeEvent->size());
}

void RasterWindow::exposeEvent(QExposeEvent *) {
    Log::d("RasterWindow::exposeEvent(QExposeEvent *) is called");
    if (isExposed())
        renderNow();
}

void RasterWindow::renderNow() {
    Log::d("RasterWindow::renderNow() is called");
    if (!isExposed())
        return;

    QRect rect(0, 0, width(), height());
    m_backingStore->beginPaint(rect);

    QPaintDevice *device = m_backingStore->paintDevice();
    QPainter painter(device);

    painter.fillRect(0, 0, width(), height(), QColor("#ffffff"));
    render(&painter);
    painter.end();

    m_backingStore->endPaint();
    m_backingStore->flush(rect);
}

void RasterWindow::render(QPainter *painter) {
    painter->save();
    // painter->drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, QStringLiteral("QWindow"));
    Log::d("RasterWindow::render(QPainter *painter) is called");
}
