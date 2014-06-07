unit Sort;

interface

const
  N = 100000;
  Q1 = -100000;
  Q2 = 100000;

type
  arr = array[1..N] of integer;

procedure bubble(var a: arr; n: integer);
procedure qSort(var a: arr; l, t: integer);
procedure CountingSort(var a: arr; n: integer);
procedure Sort_Vybor(var a: arr; n: integer);


implementation

procedure bubble(var a: arr; n: integer);
var
  i, q: integer;
  temp: integer;
begin
  for i := 2 to n do 
  begin
    q := i;
    while (q > 1) and (a[q] < a[q - 1]) do
    begin
      temp := a[q];
      a[q] := a[q - 1];
      a[q - 1] := temp;
      dec(q);
    end;
  end;
end;

function part(var a: arr; l, r: integer): integer;
var
  v, i, j, temp: integer;
begin
  V := a[r];
  I := l - 1;
  j := r;
  repeat
    repeat
      dec(j)
    until (a[j] <= v) or (j = i + 1);
    repeat
      inc(i)
    until (a[i] >= v) or (i = j - 1);
    temp := a[i];
    a[i] := a[j];
    a[j] := temp;
  until i >= j;
  a[j] := a[i];
  a[i] := a[r];
  a[r] := temp;
  part := i;
end;

procedure qSort(var a: arr; l, t: integer);
var
  i: integer;
begin
  if l < t then
  begin
    i := part(a, l, t);
    qSort(a, l, i - 1);
    qSort(a, i + 1, t);
  end;
end;

procedure MinMax(a: arr; n: integer; var min, max: integer);
var
  i: integer;
begin
  min := a[1];
  max := a[1];
  for i := 1 to n do 
  begin
    if a[i] < min then min := a[i]
    else if a[i] > max then max := a[i];
  end;
end;

procedure CountingSort(var a: arr; n: integer);
var
  min, max: integer;
  i, j, k: integer;
  b: array[Q1..Q2] of integer;
begin
  MinMax(a, n, min, max);
  for i := 1 to n do inc(b[a[i]]);
  i := 1;
  for j := min to max do
  begin
    for k := 1 to b[j] do 
    begin
      a[i] := j;
      inc(i);
    end;
  end;
end;

procedure Sort_Vybor(var a: arr; n: integer);
var
  i, m, k, temp: integer; 

begin
  for k := n downto 2 do {k- количество элементов для поиска max } 
  begin
    m := 1; { m - место max } 
    for i := 2 to k do if A[i] > A[m] then m := i; 
    temp := a[m]; 
    a[m] := A[k]; 
    a[k] := temp;
  end;  
end;

begin
end. 