#include"Image.h"
Image::Image(QString filename,double k)
{
    im_old=QImage(filename);
    koef=k;

     w = im_old.width();
     h = im_old.height();
     w1=(w/8+1)*8;
     h1=(h/8+1)*8;

    matrRGB.resize(w);
    if(w%8==0)
        matrYCbCr.resize(w);
    else
         matrYCbCr.resize(w1);

    for(int i=0;i<w;i++)
    {matrRGB[i].resize(h);}
    for(int i=0;i<matrYCbCr.size();i++){
        if(h%8==0)
            matrYCbCr[i].resize(h);
        else
            matrYCbCr[i].resize(h1);}

  for(int i=0; i<w; i++){                    //получение матрицы RGB
            for(int j=0; j<h; j++){
         QRgb rgb = im_old.pixel(i, j);

         matrRGB[i][j].setX(qRed( rgb ));
         matrRGB[i][j].setY (qGreen( rgb ));
         matrRGB[i][j].setZ (qBlue( rgb ));
         }
  }

  matrQuant.resize(8);         //создание матрицы квантования
  for(int i=0;i<8;i++)
      matrQuant[i].resize(8);
  for(int i=0;i<8;i++)
      for(int j=0;j<8;j++)
          matrQuant[i][j]=1+(i+j)*koef;
}

void Image::toYCbCr()
{
    for(int i=0; i<matrYCbCr.size(); i++){
              for(int j=0; j<matrYCbCr[0].size(); j++){
           if((i<w) && (j<h)){
               matrYCbCr[i][j].setX(0.299*matrRGB[i][j].x()+0.587*matrRGB[i][j].y()+0.114*matrRGB[i][j].z());    //RGB->YCbCr
               matrYCbCr[i][j].setY(-0.1687*matrRGB[i][j].x()-0.3313*matrRGB[i][j].y()+0.500*matrRGB[i][j].z());
               matrYCbCr[i][j].setZ(0.500*matrRGB[i][j].x()-0.4187*matrRGB[i][j].y()-0.0813*matrRGB[i][j].z());
           }

           else if ((i>=w)&& (j<h)){
               matrYCbCr[i][j].setX(0.299*matrRGB[2*(this->w)-i-1][j].x()+0.587*matrRGB[2*(this->w)-i-1][j].y()+0.114*matrRGB[2*(this->w)-i-1][j].z());    //RGB->YCbCr
               matrYCbCr[i][j].setY(-0.1687*matrRGB[2*(this->w)-i-1][j].x()-0.3313*matrRGB[2*(this->w)-i-1][j].y()+0.500*matrRGB[2*(this->w)-i-1][j].z());
               matrYCbCr[i][j].setZ(0.500*matrRGB[2*(this->w)-i-1][j].x()-0.4187*matrRGB[2*(this->w)-i-1][j].y()-0.0813*matrRGB[2*(this->w)-i-1][j].z());
           }
           else if ((i<w)&& (j>=h)){

               matrYCbCr[i][j].setX(0.299*matrRGB[i][2*h-j-1].x()+0.587*matrRGB[i][2*h-j-1].y()+0.114*matrRGB[i][2*h-j-1].z());    //RGB->YCbCr
               matrYCbCr[i][j].setY(-0.1687*matrRGB[i][2*h-j-1].x()-0.3313*matrRGB[i][2*h-j-1].y()+0.500*matrRGB[i][2*h-j-1].z());
               matrYCbCr[i][j].setZ(0.500*matrRGB[i][2*h-j-1].x()-0.4187*matrRGB[i][2*h-j-1].y()-0.0813*matrRGB[i][2*h-j-1].z());
           }
           else if ((i>=w)&& (j>=h)){

               matrYCbCr[i][j].setX(0.299*matrRGB[2*(this->w)-i-1][2*h-j-1].x()+0.587*matrRGB[2*(this->w)-i-1][2*h-j-1].y()+0.114*matrRGB[2*(this->w)-i-1][2*h-j-1].z());    //RGB->YCbCr
               matrYCbCr[i][j].setY(-0.1687*matrRGB[2*(this->w)-i-1][2*h-j-1].x()-0.3313*matrRGB[2*(this->w)-i-1][2*h-j-1].y()+0.500*matrRGB[2*(this->w)-i-1][2*h-j-1].z());
               matrYCbCr[i][j].setZ(0.500*matrRGB[2*(this->w)-i-1][2*h-j-1].x()-0.4187*matrRGB[2*(this->w)-i-1][2*h-j-1].y()-0.0813*matrRGB[2*(this->w)-i-1][2*h-j-1].z());
           }

       }
    }

}

