unit hand;

interface

uses
  CRT, sort, time;

procedure menu1();

implementation

procedure output(var a: arr; var b: arr; n: integer; p1, p2: integer; ot: boolean);
var
  i: integer;
begin
  if p2 <> 0 then begin
    writeln('�������� ������ � ', p1, '�� �� ', p2, ' ������� (����� ', n, '):');
    for i := p1 to p2 do write(a[i], ' ');
    if ot = true then begin
      writeln();
      writeln('��������������� ������:');
      for i := p1 to p2 do write(b[i], ' ');
    end;
  end else writeln('������ �� ������');
  ReadKey;
end;

procedure input(var a: arr; var b: arr; var n: integer; p1: integer; var p2: integer; var ot: boolean);{�������� �������}
var
  q1, q2, i: integer;
  q: integer;
  sym: char;
begin
  q := 1;
  repeat
    ClrScr;
    writeln('    �������� ������� (������� ������ ���������� ������)');
    case q of
      1:
        begin
          writeln('* ������� ��������� ������ � ��������� [a; b]');
          writeln('  ������� ��������� ������ � ��������� [0; b]');
          writeln('  ������� ������������� ������');
          writeln('  ������� �������������������� ������');
          write('  ');
        end;
      2:
        begin
          writeln('  ������� ��������� ������ � ��������� [a; b]');
          writeln('* ������� ��������� ������ � ��������� [0; b]');
          writeln('  ������� ������������� ������');
          writeln('  ������� �������������������� ������');
          write('  ');
        end;
      3:
        begin
          writeln('  ������� ��������� ������ � ��������� [a; b]');
          writeln('  ������� ��������� ������ � ��������� [0; b]');
          writeln('* ������� ������������� ������');
          writeln('  ������� �������������������� ������');
          write('  ');
        end;
      4:
        begin
          writeln('  ������� ��������� ������ � ��������� [a; b]');
          writeln('  ������� ��������� ������ � ��������� [0; b]');
          writeln('  ������� ������������� ������');
          writeln('* ������� �������������������� ������');
          write('  ');
        end;
      5:
        begin
          writeln('  ������� ��������� ������ � ��������� [a; b]');
          writeln('  ������� ��������� ������ � ��������� [0; b]');
          writeln('  ������� ������������� ������');
          writeln('  ������� �������������������� ������');
          write('* ');
        end;
    end;
    writeln('�����');
    sym := readKey;
    if Sym = #0 then Sym := readKey;
    case Sym of
      #40: if q < 5 then inc(q);
      #38: if q > 1 then dec(q);
      #13: 
        begin
          if q <> 5 then begin
            write('������� ������ ������� ->');
            readln(n);
            if n>0 then begin
            p2 := n; p1 := 1;
            ot := false;
            case q of
              1: 
                begin
                  write('������� ������� �������� [a,b]->');
                  readln(q1, q2);
                  for i := 1 to n do a[i] := random(q1, q2);
                end;
              2: 
                begin
                  write('������� ������� �������� ->');
                  readln(q2);
                  for i := 1 to n do a[i] := random(q2);
                end;
              3: for i := 1 to n do a[i] := i;
              4: for i := 1 to n do a[i] := n - i + 1;
            end;
            writeln('������ ������� ������');
            end else writeln('������ �� ������');
            readKey;
          end;
        end;
      #32: Output(a, b, n, p1, p2, ot);
    end;   
  until (q = 5) and (Sym = #13);
end;{�������}

procedure sort1(a: arr; var b: arr; n: integer; p1, p2: integer; var ot: boolean);
var
  t: integer;
  q: integer;
  sym: char;
begin
  q := 1;
  repeat
    ClrScr;
    writeln('    �������� ����� ���������� (������� ������ ���������� ������)');
    case q of
      1:
        begin
          writeln('* ���������� ���������');
          writeln('  ���������� �������');
          writeln('  ������� ����������');
          writeln('  ���������� ���������');
          writeln('  �����');
        end;
      2:
        begin
          writeln('  ���������� ���������');
          writeln('* ���������� �������');
          writeln('  ������� ����������');
          writeln('  ���������� ���������');
          writeln('  �����');
        end;
      3:
        begin
          writeln('  ���������� ���������');
          writeln('  ���������� �������');
          writeln('* ������� ����������');
          writeln('  ���������� ���������');
          writeln('  �����');
        end;
      4:
        begin
          writeln('  ���������� ���������');
          writeln('  ���������� �������');
          writeln('  ������� ����������');
          writeln('* ���������� ���������');
          writeln('  �����');
        end;
      5:
        begin
          writeln('  ���������� ���������');
          writeln('  ���������� �������');
          writeln('  ������� ����������');
          writeln('  ���������� ���������');
          writeln('* �����');
        end;
    end;
    sym := readKey;
    if Sym = #0 then Sym := readKey;
    case Sym of
      #40: if q < 5 then inc(q);
      #38: if q > 1 then dec(q);
      #13: 
        begin
          if q <> 5 then begin
            b := a;
            StartTimer();
            case q of
              1: bubble(b, n);
              2: Sort_Vybor(b, n);
              3: qSort(b, 1, n);
              4: CountingSort(b, n);
            end;
            t := StopTimer();
            ot := true;           
            writeln('����� ���������� ', t, '��');
            sym := ReadKey;
          end;
        end;
      #32: Output(a, b, n, p1, p2, ot);
    end;
  until (q = 5) and (Sym = #13);
end;

procedure menu1();
var
  a, b: arr;
  n, p1, p2, t: integer;
  ot: boolean;
  q: integer;
  sym: char;
begin
  ot := false;
  n := 0;
  q := 1;
  p1 := 1;
  p2 := 0;
  repeat
    ClrScr;
    writeln('    ������ ���������� (������� ������ ���������� ������)');
    case q of
      1: 
        begin
          writeln('* ������ ��������� �������');
          writeln('  ������� ��� ����������');
          writeln('  ������� �������� ������');
          writeln('  �����');
        end;
      2:
        begin
          writeln('  ������ ��������� �������');
          writeln('* ������� ��� ����������');
          writeln('  ������� �������� ������');
          writeln('  �����');
        end;
      3:
        begin
          writeln('  ������ ��������� �������');
          writeln('  ������� ��� ����������');
          writeln('* ������� �������� ������');
          writeln('  �����');
        end;
      4:
        begin
          writeln('  ������ ��������� �������');
          writeln('  ������� ��� ����������');
          writeln('  ������� �������� ������');
          writeln('* �����');
        end;
    end;
    sym := readKey;
    if Sym = #0 then Sym := readKey;
    case Sym of
      #40: if q < 4 then inc(q);
      #38: if q > 1 then dec(q);
      #13: 
        case q of
          1: input(a, b, n, p1, p2, ot);
          2: 
            if (p2 <> 0) then sort1(a, b, n, p1, p2, ot) else 
            begin
              writeln('������ �� ������'); 
              sym := ReadKey;
            end;
          3: 
            begin
              if n > 0 then begin
                write('������� �������� ������ [1;', n, '] ->');
                readln(p1, p2);
                if p1 > p2 then begin
                  t := p1;
                  p1 := p2;
                  p2 := t;
                end;
                if (p2 > n) or (p1 < 1) then begin
                  writeln('������� ����� ���������');
                  p1 := 1;
                  p2 := n;
                end;
              end else writeln('������ �� �����');
              ReadKey;
            end;
        end;
      #32: Output(a, b, n, p1, p2, ot);
    end;
  until (q = 4) and (Sym = #13);
end;

begin
end. 