/*
------------------------[ Lbanet Source ]-------------------------
Copyright (C) 2009
Author: Vivien Delage [Rincevent_123]
Email : vdelage@gmail.com

-------------------------------[ GNU License ]-------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------
*/

#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class TreeItem;

//*************************************************************************************************
//*                               class TreeModel
//*************************************************************************************************
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
	//! constructor
    TreeModel(const QVector<QVariant> &header, QObject *parent = 0);

	//! destructor
    ~TreeModel();

	//! get model data
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

	//! get flags
    Qt::ItemFlags flags(const QModelIndex &index) const;

	//! get header data
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

	//! get index
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;

	//! get parent index
    QModelIndex parent(const QModelIndex &index) const;

	//! get nb row
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

	//! get nb collumns
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

	//! insert row in a model
	bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());

	//! remove row in a model
	bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());

	//! set model data
    bool setData(const QModelIndex &index, const QVariant &value,
					int role = Qt::EditRole);


	//! set model tooltip
    bool setTooltip(const QModelIndex &index, const QVariant &value);


	//! clear the tree content
	void Clear(const QModelIndex &index = QModelIndex());

	//! add a row
	QModelIndex AppendRow(const QVector<QVariant> &data, const QModelIndex &parent = QModelIndex(), 
						bool isReadOnly = false);

	//! get index
    QModelIndex GetIndex(int column, int row, const QModelIndex &parent = QModelIndex()) const;

	//! check if given index is read only
	bool IsReadOnly(const QModelIndex &index) const;

private:
	//! get item
    TreeItem *getItem(const QModelIndex &index) const;

    TreeItem *rootItem;
};


#endif
