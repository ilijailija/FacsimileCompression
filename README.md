<<<<<<< HEAD
FacsimileCompression1D

A C++ console application that compresses a black-and-white image using the ITU-T T.4 one-dimensional coding scheme (Modified Huffman), as used in Group 3 fax machines.

How it works
Conversion to PBM: the input image (JPG/PNG) is loaded with OpenCV in grayscale and binarized with a threshold of 128. Black pixels become 1 and white pixels 0. The result is written as a plain-text PBM (P1) file.
Run-length encoding: every row of the image is converted into a sequence of (run length, color) pairs.
Modified Huffman coding: each run length is encoded using the T.4 code tables:
lengths 0-63: a single terminating code,
lengths 64-2560: a make-up code followed by a terminating code,
lengths above 2623: the 2560 make-up code is repeated until the remainder fits in the table.
Every row starts with a white run (of length 0 if the row begins with a black pixel). The codes for lengths 1792-2560 are shared between white and black runs.
Writing the output: the codes are packed into real bits (not ASCII characters), with an EOL code (000000000001) at the start, after every row, and 6 EOL codes at the end of the page. The last byte is padded with zeros.
Project structure
File	Description
Source.cpp	main, prompts for file paths and conversion of the input image to PBM
Image.h / Image.cpp	PBM loading and run-length encoding of rows
Huffman.h / Huffman.cpp	T.4 code tables, code selection for a given run length, and bit-level output
Build and run

Requirements: Visual Studio 2022 (toolset v143) and OpenCV 4.10 (opencv_world4100d.lib).

Open FacsimileCompression1D.sln.
In the project properties, set the OpenCV paths.
Run the program and enter, in order:
the path to the input image (JPG/PNG),
a name for the intermediate .pbm file,
a name for the compressed .bin output file.

File paths must not contain spaces.

Limitations
Only the encoder is implemented; there is no decoder yet.
The output is a raw T.4 bit stream without a header, so the image dimensions are not stored in the file.
=======
# FacsimileCompression1D

Konzolna C++ aplikacija koja kompresuje crno-belu sliku po standardu za faks, **ITU-T T.4 jednodimenzionalno kodiranje (Modified Huffman)**, kakav se koristi u faks uređajima grupe 3.

## Kako radi

1. **Konverzija u PBM:** ulazna slika (JPG/PNG) se učitava pomoću OpenCV-a u sivim tonovima i binarizuje pragom 128. Crni pikseli dobijaju vrednost 1, beli 0. Rezultat se upisuje kao tekstualni PBM (`P1`).
2. **Run-length kodiranje:** svaki red slike se pretvara u niz parova *(dužina niza, boja)*.
3. **Modified Huffman kodiranje:** svaka dužina niza se kodira T.4 tabelama:
   - dužine 0–63: jedan terminacioni kod,
   - dužine 64–2560: makeup kod plus terminacioni kod,
   - duže od 2623: makeup kod za 2560 se ponavlja dok ostatak ne stane u tabelu.

   Svaki red počinje belim nizom (dužine 0 ako red počinje crnim pikselom). Kodovi za dužine 1792–2560 su zajednički za bele i crne nizove.
4. **Upis u fajl:** kodovi se pakuju u prave bitove (a ne u ASCII karaktere), uz `EOL` kod (`000000000001`) na početku, iza svakog reda i 6 `EOL` kodova na kraju stranice. Poslednji bajt se dopunjava nulama.

## Struktura projekta

| Fajl | Opis |
|---|---|
| `Source.cpp` | `main`, unos putanja i konverzija ulazne slike u PBM |
| `Image.h` / `Image.cpp` | učitavanje PBM-a i run-length kodiranje redova |
| `Huffman.h` / `Huffman.cpp` | T.4 tabele kodova, izbor koda za zadatu dužinu niza i upis bitova |

## Pokretanje

Potrebno: Visual Studio 2022 (toolset v143) i OpenCV 4.10 (`opencv_world4100d.lib`).

1. Otvori `FacsimileCompression1D.sln`.
2. U svojstvima projekta podesi putanje do OpenCV-a (trenutno `C:\OpenCV\opencv\build\include` i `C:\OpenCV\opencv\build\x64\vc16\lib`). Projekat je podešen za konfiguraciju **Debug | x64**.
3. Pokreni program i unesi, redom:
   - putanju do ulazne slike (JPG/PNG),
   - ime međufajla `.pbm`,
   - ime kompresovanog izlaznog fajla `.bin`.

Putanje ne smeju sadržati razmake.

## Ograničenja

- Postoji samo enkoder, dekoder još nije napisan.
- Izlaz je T.4 tok bitova bez zaglavlja, pa nema podatka o dimenzijama slike osim onog što se može izvesti iz samih redova.
>>>>>>> 52142a1 (Fixed bit codes)
