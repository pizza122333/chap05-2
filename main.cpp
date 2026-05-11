#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void contrast_adaptive_mean();

int main(void)
{
    contrast_adaptive_mean();
    return 0;
}

void contrast_adaptive_mean()
{
    // 1. 영상 불러오기
    Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty()) {
        cerr << "Image load failed!" << endl;
        return;
    }

    // 2. 영상의 평균값 구하기
    Scalar avg = mean(src);
    double m = avg[0]; // 그레이스케일 영상이므로 0번 인덱스에 평균값이 저장됨

    cout << "Average Pixel Value: " << m << endl;

    // 3. 결과 영상 생성
    Mat dst(src.rows, src.cols, src.type());

    float alpha = 1.0f; // 명암비 조절 가중치

    // 4. 평균값을 기준으로 명암비 조절 (직접 참조 방식)
    for (int j = 0; j < src.rows; j++) {
        for (int i = 0; i < src.cols; i++) {
            int v = src.at<uchar>(j, i);

            // 수식: dst = src + (src - m) * alpha
            // 128 대신 계산된 평균값 m을 사용합니다.
            dst.at<uchar>(j, i) = saturate_cast<uchar>(v + (v - m) * alpha);
        }
    }

    // 5. 결과 확인
    imshow("src", src);
    imshow("dst (Adaptive Mean)", dst);

    waitKey();
    destroyAllWindows();
}