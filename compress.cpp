#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <zlib.h>
using namespace std;

int main(int argc, char** argv) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }

  string filename = argv[1];
  ifstream input_file(filename, ios::binary);
  if (!input_file) {
    cerr << "Error: could not open input file '" << filename << "'\n";
    return 1;
  }

  vector<char> input_data(
      (istreambuf_iterator<char>(input_file)),
      (istreambuf_iterator<char>()));

  vector<char> compressed_data(input_data.size() * 2);
  uLongf compressed_size = compressed_data.size();
  int zlib_result = compress(
      (Bytef*)&compressed_data[0],
      &compressed_size,
      (const Bytef*)&input_data[0],
      input_data.size());
  if (zlib_result != Z_OK) {
    cerr << "Error: compression failed (zlib error " << zlib_result << ")\n";
    return 1;
  }

  cout << "Compression complete:\n";
  cout << "  Input size: " << input_data.size() << " bytes\n";
  cout << "  Compressed size: " << compressed_size << " bytes\n";
  cout << "  Compression ratio: " << (double)input_data.size() / compressed_size << "\n";

  return 0;
}

