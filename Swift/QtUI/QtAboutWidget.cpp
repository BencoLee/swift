/*
 * Copyright (c) 2010-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <Swift/QtUI/QtAboutWidget.h>

#include <QCoreApplication>
#include <QFile>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QTextStream>
#include <QVBoxLayout>
#include <QtGlobal>

#include <Swiften/Base/Log.h>
#include <Swiften/Base/Platform.h>

#include <Swift/QtUI/QtSwiftUtil.h>
#include <Swift/QtUI/QtUISettingConstants.h>
#include <Swift/QtUI/QtUpdateFeedSelectionDialog.h>
#include <Swift/QtUI/SwiftUpdateFeeds.h>

namespace Swift {

QtAboutWidget::QtAboutWidget(SettingsProvider* settingsProvider) : QDialog(), settingsProvider_(settingsProvider) {
#ifndef Q_OS_MAC
    setWindowTitle(QString(tr("About %1")).arg("Swift"));
#endif
    setWindowIcon(QIcon(":/logo-icon-16.png"));

    resize(180, 240);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignHCenter);
    setLayout(mainLayout);

    QLabel* iconLabel = new QLabel(this);
    iconLabel->setPixmap(QIcon(":/logo-shaded-text.256.png").pixmap(90, 90));
    iconLabel->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(iconLabel);

    QLabel* appNameLabel = new QLabel("<center><font size='+1'><b>" + QCoreApplication::applicationName() + "</b></font></center>", this);
    mainLayout->addWidget(appNameLabel);

    QLabel* versionLabel = new QLabel((QString("<center><font size='-1'>") + tr("Version %1") + "</font></center><center><font size='-1'><br/>" + QString(tr("Built with Qt %2")) + QString("<br/>") + QString(tr("Running with Qt %3")) + "</font></center>").arg(QCoreApplication::applicationVersion()).arg(QT_VERSION_STR).arg(qVersion()));
    versionLabel->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    mainLayout->addWidget(versionLabel);

    settingsChangedConnection_ = settingsProvider_->onSettingChanged.connect([&](const std::string& path) {
        if (path == QtUISettingConstants::SOFTWARE_UPDATE_CHANNEL.getKey() || path == QtUISettingConstants::ENABLE_SOFTWARE_UPDATES.getKey()) {
            updateUpdateInfoLabel();
        }
    });

    updateInfoLabel_ = new QLabel("", this);
    updateInfoLabel_->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard | Qt::LinksAccessibleByMouse);
    connect(updateInfoLabel_, SIGNAL(linkActivated(const QString &)), this, SLOT(handleChangeUpdateChannelClicked()));
    mainLayout->addWidget(updateInfoLabel_);

    updateUpdateInfoLabel();

    if (QCoreApplication::translate("TRANSLATION_INFO", "TRANSLATION_AUTHOR") != "TRANSLATION_AUTHOR") {
        mainLayout->addWidget(new QLabel(QString("<center><font size='-1'>") + QString(tr("Using the English translation by\n%1")).arg(QCoreApplication::translate("TRANSLATION_INFO", "TRANSLATION_AUTHOR")).replace("\n", "<br/>") + "</font></center>", this));
    }
    QCoreApplication::translate("TRANSLATION_INFO", "TRANSLATION_LICENSE", "This string contains the license under which this translation is licensed. We ask you to license the translation under the BSD license. Please read http://www.opensource.org/licenses/bsd-license.php, and if you agree to release your translation under this license, use the following (untranslated) text: 'This translation is licensed under the BSD License. See http://www.opensource.org/licenses/bsd-license.php'");
#if defined(SWIFTEN_PLATFORM_WINDOWS) || defined(SWIFTEN_PLATFORM_MACOSX)
    QPushButton* licenseButton = new QPushButton(tr("View License"), this);
    mainLayout->addWidget(licenseButton);
    connect(licenseButton, SIGNAL(clicked()), this, SLOT(handleLicenseClicked()));

    QPushButton* changelogButton = new QPushButton(tr("View Changes"), this);
    mainLayout->addWidget(changelogButton);
    connect(changelogButton, SIGNAL(clicked()), this, SLOT(handleChangelogClicked()));
#else
    // Some Linux desktops have dialog window decorations without close window buttons.
    // This code adds a dedicated button to close the about window dialog.
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    mainLayout->addLayout(buttonLayout);

    QPushButton* licenseButton = new QPushButton(tr("View License"), this);
    buttonLayout->addWidget(licenseButton);
    connect(licenseButton, SIGNAL(clicked()), this, SLOT(handleLicenseClicked()));

    QPushButton* changelogButton = new QPushButton(tr("View Changes"), this);
    buttonLayout->addWidget(changelogButton);
    connect(changelogButton, SIGNAL(clicked()), this, SLOT(handleChangelogClicked()));

    buttonLayout->addItem(new QSpacerItem(20,20));

    QPushButton* closeButton = new QPushButton(tr("Close"), this);
    buttonLayout->addWidget(closeButton);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(accept()));
#endif
    setFixedSize(minimumSizeHint());
}

void QtAboutWidget::handleLicenseClicked() {
    openPlainTextWindow(":/COPYING");
}

void QtAboutWidget::handleChangelogClicked() {
    openPlainTextWindow(":/ChangeLog.md");
}

void QtAboutWidget::handleChangeUpdateChannelClicked() {
    auto feedSelectionDialog = new QtUpdateFeedSelectionDialog(settingsProvider_);
    feedSelectionDialog->show();
}

void QtAboutWidget::openPlainTextWindow(const QString& path) {
    QTextEdit* text = new QTextEdit();
    text->setAttribute(Qt::WA_DeleteOnClose);
    text->setReadOnly(true);
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        in.setCodec("UTF-8");
        text->setPlainText(in.readAll());
        file.close();
        text->resize(500, 600);
        text->show();
        text->activateWindow();
    }
    else {
        SWIFT_LOG(error) << "Failed to open " << Q2PSTRING(path) << "." << std::endl;
    }
}

void QtAboutWidget::updateUpdateInfoLabel() {
    if (settingsProvider_->getSetting(QtUISettingConstants::ENABLE_SOFTWARE_UPDATES)) {
        if (!settingsProvider_->getSetting(QtUISettingConstants::SOFTWARE_UPDATE_CHANNEL).empty()) {
            QString updateFeedDescription;
            auto addUpdateFeedDialogLink = false;
            if (settingsProvider_->getSetting(QtUISettingConstants::SOFTWARE_UPDATE_CHANNEL) == UpdateFeeds::StableChannel) {
                updateFeedDescription = tr("You are receiving updates from the Stable update channel.");
                addUpdateFeedDialogLink = true;
            }
            else if (settingsProvider_->getSetting(QtUISettingConstants::SOFTWARE_UPDATE_CHANNEL) == UpdateFeeds::DevelopmentChannel) {
                updateFeedDescription = tr("You are receiving updates from the Development update channel.");
                addUpdateFeedDialogLink = true;
            }
            else if (settingsProvider_->getSetting(QtUISettingConstants::SOFTWARE_UPDATE_CHANNEL) == UpdateFeeds::TestingChannel) {
                updateFeedDescription = tr("You are receiving updates from the Testing update channel.");
                addUpdateFeedDialogLink = true;
            }
            auto updateFeedDialogLink = QString( addUpdateFeedDialogLink ? "<a href=\"#\">%1</a>" : "" ).arg(tr("Change the update channel."));
            updateInfoLabel_->setText(QString("<center><font size='-1'>%1<br/>%2</font></center>").arg(updateFeedDescription, updateFeedDialogLink));
            updateInfoLabel_->show();
        }
        else {
            updateInfoLabel_->hide();
        }
    }
    else {
        updateInfoLabel_->hide();
    }

}

}
