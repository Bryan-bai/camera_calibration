
// MyCalibrationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyCalibration.h"
#include "MyCalibrationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyCalibrationDlg 对话框



CMyCalibrationDlg::CMyCalibrationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYCALIBRATION_DIALOG, pParent)
	, Camera_ID(0)
	, Board_Width(0)
	, Board_Height(0)
	, Square_Size(0)
	, Input_Delay(0)
	, Num_Frames(0)
	, Aspect_Ratio(0)
	, Fix_Principal_Point_Center(FALSE)
	, Zero_Tangential_Distortion(FALSE)
	, Write_Det_Fea_Points(FALSE)
	, Write_Ex_Para(FALSE)
	, Show_Undistorted_Image(FALSE)
	, Flip_Around_Hor_Axis(FALSE)
	, Cirles_Grid(false)
	, Asy_Circles_Grid(false)
	, Chess_Board(false)
	, Fx(0)
	, Fy(0)
	, Cx(0)
	, Cy(0)
	, K1(0)
	, K2(0)
	, RePro_Err(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyCalibrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT8, Camera_ID);
	DDX_Text(pDX, IDC_EDIT1, Board_Width);
	DDX_Text(pDX, IDC_EDIT2, Board_Height);
	DDX_Text(pDX, IDC_EDIT3, Square_Size);
	DDX_Text(pDX, IDC_EDIT6, Input_Delay);
	DDX_Text(pDX, IDC_EDIT7, Num_Frames);
	DDX_Text(pDX, IDC_EDIT4, Aspect_Ratio);
	DDX_Check(pDX, IDC_CHECK2, Fix_Principal_Point_Center);
	DDX_Check(pDX, IDC_CHECK3, Zero_Tangential_Distortion);
	DDX_Check(pDX, IDC_CHECK4, Write_Det_Fea_Points);
	DDX_Check(pDX, IDC_CHECK5, Write_Ex_Para);
	DDX_Check(pDX, IDC_CHECK6, Show_Undistorted_Image);
	DDX_Check(pDX, IDC_CHECK7, Flip_Around_Hor_Axis);
	DDX_Text(pDX, IDC_EDIT9, Fx);
	DDX_Text(pDX, IDC_EDIT10, Fy);
	DDX_Text(pDX, IDC_EDIT11, Cx);
	DDX_Text(pDX, IDC_EDIT12, Cy);
	DDX_Text(pDX, IDC_EDIT13, K1);
	DDX_Text(pDX, IDC_EDIT14, K2);
	DDX_Text(pDX, IDC_EDIT15, RePro_Err);
}

BEGIN_MESSAGE_MAP(CMyCalibrationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyCalibrationDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO2, &CMyCalibrationDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO4, &CMyCalibrationDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO3, &CMyCalibrationDlg::OnBnClickedRadio3)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMyCalibrationDlg 消息处理程序

