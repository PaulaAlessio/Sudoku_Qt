#ifndef CUSTOMDELEGATE_H 
#define CUSTOMDELEGATE_H
#include <QtGui>

// custom item delegate to draw grid lines around cells

class CustomDelegate : public QStyledItemDelegate
{
public:
    CustomDelegate(QTableView* tableView);
protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
 QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget * editor, const QModelIndex & index) const;
    void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const;


private:
    QPen _gridPen;
};

#endif
