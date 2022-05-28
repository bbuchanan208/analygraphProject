#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "eigen-3.4.0/Eigen/Dense"

#include <iostream>
#include <stdlib.h>

using namespace cv;
using namespace Eigen;

#define TRUE_ANALYGRAPH 1
Matrix3f trueAnalygraphLeft {
        {0.299, 0.587 , 0.114},
        {0, 0, 0},
        {0, 0, 0},
};
Matrix3f trueAnalygraphRight {
        {0, 0, 0},
        {0, 0, 0},
        {0.299, 0.587 , 0.114},
};

#define GRAY_ANALYGRAPH 2
Matrix3f grayAnalygraphLeft {
        {0.299, 0.587 , 0.114},
        {0, 0, 0},
        {0, 0, 0},
};
Matrix3f grayAnalygraphRight {
        {0, 0, 0},
        {0.299, 0.587 , 0.114},
        {0.299, 0.587 , 0.114},
};

#define COLOR_ANALYGRAPH 3
Matrix3f colorAnalygraphLeft {
        {1, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
};
Matrix3f colorAnalygraphRight {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
};

#define HALF_COLOR_ANALYGRAPH 4
Matrix3f halfColorAnalygraphLeft {
        {0.299, 0.587, 0.114},
        {0, 0, 0},
        {0, 0, 0},
};
Matrix3f halfColorAnalygraphRight {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
};

#define TV_ANALYGRAPH 5
Matrix3f tvAnalygraphLeft {
        {0, 0.7, 0.3},
        {0, 0, 0},
        {0, 0, 0},
};
Matrix3f tvAnalygraphRight {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
};

#define DUBOIS_ANALYGRAPH 6
Matrix3f duBoisAnalygraphLeft {
        {0.437, 0.449, 0.164},
        {-0.062, -0.062, -0.024},
        {-0.048, -0.050, -0.017},
};
Matrix3f duBoisAnalygraphRight {
        {-0.011, -0.032, -0.007},
        {0.377, 0.761, 0.009},
        {-0.026, -0.093, 1.234},
};

#define ROSCOLUX_ANALYGRAPH 7
Matrix3f roscoluxAnalygraphLeft {
        {0.3185, 0.0769, 0.0109},
        {0.1501, 0.0767, 0.0056},
        {0.0007, 0.0020, 0.0156},
};
Matrix3f roscoluxAnalygraphRight {
        {0.0174, 0.0484, 0.1402},
        {0.0184, 0.1807, 0.0458},
        {0.0286, 0.0991, 0.7662},
};


// Helper functions
Vector3f getRBGVectorFromImage(Mat image, int i, int j){
    // Mat image RGB values are stored as BGR values
    float blueValue = image.at<Vec3b>(i, j)[0];
    float greenValue = image.at<Vec3b>(i, j)[1];
    float redValue = image.at<Vec3b>(i, j)[2];
    return Vector3f(redValue, greenValue, blueValue);
}

Vector3f getAnalygraphRBGVector(const Matrix3f& leftMatrix,
                                const Vector3f& leftRGBVector,
                                const Matrix3f& rightMatrix,
                                const Vector3f& rightVector ){
     return (leftMatrix * leftRGBVector) + (rightMatrix * rightVector);
}

int main(int argc, char *argv[]) {

    // default arguments if no command line arguments are passed in
    std::string left_image_path = "/Users/benjaminbuchanan/CLionProjects/zeta/TwnPks_RkGdn_left_sm.jpeg";
    std::string right_image_path = "/Users/benjaminbuchanan/CLionProjects/zeta/TwnPks_RkGdn_rite_sm.jpeg";

    // default Analygraph is the colored one
    Matrix3f leftMatrix = colorAnalygraphLeft;
    Matrix3f rightMatrix = colorAnalygraphRight;

    if (argc == 4){
        left_image_path = argv[1];
        right_image_path = argv[2];
        int analygraphSelection = atoi(argv[3]);

        switch (analygraphSelection) {
            case TRUE_ANALYGRAPH:
                leftMatrix = trueAnalygraphLeft;
                rightMatrix = trueAnalygraphRight;
                break;
            case GRAY_ANALYGRAPH:
                leftMatrix = grayAnalygraphLeft;
                rightMatrix = grayAnalygraphRight;
                break;
            case COLOR_ANALYGRAPH:
                leftMatrix = colorAnalygraphLeft;
                rightMatrix = colorAnalygraphRight;
                break;
            case HALF_COLOR_ANALYGRAPH:
                leftMatrix = halfColorAnalygraphLeft;
                rightMatrix = halfColorAnalygraphRight;
                break;
            case TV_ANALYGRAPH:
                leftMatrix = tvAnalygraphLeft;
                rightMatrix = tvAnalygraphRight;
                break;
            case DUBOIS_ANALYGRAPH:
                leftMatrix = duBoisAnalygraphLeft;
                rightMatrix = duBoisAnalygraphRight;
                break;
            case ROSCOLUX_ANALYGRAPH:
                leftMatrix = roscoluxAnalygraphLeft;
                rightMatrix = roscoluxAnalygraphRight;
                break;
            default:
                // Default uses the COLOR_ANALYGRAPH
                leftMatrix = colorAnalygraphLeft;
                rightMatrix = colorAnalygraphRight;
                break;
        }
    }

    Mat left_image = imread(left_image_path);
    Mat right_image = imread(right_image_path);
    Mat new_image = Mat::zeros(left_image.size(), left_image.type());

    // Since we assume the two images have the dimensions, we can use one image to bound the for loops
    for (int i = 0; i < left_image.size().height; i++) {
        for (int j = 0; j < left_image.size().width; j++) {
            Vector3f leftRGBVector = getRBGVectorFromImage(left_image, i, j);
            Vector3f rightRGBVector = getRBGVectorFromImage(right_image, i, j);
            Vector3f analygraphRBGVector = getAnalygraphRBGVector(leftMatrix, leftRGBVector, rightMatrix, rightRGBVector);

            // The analygraphRBGVector vector stores the values as RGB but we have to format them as BGR
            new_image.at<Vec3b>(i, j)[0] = int(analygraphRBGVector[2]);
            new_image.at<Vec3b>(i, j)[1] = int(analygraphRBGVector[1]);
            new_image.at<Vec3b>(i, j)[2] = int(analygraphRBGVector[0]);
        }
    }

    // display the new image, exit the program if the user presses any key
    cv::imshow("Analygraph", new_image);
    cv::waitKey(0);
    return 0;
}