void Image::r_matrRGB()
{
    newMatrRGB.resize(w);
    for(int i=0;i<w;i++)
        newMatrRGB[i].resize(h);

    for(int i=0; i<w; i++){                    //получение матрицы RGB
              for(int j=0; j<h; j++){
           if(newMatrYCbCr[i][j].x()+1.402*newMatrYCbCr[i][j].z()>254)
               newMatrRGB[i][j].setX(254);
           else if(newMatrYCbCr[i][j].x()+1.402*newMatrYCbCr[i][j].z()<0)
               newMatrRGB[i][j].setX(0);
           else
               newMatrRGB[i][j].setX(newMatrYCbCr[i][j].x()+1.402*newMatrYCbCr[i][j].z());

           if(newMatrYCbCr[i][j].x()-0.34414*newMatrYCbCr[i][j].y()-0.71414*newMatrYCbCr[i][j].z()>254)
               newMatrRGB[i][j].setY(254);
            else if(newMatrYCbCr[i][j].x()-0.34414*newMatrYCbCr[i][j].y()-0.71414*newMatrYCbCr[i][j].z()<0)
               newMatrRGB[i][j].setY(0);
           else
               newMatrRGB[i][j].setY (newMatrYCbCr[i][j].x()-0.34414*newMatrYCbCr[i][j].y()-0.71414*newMatrYCbCr[i][j].z());

           if((newMatrYCbCr[i][j].x()+1.772*newMatrYCbCr[i][j].y())>254)
               newMatrRGB[i][j].setZ(254);
           else if((newMatrYCbCr[i][j].x()+1.772*newMatrYCbCr[i][j].y())<0)
               newMatrRGB[i][j].setZ(0);
           else
               newMatrRGB[i][j].setZ (newMatrYCbCr[i][j].x()+1.772*newMatrYCbCr[i][j].y());
           }
    }

}

