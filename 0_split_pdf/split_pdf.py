#!/home/lly/桌面/.pyvenv/bin/python3
import PyPDF2
import sys
import getopt
import os

#print '参数个数为:', len(sys.argv), '个参数。'
#print '参数列表:', str(sys.argv)
def split_pdf(input_path, output_path, page_range):
	input_file=open(input_path, 'rb')
	pdf_reader = PyPDF2.PdfReader(input_file)
	pdf_writer = PyPDF2.PdfWriter()
	for page_num in range(*page_range):
		pdf_writer.add_page(pdf_reader.pages[page_num])
	input_file.close()

	output_file=open(output_path, 'wb')
	pdf_writer.write(output_file)
	output_file.close()
	absolute_path = os.path.abspath(output_path)
	return absolute_path

if __name__=="__main__":
	try:
		opts=getopt.getopt(sys.argv[1:],"",["start-page=","end-page=","input-file=","output-file="])
		start_page=-1
		end_page=-1
		input_file=""
		output_file=""
		for opt,val in opts[0]:
			if opt=="--start-page" and int(val)>=0:
				start_page=int(val)
			if opt=="--end-page" and int(val)>=0:
				end_page=int(val)
			if opt=="--input-file" and val!="":
				input_file=val
			if opt=="--output-file" and val!="":
				output_file=val
		if start_page>=end_page or start_page<0 or end_page<0:
			raise ValueError
		print("主人~文件整理好了呢~请您过目~在这儿~\n"+split_pdf(input_file,output_file,(start_page,end_page)))
	except (getopt.GetoptError,ValueError):
		print("杂鱼~参数有问题~~略略略~~~")