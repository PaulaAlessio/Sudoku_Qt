#include "SudokuDialog.h"
#include "custom_delegate.h"
#include <iostream>

TestDialog::TestDialog(){

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* upLayout = new QHBoxLayout;
    QHBoxLayout* downLayout = new QHBoxLayout;
   
    mainLayout->addLayout(upLayout);
    setWindowTitle("Sudoku Solver");
    setGeometry(geometry().x(),geometry().y(),400,350);
    mainLayout->addLayout(downLayout);

 
    QPushButton* loadButton = new QPushButton("Load");
    QPushButton* solveButton = new QPushButton("Solve");
    QPushButton* exitButton = new QPushButton("Quit");
    exitButton->setDefault(true);
    downLayout->addWidget(loadButton);
    downLayout->addWidget(solveButton);
    downLayout->addWidget(exitButton);
    downLayout->addStretch();
  

    table  = new QTableWidget();
    
    table->setRowCount(N9);
    table->setColumnCount(N9);
    table->verticalHeader()->setVisible(false); 
    table->horizontalHeader()->setVisible(false); 
    table->setShowGrid(false);
    squares= new QTableWidgetItem*[N9*N9];
    CustomDelegate *square= new CustomDelegate(table);
    table->setItemDelegate( square);
    for (int i=0;i<N9*N9;i++){
        squares[i] =new QTableWidgetItem();
        table->setItem(i%N9, i/N9, squares[i]);
        table->item(i%N9, i/N9)->setTextAlignment(Qt::AlignCenter);
    
    }
    table->setGeometry(10,10,300,300);
    table->setStyleSheet("background: rgb(255,255,255);color:rgb(0,0,0);\
                      font-family:Tahoma;font-size:15px;\
                      font-weight:bold; border: 4px outset rgb(255,255,255);\
                      gridline-color: #000000;"
                      "selection-background-color: \
                       qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 \
                       transparent, stop: 1 white);");

    table->setItemDelegate(new CustomDelegate(table));
    table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    upLayout->addWidget(table);
    upLayout->addStretch();
    connect(exitButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(solveButton,SIGNAL(clicked()),this,SLOT(solve()));
    connect(loadButton,SIGNAL(clicked()),this,SLOT(load()));
}
 

void TestDialog::solve(){
    QString data="";
    for (int i=0;i<N9*N9;i++){
        if (squares[i]->text().isEmpty()){
            data+='.';
        }
        else{
            data+=squares[i]->text();
        }
    }
    std::string guf;
    guf=data.toStdString();
    std::cout << guf << std::endl;
    Sudoku puzzle(guf);
    int calls=puzzle.solve();

    std::array<string,N9*N9> solution=puzzle.get_sol();
    std::cout << calls << std::endl;
    for (int i=0;i<N9*N9;i++){
        squares[i]->setText(QString::fromStdString(solution[i]));
    }



    
}
 
void TestDialog::load(){
  QFile file("./input_files/hard_puzzles.txt");
  if(!file.open(QIODevice::ReadOnly)) {
    QMessageBox::information(0, "error", file.errorString());
  }
  int c=1;
  int low=1;
  int high=95;
  QTime time = QTime::currentTime();
  qsrand((uint)time.msec());
  int cc=qrand() % ((high + 1) - low) + low;  
  std::cout << cc << "\n" ;
  
  // Get random value between 0-100
  QTextStream in(&file);
  QString line = in.readLine();
  std::string input;
  bool flag=true;
  while(!line.isNull() && flag ) {
    if (c==cc)  {
        input= line.toStdString();
        std::cout << input << "\n" ;
        flag=false;
 
    }
    line = in.readLine();
    c++;

  }
  file.close();
  for (int i=0;i<N9*N9;i++){
    if (input[i]!='.'){

        squares[i]->setText(QString(input[i]));
        
    }
    else  squares[i]->setText(QString());
  }
}
