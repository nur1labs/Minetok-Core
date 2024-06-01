/***********************************************************************
***********Copyright (c) 2011-2020 The Bitcoin developers***************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT/X11 software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#ifndef MUBDI_QT_MACDOCKICONHANDLER_H
#define MUBDI_QT_MACDOCKICONHANDLER_H

#include <QMainWindow>
#include <QObject>

/** Macintosh-specific dock icon handler.
 */
class MacDockIconHandler : public QObject
{
    Q_OBJECT

public:
    static MacDockIconHandler* instance();
    static void cleanup();

Q_SIGNALS:
    void dockIconClicked();

private:
    MacDockIconHandler();
};

#endif /* MUBDI_QT_MACDOCKICONHANDLER_H */
