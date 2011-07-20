//     This file is part of MosaicLayout.  
// 
//     MosaicLayout is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
// 
//     MosaicLayout is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
// 
//     You should have received a copy of the GNU General Public License
//     along with MosaicLayout.  If not, see <http://www.gnu.org/licenses/>.

#include "MosaicLayout.h"
#include <QStyle>

MosaicLayout::MosaicLayout(QWidget* parent): QLayout(parent)
{
  setContentsMargins(9,9,9,9);
  setSpacing(4);
  minItemHSize = 100;
  minItemVSize = 100;
  maxItemHSize = 160;
  maxItemVSize = 160;
}

MosaicLayout::MosaicLayout()
{
  setContentsMargins(9,9,9,9);
  setSpacing(4);
  minItemHSize = 100;
  minItemVSize = 100;
  maxItemHSize = 160;
  maxItemVSize = 160;
}

MosaicLayout::~MosaicLayout()
{
  QLayoutItem *item;
  while ((item = takeAt(0)))    
    delete item;
}

void MosaicLayout::removeAllItems()
{
  itemsList.clear();
}

void MosaicLayout::refreshLayout(const QRect& rect)
{ 
  //item size
  int itemHSize, itemVSize;
  int totalSpacing = spacing() * itemsList.count();
  // horizontal max number of items
  int HMaxItems = contentsRect().width() / (minItemHSize + totalSpacing);  
  bool oneRow = false;
  if (HMaxItems >= itemsList.count()) 
  {
    HMaxItems = itemsList.count(); 
    if (HMaxItems == 0)
      HMaxItems += 1; // one avoid division by 0
    oneRow = true;
  }
  // horizontal dimension that could be added to each item
  // since there is room
  int HPlusSize = ( contentsRect().width()  -
  (minItemHSize * HMaxItems) ) / HMaxItems;
  //TODO: check this, too many operations
  if (oneRow)  
  {
    if (minItemHSize + HPlusSize > maxItemHSize)
      itemHSize = maxItemHSize;
    else
      itemHSize = minItemHSize + HPlusSize;
  }
  else {
    if (HPlusSize + minItemHSize > maxItemHSize)
      itemHSize = minItemHSize;
    else
      itemHSize = minItemHSize + HPlusSize;
  }
  
  //repeat same story for vertical size
  int VMaxItems = contentsRect().height()  / (minItemVSize + totalSpacing);
  int VPlusSize = ( contentsRect().height() %
  (minItemVSize * VMaxItems) ) / VMaxItems;
  if (VPlusSize + minItemVSize > maxItemVSize)
    itemVSize = minItemVSize;
  else
    itemVSize = minItemVSize + VPlusSize;
  //next lines add widgets to layout
    // absolute position to set
    int x = 0;
    int y = 0;
    
    // count of horizontal added items,
    // increment it for each added item and
    // when it reachs HMaxItems set it and
    // x to zero
    int HCountItem = 0;
    QLayoutItem *item;
    foreach (item, itemsList) {
      item->setGeometry(QRect(QPoint(x,y),QPoint(itemHSize+x,itemVSize+y)));
      HCountItem++;
      if (HCountItem >= HMaxItems) {
	HCountItem = x = 0;
	y += itemVSize + spacing();
      }
      else
	x += itemHSize + spacing();
    }
}

void MosaicLayout::setGeometry(const QRect& rect)
{
  QLayout::setGeometry(rect);
  refreshLayout(rect);
}

void MosaicLayout::setItemsMinDimension(int x, int y)
{
  minItemHSize = x;
  minItemVSize = y;
}

void MosaicLayout::setItemsMaxDimension(int x, int y)
{
  maxItemHSize = x;
  minItemVSize = y;
}



int MosaicLayout::count() const
{
  return itemsList.count();
}



//TODO: Implement this some day
QLayoutItem* MosaicLayout::itemAt(int index) const
{
  MosaicLayout* a = NULL;
  return a;
}

void MosaicLayout::addItem(QLayoutItem* item)
{
  itemsList.append(item);
}

//TODO: Implement this some day
QSize MosaicLayout::sizeHint() const
{
  QSize a;
  return a;
}

//TODO: Implement this some day
QLayoutItem* MosaicLayout::takeAt(int index)
{
  if (index >= 0 && index < itemsList.size())
    return itemsList.takeAt(index);
  else
    return 0;
}


