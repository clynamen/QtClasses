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

#ifndef MOSAICLAYOUT_H
#define MOSAICLAYOUT_H
//qt
#include <QLayout>
#include <QRect>

/** 
 * This layout adds item horizontally and then vertically 
 * when each line in the layout runs out of space.
 * When the layout is resized, it shrink and reorder its 
 * items following rules.
 **/

class MosaicLayout : public QLayout
{
  Q_OBJECT
public:
  
  
  MosaicLayout(QWidget *parent);
  MosaicLayout();
  ~MosaicLayout();
  
  //! removes all items in the layout
  void removeAllItems();
  //! \return total number of items
  int count() const;
  //! resize Layout
  void setGeometry(const QRect& rect);
  void setItemsMinDimension(int x, int y);
  void setItemsMaxDimension(int x, int y);
  
private slots:
  //! calculates and applies new dimension
  void refreshLayout(const QRect& rect);
  
private:
  //! list of all items in the layout
  QList<QLayoutItem*> itemsList;
  int minItemHSize;
  int minItemVSize;
  int maxItemHSize;
  int maxItemVSize;
  
private:
  QLayoutItem* itemAt ( int index ) const;
  void addItem ( QLayoutItem* item );
  QSize sizeHint() const;
  QLayoutItem* takeAt ( int index );
  
};

#endif // MOSAICLAYOUT_H
