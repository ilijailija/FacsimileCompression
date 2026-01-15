#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
using namespace std;

class Image
{
	int width = 0;
	int height = 0;
	vector<vector<int>> pixels;
	vector<vector<pair<int, int>>> encodedImage; //podaci slike nakon rleEncode

public:
	bool LoadImage(const string& filename);
	vector<pair<int, int>> rlEncode(const vector<int>& row);
	vector<vector<pair<int, int>>> SetEncodedImage();
};

