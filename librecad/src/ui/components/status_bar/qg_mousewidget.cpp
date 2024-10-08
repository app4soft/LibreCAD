/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software 
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!  
**
**********************************************************************/
#include "qg_mousewidget.h"

#include <QVariant>
#include <QSettings>

#include "rs_settings.h"
#include "lc_modifiersinfo.h"

/*
 *  Constructs a QG_MouseWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
QG_MouseWidget::QG_MouseWidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, fl){
    setObjectName(name);
    setupUi(this);

    QSettings settings;
    settings.beginGroup("Widgets");
    int allow_statusbar_height = settings.value("AllowStatusbarHeight", 0).toInt();
    int height {64};
    if (allow_statusbar_height) {
        height = settings.value( "StatusbarHeight", 64).toInt();
    }

    setMinimumHeight( height);
    setMaximumHeight( height);
    lLeftButton->setText("");
    lRightButton->setText("");
    lMousePixmap->setPixmap( QPixmap(":/icons/mouse.svg").scaled( height, height));

    int halfHeight = height/2 - 2;
    lblCtrl->setMinimumSize(halfHeight, halfHeight);
    lblCtrl->setMaximumSize(halfHeight, halfHeight);
    lblShift->setMinimumSize(halfHeight, halfHeight);
    lblShift->setMaximumSize(halfHeight, halfHeight);

    lblShift->setPixmap(QPixmap(":/icons/state-shift_yes.svg").scaled(halfHeight, halfHeight));
    lblCtrl->setPixmap(QPixmap(":/icons/state_ctrl_yes.svg").scaled(halfHeight, halfHeight));
//    gridLayout->setAlignment(lblCtrl,Qt::AlignCenter);
//    gridLayout->setAlignment(lblShift,Qt::AlignCenter);
}

/*
 *  Destroys the object and frees any allocated resources
 */
QG_MouseWidget::~QG_MouseWidget(){
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void QG_MouseWidget::languageChange(){
    retranslateUi(this);
}

void QG_MouseWidget::setHelp(const QString& left, const QString& right, const LC_ModifiersInfo& modifiersInfo) const {

    const QString &shiftMsg = modifiersInfo.getShiftMessage();
    setupModifier(lblShift, shiftMsg);

    const QString &ctrlMessage = modifiersInfo.getCtrlMessage();
    setupModifier(lblCtrl, ctrlMessage);

    lLeftButton->setText(left);
    lRightButton->setText(right);
}

void QG_MouseWidget::setupModifier(QLabel *btn, const QString& helpMsg) const{
    if (helpMsg != nullptr){
        btn->setVisible(true);
        btn->setToolTip(helpMsg);
    }
    else {
        btn->setVisible(false);
        btn->setToolTip("");
    }
}
