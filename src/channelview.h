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

#ifndef CHANNELSVIEW_H
#define CHANNELSVIEW_H

#include <QtWidgets>

class VideoSource;
class ChannelModel;
class ChannelListView;

class ChannelView : public QWidget {
    Q_OBJECT

public:
    ChannelView(QWidget *parent = nullptr);

signals:
    void activated(VideoSource *videoSource);

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private:
    enum SortBy {
        SortByName = 0,
        SortByAdded,
        SortByUpdated,
        SortByLastWatched,
        SortByMostWatched
    };

private slots:
    void itemActivated(const QModelIndex &index);
    void showContextMenu(const QPoint &point);
    void toggleShowUpdated(bool enable);
    void setSortBy(SortBy sortBy);
    void setSortByName() { setSortBy(SortByName); }
    void setSortByUpdated() { setSortBy(SortByUpdated); }
    void setSortByAdded() { setSortBy(SortByAdded); }
    void setSortByLastWatched() { setSortBy(SortByLastWatched); }
    void setSortByMostWatched() { setSortBy(SortByMostWatched); }
    void markAllAsWatched();
    void unwatchedCountChanged(int count);
    void updateQuery(bool transition = false);

private:
    void setupActions();
    QString noSubscriptionsMessage();

    ChannelListView *listView;
    ChannelModel *channelsModel;
    QVector<QAction *> statusActions;
    bool showUpdated;
    SortBy sortBy;
    QAction *markAsWatchedAction;
};

#endif // CHANNELSVIEW_H
