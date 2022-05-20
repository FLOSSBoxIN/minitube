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

#include "downloadsettings.h"
#include "downloadmanager.h"
#include "mainwindow.h"

DownloadSettings::DownloadSettings(QWidget *parent) : QWidget(parent) {

    QBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);

    message = new QLabel(this);
    message->setOpenExternalLinks(true);
    layout->addWidget(message);

    changeFolderButton = new QPushButton(this);
    changeFolderButton->setText(tr("Change location..."));
    changeFolderButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    connect(changeFolderButton, SIGNAL(clicked()), SLOT(changeFolder()));
    layout->addWidget(changeFolderButton);

    updateMessage();
}

void DownloadSettings::paintEvent(QPaintEvent * /*event*/) {
    QPainter painter(this);
#ifdef APP_MAC
    QBrush brush;
    if (window()->isActiveWindow()) {
        brush = QBrush(QColor(0xdd, 0xe4, 0xeb));
    } else {
        brush = palette().window();
    }
    painter.fillRect(0, 0, width(), height(), brush);
#endif
    painter.setPen(palette().color(QPalette::Mid));
    painter.drawLine(0, 0, width(), 0);
}

void DownloadSettings::changeFolder() {
    const QString path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
#ifdef APP_MAC
    QFileDialog* dialog = new QFileDialog(this);
    dialog->setFileMode(QFileDialog::Directory);
    dialog->setOptions(QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks | QFileDialog::ReadOnly);
    dialog->setDirectory(path);
    dialog->open(this, SLOT(folderChosen(const QString &)));
#else

    QString folder = QFileDialog::getExistingDirectory(window(), tr("Choose the download location"),
                                                       path,
                                                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks | QFileDialog::ReadOnly);
    folderChosen(folder);
#endif
}

void DownloadSettings::folderChosen(const QString &dir) {
    if (!dir.isEmpty()) {
        QSettings settings;
        settings.setValue("downloadFolder", dir);
        updateMessage();
        QString status = tr("Download location changed.");
        if (DownloadManager::instance()->activeItems() > 0)
            status += " " + tr("Current downloads will still go in the previous location.");
        MainWindow::instance()->showMessage(status);
    }
}

void DownloadSettings::updateMessage() {
    const QString path = DownloadManager::instance()->currentDownloadFolder();
    const QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString displayPath = path;
    displayPath = displayPath.remove(home + "/");
    message->setText(
                tr("Downloading to: %1")
                .arg("<a href='file://%1' style='text-decoration:none; color:palette(text); font-weight:bold'>%2</a>")
                .arg(path, displayPath));
}
