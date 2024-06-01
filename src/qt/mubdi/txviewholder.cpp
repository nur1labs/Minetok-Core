/***********************************************************************
***************Copyright (c) 2019 The PIVX developers*******************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#include "qt/mubdi/txviewholder.h"
#include "qt/mubdi/qtutils.h"
#include "transactiontablemodel.h"
#include <QModelIndex>

#define ADDRESS_SIZE 12

QWidget* TxViewHolder::createHolder(int pos)
{
    if (!txRow) txRow = new TxRow();
    txRow->init(isLightTheme);
    return txRow;
}

void TxViewHolder::init(QWidget* holder, const QModelIndex &index, bool isHovered, bool isSelected) const
{
    QModelIndex rIndex = (filter) ? filter->mapToSource(index) : index;
    int type = rIndex.data(TransactionTableModel::TypeRole).toInt();

    TxRow *txRow = static_cast<TxRow*>(holder);
    txRow->updateStatus(isLightTheme, isHovered, isSelected);

    QDateTime date = rIndex.data(TransactionTableModel::DateRole).toDateTime();
    QModelIndex indexType = rIndex.sibling(rIndex.row(),TransactionTableModel::Type);
    QString label = indexType.data(Qt::DisplayRole).toString();

    if (type != TransactionRecord::Other){
        QString address = rIndex.data(Qt::DisplayRole).toString();
        if (!address.isEmpty()) {
            if (type == TransactionRecord::SendToNobody) {
                // OP_RETURN record with a valid utf-8 string to show
                label.clear();
                label += address;
            } else {
                // Regular addresses
                if (address.length() > 20) {
                    address = address.left(ADDRESS_SIZE) + "..." + address.right(ADDRESS_SIZE);
                }
                label += " " + address;
            }
        }
    } else if (type == TransactionRecord::Other) {
        label += rIndex.data(Qt::DisplayRole).toString();
    }

    qint64 amountTop = rIndex.data(TransactionTableModel::AmountRole).toLongLong();
    int status = rIndex.data(TransactionTableModel::StatusRole).toInt();
    bool isUnconfirmed = (status == TransactionStatus::Unconfirmed) || (status == TransactionStatus::Immature)
                         || (status == TransactionStatus::Conflicted) || (status == TransactionStatus::NotAccepted);

    txRow->setDate(date);
    txRow->setLabel(label);
    QString amountText = MuBdIUnits::formatWithUnit(nDisplayUnit, amountTop, true, MuBdIUnits::separatorAlways);
    txRow->setAmount(amountText, "");
    txRow->setType(isLightTheme, type, !isUnconfirmed);
}

QColor TxViewHolder::rectColor(bool isHovered, bool isSelected)
{
    return getRowColor(isLightTheme, isHovered, isSelected);
}