void Image::makeBlocks()
{
    for(int i=0;i<matrYCbCr.size();i+=8){      //деление матрицы на блоки 8*8
        for(int j=0;j<matrYCbCr[0].size();j+=8){
            QVector<QVector<QVector3D>> buff;   //буферный блок
            buff.resize(8);
            for(int l=0;l<8;l++)
                buff[l].resize(8);

             for(int k=0;k<8;k++)
                 for(int m=0;m<8;m++)
                     buff[k][m]=matrYCbCr[i+k][j+m];

             blocks.push_back(buff);
        }
    }
}
void Image::r_matrYCbCr()
{
    newMatrYCbCr.resize(matrYCbCr.size());
    for(int i=0;i<matrYCbCr.size();i++)
        newMatrYCbCr[i].resize(matrYCbCr[0].size());
int cnt=0;
 for(int i=0;i<newMatrYCbCr.size();i+=8){
        for(int j=0;j<newMatrYCbCr[0].size();j+=8){

             for(int k=0;k<8;k++){
                 for(int m=0;m<8;m++){
                     newMatrYCbCr[i+k][j+m]=newBlocks[cnt][k][m];
                 }
             }
             cnt++;


        }
    }


}
void Image::makeBlocksDCT()
{
    blocksDCT.resize(blocks.size());
    for(int k=0;k<blocksDCT.size();k++)
        blocksDCT[k].resize(8);
    for(int k=0;k<blocksDCT.size();k++)
        for(int i=0;i<8;i++)
            blocksDCT[k][i].resize(8);

    for(int k=0;k<blocksDCT.size();k++){
        for(int u=0;u<8;u++){
            for(int v=0;v<8;v++){

                double w1=1,w2=1;
                if(u==0)
                    w1=1/sqrt(8);
                else
                    w1=0.5;
                if(v==0)
                    w2=1/sqrt(8);
                else
                    w2=0.5;

                double sumY=0;
                double sumCb=0;
                double sumCr=0;

              for(int x=0;x<8;x++){
                  for(int y=0;y<8;y++){
                    sumY+=blocks[k][x][y].x()*qCos(M_PI*(2*x+1)*u/16)*qCos(M_PI*(2*y+1)*v/16);
                    sumCb+=blocks[k][x][y].y()*qCos(M_PI*(2*x+1)*u/16)*qCos(M_PI*(2*y+1)*v/16);
                    sumCr+=blocks[k][x][y].z()*qCos(M_PI*(2*x+1)*u/16)*qCos(M_PI*(2*y+1)*v/16);
                  }
              }
              blocksDCT[k][u][v].setX(w1*w2*sumY);
              blocksDCT[k][u][v].setY(w1*w2*sumCb);
              blocksDCT[k][u][v].setZ(w1*w2*sumCr);
             // blocksDCT[k][u][v].setX(blocks[k][u][v].x());
              //blocksDCT[k][u][v].setY(blocks[k][u][v].y());
              //blocksDCT[k][u][v].setZ(blocks[k][u][v].z());
            }}
    }
}


void Image::r_blocks()
{
    newBlocks.resize(blocks.size());
    for(int k=0;k<blocksDCT.size();k++)
        newBlocks[k].resize(8);
    for(int k=0;k<blocksDCT.size();k++)
        for(int i=0;i<8;i++)
            newBlocks[k][i].resize(8);

    for(int k=0;k<newBlocksDCT.size();k++){
        for(int x=0;x<8;x++){
            for(int y=0;y<8;y++){

                double sumY=0;
                double sumCb=0;
                double sumCr=0;

              for(int u=0;u<8;u++){
                  for(int v=0;v<8;v++){
                      double w1=1,w2=1;
                      if(u==0)
                          w1=1/sqrt(8);
                      else
                          w1=0.5;
                      if(v==0)
                          w2=1/sqrt(8);
                      else
                          w2=0.5;
                    sumY+=w1*w2*newBlocksDCT[k][u][v].x()*qCos(M_PI*(2*x+1)*u/16)*qCos(M_PI*(2*y+1)*v/16);
                    sumCb+=w1*w2*newBlocksDCT[k][u][v].y()*qCos(M_PI*(2*x+1)*u/16)*qCos(M_PI*(2*y+1)*v/16);
                    sumCr+=w1*w2*newBlocksDCT[k][u][v].z()*qCos(M_PI*(2*x+1)*u/16)*qCos(M_PI*(2*y+1)*v/16);
                  }
              }
              newBlocks[k][x][y].setX(sumY);
              //newBlocks[k][x][y].setX(blocksDCT[k][x][y].x());
              //newBlocks[k][x][y].setY(blocksDCT[k][x][y].y());
              //newBlocks[k][x][y].setZ(blocksDCT[k][x][y].z());
              newBlocks[k][x][y].setY(sumCb);
              newBlocks[k][x][y].setZ(sumCr);
            }}
    }

}
void Image::quantization()
{
    for(int k=0;k<blocksDCT.size();k++)
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++){
            blocksDCT[k][i][j].setX(round(blocksDCT[k][i][j].x()/matrQuant[i][j]));
            blocksDCT[k][i][j].setY(round(blocksDCT[k][i][j].y()/matrQuant[i][j]));
            blocksDCT[k][i][j].setZ(round(blocksDCT[k][i][j].z()/matrQuant[i][j]));}
}

