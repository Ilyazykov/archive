unit time;

interface

var
  ntime: integer;

procedure StartTimer();
function StopTimer(): LongInt;

implementation

procedure StartTimer();
begin
  ntime := Milliseconds;
end;

function StopTimer(): LongInt;
begin
  if ntime > 0 then 
    ntime := Milliseconds - ntime;
  result := ntime;
end;

begin
end. 