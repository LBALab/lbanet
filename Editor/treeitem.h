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
#include <boost/shared_ptr.hpp>

class CustomStringListModel;
class FileDialogOptionsBase;


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
    QVariant tooltip(int column) const;
	
    int row() const;
    TreeItem *parent();

    int addChild(const QVector<QVariant> &data, bool isReadOnly);
    bool insertChildren(int position, int count, int columns);
    bool removeChildren(int position, int count);
    bool setData(int column, const QVariant &value);
    bool setTooltip(int column, const QVariant &value);

	//! clear all children
	void Clear();

	//! check if item is read only
	bool IsReadOnly() const
	{ return _isReadOnly; }

	//! SetCustomIndex
	bool SetCustomIndex(int column, boost::shared_ptr<CustomStringListModel> list);

	//! SetCustomIndex
	bool SetCustomIndex(int column, boost::shared_ptr<FileDialogOptionsBase> filefilter);

	//! SetCustomIndex
	bool SetCustomIndex(int column, boost::shared_ptr<int> list);


    boost::shared_ptr<CustomStringListModel> CustomIndex(int column) const;
    boost::shared_ptr<FileDialogOptionsBase> CustomIndexFile(int column) const;
    boost::shared_ptr<int> CustomIndexNumber(int column) const;


private:
    QList<TreeItem*>	childItems;
    QVector<QVariant>	itemData;
    QVector<QVariant>	itemTooltip;

    TreeItem*			parentItem;
	bool				_isReadOnly;

	QVector<boost::shared_ptr<CustomStringListModel> >	_customs;
	QVector<boost::shared_ptr<FileDialogOptionsBase> >	_customsfiledialog;
	QVector<boost::shared_ptr<int> >					_customsnumber;
};


#endif
