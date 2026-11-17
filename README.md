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
