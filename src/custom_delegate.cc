#include "custom_delegate.h"

CustomDelegate::CustomDelegate(QTableView* tableView)
{
    // create grid pen
    int gridHint = tableView->style()->styleHint(QStyle::SH_Table_GridLineColor, new QStyleOptionViewItemV4());
    QColor gridColor = static_cast<QRgb>(gridHint);
    _gridPen = QPen(gridColor, 0, tableView->gridStyle());
}

void CustomDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    QPen oldPen = painter->pen();
    painter->setPen(_gridPen);

    painter->drawLine(option.rect.topLeft(), option.rect.bottomLeft());
    painter->drawLine(option.rect.topLeft(), option.rect.topRight());
    // paint vertical lines
    if (index.column()%3==0 ){
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(option.rect.topLeft(), option.rect.bottomLeft());
        
    }
    else if (index.column()==8){
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(option.rect.topRight(), option.rect.bottomRight());
    }
    if (index.row()%3==0){
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(option.rect.topLeft(), option.rect.topRight());
    }
    else if(index.row()==8){
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());

    }
    painter->setPen(oldPen);
}


QWidget *CustomDelegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    editor->setValidator(new QRegExpValidator(QRegExp("[1-9]{1}"),editor));
    //editor->setValidator(new QIntValidator(1,9,editor));
    return editor;
}


void CustomDelegate::setEditorData(QWidget *editor,
                                 const QModelIndex &index) const
{
    QString value =index.model()->data(index, Qt::EditRole).toString();
        QLineEdit *line = static_cast<QLineEdit*>(editor);
        line->setText(value);
}


void CustomDelegate::setModelData(QWidget *editor,
                                QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    QLineEdit *line = static_cast<QLineEdit*>(editor);
    QString value = line->text();
    model->setData(index, value);
}


