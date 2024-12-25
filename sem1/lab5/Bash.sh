#!/bin/bash

# �������� ���������� ����������
If [ �$#� -ne 4 ]; then
    Echo ��������������: $0 <�������> <min_size> <max_size> <��������>�
    Exit 1
Fi

Dir=�$1�
Min_size=�$2�
Max_size=�$3�
Owner=�$4�

# �������� ������������� ��������
If [ ! -d �$dir� ]; then
    Echo ������� ����� ���
    Exit 1
Fi

# ����� ������ � ����� �����������
Find �$dir� -type f -size +$min_sizec -size -$max_sizec -user �$owner� -exec ls -ld {} \; > results.txt
Total_files=$(find �$dir� -type f | wc -l)
Echo ������ ����� ������������� ������: $total_files� >> results.txt

