/***********************************************************************
***********Copyright (c) 2009-2014 The Bitcoin developers***************
************Copyright (c) 2017-2019 The PIVX developers*****************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("mubdi:mubdLgywmL73JyTwQBfuU29CADz9yCJ99v?req-dontexist="));
    QVERIFY(!GUIUtil::parseMuBdIURI(uri, &rv));

    uri.setUrl(QString("mubdi:mubdLgywmL73JyTwQBfuU29CADz9yCJ99v?dontexist="));
    QVERIFY(GUIUtil::parseMuBdIURI(uri, &rv));
    QVERIFY(rv.address == QString("mubdLgywmL73JyTwQBfuU29CADz9yCJ99v"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("mubdi:mubdLgywmL73JyTwQBfuU29CADz9yCJ99v?label=Some Example Address"));
    QVERIFY(GUIUtil::parseMuBdIURI(uri, &rv));
    QVERIFY(rv.address == QString("mubdLgywmL73JyTwQBfuU29CADz9yCJ99v"));
    QVERIFY(rv.label == QString("Some Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("mubdi:mubdLgywmL73JyTwQBfuU29CADz9yCJ99v?amount=0.001"));
    QVERIFY(GUIUtil::parseMuBdIURI(uri, &rv));
    QVERIFY(rv.address == QString("mubdLgywmL73JyTwQBfuU29CADz9yCJ99v"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("mubdi:mubdLgywmL73JyTwQBfuU29CADz9yCJ99v?amount=1.001"));
    QVERIFY(GUIUtil::parseMuBdIURI(uri, &rv));
    QVERIFY(rv.address == QString("mubdLgywmL73JyTwQBfuU29CADz9yCJ99v"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("mubdi:mubdLgywmL73JyTwQBfuU29CADz9yCJ99v?amount=100&label=Some Example"));
    QVERIFY(GUIUtil::parseMuBdIURI(uri, &rv));
    QVERIFY(rv.address == QString("mubdLgywmL73JyTwQBfuU29CADz9yCJ99v"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));

    uri.setUrl(QString("mubdi:mubdLgywmL73JyTwQBfuU29CADz9yCJ99v?message=Some Example Address"));
    QVERIFY(GUIUtil::parseMuBdIURI(uri, &rv));
    QVERIFY(rv.address == QString("mubdLgywmL73JyTwQBfuU29CADz9yCJ99v"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseMuBdIURI("mubdi://mubdLgywmL73JyTwQBfuU29CADz9yCJ99v?message=Some Example Address", &rv));
    QVERIFY(rv.address == QString("mubdLgywmL73JyTwQBfuU29CADz9yCJ99v"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("mubdi:mubdLgywmL73JyTwQBfuU29CADz9yCJ99v?req-message=Some Example Address"));
    QVERIFY(GUIUtil::parseMuBdIURI(uri, &rv));

    uri.setUrl(QString("mubdi:mubdLgywmL73JyTwQBfuU29CADz9yCJ99v?amount=1,000&label=Some Example"));
    QVERIFY(GUIUtil::parseMuBdIURI(uri, &rv));

    uri.setUrl(QString("mubdi:mubdLgywmL73JyTwQBfuU29CADz9yCJ99v?amount=1,000.0&label=Some Example"));
    QVERIFY(!GUIUtil::parseMuBdIURI(uri, &rv));
}
