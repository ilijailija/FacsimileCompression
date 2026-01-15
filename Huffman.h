#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct HuffmanCode {
	string bits;
	int lenght;
};

class Huffman
{
	void InitializeHuffmanCodes();

	unordered_map<int, HuffmanCode> terminationCodes;
	unordered_map<int, HuffmanCode> makeupCodes;

public:
	Huffman();
	HuffmanCode GetHuffmanCode(int lenght, bool isBlack);
	bool ProcessEncodedImage(vector<vector<pair<int, int>>> endImg, const string& filename);
};

 