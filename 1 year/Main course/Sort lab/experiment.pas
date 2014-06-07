unit experiment;

interface

uses
  CRT, sort, time;

procedure expe();

implementation

procedure expe();
var
  a, b: arr;
  t, i, j, n, q, z, q1, q2, size: integer;
begin
  ClrScr;
  write('Введите начальный размер массива ->');
  readln(size);
  write('Введите шаг и количество приращений ->');
  readln(q, n);
  writeln('Выберите вариант заполнения массива');
  writeln('1 - случайным образом');
  writeln('2 - упорядоченный');
  writeln('3 - обратноупорядоченный');
  write('->');
  readln(z);
  if z = 1 then begin
    write('Введите границы значений массива ->');
    readln(q1, q2);
  end;
  
  ClrScr;
  writeln('Размер':10, 'Пузырёк':10, 'Выбором':10, 'Быстрая':10, 'Подсчётом':10);
  for i := 1 to n do 
  begin
    case z of
      1: for j := 1 to size do a[j] := random(q1, q2);
      2: for j := 1 to size do a[j] := j;
      3: for j := 1 to size do a[j] := size - j + 1;
    end;
    write(size:10);
    for j := 1 to 4 do 
    begin
      b := a;
      StartTimer();
      case j of
        1: bubble(b, size);
        2: Sort_Vybor(b, size);
        3: qSort(b, 1, size);
        4: CountingSort(b, size);
      end;
      t := StopTimer(); 
      write(t:8, 'мс');
    end;  
    writeln;
    size := size + q;
  end;
  readKey;
end;

begin
end. 