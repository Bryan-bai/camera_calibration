
// MyCalibrationDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
using namespace std;
// CMyCalibrationDlg 对话框
class CMyCalibrationDlg : public CDialogEx
{
// 构造
public:
	CMyCalibrationDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYCALIBRATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	enum Pattern { NOT_EXISTING, CHESSBOARD, CIRCLES_GRID, ASYMMETRIC_CIRCLES_GRID };
	struct Settings
	{
		CvSize boardSize;              // The size of the board -> Number of items by width and height
		Pattern calibrationPattern;  // One of the Chessboard, circles, or asymmetric circle pattern
		float squareSize;            // The size of a square in your defined unit (point, millimeter,etc).
		int nrFrames;                // The number of frames to use from the input for calibration
		float aspectRatio;           // The aspect ratio
		int delay;                   // In case of a video input
		bool writePoints;            // Write detected feature points
		bool writeExtrinsics;        // Write extrinsic parameters
		bool calibZeroTangentDist;   // Assume zero tangential distortion
		bool calibFixPrincipalPoint; // Fix the principal point at the center
		bool flipVertical;           // Flip the captured images around the horizontal axis
		bool showUndistorsed;        // Show undistorted images after calibration
		int cameraID;
		int flag;
	};
	int Camera_ID;
	int Board_Width;
	int Board_Height;
	float Square_Size;
	int Input_Delay;
	int Num_Frames;
	float Aspect_Ratio;
	BOOL Fix_Principal_Point_Center;
	BOOL Zero_Tangential_Distortion;
	BOOL Write_Det_Fea_Points;
	BOOL Write_Ex_Para;
	BOOL Show_Undistorted_Image;
	BOOL Flip_Around_Hor_Axis;
	bool Cirles_Grid;
	bool Asy_Circles_Grid;
	Settings s;
	bool Chess_Board;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio3();
	bool runCalibration(Settings& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs,
		vector<vector<Point2f> > imagePoints, vector<Mat>& rvecs, vector<Mat>& tvecs,
		vector<float>& reprojErrs, double& totalAvgErr);
	void calcBoardCornerPositions(Size boardSize, float squareSize, vector<Point3f>& corners, Pattern patternType);
	double computeReprojectionErrors(const vector<vector<Point3f> >& objectPoints,
		const vector<vector<Point2f> >& imagePoints,const vector<Mat>& rvecs, const vector<Mat>& tvecs,
		const Mat& cameraMatrix, const Mat& distCoeffs,vector<float>& perViewErrors);
	bool runCalibrationAndSave(Settings& s, Size imageSize, Mat& cameraMatrix, Mat& distCoeffs, vector<vector<Point2f> > imagePoints);
	void saveCameraParams(Settings& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs, const vector<Mat>& rvecs,
		const vector<Mat>& tvecs, const vector<float>& reprojErrs, const vector<vector<Point2f> >& imagePoints, double totalAvgErr);
	float Fx;
	float Fy;
	float Cx;
	float Cy;
	float K1;
	float K2;
	float RePro_Err;
};