BOOL CMyCalibrationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Camera_ID = 0;
	Board_Width =9;
	Board_Height = 6;
	Square_Size = 50;;
	Aspect_Ratio=1;
	Input_Delay=100;
	Num_Frames=25;
	Chess_Board = true;
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(TRUE);
	UpdateData(false);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyCalibrationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyCalibrationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMyCalibrationDlg::OnBnClickedButton1()
{
	const char ESC_KEY = 27;
	const char SPACE_KEY = 32;
	UpdateData(true);
	s.cameraID= Camera_ID;
	s.boardSize.width = Board_Width;
	s.boardSize.height = Board_Height;
	s.squareSize = Square_Size;
	s.aspectRatio = Aspect_Ratio;
	s.delay = Input_Delay;
	s.nrFrames = Num_Frames;

	s.calibFixPrincipalPoint = Fix_Principal_Point_Center;
	s.calibZeroTangentDist = Zero_Tangential_Distortion;
	s.flipVertical = Flip_Around_Hor_Axis;
	s.showUndistorsed = Show_Undistorted_Image;
	s.writeExtrinsics = Write_Ex_Para;
	s.writePoints = Write_Det_Fea_Points;
	
	if (s.boardSize.width <= 0 || s.boardSize.height <= 0)
	{
		CString err;
		err.Format(_T("Invalid Board size: %d====%d\n"),s.boardSize.width,s.boardSize.height);
		AfxMessageBox(err,MB_OKCANCEL,MB_ICONEXCLAMATION);
		return;
	}
	if (s.squareSize <= 10e-6)
	{
		CString err;
		err.Format(_T("Invalid square size: %d\n"), s.squareSize);
		AfxMessageBox(err, MB_OKCANCEL, MB_ICONEXCLAMATION);
		return;
	}
	if (s.nrFrames <= 0)
	{
		CString err;
		err.Format(_T("Invalid number of frames: %d\n"), s.nrFrames);
		AfxMessageBox(err, MB_OKCANCEL, MB_ICONEXCLAMATION);
		return;
	}
	VideoCapture inputCapture(s.cameraID);
	if (!inputCapture.isOpened())
	{
		CString err;
		err.Format(_T(" Can not open Camera%d\n"), s.cameraID);
		AfxMessageBox(err, MB_OKCANCEL, MB_ICONEXCLAMATION);
		return;
	}
	s.flag = 0;
	if (s.calibFixPrincipalPoint) s.flag |= CALIB_FIX_PRINCIPAL_POINT;
	if (s.calibZeroTangentDist)   s.flag |= CALIB_ZERO_TANGENT_DIST;
	if (s.aspectRatio)            s.flag |= CALIB_FIX_ASPECT_RATIO;
	
	s.calibrationPattern = NOT_EXISTING;
	if (Chess_Board == true)
		s.calibrationPattern = CHESSBOARD;
	if (Cirles_Grid == true)
		s.calibrationPattern = CIRCLES_GRID;
	if (Asy_Circles_Grid == true)
		s.calibrationPattern = ASYMMETRIC_CIRCLES_GRID;

	if (s.calibrationPattern == NOT_EXISTING)
	{
		CString err;
		err.Format(_T("Camera calibration mode does not exist:%d\n"), s.calibrationPattern);
		AfxMessageBox(err, MB_OKCANCEL, MB_ICONEXCLAMATION);
		return;
	}
	const Scalar RED(0, 0, 255), GREEN(0, 255, 0);
	while (1)
	{
		vector<vector<Point2f> > imagePoints;
		Mat cameraMatrix, distCoeffs;
		Size imageSize;
		clock_t prevTimestamp = 0;
		Mat view;
		vector<Point2f> pointBuf;
		if (inputCapture.isOpened());
			inputCapture.retrieve(view);
		string msg = "Calibrated: Press 'c' to start,Press 'Esc' to quit";
		int baseLine = 0;
		Size textSize = getTextSize(msg, 1, 1, 1, &baseLine);
		Point textOrigin(view.cols - 2 * textSize.width+200, view.rows - 2 * baseLine - 10);
		putText(view, msg, textOrigin, 1, 1, RED);
		
		imshow("Image View", view);
		char key = (char)waitKey(inputCapture.isOpened() ? 50 : s.delay);
		if (key == ESC_KEY)
		{
			destroyWindow("Image View");
			break;
		}

		if (inputCapture.isOpened() && key == 'c')
		{
			while (1)
			{
				bool blinkOutput = false;
				if (inputCapture.isOpened());
					inputCapture.retrieve(view);
				imageSize = view.size();  // Format input image.
				if (s.flipVertical)    flip(view, view, 0);
				bool found = false;
				switch (s.calibrationPattern) // Find feature points on the input format
				{
				case CHESSBOARD:
					found = findChessboardCorners(view, s.boardSize, pointBuf, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);
					break;
				case CIRCLES_GRID:
					found = findCirclesGrid(view, s.boardSize, pointBuf);
					break;
				case ASYMMETRIC_CIRCLES_GRID:
					found = findCirclesGrid(view, s.boardSize, pointBuf, CALIB_CB_ASYMMETRIC_GRID);
					break;
				default:
					found = false;
					break;
				}
				if (found)                // If done with success,
				{
					// improve the found corners' coordinate accuracy for chessboard
					if (s.calibrationPattern == CHESSBOARD)
					{
						Mat viewGray;
						cvtColor(view, viewGray, COLOR_BGR2GRAY);
						cornerSubPix(viewGray, pointBuf, Size(11, 11), Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));
					}
					// Draw the corners.
					drawChessboardCorners(view, s.boardSize, Mat(pointBuf), found);
					if (!inputCapture.isOpened() || clock() - prevTimestamp > s.delay*1e-3*CLOCKS_PER_SEC)
					{
						imagePoints.push_back(pointBuf);
						prevTimestamp = clock();
						blinkOutput = inputCapture.isOpened();
					}
				}				
				if (s.showUndistorsed)
					msg = format("%d/%d Undist", (int)imagePoints.size(), s.nrFrames);
				else
					msg = format("%d/%d", (int)imagePoints.size(), s.nrFrames);
				putText(view, msg, textOrigin, 1, 1,GREEN);
				if (blinkOutput)
					bitwise_not(view, view);
				if (imagePoints.size() >= (size_t)s.nrFrames)
				{
					if (runCalibrationAndSave(s, imageSize, cameraMatrix, distCoeffs, imagePoints))
					{
						if (s.showUndistorsed)
						{
							Mat temp = view.clone();
							undistort(temp, view, cameraMatrix, distCoeffs);
							imshow("Image View", view);
						}
						while (1)
						{
							string msg = "Calibrated: Press 'space' to continue";
							int baseLine = 0;
							Size textSize = getTextSize(msg, 1, 1, 1, &baseLine);
							Point textOrigin(view.cols - 2 * textSize.width +250, view.rows - 2 * baseLine - 10);
							putText(view, msg, textOrigin, 1, 1, RED);
							imshow("Image View", view);
							char key = (char)waitKey(inputCapture.isOpened() ? 50 : s.delay);
							if (key == SPACE_KEY)
								break;
						}
						break;
					}
				}
				imshow("Image View", view);
				char key = (char)waitKey(inputCapture.isOpened() ? 50 : s.delay);
				if (key == ESC_KEY)
					break;
			}
			
		}
	}
	
}
bool CMyCalibrationDlg::runCalibrationAndSave(Settings& s, Size imageSize, Mat& cameraMatrix, Mat& distCoeffs,vector<vector<Point2f> > imagePoints)
{
	vector<Mat> rvecs, tvecs;
	vector<float> reprojErrs;
	double totalAvgErr = 0;

	bool ok = runCalibration(s, imageSize, cameraMatrix, distCoeffs, imagePoints, rvecs, tvecs, reprojErrs,totalAvgErr);
	CString info;
	if (ok)
	{
		//info.Format(_T("Calibration succeeded. avg re projection error = %f\n"),totalAvgErr);
		//AfxMessageBox(info, MB_OKCANCEL, MB_ICONINFORMATION);
		saveCameraParams(s, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs, reprojErrs, imagePoints,totalAvgErr);
		Fx = cameraMatrix.at<double>(0, 0);
		Fy = cameraMatrix.at<double>(1, 1);
		Cx = cameraMatrix.at<double>(0, 2);
		Cy = cameraMatrix.at<double>(1, 2);
		K1 = distCoeffs.at<double>(0, 0);
		K2 = distCoeffs.at<double>(1, 0);
		RePro_Err = totalAvgErr;
		UpdateData(false);
	}
	else
	{
		info.Format(_T("Calibration failed. avg re projection error = %f\n"), totalAvgErr);
		AfxMessageBox(info, MB_OKCANCEL, MB_ICONEXCLAMATION);
	}
	return ok;
}
void  CMyCalibrationDlg::saveCameraParams(Settings& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs,
	const vector<Mat>& rvecs, const vector<Mat>& tvecs,
	const vector<float>& reprojErrs, const vector<vector<Point2f> >& imagePoints,
	double totalAvgErr)
{
	FileStorage fs("out_camera_data.yml", FileStorage::WRITE);

	time_t tm;
	time(&tm);
	struct tm t2;
	localtime_s(&t2, &tm);
	char buf[1024];
	strftime(buf, sizeof(buf), "%c", &t2);

	fs << "calibration_time" << buf;

	if (!rvecs.empty() || !reprojErrs.empty())
		fs << "nr_of_frames" << (int)std::max(rvecs.size(), reprojErrs.size());
	fs << "image_width" << imageSize.width;
	fs << "image_height" << imageSize.height;
	fs << "board_width" << s.boardSize.width;
	fs << "board_height" << s.boardSize.height;
	fs << "square_size" << s.squareSize;

	if (s.flag & CALIB_FIX_ASPECT_RATIO)
		fs << "fix_aspect_ratio" << s.aspectRatio;

	if (s.flag)
	{
		printf(buf, "flags: %s%s%s%s",
			s.flag & CALIB_USE_INTRINSIC_GUESS ? " +use_intrinsic_guess" : "",
			s.flag & CALIB_FIX_ASPECT_RATIO ? " +fix_aspect_ratio" : "",
			s.flag & CALIB_FIX_PRINCIPAL_POINT ? " +fix_principal_point" : "",
			s.flag & CALIB_ZERO_TANGENT_DIST ? " +zero_tangent_dist" : "");
		cvWriteComment(*fs, buf, 0);
	}

	fs << "flags" << s.flag;

	fs << "camera_matrix" << cameraMatrix;
	fs << "distortion_coefficients" << distCoeffs;

	fs << "avg_reprojection_error" << totalAvgErr;
	if (s.writeExtrinsics && !reprojErrs.empty())
		fs << "per_view_reprojection_errors" << Mat(reprojErrs);

	if (s.writeExtrinsics && !rvecs.empty() && !tvecs.empty())
	{
		CV_Assert(rvecs[0].type() == tvecs[0].type());
		Mat bigmat((int)rvecs.size()*3, 4, rvecs[0].type());
		//Mat bigmat((int)rvecs.size(), 6, rvecs[0].type());
		for (size_t i = 0; i < rvecs.size(); i++)
		{
			Mat r = bigmat(Range(int(i*3), int(i*3 + 3)), Range(0, 3));
			Mat t = bigmat(Range(int(i*3), int(i*3 + 3)), Range(3, 4));
			//Mat r = bigmat(Range(int(i), int(i+ 1)), Range(0, 3));
			//Mat t = bigmat(Range(int(i), int(i + 1)), Range(3, 6));

			CV_Assert(rvecs[i].rows == 3 && rvecs[i].cols == 1);
			CV_Assert(tvecs[i].rows == 3 && tvecs[i].cols == 1);
			Rodrigues(rvecs[i], r);
			//*.t() is MatExpr (not Mat) so we can use assignment operator
			//r = rvecs[i].t();
			//t = tvecs[i].t();
			tvecs[i].copyTo(t);
		}	
		//cvWriteComment( *fs, "a set of 6-tuples (rotation vector + translation vector) for each view", 0 );
		fs << "extrinsic_parameters" << bigmat;
	}

	if (s.writePoints && !imagePoints.empty())
	{
		Mat imagePtMat((int)imagePoints.size(), (int)imagePoints[0].size(), CV_32FC2);
		for (size_t i = 0; i < imagePoints.size(); i++)
		{
			Mat r = imagePtMat.row(int(i)).reshape(2, imagePtMat.cols);
			Mat imgpti(imagePoints[i]);
			imgpti.copyTo(r);
		}
		fs << "image_points" << imagePtMat;
	}
}
bool CMyCalibrationDlg:: runCalibration(Settings& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs,
	vector<vector<Point2f> > imagePoints, vector<Mat>& rvecs, vector<Mat>& tvecs,
	vector<float>& reprojErrs, double& totalAvgErr)
{
	//! [fixed_aspect]
	cameraMatrix = Mat::eye(3, 3, CV_64F);
	if (s.flag & CALIB_FIX_ASPECT_RATIO)
		cameraMatrix.at<double>(0, 0) = s.aspectRatio;
	//! [fixed_aspect]
	distCoeffs = Mat::zeros(8, 1, CV_64F);

	vector<vector<Point3f> > objectPoints(1);
	calcBoardCornerPositions(s.boardSize, s.squareSize, objectPoints[0], s.calibrationPattern);

	objectPoints.resize(imagePoints.size(), objectPoints[0]);

	//Find intrinsic and extrinsic camera parameters
	double rms = calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix,distCoeffs, rvecs, tvecs, s.flag | CALIB_FIX_K4 | CALIB_FIX_K5);

	bool ok = checkRange(cameraMatrix) && checkRange(distCoeffs);

	totalAvgErr = computeReprojectionErrors(objectPoints, imagePoints,rvecs, tvecs, cameraMatrix, distCoeffs, reprojErrs);

	return ok;
}
void CMyCalibrationDlg::calcBoardCornerPositions(Size boardSize, float squareSize, vector<Point3f>& corners,Pattern patternType)
{
	corners.clear();
	switch (patternType)
	{
	case CHESSBOARD:
		//	break;
	case CIRCLES_GRID:
			for (int i = 0; i < boardSize.height; ++i)
				for (int j = 0; j < boardSize.width; ++j)
					corners.push_back(Point3f(j*squareSize, i*squareSize, 0));
			break;
	case ASYMMETRIC_CIRCLES_GRID:
			for (int i = 0; i < boardSize.height; i++)
				for (int j = 0; j < boardSize.width; j++)
					corners.push_back(Point3f((2 * j + i % 2)*squareSize, i*squareSize, 0));
			break;
	default:
			break;
	}
}
double CMyCalibrationDlg::computeReprojectionErrors(const vector<vector<Point3f> >& objectPoints,
	const vector<vector<Point2f> >& imagePoints,const vector<Mat>& rvecs, const vector<Mat>& tvecs,
	const Mat& cameraMatrix, const Mat& distCoeffs,vector<float>& perViewErrors)
{
	vector<Point2f> imagePoints2;
	size_t totalPoints = 0;
	double totalErr = 0, err;
	perViewErrors.resize(objectPoints.size());

	for (size_t i = 0; i < objectPoints.size(); ++i)
	{
		projectPoints(objectPoints[i], rvecs[i], tvecs[i], cameraMatrix, distCoeffs, imagePoints2);
		err = norm(imagePoints[i], imagePoints2, NORM_L2);

		size_t n = objectPoints[i].size();
		perViewErrors[i] = (float)std::sqrt(err*err / n);
		totalErr += err*err;
		totalPoints += n;
	}

	return sqrt(totalErr / totalPoints);
}

void CMyCalibrationDlg::OnBnClickedRadio2()
{
	 Cirles_Grid= true;
	 Chess_Board = false;
	 Asy_Circles_Grid = false;
}


void CMyCalibrationDlg::OnBnClickedRadio4()
{
	Chess_Board = true;
	Cirles_Grid = false;
	Asy_Circles_Grid = false;
}


void CMyCalibrationDlg::OnBnClickedRadio3()
{
	Asy_Circles_Grid = true;
	Cirles_Grid = false;
	Chess_Board = false;
}