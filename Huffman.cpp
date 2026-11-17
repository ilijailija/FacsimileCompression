#include "Huffman.h"
#include <iostream>

using namespace std;

Huffman::Huffman() {
	InitializeHuffmanCodes();
}

HuffmanCode Huffman::GetHuffmanCode(int lenght, bool isBlack) {
    int blackOffset = isBlack ? 64 : 0;
    int blackOffsetMakeup = isBlack ? 40 : 0;

    HuffmanCode combinedCode;
    combinedCode.bits = "";


    while (lenght > 2623) {
        combinedCode.bits += makeupCodes.at(39).bits; // 2560
        lenght -= 2560;
    }

    if (lenght >= 64) {
        int makeUpIndex = lenght / 64 - 1;
        if (isBlack && makeUpIndex < 27)
            makeUpIndex += blackOffsetMakeup;
        combinedCode.bits += makeupCodes.at(makeUpIndex).bits;
    }
    combinedCode.bits += terminationCodes.at(lenght % 64 + blackOffset).bits;

    combinedCode.lenght = static_cast<int>(combinedCode.bits.size()); // ukupan broj bitova
    return combinedCode;
}
bool Huffman::ProcessEncodedImage(vector<vector<pair<int, int>>> endImg, const string& filename)
{
    ofstream os(filename, ios::out | ios::binary);

    if (!os) {
        cout << "Neuspesno otvaranje output fajla." << endl;
        return false;
    }

    unsigned char buffer = 0; // bajt koji se trenutno puni
    int bitCount = 0;         // koliko je bitova vec upisano u buffer (0-7)

    // upisuje string od '0' i '1' karaktera kao prave bitove, bajt po bajt
    auto writeBits = [&](const string& bits) {
        for (char c : bits) {
            buffer = (buffer << 1) | (c == '1' ? 1 : 0);
            if (++bitCount == 8) {
                os.put(static_cast<char>(buffer));
                buffer = 0;
                bitCount = 0;
            }
        }
        };

    size_t size = endImg.size();
    const string eol = "000000000001";

    writeBits(eol); // prvi eol na stranici

    for (size_t i = 0; i < size; i++) {
        if (endImg[i][0].second == 1) { // red mora poceti belim nizom; ako je prvi niz crn, beli niz je duzine 0
            writeBits(terminationCodes[0].bits);
        }
        for (size_t j = 0; j < endImg[i].size(); j++) {
            HuffmanCode str = GetHuffmanCode(endImg[i][j].first, endImg[i][j].second);
            writeBits(str.bits);
        }
        writeBits(eol); // eol na kraju svake linije
    }
    for (int i = 0; i < 6; i++)
        writeBits(eol); // 6 eol-a na kraju stranice

    // poslednji nepopunjen bajt se dopunjuje nulama zdesna i upisuje
    if (bitCount > 0) {
        buffer <<= (8 - bitCount);
        os.put(static_cast<char>(buffer));
    }

    os.close();
    return true;
}
void Huffman::InitializeHuffmanCodes()
{
    terminationCodes[0] = { "00110101", 8 };
    terminationCodes[1] = { "000111", 6 };
    terminationCodes[2] = { "0111", 4 };
    terminationCodes[3] = { "1000", 4 };
    terminationCodes[4] = { "1011", 4 };
    terminationCodes[5] = { "1100", 4 };
    terminationCodes[6] = { "1110", 4 };
    terminationCodes[7] = { "1111", 4 };
    terminationCodes[8] = { "10011", 5 };
    terminationCodes[9] = { "10100", 5 };
    terminationCodes[10] = { "00111", 5 };
    terminationCodes[11] = { "01000", 5 };
    terminationCodes[12] = { "001000", 6 };
    terminationCodes[13] = { "000011", 6 };
    terminationCodes[14] = { "110100", 6 };
    terminationCodes[15] = { "110101", 6 };
    terminationCodes[16] = { "101010", 6 };
    terminationCodes[17] = { "101011", 6 };
    terminationCodes[18] = { "0100111", 7 };
    terminationCodes[19] = { "0001100", 7 };
    terminationCodes[20] = { "0001000", 7 };
    terminationCodes[21] = { "0010111", 7 };
    terminationCodes[22] = { "0000011", 7 };
    terminationCodes[23] = { "0000100", 7 };
    terminationCodes[24] = { "0101000", 7 };
    terminationCodes[25] = { "0101011", 7 };
    terminationCodes[26] = { "0010011", 7 };
    terminationCodes[27] = { "0100100", 7 };
    terminationCodes[28] = { "0011000", 7 };
    terminationCodes[29] = { "00000010", 8 };
    terminationCodes[30] = { "00000011", 8 };
    terminationCodes[31] = { "00011010", 8 }; 
    terminationCodes[32] = { "00011011", 8 };
    terminationCodes[33] = { "00010010", 8 };
    terminationCodes[34] = { "00010011", 8 };
    terminationCodes[35] = { "00010100", 8 };
    terminationCodes[36] = { "00010101", 8 };
    terminationCodes[37] = { "00010110", 8 };
    terminationCodes[38] = { "00010111", 8 };
    terminationCodes[39] = { "00101000", 8 };
    terminationCodes[40] = { "00101001", 8 };
    terminationCodes[41] = { "00101010", 8 };
    terminationCodes[42] = { "00101011", 8 };
    terminationCodes[43] = { "00101100", 8 };
    terminationCodes[44] = { "00101101", 8 };
    terminationCodes[45] = { "00000100", 8 };
    terminationCodes[46] = { "00000101", 8 };
    terminationCodes[47] = { "00001010", 8 };
    terminationCodes[48] = { "00001011", 8 };
    terminationCodes[49] = { "01010010", 8 };
    terminationCodes[50] = { "01010011", 8 };
    terminationCodes[51] = { "01010100", 8 };
    terminationCodes[52] = { "01010101", 8 };
    terminationCodes[53] = { "00100100", 8 };
    terminationCodes[54] = { "00100101", 8 };
    terminationCodes[55] = { "01011000", 8 };
    terminationCodes[56] = { "01011001", 8 };
    terminationCodes[57] = { "01011010", 8 };
    terminationCodes[58] = { "01011011", 8 };
    terminationCodes[59] = { "01001010", 8 };
    terminationCodes[60] = { "01001011", 8 };
    terminationCodes[61] = { "00110010", 8 };
    terminationCodes[62] = { "00110011", 8 };
    terminationCodes[63] = { "00110100", 8 }; // beli su provereni

    // Terminacioni kodovi za crne sekvence (od 0 do 63 piksela)
    terminationCodes[64] = { "0000110111", 10 };    // 0 crnih piksela
    terminationCodes[65] = { "010", 3 };            // 1 crni piksel
    terminationCodes[66] = { "11", 2 };             // 2 crna piksela
    terminationCodes[67] = { "10", 2 };             // 3 crna piksela
    terminationCodes[68] = { "011", 3 };            // 4 crna piksela
    terminationCodes[69] = { "0011", 4 };           // 5 crnih piksela
    terminationCodes[70] = { "0010", 4 };           // 6 crnih piksela
    terminationCodes[71] = { "00011", 5 };          // 7 crnih piksela
    terminationCodes[72] = { "000101", 6 };         // 8 crnih piksela
    terminationCodes[73] = { "000100", 6 };         // 9 crnih piksela
    terminationCodes[74] = { "0000100", 7 };        // 10 crnih piksela
    terminationCodes[75] = { "0000101", 7 };        // 11 crnih piksela
    terminationCodes[76] = { "0000111", 7 };        // 12 crnih piksela
    terminationCodes[77] = { "00000100", 8 };       // 13 crnih piksela
    terminationCodes[78] = { "00000111", 8 };       // 14 crnih piksela
    terminationCodes[79] = { "000011000", 9 };      // 15 crnih piksela
    terminationCodes[80] = { "0000010111", 10 };    // 16 crnih piksela
    terminationCodes[81] = { "0000011000", 10 };    // 17 crnih piksela
    terminationCodes[82] = { "0000001000", 10 };    // 18 crnih piksela
    terminationCodes[83] = { "00001100111", 11 };  // 19 crnih piksela
    terminationCodes[84] = { "00001101000", 11 };  // 20 crnih piksela
    terminationCodes[85] = { "00001101100", 11 };  // 21 crnih piksela
    terminationCodes[86] = { "00000110111", 11 };  // 22 crnih piksela
    terminationCodes[87] = { "00000101000", 11 };  // 23 crnih piksela
    terminationCodes[88] = { "00000010111", 11 };  // 24 crnih piksela
    terminationCodes[89] = { "00000011000", 11 };  // 25 crnih piksela
    terminationCodes[90] = { "000011001010", 12 };  // 26 crnih piksela
    terminationCodes[91] = { "000011001011", 12 };  // 27 crnih piksela
    terminationCodes[92] = { "000011001100", 12 };  // 28 crnih piksela
    terminationCodes[93] = { "000011001101", 12 };  // 29 crnih piksela
    terminationCodes[94] = { "000001101000", 12 };  // 30 crnih piksela
    terminationCodes[95] = { "000001101001", 12 };  // 31 crnih piksela
    terminationCodes[96] = { "000001101010", 12 };  // 32 crnih piksela
    terminationCodes[97] = { "000001101011", 12 };  // 33 crnih piksela
    terminationCodes[98] = { "000011010010", 12 };  // 34 crnih piksela
    terminationCodes[99] = { "000011010011", 12 };  // 35 crnih piksela
    terminationCodes[100] = { "000011010100", 12 }; // 36 crnih piksela
    terminationCodes[101] = { "000011010101", 12 }; // 37 crnih piksela
    terminationCodes[102] = { "000011010110", 12 }; // 38 crnih piksela
    terminationCodes[103] = { "000011010111", 12 }; // 39 crnih piksela
    terminationCodes[104] = { "000001101100", 12 }; // 40 crnih piksela
    terminationCodes[105] = { "000001101101", 12 }; // 41 crnih piksela
    terminationCodes[106] = { "000011011010", 12 }; // 42 crnih piksela
    terminationCodes[107] = { "000011011011", 12 }; // 43 crnih piksela
    terminationCodes[108] = { "000001010100", 12 }; // 44 crnih piksela
    terminationCodes[109] = { "000001010101", 12 }; // 45 crnih piksela
    terminationCodes[110] = { "000001010110", 12 }; // 46 crnih piksela
    terminationCodes[111] = { "000001010111", 12 }; // 47 crnih piksela
    terminationCodes[112] = { "000001100100", 12 }; // 48 crnih piksela
    terminationCodes[113] = { "000001100101", 12 }; // 49 crnih piksela
    terminationCodes[114] = { "000001010010", 12 }; // 50 crnih piksela
    terminationCodes[115] = { "000001010011", 12 }; // 51 crnih piksela
    terminationCodes[116] = { "000000100100", 12 }; // 52 crnih piksela
    terminationCodes[117] = { "000000110111", 12 }; // 53 crnih piksela
    terminationCodes[118] = { "000000111000", 12 }; // 54 crnih piksela
    terminationCodes[119] = { "000000100111", 12 }; // 55 crnih piksela
    terminationCodes[120] = { "000000101000", 12 }; // 56 crnih piksela
    terminationCodes[121] = { "000001011000", 12 }; // 57 crnih piksela
    terminationCodes[122] = { "000001011001", 12 }; // 58 crnih piksela
    terminationCodes[123] = { "000000101011", 12 }; // 59 crnih piksela
    terminationCodes[124] = { "000000101100", 12 }; // 60 crnih piksela
    terminationCodes[125] = { "000001011010", 12 }; // 61 crnih piksela
    terminationCodes[126] = { "000001100110", 12 }; // 62 crnih piksela
    terminationCodes[127] = { "000001100111", 12 }; // 63 crnih piksela

    makeupCodes[0] = { "11011", 5 };        // 64 bele piksela
    makeupCodes[1] = { "10010", 5 };       // 128 belih piksela
    makeupCodes[2] = { "010111", 6 };       // 192 bele piksela
    makeupCodes[3] = { "0110111", 7 };       // 256 belih piksela
    makeupCodes[4] = { "00110110", 8 };       // 320 belih piksela
    makeupCodes[5] = { "00110111", 8 };       // 384 belih piksela
    makeupCodes[6] = { "01100100", 8 };       // 448 belih piksela
    makeupCodes[7] = { "01100101", 8 };       // 512 belih piksela
    makeupCodes[8] = { "01101000", 8 };       // 576 belih piksela
    makeupCodes[9] = { "01100111", 8 };       // 640 belih piksela
    makeupCodes[10] = { "011001100", 9 };      // 704 bele piksela
    makeupCodes[11] = { "011001101", 9 };      // 768 belih piksela
    makeupCodes[12] = { "011010010", 9 };     // 832 belih piksela
    makeupCodes[13] = { "011010011", 9 };     // 896 belih piksela
    makeupCodes[14] = { "011010100", 9 };     // 960 belih piksela
    makeupCodes[15] = { "011010101", 9 };     // 1024 bele piksela
    makeupCodes[16] = { "011010110", 9 };     // 1088 belih piksela
    makeupCodes[17] = { "011010111", 9 };    // 1152 belih piksela
    makeupCodes[18] = { "011011000", 9 };    // 1216 belih piksela
    makeupCodes[19] = { "011011001", 9 };    // 1280 belih piksela
    makeupCodes[20] = { "011011010", 9 };    // 1344 belih piksela
    makeupCodes[21] = { "011011011", 9 };    // 1408 belih piksela
    makeupCodes[22] = { "010011000", 9 };    // 1472 belih piksela
    makeupCodes[23] = { "010011001", 9 };    // 1536 belih piksela
    makeupCodes[24] = { "010011010", 9 };    // 1600 belih piksela
    makeupCodes[25] = { "011000", 6 };    // 1664 belih piksela
    makeupCodes[26] = { "010011011", 9 };    // 1728 belih piksela
    makeupCodes[27] = { "00000001000", 11 };    // 1792 belih piksela
    makeupCodes[28] = { "00000001100", 11 };    // 1856 belih piksela
    makeupCodes[29] = { "00000001101", 11 };    // 1920 belih piksela
    makeupCodes[30] = { "000000010010", 12 };    // 1984 belih piksela
    makeupCodes[31] = { "000000010011", 12 };    // 2048 belih piksela
    makeupCodes[32] = { "000000010100", 12 };    // 2112 belih piksela
    makeupCodes[33] = { "000000010101", 12 };   // 2176 belih piksela
    makeupCodes[34] = { "000000010110", 12 };   // 2240 belih piksela
    makeupCodes[35] = { "000000010111", 12 };   // 2304 belih piksela
    makeupCodes[36] = { "000000011100", 12 };   // 2368 belih piksela
    makeupCodes[37] = { "000000011101", 12 };   // 2432 belih piksela
    makeupCodes[38] = { "000000011110", 12 };   // 2496 belih piksela
    makeupCodes[39] = { "000000011111", 12 };   // 2560 belih piksela

    makeupCodes[40] = { "0000001111", 10 };       // 64 crnih piksela
    makeupCodes[41] = { "000011001000", 12 };       // 128 crnih piksela
    makeupCodes[42] = { "000011001001", 12 };       // 192 crnih piksela
    makeupCodes[43] = { "000001011011", 12 };       // 256 crnih piksela
    makeupCodes[44] = { "000000110011", 12 };       // 320 crnih piksela
    makeupCodes[45] = { "000000110100", 12 };       // 384 crnih piksela
    makeupCodes[46] = { "000000110101", 12 };       // 448 crnih piksela
    makeupCodes[47] = { "0000001101100", 13 };       // 512 crnih piksela
    makeupCodes[48] = { "0000001101101", 13 };       // 576 crnih piksela
    makeupCodes[49] = { "0000001001010", 13 };       // 640 crnih piksela
    makeupCodes[50] = { "0000001001011", 13 };       // 704 crnih piksela
    makeupCodes[51] = { "0000001001100", 13 };       // 768 crnih piksela
    makeupCodes[52] = { "0000001001101", 13 };       // 832 crnih piksela
    makeupCodes[53] = { "0000001110010", 13 };       // 896 crnih piksela
    makeupCodes[54] = { "0000001110011", 13 };       // 960 crnih piksela
    makeupCodes[55] = { "0000001110100", 13 };       // 1024 crnih piksela
    makeupCodes[56] = { "0000001110101", 13 };       // 1088 crnih piksela
    makeupCodes[57] = { "0000001110110", 13 };       // 1152 crnih piksela
    makeupCodes[58] = { "0000001110111", 13 };       // 1216 crnih piksela
    makeupCodes[59] = { "0000001010010", 13 };       // 1280 crnih piksela
    makeupCodes[60] = { "0000001010011", 13 };       // 1344 crnih piksela
    makeupCodes[61] = { "0000001010100", 13 };       // 1408 crnih piksela
    makeupCodes[62] = { "0000001010101", 13 };       // 1472 crnih piksela
    makeupCodes[63] = { "0000001011010", 13 };       // 1536 crnih piksela
    makeupCodes[64] = { "0000001011011", 13 };       // 1600 crnih piksela
    makeupCodes[65] = { "0000001100100", 13 };       // 1664 crnih piksela
    makeupCodes[66] = { "0000001100101", 13 };       // 1728 crnih piksela
}
