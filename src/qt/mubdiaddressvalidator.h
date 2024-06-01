/***********************************************************************
***********Copyright (c) 2011-2014 The Bitcoin developers***************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT/X11 software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#ifndef MUBDI_QT_MUBDIADDRESSVALIDATOR_H
#define MUBDI_QT_MUBDIADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class MuBdIAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit MuBdIAddressEntryValidator(QObject* parent);

    State validate(QString& input, int& pos) const;
};

/** MuBdI address widget validator, checks for a valid mubdi address.
 */
class MuBdIAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit MuBdIAddressCheckValidator(QObject* parent);

    State validate(QString& input, int& pos) const;
};

#endif /* MUBDI_QT_MUBDIADDRESSVALIDATOR_H */
