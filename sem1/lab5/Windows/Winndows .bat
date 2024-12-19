@echo off
chcp 1251
setlocal

rem �������� ���������� ��� �������� ��������� ������ � ���������� ���������
set "total_memory=0"
set "process_count=0"

rem ������������� ������� tasklist ��� ��������� ���������� � ���������
for /f "skip=3 tokens=5" %%A in ('tasklist') do (
    set /a total_memory+=%%A
    set /a process_count+=1
)

rem ���������� ����������� � ����
set "output_file=system_memory_usage.txt"
echo ��������� ����� ������ (� KB): %total_memory% > "%output_file%"
echo ����� �������� ���������: %process_count% >> "%output_file%"

echo ���������� ��������� � ���� %output_file%
pause

