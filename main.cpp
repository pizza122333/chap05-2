#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

// 함수 선언 (컴파일러에게 "이런 함수가 나중에 나올 거야"라고 알려주는 역할)
void contrast_direct_access();

int main(void)
{
    // 이제 main이 처음에 있어도 아래에 있는 함수를 호출할 수 있습니다.
    contrast_direct_access();
    return 0;
}

// 함수 정의 (실제 구현부)
void contrast_direct_access()
{
    // 1. 영상 불러오기 (그레이스케일)
    Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty()) {
        cerr << "Image load failed!" << endl;
        return;
    }

    // 2. 결과 영상 생성 (원본과 동일한 크기, 타입)
    Mat dst(src.rows, src.cols, src.type());

    float s = 2.f; // 명암비 조절 비율

    // 3. 픽셀 직접 참조 방식 (이중 for문)
    for (int j = 0; j < src.rows; j++) {
        for (int i = 0; i < src.cols; i++) {
            // 연산자 함수(dst = s * src)의 내부 동작을 직접 구현
            // saturate_cast는 0~255 범위를 벗어나지 않게 안전하게 변환합니다.
            dst.at<uchar>(j, i) = saturate_cast<uchar>(s * src.at<uchar>(j, i));
        }
    }

    // 4. 결과 출력
    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}