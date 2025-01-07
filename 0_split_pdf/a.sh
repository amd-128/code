#!/bin/bash
PAGE_NUM=`./get_pdf_page_num.py $1`
SINGLE_NUM=$(expr $PAGE_NUM / $2)
START_PAGE=0
for i in $(seq 1 $(expr $2 - 1)); do
    END_PAGE=$(expr $SINGLE_NUM \* $i)
    ./split_pdf.py --input-file=$1 --output-file="$1_$i.pdf" --start-page=$START_PAGE --end-page=$END_PAGE
    START_PAGE=$END_PAGE
done
./split_pdf.py --input-file=$1 --output-file=$1_$2.pdf --start-page=$START_PAGE --end-page=$PAGE_NUM