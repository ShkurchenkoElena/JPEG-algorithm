#ifndef IMAGE_H
#define IMAGE_H


#include<QImage>
#include<QVector3D>
#include<QVector>
#include<QtMath>
class Image{
    QImage im_old;      //исходное изображение
    QImage im_new;      //новое изображение
    int w,h;            //ширина и высота исходного изображения
    int w1,h1;          //ближайшее к исх.ширине и высоте сверху, делящееся на 8 число
    QVector<QVector<QVector3D>> matrRGB;   //матрица RGB
    QVector<QVector<QVector3D>> matrYCbCr; //матрица YCbCr
    QVector<QVector<QVector<QVector3D>>> blocks;   //блоки 8*8 из матрицы YCbCr
    QVector<QVector<QVector<QVector3D>>> blocksDCT;  //блоки, к которым примерено дискретное косинусное преобразование

    QVector<QVector<QVector3D>> newMatrRGB;    // то же самое, но на обратном ходу
    QVector<QVector<QVector3D>> newMatrYCbCr;
    QVector<QVector<QVector<QVector3D>>> newBlocks;
    QVector<QVector<QVector<QVector3D>>> newBlocksDCT;
    double koef; //коэффициент сжатия
    QVector<QVector<double>> vectDCT;

    QVector<QVector<double>> matrQuant;   //матрица квантования


    bool move_down(int& i)                //функции для зигзагообразного прохода матрицы
    {
        if (7 == i) return false;
        ++i;
        return true;
    }

    bool move_right(int& j)
    {
        if (7 == j) return false;
        ++j;
        return true;
    }

    bool move_diag_up(int& i, int& j)
    {
        if (0 == i || 7== j) return false;
        --i;
        ++j;
        return true;
    }

    bool move_diag_down(int& i, int& j)
    {
        if (7 == i || 0 == j) return false;
        ++i;
        --j;
        return true;
    }

public:
    Image(QString filename,double k);

    QImage getIm()
    { im_new=im_old;
     for(int i=0; i<newMatrRGB.size(); i++){
        for(int j=0; j<newMatrRGB[0].size(); j++){
                 QColor a;
                 a.setRgb(newMatrRGB[i][j].x(),newMatrRGB[i][j].y(),newMatrRGB[i][j].z());
                 QPoint p(i,j);
                 im_new.setPixelColor(p,a);
             }
         }
     return im_new;
    }

    QImage getOldIm(){return im_old;}
    void toYCbCr();   //перевод в YCbCr
    void makeBlocks(); // матрица разбивается на блоки 8*8
    void makeBlocksDCT(); //дискретное косинусное преобразование
    void quantization();  //квантование
    void makeVectDCT();   // перевод блоков ДКП в векторы длиной 64 зигзагообразным проходом матрицы
    void r_quantization();
     //обратный алгоритм
    void r_blocksDct(); // из векторов ДКП делается матрица
    void r_blocks();    // обратное дискретное косинусное преобразование
    void r_matrYCbCr(); //получение матрицы из блоков
    void r_matrRGB();   // перевод обратно в RGB


    void jpeg(){
        toYCbCr();
        makeBlocks();
        makeBlocksDCT();
        quantization();
        makeVectDCT();

        r_blocksDct();
        r_quantization();
        r_blocks();
        r_matrYCbCr();
        r_matrRGB();
    }

};
#endif // IMAGE_H
