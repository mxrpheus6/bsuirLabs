entity add1 is
port(b1,b2: in BIT;
 c1,s1: out BIT);
end add1;

architecture struct of add1 is
begin 
s1<=b1 xor b2;
c1<=b1 and b2;
end struct;
