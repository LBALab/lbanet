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

#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVector>
#include <QVariant>


//*************************************************************************************************
//*                               class TreeModel
//*************************************************************************************************
class TreeItem
{
public:
	//! constructor
    TreeItem(const QVector<QVariant> &data, TreeItem *parent = 0, bool isReadOnly = false);

	//! destructor
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *parent();

    int addChild(const QVector<QVariant> &data, bool isReadOnly);
    bool insertChildren(int position, int count, int columns);
    bool removeChildren(int position, int count);
    bool setData(int column, const QVariant &value);

	//! clear all children
	void Clear();

	//! check if item is read only
	bool IsReadOnly() const
	{ return _isReadOnly; }

private:
    QList<TreeItem*>	childItems;
    QVector<QVariant>	itemData;
    TreeItem*			parentItem;
	bool				_isReadOnly;
};


#endif
