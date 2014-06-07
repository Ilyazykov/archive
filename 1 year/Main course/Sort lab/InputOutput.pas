unit InputOutput;

interface

uses
  CRT, hand, experiment;

procedure menu();

implementation

procedure menu();
var
  q: integer;
  sym: char;
begin
  q := 1;
  repeat
    ClrScr;
    writeln('    Главное меню');
    case q of
      1:
        begin
          writeln('* Сортировать вручную');
          writeln('  Эксперимент');
          writeln('  Выход');
        end;
      2:
        begin
          writeln('  Сортировать вручную');
          writeln('* Эксперимент');
          writeln('  Выход');
        end;
      3:
        begin
          writeln('  Сортировать вручную');
          writeln('  Эксперимент');
          writeln('* Выход');
        end;
    end;
    sym := readKey;
    if Sym = #0 then Sym := readKey;
    case Sym of
      #40: if q < 3 then inc(q);
      #38: if q > 1 then dec(q);
      #13: 
        case q of
          1: menu1();
          2: expe();
        end;
    end;
  until (q = 3) and (Sym = #13);
end;

begin
end. 