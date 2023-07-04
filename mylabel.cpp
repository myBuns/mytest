#include "mylabel.h"
#include <QDebug>

void fun(int* arr, int left, int right);

int num = 0;
myLabel::myLabel(QWidget *parent):QLabel(parent)
{
    this->setText("character number:" + QString::number( 0 ));
}

void myLabel::setStrNum(const QString &str)
{
    this->setText("character number:" + str);
}

//只能实现简单left=0,right=length-1
//void fun(int* arr, int left, int right)
//{
//    if(left < right)
//    {
//        num++;
//        int min = left;
//        int min_value = arr[left];
//        int min_p = left;

//        while(min <= right)
//        {
//            if(min_value > arr[min])
//            {
//                min_value = arr[min];
//                min_p = min;
//            }
//            min++;
//        }

//        if(min_p != left)
//        {
//            int temp =arr[left];
//            arr[left] = arr[min_p];
//            arr[min_p] = temp;
//        }

//        int max = right;
//        int max_value = arr[right];
//        int max_p = right;

//        while(max >= left)
//        {
//            if(max_value < arr[max])
//            {
//                max_p = max;
//                max_value = arr[max];
//            }
//            max--;
//        }

//        if(max_p != right)
//        {
//            int temp =arr[right];
//            arr[right] = arr[max_p];
//            arr[max_p] = temp;
//        }

//        fun(arr,++left,--right);
//    }
//}
