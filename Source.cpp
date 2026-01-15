#pragma once
#include <iostream>
#include <fstream>
#include "Image.h"
#include "Huffman.h"

void convertToPBM(const string& inputFilename, const string& outputFilename) {
	cv::Mat image = cv::imread(inputFilename, cv::IMREAD_GRAYSCALE);
	if (image.empty()) {
		cout << "Greska pri otvaranju slike: " << inputFilename << endl;
		return;
	}

	//konvertuje input sliku u binarno crno-belu
	cv::Mat binaryImage;
	cv::threshold(image, binaryImage, 128, 1, cv::THRESH_BINARY_INV); // inverse je jer su meni beli pikseli 0, a crni 1

	ofstream outputFile(outputFilename, ios::out | ios::binary);
	if (!outputFile.is_open()) {
		cout << "Greska pri otvaranju izlaznog fajla: " << outputFilename << endl;
		return;
	}

	outputFile << "P1\n";
	outputFile << binaryImage.cols << " " << binaryImage.rows << "\n";
	for (int i = 0; i < binaryImage.rows; i++) {
		for (int j = 0; j < binaryImage.cols; j++)
			outputFile << static_cast<int>(binaryImage.at<uchar>(i, j)) << " ";
		outputFile << "\n";
	}

	outputFile.close();
	cout << "Konverzija u PBM gotova." << endl;
}

int main()
{
	string inputFilename;
	string outputFilename;
	cout << "Unesite putanju do input fajla (JPG/PNG slika):" << endl;
	cin >> inputFilename;

	cout << "Unesite ime za PBM datoteku (mora imati extension .pbm):" << endl;
	cin >> outputFilename;

	convertToPBM(inputFilename, outputFilename);

	string outputFile;
	cout << "Unesite ime za kompresovanu output datoteku (mora imati extension .bin):" << endl;
	cin >> outputFile;

	Huffman h;
	Image img;
	if (img.LoadImage(outputFilename)) {
		cout << "Uspesno ucitana slika." << endl;
	}
	else {
		cerr << "Neuspesno učitavanje slike." << endl;
	}

	vector<vector<pair<int, int>>> enc = img.SetEncodedImage();

	h.ProcessEncodedImage(enc, outputFile);
};