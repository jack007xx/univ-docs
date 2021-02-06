program PL3C;
var a[1..5],i,n;
begin
  n := 20;
  i := 12;
  a[1] := n;
  for i := 1 to n do
    write(a[i]);
end.
