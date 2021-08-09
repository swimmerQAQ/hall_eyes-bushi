#include <opencv2/opencv.hpp>
 using namespace cv;
 #include <iostream>
 using namespace std;

/*
usage: 
初始化申请变量。传入参数 image/目标图片 contours/筛选的点云 hierarchy/图片等级 

调用变量的成员函数： xxxx.selectContours(输入四个int的图片等级筛选，不需要的使用-2)

函数返回为点云；可以直接操作该点云

例如：我需要筛选--前--没有别的图片的图像
设置为 --->  -2,-1,-2,-2

其他类似
*/
class contoursSelect
{
    private:
    vector<Vec4i> hierarchy;
    vector<vector<Point>> contours;
    int nex =-2;
    int pre =-2;
    int son =-2;
    int dad =-2;
    Mat image;
    public:
    contoursSelect(Mat in_img,vector<vector<Point>> contours,vector<Vec4i> hierarchy)
    {
        image = in_img;
        //for tree_find
        findContours( in_img, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

        cout << " finish initial " << endl;
        cout << " ready for selectcontours() " << endl;
    }
    ~contoursSelect();
    vector<vector<Point>> selectContours(int inex,int ipre,int ison, int idad)
    {
        nex = inex; pre = ipre; son = ison; dad = idad;
        if(nex < -1 || nex > 2)
        {
            cout << " finding invaild hierarchy in next !" << endl;
        }
        if(pre < -1 || pre > 2)
        {
            cout << " finding invaild hierarchy in next !" << endl;
        }
        if(son < -1 || son > 2)
        {
            cout << " finding invaild hierarchy in next !" << endl;
        }
        if(dad < -1 || dad > 2)
        {
            cout << " finding invaild hierarchy in next !" << endl;
        }
        for(int rank;rank < contours.size();rank++)
        {
            if(nex != -2)
            {
                if(hierarchy[rank][0]==nex)
                {
                    if(hierarchy[rank][1]==pre)
                    {
                        if(hierarchy[rank][2]==son)
                        {
                            if(hierarchy[rank][3]==dad)
                            {
                                drawContours(image, contours,rank,Scalar(255,0,255),1,8,hierarchy);
                                cout << " succeed in drawing contours " << endl;
                            }
                        }
                    }
                }
            }else{
                if(pre != -2)
                {
                    if(hierarchy[rank][1]==pre)
                    {
                        if(hierarchy[rank][2]==son)
                        {
                            if(hierarchy[rank][3]==dad)
                            {
                                drawContours(image, contours,rank,Scalar(255,0,255),1,8,hierarchy);
                            }
                        }
                    }
                }else{
                    if(son != -2)
                    {
                        if(hierarchy[rank][2]==son)
                        {
                            if(hierarchy[rank][3]==dad)
                            {
                                drawContours(image, contours,rank,Scalar(255,0,255),1,8,hierarchy);
                            }
                        }
                    }else{
                        if(dad != -2)
                        {
                            if(hierarchy[rank][3]==dad)
                            {
                                drawContours(image, contours,rank,Scalar(255,0,255),1,8,hierarchy);
                            }
                        }else{
                            cout << " fail to select, you use the invaild hierarchy ?(<_<)? " << endl;
                            cout << " going to draw red contours " <<endl;
                            drawContours(image, contours,rank,Scalar(0,0,255),1,8,hierarchy);
                        }
                    }
                }
            }
        }
    }
};