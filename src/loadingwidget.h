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

#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H

#include <QtWidgets>

#include "video.h"

class LoadingWidget : public QWidget {
    Q_OBJECT

public:
    LoadingWidget(QWidget *parent);
    void setVideo(Video *video);
    void setError(const QString &message);
    void clear();

protected:
    void resizeEvent(QResizeEvent *e);

public slots:
    void bufferStatus(qreal value);

private:
    void adjustFontSize();

    QLabel *titleLabel;
    QLabel *descriptionLabel;
    QProgressBar *progressBar;
    QElapsedTimer startTime;
};

#endif // LOADINGWIDGET_H
