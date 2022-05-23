/* $BEGIN_LICENSE

This file is part of Minitube.
Copyright 2009, Flavio Tordini <flavio.tordini@gmail.com>

Minitube is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Minitube is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Minitube.  If not, see <http://www.gnu.org/licenses/>.

$END_LICENSE */

#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QtWidgets>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
typedef QEnterEvent CompatibleEnterEvent;
#else
typedef QEvent CompatibleEnterEvent;
#endif

class GridWidget : public QWidget {
    Q_OBJECT

public:
    GridWidget(QWidget *parent = nullptr);

signals:
    void activated();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(CompatibleEnterEvent *event);
    void leaveEvent(QEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    bool hovered;
    bool pressed;
};

#endif // GRIDWIDGET_H
