#!/home/lly/桌面/.pyvenv/bin/python3
from PyPDF2 import PdfReader
import sys
filename = sys.argv[1]
reader = PdfReader(filename)

page = len(reader.pages)
print(page)