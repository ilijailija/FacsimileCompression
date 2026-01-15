#include "Image.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

bool Image::LoadImage(const string& filename)
{
	ifstream f(filename);
	if (!f.is_open())
	{
		cout << "Neuspešno otvaranje fajla!" << endl;
		return false;
	}

	string line;
	getline(f, line);
	if (line != "P1")
	{
		cout << "Format nije podržan." << endl;
		return false;
	}

	while (getline(f, line)) {
		if (line[0] != '#') { // Ako linija nije komentar
			break; // Našli smo liniju sa dimenzijama, izlazimo iz petlje
		}
	}

	istringstream iss(line);
	iss >> width >> height;

	pixels.clear();
	pixels.resize(height, vector<int>(width));

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			f >> pixels[i][j];
		}
	}
	cout << width << endl;
	cout << height << endl;

	f.close();
	return true;
}

vector<pair<int, int>> Image::rlEncode(const vector<int>& row)
{
	vector<pair<int, int>> encoded; // prazan vektor: duzina niza-boja piksela u nizu
	if (row.empty())
		return encoded;

	int count = 1;
	int currentPixel = row[0];

	for (int i = 1; i < row.size(); i++) {
		if (row[i] == currentPixel)
			count++; // ako je piksel isti kao prethodni, povecava brojac sekvence
		else {
			//cuva trenutnu sekvencu i resetuje brojac
			encoded.push_back({ count,currentPixel });
			currentPixel = row[i];
			count = 1;
		}
	}
	// cuva poslednju sekvencu
	encoded.push_back({ count,currentPixel });

	return encoded;
}


vector<vector<pair<int, int>>> Image::SetEncodedImage()
{
	for (int i = 0; i < height; i++)
	{
		encodedImage.push_back(rlEncode(pixels[i]));
	}
	return encodedImage;
}