void Image::r_quantization()
{ for(int k=0;k<blocksDCT.size();k++)
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++){
            newBlocksDCT[k][i][j].setX(newBlocksDCT[k][i][j].x()*matrQuant[i][j]);
            newBlocksDCT[k][i][j].setY(newBlocksDCT[k][i][j].y()*matrQuant[i][j]);
            newBlocksDCT[k][i][j].setZ(newBlocksDCT[k][i][j].z()*matrQuant[i][j]);}

}
void Image::makeVectDCT()
{
    double eps=1e-5;
    vectDCT.resize(blocksDCT.size());
    using dir_t = enum { down, right, diag_up, diag_down };
for(int k=0;k<vectDCT.size();k++){
        int i = 0, j = 0, part = 1;
        dir_t dir = right;
        while (true)
        {   if(abs(blocksDCT[k][i][j].x())<eps)
                vectDCT[k].push_back(0);
            else
                vectDCT[k].push_back(blocksDCT[k][i][j].x());
            if (7 == i && 7 == j) break;
            if (7 == i && 0 == j) part = 2;
            bool border_reached;
            do
            {
                border_reached = false;
                switch (dir)
                {
                case down :
                    if (!move_down(i))
                    {
                        dir = right;
                        border_reached = true;
                    }
                    else
                    {
                        dir = 1 == part ? diag_up : diag_down;
                    }
                    break;
                case diag_down :
                    if (!move_diag_down(i, j))
                    {
                        dir = 1 == part ? down : right;
                        border_reached = true;
                    }
                    break;
                case right :
                    if (!move_right(j))
                    {
                        dir = diag_up;
                        border_reached = true;
                    }
                    else
                    {
                        dir = 1 == part ? diag_down : diag_up;
                    }
                    break;
                case diag_up :
                    if (!move_diag_up(i, j))
                    {
                        dir = 1 == part ? right : down;
                        border_reached = true;
                    }
                    break;
                }
            }
            while (border_reached);
        }
}

}
void Image::r_blocksDct()
{
    newBlocksDCT.resize(blocksDCT.size());
    for(int k=0;k<blocksDCT.size();k++)
        newBlocksDCT[k].resize(8);
     for(int k=0;k<blocksDCT.size();k++)
         for(int i=0;i<8;i++)
             newBlocksDCT[k][i].resize(8);


    using dir_t = enum { down, right, diag_up, diag_down };
for(int k=0;k<vectDCT.size();k++){
        int i = 0, j = 0, part = 1, cnt=0;
        dir_t dir = right;

        while (true)
        {  newBlocksDCT[k][i][j].setX(vectDCT[k][cnt]);
           newBlocksDCT[k][i][j].setY(blocksDCT[k][i][j].y());
           newBlocksDCT[k][i][j].setZ(blocksDCT[k][i][j].z());
            cnt++;
            if (7 == i && 7 == j) break;
            if (7 == i && 0 == j) part = 2;
            bool border_reached;
            do
            {
                border_reached = false;
                switch (dir)
                {
                case down :
                    if (!move_down(i))
                    {
                        dir = right;
                        border_reached = true;
                    }
                    else
                    {
                        dir = 1 == part ? diag_up : diag_down;
                    }
                    break;
                case diag_down :
                    if (!move_diag_down(i, j))
                    {
                        dir = 1 == part ? down : right;
                        border_reached = true;
                    }
                    break;
                case right :
                    if (!move_right(j))
                    {
                        dir = diag_up;
                        border_reached = true;
                    }
                    else
                    {
                        dir = 1 == part ? diag_down : diag_up;
                    }
                    break;
                case diag_up :
                    if (!move_diag_up(i, j))
                    {
                        dir = 1 == part ? right : down;
                        border_reached = true;
                    }
                    break;
                }
            }
            while (border_reached);

        }
}

}
