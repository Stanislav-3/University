; ���������, ����������� ������� � ���������� �����, ����� ������, � ����������� �������.

        .model     tiny
        .stack     100h
        .code
        .386p                          ; ��� ���� ������� ���������� �� 80386
        org        100h                ; ��� ���-���������

start:
; ����������� ���������� ��������
        push       cs
        pop        ds               ; DS - ������� ������ (� ����) ����� ���������
        push       0B800h
        pop        es               ; ES - ������� �����������
; ��������� ����������
        cli
; ��������� ������������� ����������
        in         al,70h              ; ��������� ���� CMOS
        or         al,80h              ; ��������� ���� 7 � ��� ��������� NMI
        out        70h,al
; ������� � ���������� �����
        mov        eax,cr0             ; ��������� ������� CRO
        or         al,1                ; ���������� ��� ��,
        mov        cr0,eax             ; � ����� ������� �� � ���������� ������



; ������������� � �������� �����
        mov        eax,cr0             ; ��������� CR0
        and        al,0FEh             ; �������� ��� ��
        mov        cr0,eax             ; � ����� ������� ��������� �������� � �������� ������
; ��������� ������������� ����������
        in         al,70h              ; ��������� ���� CMOS
        and        al,07Fh             ; ����� ���� 7 �������� ������������ NMI
        out        70h,al
; ��������� ����������
        sti
; ��������� ������� ����� �������
;        mov        ah,0
;        int        16h
; ����� �� ���������
        mov ax, 4c00h
        int 21h
end        start