/***********************************************************************
***************Copyright (c) 2019 The PIVX developers*******************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#ifndef SETTINGSMUBTOOLWIDGET_H
#define SETTINGSMUBTOOLWIDGET_H

#include <QWidget>
#include "qt/mubdi/pwidget.h"
#include "qt/mubdi/contactsdropdown.h"
#include "key.h"

namespace Ui {
class SettingsMubToolWidget;
}

class SettingsMubToolWidget : public PWidget
{
    Q_OBJECT

public:
    explicit SettingsMubToolWidget(MuBdIGUI* _window, QWidget *parent = nullptr);
    ~SettingsMubToolWidget();
protected:
    void resizeEvent(QResizeEvent *event) override;
public Q_SLOTS:
    void onEncryptSelected(bool isEncr);
    void setAddress_ENC(const QString& address);
    void onEncryptKeyButtonENCClicked();
    void onClearAll();
    void onClearDecrypt();
    void onAddressesClicked();
    void onDecryptClicked();
    void importAddressFromDecKey();

private:
    Ui::SettingsMubToolWidget *ui;
    QAction *btnContact;
    ContactsDropdown *menuContacts = nullptr;

    // Cached key
    CKey key;

    void resizeMenu();
};

#endif // SETTINGSBITTOOLWIDGET_H
